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

typedef void (*ButtonAction)();

void setup() {
  pinMode(MUTE_PIN, INPUT_PULLUP);
  pinMode(VIDEO_PIN, INPUT_PULLUP);

  Keyboard.begin();
}

void handleButton(int buttonPin, int *lastButtonState, unsigned long *lastDebounceTime, int *buttonState, unsigned long debounceDelay, ButtonAction action) {
  int buttonReading = digitalRead(buttonPin);
  if (buttonReading != *lastButtonState) {
    *lastDebounceTime = millis();
  }

  if ((millis() - *lastDebounceTime) > debounceDelay) {
    if (buttonReading != *buttonState) {
      *buttonState = buttonReading;

      if (*buttonState == LOW) {
        action();
      }
    }
  }

  *lastButtonState = buttonReading;
}

// TOGGLE MUTE (SHIFT + COMMAND + M)
void toggleMute() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('M');
  delay(100);
  Keyboard.releaseAll();
  delay(100);
}

// TOGGLE VIDEO (CONTROL + SHIFT + V)
void toggleVideo() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('V');
  delay(100);
  Keyboard.releaseAll();
  delay(100);
}

void loop() {
  handleButton(MUTE_PIN, &lastMuteButtonState, &lastMuteDebounceTime, &muteButtonState, muteDebounceDelay, toggleMute);
  handleButton(VIDEO_PIN, &lastVideoButtonState, &lastVideoDebounceTime, &videoButtonState, videoDebounceDelay, toggleVideo);
}

