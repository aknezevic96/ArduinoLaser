/*
 * Aleksandar Knezevic - knezevi2
 * Caglar kurtkaya - ckurtk2
 *
 * 362 Final Project Receiver
 *
 * Description
 * -Receives light from transmitted laser and decodes the laser pulses into
 * characters to be displayed on an LCD.
 *
 * Assumptions
 * -We thought the photoresistor would be fine exposed but we needed to wrap
 * it in duct tape to block out any unwanted light.
 * -Got the laser timings to work when printing to serial but didn't work when
 * we started displaying output to LCD, delay affected it.
 *
 * References
 *
-https://create.arduino.cc/projecthub/achindra/morse-code-transceiver-b5ae38?ref=tag&ref_id=c
ommunication&offset=20
 * -https://www.arduino.cc/en/Tutorial/LiquidCrystalScroll
 * -https://www.instructables.com/id/How-to-use-a-photoresistor-or-photocell-Arduino-Tu/
 *
-https://create.arduino.cc/projecthub/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-ar
duino-uno-89df45
 */

 const char MorseTree[] = {'\0','E', 'T', 'I', 'A', 'N', 'M', 'S',
 'U', 'R', 'W', 'D', 'K', 'G', 'O', 'H',
 'V', 'F', 'U', 'L', 'A', 'P', 'J', 'B',
 'X', 'C', 'Y', 'Z', 'Q', '\0','\0','5',
 '4', '\0','3', '\0','\0','\0','2', '\0',
 '\0','+', '\0','\0','\0','\0','1', '6',
 '=', '/', '\0','\0','\0','(', '\0','7',
 '\0','\0','\0','8', '\0','9', '0', '\0',
 '\0','\0','\0','\0','\0','\0','\0','\0',
 '\0','\0','\0','?', '_', '\0','\0','\0',
 '\0','"', '\0','\0','.', '\0','\0','\0',
 '\0','@', '\0','\0','\0','\0','\0','\0',
 '-', '\0','\0','\0','\0','\0','\0','\0',
 '\0',';', '!', '\0',')', '\0','\0','\0',
 '\0','\0',',', '\0','\0','\0','\0',':',
 '\0','\0','\0','\0','\0','\0','\0'
 };
 //binary tree of chars for decoding
#include <LiquidCrystal.h>
int val = 0; // A Variable to Store the Light Value from the LDR
int ctrHigh = 0; //controls boundaries for dots/dashes
int ctrLow = 0;
int codePtr = 0; //controls what letter to be decoded
int dotLen = 4000; //approximation of pulse
int numChars = 0; //for LCD cursor positioning
bool isRow2 = false; //same as above
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  Serial.begin(9600);// Start a Serial Connection
  Serial.print(codePtr);
  lcd.begin(16, 2); //set up LCD
  lcd.clear();
}

void loop() {
 val = analogRead(0); //reads photoresistor value
 if (val >= 250) { //if receiving light
 ctrHigh++; //increment
 ctrLow = 0;
 digitalWrite(13, HIGH); //light up onboard LED
 tone(7, 1000); //emit noise
 }
 else { //not receiving light
 ctrLow++; //increment
 if ((ctrHigh >= dotLen) && (ctrHigh < 7000)) { //upper boundary for dash
 Serial.println(ctrHigh);
 Serial.print(".");
 codePtr = (2 * codePtr) + 1; //find character from array
 }
 else if (ctrHigh >= 7000) { //lower boundary for dash
 Serial.println(ctrHigh);
 Serial.print("-");
 codePtr = (2 * codePtr) + 2;
 }
 else {
 if(ctrLow == dotLen * 2){ //character matched to morse
 Serial.print(MorseTree[codePtr]);
 lcd.print(MorseTree[codePtr]); //display character
 numChars++;
 if(!isRow2) { //cursor positioning
 lcd.setCursor(numChars, 0);
 if(numChars == 16) {
 isRow2 = true;
 }
 }
 else {
 if(numChars >= 16) {
 numChars = 0;
 }
 lcd.setCursor(numChars, 1);
 }
 codePtr = 0; //reset value
 }
 }
 ctrHigh = 0; //reset value
 digitalWrite(13, LOW); //turn off onboard LED
 noTone(7); //turn noise off
 }
}
