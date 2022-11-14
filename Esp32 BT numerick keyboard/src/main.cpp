#include <Arduino.h>
/*******************************************************************
 *  A simple Macro keyboard built with an ESP32 and a        
 *  4*4 Button Matrix.
 *  
 *  I use a TinyPICO ESP32 for this project, but you could
 *  use any ESP32, just adjust the row and col pins if
 *  required.
 *  
 *  Parts:
 *  TinyPICO ESP32 - https://www.tinypico.com/
 *  4*4 Keypad Button Matrix* - http://s.click.aliexpress.com/e/CqnjTgGg 
 *  
 *  * = Affilate
 *  
 *  If you find what I do useful and would like to support me,
 *  please consider becoming a sponsor on Github
 *  https://github.com/sponsors/witnessmenow/
 *                                                                 
 *  Written by Brian Lough
 *  YouTube: https://www.youtube.com/brianlough
 *  Tindie: https://www.tindie.com/stores/brianlough/
 *  Twitter: https://twitter.com/witnessmenow                                 
 *******************************************************************/

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <BleKeyboard.h>
// This library is for using BLE HID with your ESP32
// 
// This is not availble on the library manager so
// needs to be installed from Github
// https://github.com/T-vK/ESP32-BLE-Keyboard

#include <Keypad.h>
// This library is for interfacing with the 4x4 Matrix
// 
// Can be installed from the library manager, search for "keypad"
// and install the one by Mark Stanley and Alexander Brevig
// https://playground.arduino.cc/Code/Keypad/

// the library will return the character inside this array
// when the appropriate button is pressed.
#define ROW_NUM     4 // four rows
#define COLUMN_NUM  3 // three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pin_rows[ROW_NUM] = {18, 5, 17, 16}; // GIOP18, GIOP5, GIOP17, GIOP16 connect to the row pins
byte pin_column[COLUMN_NUM] = {4, 2, 15};  // GIOP4, GIOP0, GIOP2 connect to the column pins

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

// First param is name
// Second is manufacturer
// Third is initial batter level
BleKeyboard bleKeyboard("BLE_Fbellsan", "BLough", 100);

void setup() {
  Serial.begin(9600);
  bleKeyboard.begin();
}

// This will hold down all the following buttons.
void sendMacroCommand(uint8_t key) {
  //bleKeyboard.press(KEY_LEFT_CTRL);
  //bleKeyboard.press(KEY_LEFT_SHIFT);
  //bleKeyboard.press(KEY_LEFT_ALT);
  bleKeyboard.press(key);
}

void loop() {
  char key = keypad.getKey();

  // Only do something with the keypress if we
  // are connected to something via bluetooth
  
  if (bleKeyboard.isConnected() && key) {
    Serial.println(key);
    switch (key) {
      case '1':
        sendMacroCommand(KEY_NUM_1);
        break;
      case '2':
        sendMacroCommand(KEY_NUM_2);
        break;
      case '3':
        sendMacroCommand(KEY_NUM_3);
        break;
      case '4':
        sendMacroCommand(KEY_NUM_4);
        break;
      case '5':
        sendMacroCommand(KEY_NUM_5);
        break;
      case '6':
        sendMacroCommand(KEY_NUM_6);
        break;
      case '7':
        sendMacroCommand(KEY_NUM_7);
        break;
      case '8':
        sendMacroCommand(KEY_NUM_8);
        break;
      case '9':
        sendMacroCommand(KEY_NUM_9);
        break;
      case '0':
        sendMacroCommand(KEY_NUM_0);
        break;
      case '*':
        sendMacroCommand(KEY_F11);
        break;
      case '#':
        sendMacroCommand(KEY_F12);
        break;
      case 'A':
        sendMacroCommand('a');
        break;
      case 'B':
        sendMacroCommand('b');
        break;
      case 'C':
        sendMacroCommand('c');
        break;
      case 'D':
        sendMacroCommand('d');
        break;
    }

    delay(100);
    bleKeyboard.releaseAll(); // this releases the buttons
  }
}