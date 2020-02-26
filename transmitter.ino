// Name= Caglar Kurtkaya
// Name = Aleksandar Knezevic
//
// Final Project - Morse Code Laser Communication
//
// Description -
// It reads for any data on Serial port, character by character.
// Find the equivalent Morse code for the character and generate ‘dot’ and ‘dash’ light stream.
// It also has buttons to store dashes and dots. When buttons pressed it stores the values in a string
// When done button is pressed it goes over the string and the flashes either dots or dashes.
const char* MorseTable[] = {
 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
 // space, !, ", #, $, %, &, '
 NULL, "-.-.--", ".-..-.", NULL, NULL, NULL, NULL, ".----.",
 // ( ) * + , - . /
 "-.--.", "-.--.-", NULL, ".-.-.", "--..--", "-....-", ".-.-.-", "-..-.",
 // 0 1 2 3 4 5 6 7
 "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...",
 // 8 9 : ; < = > ?
 "---..", "----.", "---...", "-.-.-.", NULL, "-...-", NULL, "..--..",
 // @ A B C D E F G
 ".--.-.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
 // H I J K L M N O
 "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
 // P Q R S T U V W
 ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
 // X Y Z [ \ ] ^ _
 "-..-", "-.--", "--..", NULL, NULL, NULL, NULL, "..--.-",
 // ' a b c d e f g
 NULL, ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
 // h i j k l m n o
 "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
 // p q r s t u v w
 ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
 // x y z { | } ~ DEL
 "-..-", "-.--", "--..", NULL, NULL, NULL, NULL, NULL,
 };

 int dotLength = 400; // length of dot
int dashLength = 800; // length of dot
//Pins for buttons
const int dotButton = 2;
const int dashButton = 3;
const int doneButton = 4;
//String to hold dots and dashes coming from buttons
String str = " ";
//these values used for brooklyn debounce
int val;
int val2;
int val3;
int val4;
int val5;
int val6;
// button states used for brooklyn debounce
int dotButtonState= 0;
int dashButtonState = 0;
int doneButtonState = 0;
void setup() {
 // put your setup code here, to run once:
 pinMode(13, OUTPUT);
 pinMode(dashButton, INPUT);
 pinMode(dotButton, INPUT);
 pinMode(doneButton, INPUT);
 Serial.begin(9600);
}

void loop() {
 char ch;
 if(Serial.available()){
 ch = Serial.read();
 flashDashDot(MorseTable[ch]);
 delay(dotLength*2);
 }
 val = digitalRead(dotButton); // read input value and store it in val
 delay(10); // 10 milliseconds is a good amount of time
 val2 = digitalRead(dotButton); // read the input again to check for bounces
 if (val == val2) { // make sure we got 2 consistant readings!
 if (val != dotButtonState) { // the button state has changed!
 if (val == LOW) { // check if the button is pressed
 str += ".";
 }
 }
 dotButtonState = val; // update button state
 }
 val3 = digitalRead(dashButton); // read input value and store it in val
 delay(10); // 10 milliseconds is a good amount of time
 val4 = digitalRead(dashButton); // read the input again to check for bounces
 if (val3 == val4) { // make sure we got 2 consistant readings!
 if (val3 != dashButtonState) { // the button state has changed!
 if (val3 == LOW) { // check if the button is pressed
 str += "-";
 //dot();
 }
 }
 dashButtonState = val3; // update button state
 }
 val5 = digitalRead(doneButton); // read input value and store it in val
 delay(10); // 10 milliseconds is a good amount of time
 val6 = digitalRead(doneButton); // read the input again to check for bounces
 if (val5 == val6) { // make sure we got 2 consistant readings!
 if (val5 != doneButtonState) { // the button state has changed!
 if (val5 == LOW) { // check if the button is pressed
 flashDashDot2(str);
 str = " ";
  }
 }
 doneButtonState = val5; // update button state
 }
}
// this function used to go over the string and then outputs either dot or dash
void flashDashDot2(String s)
{
 int i = 0;
 while(s[i] != 0)
 {
 if(s[i] == '.'){
 dot();
 } else if (s[i] == '-'){
 dash();
 }
 i++;
 }
}
void flashDashDot(const char * morseCode)
{
 int i = 0;
 while(morseCode[i] != 0)
 {
 if(morseCode[i] == '.'){
 dot();
 } else if (morseCode[i] == '-'){
 dash();
 }
 i++;
 }
}
//flashes dot
void dot()
{
 digitalWrite(13, HIGH);
 delay(dotLength);
 digitalWrite(13, LOW);
 delay(dotLength); }
//flashes dash
void dash() {
 digitalWrite(13, HIGH);
 delay(dashLength);
 digitalWrite(13, LOW);
 delay(dotLength); }
