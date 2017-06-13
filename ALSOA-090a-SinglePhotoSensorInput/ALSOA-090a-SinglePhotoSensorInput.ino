/*  <--- Single photo sensor testing--->
 * 
 * This sketch shows the output of a single photo sensor to 
 * the serial monitor
 * 
 * Components  used in this sketch
 * ----------
 *  - Arduino Uno
 *  - Breadboard
 *  - 1 x Light Dependent Resistors (Photoresistors) 
 *  - 1 x 10kΩ resistors  
 *    
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections 
 * -----------
 * Please see schematic 090a. The schematic is available as part of the 
 * lecture downloadable resources.
 * 
 * Other information
 * ----------------- 
 *  More about the photoresistors: https://en.wikipedia.org/wiki/Photoresistor
 *  
 *  
 *  Created on June 12 2017 by Peter Dalmaris
 * 
 */

int sensorPin = A2;    // select the input pin for the photosensor
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);

  // Print the value from the photo resistor to the serial monitor
  Serial.println(sensorValue);
  
  delay(10);
}
