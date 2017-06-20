/*  <--- Arduino Ultrasonic Distance sensor, non-blocking --->
 * 
 * This sketch gets readings from an ultrasonic sensor without blocking. This
 * is very useful for improving performance.
 * 
 * Components  used in this sketch
 * ----------
 *  - Arduino Uno
 *  - Breadboard  
 *  - 1 x HC-SR04 
 *    
 *  Libraries
 *  ---------
 *  - HC_SR04.h   (Download from txplo.re/HC_SR04lib)
 *
 * Connections 
 * -----------
 *  - Connect HC_SR04 trig pin to Arduino pin 3
 *  - Connect HC_SR04 echo pin to Arduino pin 2
 * 
 * Other information
 * -----------------
 *  Original code is available at https://github.com/jazzycamel/arduino/tree/master/ultrasonic
 *  Download the HC_SR04 library as used in this course from txplo.re/HC_SR04lib
 *  
 *  Created on June 14 2017 by Peter Dalmaris
 * 
 */


#include <HC_SR04.h>

#define TRIG_PIN 3   // HC_SR04 trig pin to Arduino pin 3
#define ECHO_PIN 2   // HC_SR04 echo pin to Arduino pin 2 (this pin is Arduino's interrupt pin 0)
#define ECHO_INT 0   // The HC_SR04 echo pin is connected to Arduino pin 2 which is interrupt id 0)  

HC_SR04 sensor(TRIG_PIN, ECHO_PIN, ECHO_INT);  // Create the sensor object

void setup(){  
  sensor.begin();              // Setup the sensor
  Serial.begin(9600); 
  while(!Serial) continue;
}

void loop(){
  sensor.start();                      // Start the sensor
  while(!sensor.isFinished()) return;   // If the sensor does not have a reading, continue
  Serial.print(sensor.getRange());     // if the sensor has a reading, print out its reading
  Serial.println("cm");
  delay(1000);
}

