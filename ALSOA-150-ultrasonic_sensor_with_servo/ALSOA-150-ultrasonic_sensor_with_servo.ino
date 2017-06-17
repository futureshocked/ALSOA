/*  <--- Arduino Ultrasonic Distance sensor with micro Servo --->
 * 
 * This sketch shows how the Ultrasonic Distance sensor 
 * works using the Serial Monitor and a micro servo to
 * turn left and right and choose the clear path.
 * 
 * Components  used in this sketch
 * ----------
 *  - Arduino Uno
 *  - Breadboard  
 *  - HC-SR04 Ultrasonic Distance Sensor 
 *  - 1 x Micro generic Servo 
 *  - 1 x 100μF capacitor 
 *    
 *  Libraries
 *  ---------
 *  - Servo.h
 *  - HC_SR04.h   (Download from txplo.re/HC_SR04lib)
 *
 * Connections 
 * -----------
 *  - Connect HC_SR04 trig pin to Arduino pin 3
 *  - Connect HC_SR04 echo pin to Arduino pin 2
 *  - Connect the motor black wire to GND rail on the breadboard
 *  - Connect the motor red wire to 6V rail on the breadboard. You can get 6V
 *    from a 1.5V AA x 4 battery pack. If you don't have one, it is safe to power
 *    the motor from the Arduino 5V pin.
 *  - Connect the motor white wire to digital pin 6
 *  
 *  For the breadboard:
 *  - Connect the GND rail of the breaboard to the GND pin of the Arduino and 
 *    the GND wire of the battery pack.
 *  - Connect the red rail of the breaboard to the 6V wire of the the 
 *    1.5V AA x 4 battery pack or the 5V pin of the Arduino.
 *    
 *  
 *  For the capacitors:
 *  - Plug the capacitor directly on the power rail of the breadboard. If you are
 *    using an electrolitic capacitor, beware of the polarity.
 * 
 * 
 * Other information
 * -----------------
 *  Original code is available at https://github.com/jazzycamel/arduino/tree/master/ultrasonic
 *  Download the HC_SR04 library as used in this course from txplo.re/HC_SR04lib
 *  
 *  Created on February 7 2017 by Evangelos Chantzis
 *  Modified on June 14 2017 by Peter Dalmaris
 * 
 */

#include <Servo.h> //include Servo library

#include <HC_SR04.h>

#define TRIG_PIN 3   // HC_SR04 trig pin to Arduino pin 3
#define ECHO_PIN 2   // HC_SR04 echo pin to Arduino pin 2 (this pin is Arduino's interrupt pin 0)
#define ECHO_INT 0   // The HC_SR04 echo pin is connected to Arduino pin 2 which is interrupt id 0)  

HC_SR04 sensor(TRIG_PIN, ECHO_PIN, ECHO_INT);  // Create the sensor object

const int collisionThresh = 15;         //threshold for obstacles (in cm)
int       leftDistance, rightDistance;  //distances on either side
Servo     panMotor;                     //micro servo with the distance sensor on it

void setup()
{
  panMotor.attach(6);          // connect servo to pin 6
  panMotor.write(90);          // center the pan servo

  sensor.begin();              // Setup the sensor
  
  Serial.begin(9600);
  Serial.println("This monitor will show us where the robot will go");
}

void loop(){
  int distance = ping();  //call the ping function to get the distance in front of the robot
  Serial.print(distance);
  Serial.println("cm");
  if (distance > collisionThresh) //if path is clear be guided from the light
  {
    Serial.println("Forward, path clear!");
    delay(250);
  }
  else //if path is blocked
  { 
    panMotor.write(0); 
    delay(500);
    leftDistance = ping();  //scan to the right
    delay(500);
    panMotor.write(180);
    delay(700);
    rightDistance = ping(); //scan to the left
    delay(500);
    panMotor.write(90);     //return to center
    delay(100);
    compareDistance();
  }
}

void compareDistance()
{
  if (leftDistance > rightDistance) //if left is less obstructed 
  {
    Serial.println("Left turn!");
    delay(500); 
  }
  else if (rightDistance > leftDistance) //if right is less obstructed
  {
    Serial.println("Right turn!");
    delay(500);
  }
   else //if they are equally obstructed
  {
    Serial.println("Turn back!");
    delay(1000);
  }
}

long ping()
{
  sensor.start();                         // Start the sensor to take a distance measurement
  
  while(!sensor.isFinished()) {};         // Wait until the sensor returns a reading. We need a valid value before we can continue.

  return sensor.getRange();               // The sensor has returned a reading, get it and return it to the caller.
}
