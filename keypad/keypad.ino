/*  Keypadtest.pde
 *
 *  Demonstrate the simplest use of the  keypad library.
 *
 *  The first step is to connect your keypad to the
 *  Arduino  using the pin numbers listed below in
 *  rowPins[] and colPins[]. If you want to use different
 *  pins then  you  can  change  the  numbers below to
 *  match your setup.
 *
 */
#include "Arduino.h"
#include <avr/pgmspace.h>
#include <Keypad.h>
#include "Keyboard.h"
#include "ext_def.h"

#define ROWS 4
#define COLS 4
#define SETS 4
#define PGM_BUFFER_LENGTH 255
#define INPUT_BUFFER_LENGTH 50

// Uncomment this if using a Leonardo
//#define Leonardo

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 5, 4, 3, 2 };
// Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins.
byte colPins[COLS] = { 9, 8, 7, 6 };

// Connect LEDs LED0, LED1, LED2 and LED3 to these Arduino pins.
#ifdef Leonardo
byte setLeds[SETS] = { 10, 11, 12, 13 }; // Leonardo
#else
byte setLeds[SETS] = { 10, 16, 14, 15 }; // Pro Micro
#endif

char password[] = PIN;
char pwBuffer[INPUT_BUFFER_LENGTH];

byte activeSet = 0;
bool authenticated = false;
byte charCount = 0;
boolean debug = false;

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {

  // Set LED pins as output
  for (byte i=0; i<SETS; i++) {
    pinMode(setLeds[i], OUTPUT);
  }

  // Light first LED
  digitalWrite(setLeds[0], HIGH);

  if (debug) {

    // Start serial communication
    Serial.begin(9600);

    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB
    }
  }

  // Light second LED
  digitalWrite(setLeds[1], HIGH);

  // Start USB keyboard
  Keyboard.begin();

  // Light third LED
  digitalWrite(setLeds[2], HIGH);

  if (debug) Serial.println("Setup complete");

  // Light fourth LED
  digitalWrite(setLeds[3], HIGH);
}

void loop() {

  char key = kpd.getKey();

  if (key) {

    if (authenticated) {
      passwordAction(key);
    } else {
      authenticateAction(key);
    }
  }
}

void authenticateAction(char key) {

  // Debug
  if (debug) {
    Serial.print("Auth: ");
    Serial.println(key);
  }

  switch (key) {

    case '*' :
      clearPwBuffer();
      blinkCleared();
    break;

    case '#' :
      if (checkPin()) pinOK(); else pinFailed();
    break;

    default :

      if (charCount < INPUT_BUFFER_LENGTH) {

        pwBuffer[charCount] = key;
        charCount++;

        if (charCount > 0) {
          // Set leds to status "typing"
          blinkTyping();
      
        } else {
          // Set leds to status "cleared"
          blinkCleared();
        }

      } else {

        pinFailed();
      }

    break;
  }
}

bool checkPin() {
  return !strcmp(pwBuffer, password);
}

void pinOK() {
  authenticated = true;
  blinkSuccess();
  selectSet(0);
  if (debug) Serial.println(F("Authenticate Success"));
}

void pinFailed() {
  authenticated = false;
  blinkError();
  clearPwBuffer();
  blinkCleared();
  if (debug) Serial.println(F("Authenticate Failed"));
}

void passwordAction(char key) {

  if (debug) {
    Serial.print("PWD: ");
    Serial.println(key);
  }

  switch (key) {

    case 'A':
      selectSet(0);
    break;

    case 'B':
      selectSet(1);
    break;

    case 'C':
      selectSet(2);
    break;

    case 'D':
      selectSet(3);
    break;

    case '*':
      // Sperren
      clearPwBuffer();
      authenticated = false;
      blinkCleared();
    break;

    case '#':
    break;

    default :
      keypressed(key);
  }
}

void selectSet(byte selected) {

  ledsAllOff();
  digitalWrite(setLeds[selected], HIGH);
  activeSet = selected;
}

