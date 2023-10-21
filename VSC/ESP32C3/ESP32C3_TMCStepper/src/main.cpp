#include <Arduino.h>

// /**
//  * Author Teemu Mäntykallio
//  * Initializes the library and runs the stepper
//  * motor in alternating directions.
//  */

#include <TMCStepper.h>

#define SERVO_PIN 1
#define HALL_SENSOR_PIN 4

#define EN_PIN           0 // Enable
#define DIR_PIN          5  // Direction
#define STEP_PIN         6  // Step
//#define MS1              23
//#define MS2              22 
#define SW_SCK           10 // Software Slave Clock (SCK)
//#define SW_RX            7 // TMC2208/TMC2224 SoftwareSerial receive pin
//#define SW_TX            8 // TMC2208/TMC2224 SoftwareSerial transmit pin
#define SERIAL_PORT Serial1 // TMC2208/TMC2224 HardwareSerial port
#define DRIVER_ADDRESS 0b00 // TMC2209 Driver address according to MS1 and MS2

#define R_SENSE 0.11f // Match to your driver
                      // SilentStepStick series use 0.11
                      // UltiMachine Einsy and Archim2 boards use 0.2
                      // Panucatt BSD2660 uses 0.1
                      // Watterott TMC5160 uses 0.075

//HardwareSerial SERIAL_PORT(1);
TMC2209Stepper driver(&SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
//TMC2209Stepper driver(SW_RX, SW_TX, R_SENSE, DRIVER_ADDRESS);

void setup() {
  Serial.setTimeout(500);
  Serial.begin(115200);
  
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);      // Enable driver in hardware

                                  // Enable one according to your setup
//SPI.begin();                    // SPI drivers
// SERIAL_PORT.begin(115200, SERIAL_8N1, SW_RX, SW_TX);      // HW UART drivers
 SERIAL_PORT.begin(115200);
//driver.beginSerial(115200);     // SW UART drivers

  driver.begin();                 //  SPI: Init CS pins and possible SW SPI pins
                                  // UART: Init SW UART (if selected) with default 115200 baudrate

  driver.toff(5);                 // Enables driver in software
  driver.rms_current(600);        // Set motor RMS current
  driver.microsteps(8);          // Set microsteps to 1/16th

//driver.en_pwm_mode(true);       // Toggle stealthChop on TMC2130/2160/5130/5160
//driver.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
//  driver.pwm_autoscale(true);     // Needed for stealthChop



}

bool shaft = false;

void loop() {

  if(Serial.available())
  {
    char charText = Serial.read();
    switch (charText) {
    case '+':
      Serial.printf("%c => Move Forward\r\n", charText);
      digitalWrite(DIR_PIN, true);
      
      for (uint16_t i = 1600; i>0; i--) 
      {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(100);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(100);
      }
      break;
    case '-':
      Serial.printf("%c => Move Backward\r\n", charText);
      digitalWrite(DIR_PIN, false);
      for (uint16_t i = 1600; i>0; i--) 
      {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(100);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(100);
      }     
      break;
    case 'e':
      Serial.printf("Enable Stepping Driver\r\n");
      digitalWrite(EN_PIN, LOW);
      break;
    case 'd':
      Serial.printf("Disable Stepping Driver\r\n");
      digitalWrite(EN_PIN, HIGH);
      break;
    }

  }
}



