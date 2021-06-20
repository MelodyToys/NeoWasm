#include <ArduinoJson.h>
#ifdef ESP32
#include <FS.h>
#include <SPIFFS.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESP8266mDNS.h>
#endif
#include <ESPAsyncWebServer.h>
#include <wasm3.h>
#include "m3_neowasm.h"
#include <Adafruit_NeoPixel.h>

#define WASM_STACK_SLOTS 2 * 1024
#define NATIVE_STACK_SIZE 32 * 1024

#define DEBUG     0
#define NEOWASM_VER "1.0-PRE"

struct Config {
	int  vm_alloc;
	int  led_pin;
	int  led_count;
	char wifi_sta_ssid[64];
	char wifi_sta_pass[64];
	char wifi_ap_ssid[64];
	char wifi_ap_pass[64];
	char hostName[64];
	char http_username[64];
	char http_password[64];
};

Config  config;
bool    vm_init = false;
String  spiffs_pwd  = "";
bool    spiffs_init = false;

IM3Environment	m3_env;
IM3Runtime		m3_runtime;
IM3Module		m3_module;
IM3Function		m3_setup;
IM3Function		m3_loop;

Adafruit_NeoPixel strip(10, 10, NEO_GRB + NEO_KHZ800); // FIXME: Hack ~ set to anything ... then redefine in setup()

AsyncWebServer server(80);

uint8_t wheelR(uint8_t Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return 255 - Pos * 3; }
  if(Pos < 170) { return 0; }
  Pos -= 170;
  return Pos * 3;
}

uint8_t wheelG(uint8_t Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return 0; }
  if(Pos < 170) { Pos -= 85; return Pos * 3; }
  Pos -= 170;
  return 255 - Pos * 3;
}

uint8_t wheelB(uint8_t Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return Pos * 3; }
  if(Pos < 170) { Pos -= 85; return 255 - Pos * 3; }
  return 0;
}

uint32_t wheel(uint8_t Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) {
    return strip.Color(255 - Pos * 3, 0, Pos * 3);
  }
  if(Pos < 170) {
    Pos -= 85;
    return strip.Color(0, Pos * 3, 255 - Pos * 3);
  }
  Pos -= 170;
  return strip.Color(Pos * 3, 255 - Pos * 3, 0);
}

