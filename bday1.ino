#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Address 0x27 for a 16x2 display

const int buttonPin = 4; // Pin connected to the push button
const int ledPins[] = {6, 9, 11}; // Pins connected to the LEDs

int speakerPin = 3;
int length = 28; // the number of notes
char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";
int beats[] = { 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8,8, 16, 1, 2,2,8,8,8,8,16, 1,2,2,8,8,8,16 };
int tempo = 150;
void playTone(int tone, int duration) {
for (long i = 0; i < duration * 1000L; i += tone * 2) {
   digitalWrite(speakerPin, HIGH);
   delayMicroseconds(tone);
   digitalWrite(speakerPin, LOW);
   delayMicroseconds(tone);
}
}
void playNote(char note, int duration) {
char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           

                 'c', 'd', 'e', 'f', 'g', 'a', 'b',

                 'x', 'y' };

int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,

                 956,  834,  765,  593,  468,  346,  224,

                 655 , 715 };

int SPEE = 5;
// play the tone corresponding to the note name
for (int i = 0; i < 17; i++) {
   if (names[i] == note) {
    int newduration = duration/SPEE;
     playTone(tones[i], newduration);

   }
}
}


void setup() {
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  lcd.clear(); // Clear the LCD screen
  pinMode(speakerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with internal pull-up resistor
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT); // Set LED pins as output
  }
}

void loop() {
  
     tune();// If button is pressed
    for (int i = 0; i < 5; i++) { // Display text 5 times
      displayText(); // Display text on LCD
      for (int j = 0; j < 3; j++) { // Loop through LEDs
        digitalWrite(ledPins[j], HIGH); // Turn on LED
        delay(500); // Delay
        digitalWrite(ledPins[j], LOW); // Turn off LED
      }
    }
  
}

void displayText() {
  String message = "Happy Birthday Aashay";
  int messageLength = message.length();
  
  for (int i = 0; i < messageLength + 16; i++) { // Scroll text
    lcd.clear();
    lcd.setCursor(i, 0);
    lcd.print(message);
    delay(300);
  }
}

void tune(){
  for (int i = 0; i < length; i++) {
   if (notes[i] == ' ') {
     delay(beats[i] * tempo); // rest
   } else {
     playNote(notes[i], beats[i] * tempo);
   }
   // pause between notes
   delay(tempo);
}
}
