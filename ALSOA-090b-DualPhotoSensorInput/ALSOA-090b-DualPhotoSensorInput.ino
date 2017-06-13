/*  <--- Dual photo sensor testing--->
 * 
 * This sketch shows the output of two photo sensors to 
 * the serial monitor. This is a step towards detecting the bearing
 * of a light source based on the information provided by the two sensors.
 * 
 * Components  used in this sketch
 * ----------
 *  - Arduino Uno
 *  - Breadboard
 *  - 2 x Light Dependent Resistors (Photoresistors) 
 *  - 2 x 10kΩ resistors  
 *    
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections 
 * -----------
 * Please see schematic 090b. The schematic is available as part of the 
 * lecture downloadable resources.
 * 
 * Other information
 * ----------------- 
 *  More about the photoresistors: https://en.wikipedia.org/wiki/Photoresistor
 *  
 *  
 *  Created on June 12 2018 by Peter Dalmaris
 * 
 */

int leftSensorPin    = A2;   // select the input pin for the left photo sensor
int leftSensorValue  = 0;    // variable to store the value coming from the left sensor
int rightSensorPin   = A0;   // select the input pin for the left photo sensor
int rightSensorValue = 0;    // variable to store the value coming from the left sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensors:
  leftSensorValue  = analogRead(leftSensorPin);
  rightSensorValue = analogRead(rightSensorPin);

  // Print the value from the photo resistor to the serial monitor
  Serial.print(leftSensorValue);
  Serial.print(", ");
  Serial.println(rightSensorValue);
  
  delay(10);
}
