/*
 * Digispark Touchless Presenter
 * LED    status LED
 * LED2   sense LED
 * SENSOR GP2Y0A21YK
 */
#include "DigiKeyboard.h"

#define LED 1     // P1
#define LED2 0    // P0 (onBoard)
#define SENSOR  1 // P2

#define THRESHOLD 500
#define HYSTERESIS 1500
#define WAIT 500

#define PUSHKEY  0x4F  // Right Arrow

void setup() {

  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(SENSOR, INPUT);

  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);

}

void loop() {

  static int sense = 0;
  static int hyst = 0;
  static bool sent = false;
  static bool ind = HIGH;

  sense = analogRead(SENSOR);

  if (sense > THRESHOLD) {
    // Hand on sensor
    digitalWrite(LED2, HIGH);
    if (hyst >= HYSTERESIS) {
      if (sent == false) {
        DigiKeyboard.sendKeyStroke(0);
        DigiKeyboard.sendKeyStroke(PUSHKEY);
        sent = true;
      }
    } else {
      hyst += WAIT;
    }
  } else {
    hyst = 0;
    sent = false;
    digitalWrite(LED2, LOW);
  }

  digitalWrite(LED, ind);
  ind = not ind;

  DigiKeyboard.delay(WAIT);

}
