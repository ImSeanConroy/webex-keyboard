#include <Keyboard.h>

#define MUTE_PIN  2   // pin_d1
#define VIDEO_PIN 3   // pin_d2

void setup() {
  pinMode(MUTE_PIN, INPUT_PULLUP);
  pinMode(VIDEO_PIN, INPUT_PULLUP);

  Keyboard.begin();
}

void loop() {
  // TOGGLE MUTE (SHIFT + COMMAND + M)
  if (digitalRead(MUTE_PIN) == LOW){ 
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('M');
    releaseKeys();
  } 
    
  // TOGGLE VIDEO (CONTROL + SHIFT + V)
  else if (digitalRead(VIDEO_PIN) == LOW){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('V');
    releaseKeys();
  }
}

void releaseKeys() {
  delay(500);
  Keyboard.releaseAll();
  delay(500);
}