void keypressed(byte key) {

  if (activeSet == 0) {
    
    switch (key) {

      case '0' :
        print(values0_0);
      break;

      case '1' :
        print(values0_1);
      break;

      case '2' :
        print(values0_2);
      break;

      case '3' :
        print(values0_3);
      break;

      case '4' :
        print(values0_4);
      break;

      case '5' :
        print(values0_5);
      break;

      case '6' :
        print(values0_6);
      break;

      case '7' :
        print(values0_7);
      break;

      case '8' :
        print(values0_8);
      break;

      case '9' :
        print(values0_9);
      break;
    }
    
  } else if (activeSet == 1) {

    switch (key) {

      case '0' :
        print(values1_0);
      break;

      case '1' :
        print(values1_1);
      break;

      case '2' :
        print(values1_2);
      break;

      case '3' :
        print(values1_3);
      break;

      case '4' :
        print(values1_4);
      break;

      case '5' :
        print(values1_5);
      break;

      case '6' :
        print(values1_6);
      break;

      case '7' :
        print(values1_7);
      break;

      case '8' :
        print(values1_8);
      break;

      case '9' :
        print(values1_9);
      break;
    }

  } else if (activeSet == 2) {

    switch (key) {

      case '0' :
        print(values2_0);
      break;

      case '1' :
        print(values2_1);
      break;

      case '2' :
        print(values2_2);
      break;

      case '3' :
        print(values2_3);
      break;

      case '4' :
        print(values2_4);
      break;

      case '5' :
        print(values2_5);
      break;

      case '6' :
        print(values2_6);
      break;

      case '7' :
        print(values2_7);
      break;

      case '8' :
        print(values2_8);
      break;

      case '9' :
        print(values2_9);
      break;
    }

  } else if (activeSet == 3) {

    switch (key) {

      case '0' :
        print(values3_0);
      break;

      case '1' :
        print(values3_1);
      break;

      case '2' :
        print(values3_2);
      break;

      case '3' :
        print(values3_3);
      break;

      case '4' :
        print(values3_4);
      break;

      case '5' :
        print(values3_5);
      break;

      case '6' :
        print(values3_6);
      break;

      case '7' :
        print(values3_7);
      break;

      case '8' :
        print(values3_8);
      break;

      case '9' :
        print(values3_9);
      break;
    }
  }
}

void print(char* var) {

  char lastModifier = NULL;

  for (int i = 0; i < PGM_BUFFER_LENGTH; i++) {

    unsigned char myChar = pgm_read_byte_near(var + i);

    if (myChar == 0x00)
      break;

    if (myChar == 0x86) {

      lastModifier = myChar;
      Keyboard.press(myChar);

    } else {
    
      myChar = translate(myChar);
      Keyboard.write(myChar);

      if (lastModifier != NULL) {
        Keyboard.release(lastModifier);
        lastModifier = NULL;
      }
    }
  }
}

char translate(char theChar) {

  switch (theChar) {

    case 0x7A : // z
      theChar = 0x79; // y
    break;

    case 0x79 : // y
      theChar = 0x7A; // z
    break;

    case 0x59 : // Y
      theChar = 0x5A; // Z
    break;

    case 0x5A : // Z
      theChar = 0x59; // Y
    break;

    case 0x2D : // ß
      theChar = 0x2F; // -
    break;
  }

  return theChar;
}

void blinkTyping() {

  for (byte i=0; i<SETS; i++) {
    digitalWrite(setLeds[i], LOW);
  }

  digitalWrite(setLeds[1], HIGH);
  digitalWrite(setLeds[3], HIGH);
}

void blinkCleared() {

  for (byte i=0; i<SETS; i++) {
    digitalWrite(setLeds[i], LOW);
  }

  digitalWrite(setLeds[2], HIGH);
  digitalWrite(setLeds[3], HIGH);
}

/** Blink code for error message. Flashes all leds two times
  */
void blinkError() {

  ledsAllOff();
  delay(500);

  for (byte i=0; i<3; i++) {
    ledsAllOn();
    delay(250);
    ledsAllOff();
    delay(250);
  }
}

/** Blink code for success. Turns of one led per second until all off and then turns the first on
 */
void blinkSuccess() {

  ledsAllOff();
  delay(500);
  ledsAllOn();
  delay(500);
  ledsAllOff();
  delay(500);
}

void ledsAllOff() {

  for (byte i=0; i<SETS; i++) {
    digitalWrite(setLeds[i], LOW);
  }
}

void ledsAllOn() {

  for (byte i=0; i<SETS; i++) {
    digitalWrite(setLeds[i], HIGH);
  }
}

/** Clear password input buffer
 */
void clearPwBuffer() {

  charCount = 0;
  for (int i=0; i<INPUT_BUFFER_LENGTH; i++) {
    pwBuffer[i] = 0;
  }
}