void wasmInit(void *) {
	M3Result result = m3Err_none;

	m3_env = m3_NewEnvironment();
	if(!m3_env) {
		Serial.println("NewEnvironment: failed");
		return;
	}

	m3_runtime = m3_NewRuntime(m3_env, WASM_STACK_SLOTS, NULL);
	if(!m3_runtime) {
		Serial.println("NewRuntime: failed");
		return;
	}

	if(spiffs_init) {
	  
		size_t wasm_size = m3_readWasmSize("/init.wasm");
		if(wasm_size == 0) {
			Serial.println("ReadWasm: File not found");
			return;
		}
		uint8_t buffer[wasm_size];
		size_t read_bytes = m3_readWasm("/init.wasm", buffer);
		if(read_bytes == 0) {
			Serial.println("ReadWasm: File not found")
			return;
		}
		
		result = m3_ParseModule(m3_env, &m3_module, buffer, wasm_size);
		if(result) {
			Serial.print("ParseModule: ");
			Serial.println(result);
			return;
		}
	
		result = m3_LoadModule(m3_runtime, m3_module);
		if(result) {
			Serial.print("LoadModule: ";
			Serial.println(result);
			return;
		}

		result = m3_LinkArduino(m3_runtime);
		if(result) {
			Serial.print("LinkArduino: ");
			Serial.println(result);
			return;
		}

		result = m3_FindFunction(&m3_setup, m3_runtime, "setup");
		if(result) {
			Serial.print("FindFunction setup: ");
			Serial.println(result);
			//return; // stricked 
		}
  
		result = m3_FindFunction(&m3_loop, m3_runtime, "loop");
		if(result) {
			Serial.print("FindFunction loop: ");
			Serial.println(result);
			return; // stricked
		} else {
			vm_init = true;
			Serial.println("WebAssembly VM Running...\n");
		}
		
		result = m3_CallV(m3_setup);

		if(result) {
			M3ErrorInfo info;
			m3_GetErrorInfo(m3_runtime, &info);
			Serial.print("Error: ");
			Serial.print(result);
			Serial.print(" (");
			Serial.print(info.message);
			Serial.println(")");
			// vm_init = false; // stricked
		}
    } else {
      if(DEBUG) { Serial.println(F("/init.wasm failed")); }
      vm_init = false;
    }
}

void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
{
  if (!filename.endsWith(".wasm"))
  {
    request->send(400, "text/plain", "Only wasm files accepted");
    return;
  }
  if (!index)
  {
    Serial.printf("UploadStart: %s\n", filename.c_str());
    request->_tempFile = SPIFFS.open("/init.wasm", "w");
  }
  if (len)
  {
    request->_tempFile.write(data, len);
  }
  //Serial.printf("%s", (const char *)data);
  if (final)
  {
    request->_tempFile.close();
    Serial.printf("UploadEnd: %s (%u)\n", filename.c_str(), index + len);
    request->send(200, "text/plain", "Uploaded");
    delay(1000);
    ESP.restart();
  }
}

bool loadConfig(Config &config) {
  if(spiffs_init) {
    File configFile = SPIFFS.open("/config.json", "r");
    if (!configFile) {
      if(DEBUG) { Serial.println(F("Failed to open config file")); }
    }
    size_t size = configFile.size();
    if (size > 1024) {
      if(DEBUG) { Serial.println(F("Config file size is too large")); }
    }
    StaticJsonBuffer<512> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(configFile);
    configFile.close();
    config.led_pin = root["led_pin"] | 4;
    config.led_count = root["led_count"] | 8;
    config.elk_alloc = root["vm_alloc"] | 4096;
    strlcpy(config.wifi_sta_ssid, root["wifi_sta_ssid"] | "", sizeof(config.wifi_sta_ssid));
    strlcpy(config.wifi_sta_pass, root["wifi_sta_pass"] | "", sizeof(config.wifi_sta_pass));
    strlcpy(config.wifi_ap_ssid, root["wifi_ap_ssid"] | "", sizeof(config.wifi_ap_ssid));
    strlcpy(config.wifi_ap_pass, root["wifi_ap_pass"] | "", sizeof(config.wifi_ap_pass));
    strlcpy(config.hostName, root["hostName"] | "NeoWasm", sizeof(config.hostName));
    strlcpy(config.http_username, root["http_username"] | "", sizeof(config.http_username));
    strlcpy(config.http_password, root["http_password"] | "", sizeof(config.http_password));
    if (!root.success()) {
      if(DEBUG) { Serial.println(F("Failed to read file, using default configuration")); }
      return false;
    }
  } else {
    if(DEBUG) { Serial.println(F("Failed to read file, using default configuration")); }
    config.led_pin = 4;
    config.led_count = 8;
    config.elk_alloc = 4096;
    strlcpy(config.wifi_sta_ssid, "", sizeof(config.wifi_sta_ssid));
    strlcpy(config.wifi_sta_pass, "", sizeof(config.wifi_sta_pass));
    strlcpy(config.wifi_ap_ssid, "", sizeof(config.wifi_ap_ssid));
    strlcpy(config.wifi_ap_pass, "", sizeof(config.wifi_ap_pass));
    strlcpy(config.hostName, "NeoWasm", sizeof(config.hostName));
    strlcpy(config.http_username, "", sizeof(config.http_username));
    strlcpy(config.http_password, "", sizeof(config.http_password));
    return false;
  }
  return true;
}

bool saveConfiguration(Config &config) {
  if(spiffs_init) {
    SPIFFS.remove("/config.json");
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      if(DEBUG) { Serial.println(F("Failed to create Config file")); }
      return false;
    }
    StaticJsonBuffer<256> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["led_pin"] = config.led_pin;
    root["led_count"] = config.led_count;
    root["vm_alloc"] = config.vm_alloc;
    root["wifi_sta_ssid"] = config.wifi_sta_ssid;
    root["wifi_sta_pass"] = config.wifi_sta_pass;
    root["wifi_ap_ssid"] = config.wifi_ap_ssid; 
    root["wifi_ap_pass"] = config.wifi_ap_pass;
    root["hostname"] = config.hostName;
    root["http_username"] = config.http_username;
    root["http_password"] = config.http_password;
    if (root.printTo(configFile) == 0) {
      if(DEBUG) { Serial.println(F("Failed to write to Config file")); }
      return false;
    }
    configFile.close();
    if(DEBUG) { Serial.println(F("Config File write complete")); }
    return true;
  }
}

