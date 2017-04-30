#include "pitches.h"
#include <Adafruit_CharacterOLED.h>
#include "Adafruit_Thermal.h"
#include "alto_clef.h"
#include "notes.h"
#include "SoftwareSerial.h"
#define TX_PIN 5 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 4 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

/*------- Hardware configuration -------*/
const int LED_LEFT = 34;
const int SWITCH_PIN_LEFT = 30;    
const int LED_RIGHT = 28;
const int SWITCH_PIN_RIGHT = 32; 

const int TONE_PIN = 3;
const int potPin1 = A0;

const int NOTE_DURATION = 100;

int right_switch_reading;
int left_switch_reading;

Adafruit_CharacterOLED lcd(OLED_V2, 6, 7, 8, 9, 10, 11, 12);


  
/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */
void setup() {
  // establish direction of pins we are using for LEDs 
  pinMode(LED_LEFT, OUTPUT); 
  pinMode(LED_RIGHT, OUTPUT); 
  pinMode(SWITCH_PIN_LEFT, INPUT);
  pinMode(SWITCH_PIN_RIGHT, INPUT);

  // Print a message to the LCD.
  lcd.begin(16, 2);
  lcd.print(" MUSIC PRINTER >");

  // printer set up 
  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)

  //printer.printBitmap(notes_width, notes_height, notes_data);
  printer.printBitmap(alto_clef_width, alto_clef_height, alto_clef_data);
}


/* Main routine (called repeated by from the Arduino framework) */
void loop() {

    lcd.setCursor(0,1); // Sets the cursor to col 0 and row 0
    lcd.print("SensorVal1: "); // Prints Sensor Val: to LCD
    lcd.print(analogRead(potPin1)); // Prints value on Potpin1 to LCD
  
    right_switch_reading = digitalRead(SWITCH_PIN_RIGHT);

    if (right_switch_reading == LOW) {
       digitalWrite(LED_RIGHT, HIGH);
       
    } else {
       digitalWrite(LED_RIGHT, LOW);
       tone(3, NOTE_A3, NOTE_DURATION);
    }

    left_switch_reading = digitalRead(SWITCH_PIN_LEFT);

    if (left_switch_reading == LOW) {
       digitalWrite(LED_LEFT, HIGH);
    } else {
       digitalWrite(LED_LEFT, LOW);
       tone(3, NOTE_D3, NOTE_DURATION);
    }
  
}  // end loop()
