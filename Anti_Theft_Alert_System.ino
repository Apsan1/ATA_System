#include <WiFi.h> //including the library of Wifi to connect it with the network
#include <LiquidCrystal.h> //including the library of LCD to use LCD
#include <HTTPClient.h>

LiquidCrystal lcd(14, 27, 26, 25, 33, 32); //defining the LCD pins

const char* ssid = "Your WiFi SSID"; //the name of the network
const char* password = "Your WiFi Password"; //the password of the network

int triggerPin = 2; //defining the trigger pin of the ultrasonic sensor
int echoPin = 4;   //defining the echo pin of the ultrasonic sensor
int saveButtonPin = 19; //defining the save button pin
int resetButtonPin = 5;  //defining the reset button pin
int buzzerPin = 21;  //defining the buzzer pin
float savedDistance = 0;  //defining the saved distance globally to use it in the whole code
bool isDistanceSaved = false;  //defining the boolean variable to check if the distance is saved or not

void setup() {
  pinMode(triggerPin, OUTPUT);  //defining the trigger pin as output
  pinMode(echoPin, INPUT); //defining the echo pin as input
  pinMode(saveButtonPin, INPUT_PULLUP); //defining the save button pin as input
  pinMode(buzzerPin, OUTPUT); //defining the buzzer pin as output
  pinMode(resetButtonPin, INPUT_PULLUP); //defining the reset button pin as input

  Serial.begin(9600); //starting the serial monitor
  lcd.begin(16, 2); //defining the LCD size as 16x2

  lcd.clear(); //clearing the LCD screen to start writing on it
  lcd.println("System Starting.."); //printing the text on the LCD screen
  delay(1000); //delaying the code for 1 second
  lcd.clear(); //clearing the LCD screen to start writing on it
  Serial.print("Connecting to "); //printing the text on the serial monitor
  lcd.print("Connecting to "); //printing the text on the LCD screen
  lcd.setCursor(1, 0); //setting the cursor of the LCD screen to the second row
  lcd.print(ssid); //printing the name of the network on the LCD screen
  Serial.println(ssid); //printing the name of the network on the serial monitor
  delay(500); //delaying the code for 0.5 second
  WiFi.begin(ssid, password); //connecting to the network

  while (WiFi.status() != WL_CONNECTED) { //checking if the device is connected to the network or not
    delay(500); //delaying the code for 0.5 second
    Serial.print("."); //printing the text on the serial monitor
  }

  Serial.println("WiFi connected"); //printing the text on the serial monitor
  lcd.clear(); //clearing the LCD screen to start writing on it
  lcd.print("WiFi Connected!!"); //printing the text on the LCD screen
  delay(2000); //delaying the code for 2 seconds
  Serial.print("IP address: "); //printing the text on the serial monitor
  Serial.println(WiFi.localIP()); //printing the IP address of the device on the serial monitor

  lcd.clear(); //clearing the LCD screen to start writing on it
  lcd.print("Ultrasonic");
  lcd.setCursor(0, 1); //setting the cursor of the LCD screen to the second row  
  lcd.print("Distance: ");  
}

void loop() {
  delay(20);
 
  digitalWrite(triggerPin, LOW); // Clear the trigger
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); // Set the trigger
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW); // Clear the trigger

  long duration = pulseIn(echoPin, HIGH); // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds
  float distance = duration / 58.0; // Calculate the distance

  lcd.setCursor(10, 1); //setting the cursor of the LCD screen to the second row
  lcd.print(distance); //printing the distance on the LCD screen
  lcd.print("cm "); //printing the text on the LCD screen

  Serial.print("Distance: "); //printing the text on the serial monitor
  Serial.print(distance); //printing the distance on the serial monitor
  Serial.println("cm"); //printing the text on the serial monitor
 
  if (digitalRead(saveButtonPin) == LOW && !isDistanceSaved) { //checking if the save button is pressed or not and if the distance is saved or not
  //if the save button is pressed and the distance is not saved, then save the distance

    savedDistance = distance;
    isDistanceSaved = true;
    Serial.println("Distance saved: ");
    Serial.println(savedDistance);
  }

  if (digitalRead(resetButtonPin) == LOW) { //checking if the reset button is pressed or not
   
    savedDistance = 0;  //resetting the saved distance
    isDistanceSaved = false; //resetting the boolean variable
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(buzzerPin, LOW);
    Serial.println("Distance reset.");
    lcd.clear();
    lcd.print("Ultrasonic");  
    lcd.setCursor(0, 1);      
    lcd.print("Distance: "); 
  }

  if (savedDistance != 0) { //checking if the saved distance is not equal to zero
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("Saved Distance: ");
    lcd.setCursor(0, 1);
    lcd.print(savedDistance);
    lcd.print("cm ");
  }

  if (abs(distance - savedDistance) > 2 && isDistanceSaved) {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);
    lcd.clear();
    lcd.print("WARNING!!!!");
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.print("Distance changed!");
    if (WiFi.status() == WL_CONNECTED) { //checking if the device is connected to the network or not
      Serial.println("Sending request"); //printing the text on the serial monitor
      lcd.clear(); //clearing the LCD screen to start writing on it
      lcd.print("Sending Request"); //printing the text on the LCD screen
      HTTPClient http;
      http.begin("https://maker.ifttt.com/trigger/iot_object/json/with/key/esmoAy7KtRGe-iUYJ7Jv-01b1Y6KgO5hW2Egyw0yBFQ"); //connecting to the IFTTT webhooks
      http.GET(); //sending the GET request
      lcd.clear(); //clearing the LCD screen to start writing on it
      lcd.print("Notified!"); //printing the text on the LCD screen
      Serial.println("Notified!"); //printing the text on the serial monitor
      delay(2000); //delaying the code for 2 seconds
      http.end(); //closing the connection
    }
  }
}
