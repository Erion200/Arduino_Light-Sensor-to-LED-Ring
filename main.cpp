#include <Adafruit_NeoPixel.h>

int ldrpin = A5;
int limit = 512;
#define PIN 4
#define NUMPIXELS 12
Adafruit_NeoPixel modul_led_ring = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int red = 12;
int green = 10;

void setup(){
  Serial.begin(9600);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

  modul_led_ring.begin();
  
  pinMode(button_pin, INPUT_PULLUP);
}

void loop() {  
  messuring();
  modul_led_ring.show();
}

//all Colors in an Array
uint32_t colors[12] = {
  modul_led_ring.Color(255,72,0),
  modul_led_ring.Color(255,132,0),
  modul_led_ring.Color(252,255,0),
  modul_led_ring.Color(99,255,0),
  modul_led_ring.Color(0,255,157),
  modul_led_ring.Color(0,154,255),
  modul_led_ring.Color(0,1,255),
  modul_led_ring.Color(114,0,143),
  modul_led_ring.Color(255,0,243),
  modul_led_ring.Color(255,0,155),
  modul_led_ring.Color(247,158,158),
  modul_led_ring.Color(255,255,255)
};

void messung() {
  int vldr = analogRead(ldrpin);
  Serial.print("V= ");
  Serial.println(vldr);

  // Red/green logik
  if (vldr <= limit) {
    digitalWrite(Gruen, LOW);
    digitalWrite(Rot, HIGH);
  } else {
    digitalWrite(Gruen, HIGH);
    digitalWrite(Rot, LOW);
  }

  //produodecim
  int activeLEDs = constrain(vldr / 70, 1, 12);

  //set all LEDs in a loop
  for (int i = 0; i < 12; i++) {
    uint32_t color = (i < activeLEDs) ? colors[i] : modul_led_ring.Color(0, 0, 0);
    modul_led_ring.setPixelColor(i, color);
  }

  modul_led_ring.show();
}
