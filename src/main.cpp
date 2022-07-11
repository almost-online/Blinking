#include <ESP8266WiFi.h>
#include "Arduino.h"

#define LED_BUILDIN 2

const char *ssid = "*******";
const char *password = "**********";

bool pin_status = false;

void switch_pin() {
    digitalWrite(LED_BUILDIN, pin_status ? LOW : HIGH);
    pin_status = !pin_status;
}

void blinkin(int times = 1, int dlay=100) {
    for (int i = 0; i < times; i++) {
        switch_pin();
        delay(dlay);
        switch_pin();
        delay(dlay);
    }
}

void setup() {
    pinMode(LED_BUILDIN, OUTPUT);
    switch_pin();

    Serial.begin(115200);
    Serial.println();
    Serial.print("Wifi connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);


    Serial.println();
    Serial.print("Connecting");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        switch_pin();
    }

    if (!pin_status) {
        switch_pin();
    }


    // blinkin when connected
    blinkin(4);
    // 
    digitalWrite(LED_BUILDIN, HIGH);
    Serial.println();
    Serial.println("Wifi Connected Success!");
    Serial.print("NodeMCU IP Address : ");
    Serial.println(WiFi.localIP());
}

void loop() {
    static int lastms = 0;

    if (WiFi.status() == WL_CONNECTED) {
        if (millis()-lastms > 100000) {
        lastms = millis();
        Serial.printf("Running for %d ms...\n", lastms);
        Serial.flush();
        blinkin(3, 50);
        }
        delay(20000);
    } else {
        blinkin(4);
    }
}
