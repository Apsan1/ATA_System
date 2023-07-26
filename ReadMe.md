# Anti-Theft Detection System Readme
## Description
The Anti-Theft Detection System is a device built using Arduino and various components such as an ultrasonic sensor, LCD display, and a buzzer. The system is designed to detect any changes in the distance between the device and an object, and if the distance changes significantly, it triggers an alert to notify the user of a potential theft. The system also features the ability to save a reference distance, allowing the user to monitor any variations from the saved distance.

## Components Required
- Arduino board
- Ultrasonic sensor (HC-SR04)
- LCD display (16x2)
- Buzzer
- Two push buttons (save and reset)
- Jumper wires
- Circuit Connections
- Ensure you connect the components as follows:

### Ultrasonic Sensor:

+ VCC pin to 5V on Arduino
+ GND pin to GND on Arduino
+ Trigger pin to pin 2 on Arduino
+ Echo pin to pin 4 on Arduino

### LCD Display:

+ VSS pin to GND on Arduino
+ VDD pin to 5V on Arduino
+ V0 pin to center pin of the 10k potentiometer
+ RS pin to pin 14 on Arduino
+ RW pin to GND on Arduino
+ E pin to pin 27 on Arduino
+ D4-D7 pins to pins 26, 25, 33, 32 on Arduino
+ A pin of the potentiometer to 5V
+ B pin of the potentiometer to GND
+ Wiper pin of the potentiometer to pin 3 on Arduino

### Buzzer:

- Positive (longer) pin to pin 21 on Arduino
- Negative (shorter) pin to GND on Arduino

### Save Button:

- One terminal to pin 19 on Arduino
- The other terminal to GND on Arduino

### Reset Button:

- One terminal to pin 5 on Arduino
- The other terminal to GND on Arduino

## How the System Works

- The system connects to a WiFi network using the provided credentials.
- The LCD displays the current distance measured by the ultrasonic sensor in centimeters.
- Pressing the "Save" button saves the current distance as the reference distance for comparison.
- Pressing the "Reset" button resets the reference distance to 0.
- If the distance measured by the ultrasonic sensor changes significantly from the saved distance (more than 2 cm), the buzzer is activated, and a warning message is displayed on the LCD.
- If the device is connected to the internet, it sends a request to a pre-configured IFTTT webhook, notifying the user of the potential theft.

## Setting Up

- Connect the components according to the "Circuit Connections" section above.
- Open the Arduino IDE, create a new sketch, and copy-paste the provided code into the sketch.
- Modify the following lines in the code to match your WiFi credentials:
arduino
<pre>
    const char* ssid = "Your WiFi SSID";
    const char* password = "Your WiFi Password";
</pre>

- Upload the code to your Arduino board.
- Once the upload is complete, open the serial monitor to view the system's status and IP address.

## Usage

- Power on the device and wait for the LCD to display "WiFi Connected!!" along with the IP address.
- The LCD will display the current distance measured by the ultrasonic sensor.
- Press the "Save" button to save the current distance as the reference distance.
- Press the "Reset" button to reset the reference distance to 0.
- If the distance measured by the ultrasonic sensor changes significantly from the saved distance, the buzzer will activate, and a warning message will be displayed on the LCD.
- If the device is connected to the internet, it will notify the user of the potential theft via the IFTTT webhook.

## Notes

- Make sure to secure the device in a position where it can monitor the area of interest effectively.
- Adjust the sensitivity threshold (2 cm in the provided code) as needed, depending on your specific use case.

## Troubleshooting

- If you encounter issues with the WiFi connection, double-check the provided WiFi credentials in the code.
- Ensure all components are correctly connected according to the "Circuit Connections" section.
- If the system is not working as expected, check for any error messages in the Arduino IDE's serial monitor.

## Disclaimer

- This project is provided as-is and may require further customization or adaptation to suit your specific requirements. The provided code and instructions are for educational purposes and may be subject to change or improvement. Use the system responsibly and avoid using it for any illegal or unauthorized activities. The creator of this project is not liable for any damages or consequences resulting from the use or misuse of this system.