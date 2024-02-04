#include <Keyboard.h>

#define MUTE_PIN  2   // pin_d1
#define VIDEO_PIN 3   // pin_d2

int muteButtonState = HIGH;          // current state of the mute button
int lastMuteButtonState = HIGH;      // previous state of the mute button
unsigned long lastMuteDebounceTime = 0;  // last time the mute button state was toggled
unsigned long muteDebounceDelay = 50;  // debounce time in milliseconds

int videoButtonState = HIGH;          // current state of the video button
int lastVideoButtonState = HIGH;      // previous state of the video button
unsigned long lastVideoDebounceTime = 0;  // last time the video button state was toggled
unsigned long videoDebounceDelay = 50;  // debounce time in milliseconds

void setup() {
  pinMode(MUTE_PIN, INPUT_PULLUP);
  pinMode(VIDEO_PIN, INPUT_PULLUP);

  Keyboard.begin();
}

void loop() {
  // TOGGLE MUTE (SHIFT + COMMAND + M)
  int muteReading = digitalRead(MUTE_PIN);
  if (muteReading != lastMuteButtonState) {
    lastMuteDebounceTime = millis();
  }

  if ((millis() - lastMuteDebounceTime) > muteDebounceDelay) {
    if (muteReading != muteButtonState) {
      muteButtonState = muteReading;

      if (muteButtonState == LOW) {
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press('M');
        releaseKeys();
      }
    }
  }

  lastMuteButtonState = muteReading;

  // TOGGLE VIDEO (CONTROL + SHIFT + V)
  int videoReading = digitalRead(VIDEO_PIN);
  if (videoReading != lastVideoButtonState) {
    lastVideoDebounceTime = millis();
  }

  if ((millis() - lastVideoDebounceTime) > videoDebounceDelay) {
    if (videoReading != videoButtonState) {
      videoButtonState = videoReading;

      if (videoButtonState == LOW) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press('V');
        releaseKeys();
      }
    }
  }

  lastVideoButtonState = videoReading;
}

void releaseKeys() {
  delay(100);
  Keyboard.releaseAll();
  delay(100);
}
