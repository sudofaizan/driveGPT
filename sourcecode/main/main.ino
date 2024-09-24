#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "ELMduino.h"

SoftwareSerial btm(11, 10); // RX, TX init onboard btm
#define ELM_PORT btm
uint32_t rpm = 0;

uint32_t load = 0;
bool connected = false;
ELM327 myELM327;

LiquidCrystal_I2C lcd(0x27,  16, 2);
const int LED_YELLOW = 12;
const int LED_BLUE = 13;
const int BTM = 8;
const int BTM_KEY = 9;
const int BTM_RX = 11;
const int BTM_TX = 10;
const int BUZZ = 7;
const int RELAY = 6;

void checkcar(){
    btm.println("ATZ"); // Send "AT" command
  delay(300);
  String response = btm.readStringUntil('\n');
response.trim();
  Serial.println(response);

if (response.indexOf("ELM327 v1.5") != -1) {
  Serial.println("car detected");
      digitalWrite(LED_YELLOW, 1);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("CAR Connected");
        connected = true;  // Set connected to true after first run
        digitalWrite(BUZZ, 1);
        delay(50);
        digitalWrite(BUZZ, 0);
        delay(50);
        digitalWrite(BUZZ, 1);
        delay(50);
        digitalWrite(BUZZ, 0);
        delay(50);
        digitalWrite(BUZZ, 1);
        delay(50);
        digitalWrite(BUZZ, 0);
        delay(50);
        digitalWrite(BUZZ, 1);
        delay(50);
        digitalWrite(BUZZ, 0);
        digitalWrite(LED_YELLOW, 1);
  if (!myELM327.begin(ELM_PORT, true, 2000))
  {
    Serial.println("Couldn't connect to OBD scanner");
    while (1);
  }




} else {
  digitalWrite(BUZZ, 1);
  Serial.println("car not found");
        lcd.clear();
      lcd.setCursor(0,0);
    lcd.print("CAR Not FOuNd");
      lcd.setCursor(0,1);
      lcd.print("Searching...");
  digitalWrite(BUZZ, 0);
    checkcar();


}
}
void setup() {

  Serial.begin(9600);
  btm.begin(38400);
  pinMode(LED_BLUE, OUTPUT); //Blue led 
  pinMode(RELAY, OUTPUT); //Blue led 
  pinMode(LED_YELLOW, OUTPUT); //Yello led
  pinMode(BTM, OUTPUT);  //BTM
  pinMode(BTM_KEY, OUTPUT);  //BTM key
  pinMode(BUZZ, OUTPUT); //buzzer
  //initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("DriveGPT by ");
  lcd.setCursor(0,1);
  lcd.print("Faizan");
  delay(2000);
  lcd.clear();
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
  Serial.println("got ok back");
  digitalWrite(BTM, 1);
  digitalWrite(LED_YELLOW, 1);
  digitalWrite(BUZZ, 1);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HC05-OK");
  delay(300);
  digitalWrite(LED_YELLOW, 0);
  btm.println("AT+RESET"); // Send "AT" command
  digitalWrite(BTM_KEY, 0);
  delay(1000);
  digitalWrite(BUZZ, 0);
  btm.begin(9600);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CAR CHECKING");
  if (!connected) {
  checkcar();
  }
} else {
  Serial.println("Connection failed");
}
}

void loop()
{

  float tempLOAD = myELM327.engineLoad();
  float tempRPM = myELM327.rpm();
  // float tempTEMP = myELM327.engineCoolantTemp();

  if (myELM327.nb_rx_state == ELM_SUCCESS)
  {
    rpm = (uint32_t)tempRPM;
    load = (uint32_t)tempLOAD;
    // temp = (uint32_t)tempTEMP;

    if (load > 60)
    {
        digitalWrite(BUZZ, 1);
        digitalWrite(RELAY, 1);

    }
    else{
        digitalWrite(BUZZ, 0);
        digitalWrite(RELAY, 0);

    }
    if (rpm > 2200)
    {
        digitalWrite(BUZZ, 1);
        digitalWrite(RELAY, 1);

    }
    else{
        digitalWrite(BUZZ, 0);
        digitalWrite(RELAY, 0);

    }
    Serial.print("RPM: "); Serial.println(rpm);
    Serial.print("TEMP: "); Serial.println(load);
      lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(rpm);
  lcd.setCursor(0,1);
  lcd.print(load);
  }
  else if (myELM327.nb_rx_state != ELM_GETTING_MSG)
    myELM327.printError();

}