void setup()
{
  WiFi.persistent(false); // do not use SDK wifi settings in flash ?
    
  Serial.begin(115200);
  Serial.setDebugOutput(false); // do not use wifi debug to console
  Serial.println("");

  if(!SPIFFS.begin()) {
    if(DEBUG) { Serial.println(F("SPIFFS Initialization ... failed")); }
  } else { 
    if(DEBUG) { Serial.println(F("\nSPIFFS Initialize....ok")); }
    spiffs_init = true;
  }
  
  if(!loadConfig(config)) {
    if(DEBUG) { Serial.println(F("Config Initialization ... failed")); }
  } else { if(DEBUG) { Serial.println(F("Config Initialize....ok")); }}

  strip.updateLength(config.led_count);
  strip.setPin(config.led_pin);
  strip.begin();
  strip.show();
  strip.setBrightness(50);

  wasmInit();  

  WiFi.hostname(config.hostName);
  WiFi.mode(WIFI_AP_STA);
  if((String(config.wifi_ap_pass) != "") && (String(config.wifi_ap_ssid) != "")) // make sure ssid is set too?
    WiFi.softAP(config.wifi_ap_ssid, config.wifi_ap_pass);
  else
    if(String(config.wifi_ap_ssid) != "")
      WiFi.softAP(config.wifi_ap_ssid);
    else
      WiFi.softAP(config.hostName); // always start an AP ...
    
  if(String(config.wifi_sta_ssid != "")) {
    if(String(config.wifi_sta_pass != ""))
      WiFi.begin(config.wifi_sta_ssid, config.wifi_sta_pass);
    else
      WiFi.begin(config.wifi_sta_ssid);
  }

  MDNS.begin(config.hostName);
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request){request->send(200, "text/plain", String(ESP.getFreeHeap()));});
  server.on("/upload", HTTP_POST, [](AsyncWebServerRequest *request) {}, handleUpload);
  server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request) {
    String json = "[";
   
    int n = WiFi.scanComplete();
    if(n == -2){

    #ifdef ESP32
      WiFi.scanNetworks(true, true);
    #elif defined(ESP8266) 
      WiFi.scanNetworks(true);
    #endif

    } else if(n){
      for(int i = 0; i < n; ++i){
        if(i) json += ",";
        json += "{";
        json += "\"rssi\":"+String(WiFi.RSSI(i));
        json += ",\"ssid\":\""+WiFi.SSID(i)+"\"";
        json += ",\"bssid\":\""+WiFi.BSSIDstr(i)+"\"";
        json += ",\"channel\":"+String(WiFi.channel(i));
        json += ",\"secure\":"+String(WiFi.encryptionType(i));
    #ifdef ESP8266
        json += ",\"hidden\":"+String(WiFi.isHidden(i)?"true":"false");
    #endif
        json += "}";
      }
      WiFi.scanDelete();
      if(WiFi.scanComplete() == -2){
        WiFi.scanNetworks(true);
      }
    }
    json += "]";
    request->send(200, "application/json", json);
    json = String();}
  );
  server.onNotFound([](AsyncWebServerRequest *request) {
    int headers = request->headers();
    int i;
    for(i=0;i<headers;i++){
      AsyncWebHeader* h = request->getHeader(i);
    }
    int params = request->params();
    for(i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
    }
    request->send(404);}
  );
  server.onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){});
  server.begin();
  MDNS.addService("ota", "http", "tcp", 80);

}

void loop() {
	if(vm_init)
		M3Result result = m3_CallV(m3_loop);
		if(result) {
			M3ErrorInfo info;
			m3_GetErrorInfo(m3_runtime, &info);
			Serial.print("Error: ");
			Serial.print(result);
			Serial.print(" (");
			Serial.print(info.message);
			Serial.println(")");
			vm_init = false; // stricked
		}
	}
	delay(0);
}
