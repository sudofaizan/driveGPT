// |———————————————————————————————————————————————————————| 
// |  made by Arduino_uno_guy 11/13/2019                   |
// |   https://create.arduino.cc/projecthub/arduino_uno_guy|
//  |———————————————————————————————————————————————————————|


#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial btm(11, 10); // RX, TX

//initialize the liquid crystal library
//the first parameter is  the I2C address
//the second parameter is how many rows are on your screen
//the  third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(0x27,  16, 2);
const int LED_YELLOW = 12;
const int LED_BLUE = 13;
const int BTM = 8;
const int BTM_KEY = 9;
const int BTM_RX = 11;
const int BTM_TX = 10;
const int BUZZ = 7;

void setup() {
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  btm.begin(38400);
  pinMode(LED_BLUE, OUTPUT); //Blue led 
  pinMode(LED_YELLOW, OUTPUT); //Yello led
  pinMode(BTM, OUTPUT);  //BTM
  pinMode(BTM_KEY, OUTPUT);  //BTM
  pinMode(BTM, OUTPUT);  //BTM
  pinMode(BUZZ, OUTPUT); //buzzer
  //initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();
  digitalWrite(BTM, 1);
  digitalWrite(BTM_KEY, 1);
  lcd.setCursor(0,0);
  lcd.print("HC05-Checking");
  delay(4000);
  //+ADDR:0022:04:012126 car hc05 addr
  btm.println("AT"); // Send "AT" command
  delay(50); // Allow device to respond
  String response = btm.readStringUntil('\n'); // Read response
  response.trim(); // Remove leading/trailing whitespace
    // Serial.println(response);

if (response.endsWith("OK")) {
  Serial.println("Connected");
  digitalWrite(LED_YELLOW, 1);
  digitalWrite(BUZZ, 1);
  

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HC05-OK");
  delay(1000);
  digitalWrite(LED_YELLOW, 0);
  digitalWrite(BUZZ, 0);


} else {
  Serial.println("Connection failed");
}
}

void loop() {
  




  
}
