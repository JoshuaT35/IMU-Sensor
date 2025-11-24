#include "led-control.h"
#include <Arduino.h>

// initialize LEDS
void initLEDs() {
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
}

// turn on only red pin
void pinRedOnly() {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, HIGH);
}

// turn on only blue pin
void pinBlueOnly() {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, HIGH);
}

// turn on only green pin
void pinGreenOnly() {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, LOW);
}

// turn off all pins
void allPinsOff() {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, HIGH);
}