#ifndef NOT_DEFINED
#include <Arduino.h>
#else
#include <Arduino_dummy.h>
#endif // NOT_DEFINED

#include "loop.h"
void Loop::setup() {
    pinMode(MY_LED, OUTPUT);
}

void Loop::loop() {
    Serial.println("Going high...");
    digitalWrite(MY_LED, HIGH);
    delay(1000);
    Serial.println("Going low...");
    digitalWrite(MY_LED, LOW);
    delay(1000);
}