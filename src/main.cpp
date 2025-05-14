#include <Arduino.h>

#define BLYNK_TEMPLATE_ID "TMPL6vxThKswZ"
#define BLYNK_TEMPLATE_NAME "Animal Feed System"
#define BLYNK_AUTH_TOKEN "Mpg-_dNTasYTkMAGZWqvNwz6plXj_0uc"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h> 

Servo feederServo;

// WiFi credentials
const char* ssid = "Wokwi-GUEST";
const char* pass = "";

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo and Buzzer
const int servoPin = 5;
const int buzzerPin = 26;

// State variables
int happiness = 50;
int sadness = 50;
int feedLevel = 50;

// Flags
bool systemRunning = false;

// Blynk virtual pins
#define VPIN_START V0
#define VPIN_FEED V1
#define VPIN_ENERGY V2
#define VPIN_ALARM V3
#define VPIN_LABEL V4

// Function to update the LCD display
void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hap:");
  lcd.print(happiness);
  lcd.print(" Sad:");
  lcd.print(sadness);
  
  lcd.setCursor(0, 1);
  lcd.print("Feed:");
  lcd.print(feedLevel);
}

// Function to control the servo motor
void checkServo() {
  if (happiness >= 100) {
    feederServo.write(90);  // Turn servo
    delay(1000);
    feederServo.write(0);   // Reset
  }
}

// Function to handle alarm
void checkAlarm() {
  if (sadness >= 100) {
    digitalWrite(buzzerPin, HIGH);
    Blynk.virtualWrite(VPIN_ALARM, 1); // Notify Blynk alarm
  } else {
    digitalWrite(buzzerPin, LOW);
    Blynk.virtualWrite(VPIN_ALARM, 0); // No alarm
  }
}

//Notify the user
void notify(){
  if (happiness==100)
  {
    Blynk.virtualWrite(VPIN_LABEL,"Max level reached");
  }
  else if(sadness==100){
    Blynk.virtualWrite(VPIN_LABEL,"Alarm worked");
  }else{
    Blynk.virtualWrite(VPIN_LABEL,"Processing");
  }
  
}


// Start Button Handler
BLYNK_WRITE(VPIN_START) {
  int start = param.asInt();
  systemRunning = (start == 1);

  if (systemRunning) {
    feedLevel -= 10;
    happiness -= 10;
    sadness += 10;

    // Bounds checking
    happiness = constrain(happiness, 0, 100);
    sadness = constrain(sadness, 0, 100);
    feedLevel = constrain(feedLevel, 0, 100);

    updateLCD();
    checkServo();
    checkAlarm();
    notify();
  }
}

// Feed Button Handler
BLYNK_WRITE(VPIN_FEED) {
  int feed = param.asInt();
  systemRunning = (feed == 1);

  if (systemRunning) {
    feedLevel += 10;
    happiness += 10;
    sadness -= 10;

    // Bounds checking
    happiness = constrain(happiness, 0, 100);
    sadness = constrain(sadness, 0, 100);

    updateLCD();
    checkServo();
    checkAlarm();
    notify();
  }
}

// Energy Button Handler
BLYNK_WRITE(VPIN_ENERGY) {
  int energy = param.asInt();
  systemRunning = (energy == 1);

  if (systemRunning) {
    happiness -= 10;
    sadness += 10;

    // Bounds checking
    happiness = constrain(happiness, 0, 100);
    sadness = constrain(sadness, 0, 100);

    updateLCD();
    checkServo();
    checkAlarm();
    notify();
  }
}


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.println("Connectiong to WiFi..");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to WiFi");
  
  Serial.println(WiFi.localIP());
  

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  lcd.init();
  lcd.backlight();
  updateLCD();

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  feederServo.attach(servoPin);
  feederServo.write(0);
}

void loop() {
  Blynk.run();
}
