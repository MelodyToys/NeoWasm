#![no_std]

mod arduino;
use arduino::*;

struct App {
    led: u32,
}

impl App {
    fn new() -> Self {
        println("Rust is running 😎");

        let led = getPinLED();
        pinMode(led, OUTPUT);
        Self { led }
    }

    fn run(&self) {
        digitalWrite(self.led, HIGH);
        delay(100);
        digitalWrite(self.led, LOW);
        delay(900);
    }
}

#[no_mangle]
pub extern fn _start() {
    let app = App::new();
    loop {
        app.run()
    }
}
