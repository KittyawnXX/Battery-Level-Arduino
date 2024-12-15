// Code made with luv by Kittyawn 💙 aka. Alvian
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define NUM_LEDS 10
const int ledPins[NUM_LEDS] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LEDLOW 2
#define LEDHIGH 3

float tegangan = 0.0;
int persen = 0;
unsigned long lastBlinkTime = 0;
bool ledLowState = false;

void setup() {
    lcd.begin(16, 2);
    lcd.backlight();

    for (int i = 0; i < NUM_LEDS; i++) {
        pinMode(ledPins[i], OUTPUT);
    }

    pinMode(LEDLOW, OUTPUT);
    pinMode(LEDHIGH, OUTPUT);

    digitalWrite(LEDLOW, HIGH);
}

void loop() {
    unsigned long currentTime = millis();

    if (currentTime - lastBlinkTime >= 1000) {
        lastBlinkTime = currentTime;
        ledLowState = !ledLowState;
        digitalWrite(LEDLOW, ledLowState ? HIGH : LOW);
    }

    int nilaiAnalog = analogRead(A0);
    tegangan = nilaiAnalog * 5.0 / 1023.0;
    persen = (tegangan / 5.0) * 100;

    lcd.setCursor(0, 0);
    lcd.print("POWER: ");
    lcd.print(tegangan, 2);
    lcd.print("V ");

    lcd.setCursor(0, 1);
    if (persen == 0) {
        lcd.print("LOW BATTERY    ");
    } else if (persen >= 100) {
        lcd.print("FULL BATTERY   ");
    } else {
        lcd.print(persen);
        lcd.print("%           ");
    }

    int aktifLed = map(nilaiAnalog, 0, 1023, 0, NUM_LEDS);
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i < aktifLed) {
            digitalWrite(ledPins[i], HIGH);
        } else {
            digitalWrite(ledPins[i], LOW);
        }
    }

    if (persen >= 100) {
        digitalWrite(LEDLOW, LOW);
        digitalWrite(LEDHIGH, HIGH);
    } else {
        digitalWrite(LEDHIGH, LOW);
    }
}
