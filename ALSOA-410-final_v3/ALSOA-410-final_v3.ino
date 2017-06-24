/*  <--- Arduino Light Seeking and Obstacle Avoiding Robot --->
 * 
 * This sketch shows all the functions of the robot
 * combined. It is the final sketch.
 * 
 * Components  used in this sketch
 * ----------
 *  - Arduino Uno
 *  - Breadboard  
 *  - HC-SR04 Ultrasonic Distance Sensor 
 *  - 1 x Micro generic Servo 
 *  - 1 x 100μF capacitor 
 *  - A potentiometer
 *  - 2 x Continuous Rotation Servo (SpringRC SM-S4303R) 
 *  - 2 x 330μF capacitors
 *  - 2 x Light Dependent Resistors 
 *  - 2 x 10kΩ resistors 
 *  - Magician Robot Chassis 
 *  - 2 x plastic wheels 6cm diameter, 0.7cm width 
 *  - 4 x 1.5V batteries for the motors and 4 x 1.5V batteries for the Arduino and sensors
 *    
 *  Libraries
 *  ---------
 *  - Servo.h
 *  - HC_SR04.h   (Download from txplo.re/HC_SR04lib)
 *
 * Connections 
 * -----------
 *  See schematic in file "ALSOA - final schematic.png", available for download from the downloadable resources
 *  for this lecture.
 * 
 * Other information
 * -----------------
 *  Always remember to plug in the Servo Motors batteries first and then the Arduino batteries.
 *  Original code for the HC_SR04 library is available at https://github.com/jazzycamel/arduino/tree/master/ultrasonic
 *  Download the HC_SR04 library as used in this course from txplo.re/HC_SR04lib
 *  
 *  
 *  Created on February 7 2017 by Evangelos Chantzis
 *  Updated on June 20 2017 by Peter Dalmaris
 * 
 */

#include <Servo.h> //include Servo library

#include <HC_SR04.h>

#define TRIG_PIN 3   // HC_SR04 trig pin to Arduino pin 3
#define ECHO_PIN 2   // HC_SR04 echo pin to Arduino pin 2 (this pin is Arduino's interrupt pin 0)
#define ECHO_INT 0   // The HC_SR04 echo pin is connected to Arduino pin 2 which is interrupt id 0)  

HC_SR04 sensor(TRIG_PIN, ECHO_PIN, ECHO_INT);  // Create the sensor object

const int RForward          = 120;  //the speed of the servo, maximum speed is 180
const int RForwardHalf      = 110;
const int RBackward         = 60;   
const int LForward          = 60; 
const int LBackward         = 120; 
const int LBackwardHalf     = 110;
const int RNeutral          = 90;  //centered position
const int LNeutral          = 90;
const int RightLightSensor  = 0;  // This is analog pin 0 for the right light sensor
const int LeftLightSensor   = 2;  // This is analog pin 2 for the left light sensor
const int collisionThresh   = 15; //threshold for obstacles (in cm)
const int threshold_pot     = 4;  // Use this potentiometer to calibrate the threshold of
                                  // the sensors to the light source. NOTE: this is ANALOG pin 4
const int closeness         = 60; // This value defines when the left and right light
                                  // sensors detect light at a similar enough intensity
                                  // to indicate that the light source is straight ahead. 
const int RightLEDIndicator = 5;  // This is digital pin
const int LeftLEDIndicator  = 4;  // This is digital pin                                                                   

int SensorLeft;                  // Stores the value from the left light sensor
int SensorRight;                 // Stores the value from the right light sensor
int SensorDifference;            // Stores absolute difference between the values from the two light sensors
int leftDistance, rightDistance; //distances on either side

Servo panMotor;   //The micro servo with the distance sensor on it
Servo leftMotor;  //the Left motor
Servo rightMotor; //the Right motor

void setup()
{
  rightMotor.attach(11);  //attach the right motor
  leftMotor.attach(10);   //attach the left motors
  panMotor.attach(6);     // attache the micro servo
  panMotor.write(90);     //center the micro servo

  sensor.begin();
  
  pinMode(TRIG_PIN,          OUTPUT);
  pinMode(ECHO_PIN,          INPUT);
  pinMode(LeftLightSensor,   INPUT);
  pinMode(RightLightSensor,  INPUT);
  pinMode(threshold_pot,     INPUT);  
  pinMode(RightLEDIndicator, OUTPUT);
  pinMode(LeftLEDIndicator,  OUTPUT);

  Serial.begin(9600);
}

void loop(){

  int threshold = analogRead(threshold_pot);
  int distance  = ping();  //call the ping function to get the distance in front of the robot
//  int distance = 17;
  Serial.print("Thresh:");
  Serial.print(threshold);
  Serial.print("(");
  Serial.print(threshold/2);
  Serial.print("), L=");
  SensorLeft = analogRead(LeftLightSensor);  //read the left light sensor
  Serial.print(SensorLeft);
  Serial.print(", R=");

  SensorRight = analogRead(RightLightSensor); //read the right light sensor
  Serial.print(SensorRight);
  Serial.print(", Diff=");

  SensorDifference = abs(SensorLeft - SensorRight);  //Calcuate the difference between
                                                     // left and right light sensors
  Serial.print(SensorDifference);

  Serial.print(", Obstacle:");
  Serial.print(distance);

  Serial.print("cm, Move:");

  if (distance > collisionThresh) //if path is clear, the robot can use the light sensors to navigate towards the light
  {
  // Check the conditions for moving forward
  if ( SensorLeft       <= threshold     && 
       SensorRight      <= threshold     && 
       SensorLeft       >= threshold/2   && 
       SensorRight      >= threshold/2   && 
       SensorDifference <= closeness) 
       {  
          Serial.print("Forward");
          leftMotor.write(LForward); 
          rightMotor.write(RForward);
          //leftMotor.write(LNeutral);   // Stop the left motor
      //rightMotor.write(RNeutral);  // Stop the right motor
          digitalWrite(LeftLEDIndicator, HIGH);
          digitalWrite(RightLEDIndicator, HIGH);
          delay(250);  
        }

  //This condition indicates that the robot has reached the light source,
  //so it will stop
  else if ( SensorLeft       >= threshold && 
            SensorRight      >= threshold && 
            SensorDifference <= closeness) 
       {  
          Serial.print("STOP");
          leftMotor.write(LNeutral);
          rightMotor.write(RNeutral); 
          digitalWrite(RightLEDIndicator, LOW);
          digitalWrite(LeftLEDIndicator, LOW);
          delay(200);
        }
        
  // If the left light sensor value is smaller than that of the right sensor, 
  // and the difference between the values is large, then
  // the light source is towards the left, so robot should turn left. 
  else if ( SensorLeft       <  SensorRight &&       
            SensorRight       >= threshold/2 ) 
            { 
              Serial.print("Right");
              leftMotor.write(LForward); 
              rightMotor.write(RBackward);
              digitalWrite(RightLEDIndicator, LOW);
              digitalWrite(LeftLEDIndicator, HIGH);
              delay(100);
            }

  // If the right light sensor value is smaller than that of the left sensor, 
  // and the difference between the values is large, then
  // the light source is towards the right, so robot should turn right. 
  else if ( SensorLeft       >  SensorRight  &&        
            SensorLeft       >= threshold/2 ) 
            { 
                Serial.print("Left");
//                leftMotor.write(LNeutral);   // Stop the left motor
//      rightMotor.write(RNeutral);  // Stop the right motor
                leftMotor.write(LBackward); 
                rightMotor.write(RForward); 
                digitalWrite(RightLEDIndicator, HIGH);
                digitalWrite(LeftLEDIndicator, LOW);
                delay(100);
            }

  //This condition indicates that both sensor of the robot are heading away from,
  //the light, so it should turn around
  else if ( SensorLeft  < threshold/2 && 
            SensorRight < threshold/2) 
            {                
                Serial.print("LOST");
                leftMotor.write(LBackwardHalf); 
                rightMotor.write(RForwardHalf); 
                delay(250);
//                for (int i = 0; i <2; i++)  // Make the LEDs blink fast
//                {
                digitalWrite(RightLEDIndicator, LOW);
                digitalWrite(LeftLEDIndicator, LOW);
//                delay(50);
//                digitalWrite(RightLEDIndicator, HIGH);
//                digitalWrite(LeftLEDIndicator, HIGH);
//                delay(50);
//                }
            }
  }
  else    // The path is blocked, so the robot will use the distance sensor to find a clear path
  {
      Serial.print(" blocked ");
      leftMotor.write(LNeutral);   // Stop the left motor
      rightMotor.write(RNeutral);  // Stop the right motor
      panMotor.write(0);           // Turn the distance sensor to the left
      delay(500);                  // Wait for the sensor to move into position
      leftDistance = ping();       // scan to the right
      delay(500);                  // Wait for the sensor to move into position
      panMotor.write(180);         // Turn the distance sensor to the right
      delay(700);                  // Wait for the sensor to move into position
      rightDistance = ping();      // Scan to the left
      delay(500);                  // Wait for the sensor to move into position
      panMotor.write(90);          // Return to center
      delay(100);                  // Wait for the sensor to move into position
      compareDistance();
  }
  
  Serial.println();

}

void compareDistance()
{
  if (leftDistance > rightDistance) //if left is less obstructed 
  {
    leftMotor.write(LBackward); 
    rightMotor.write(RForward); 
    Serial.print("Left");
    delay(10); 
    leftMotor.write(LForward);  // Then move forward just a bit
    rightMotor.write(RForward); // to try and clear the obstacle
    delay(200);
  }
  else if (rightDistance > leftDistance) //if right is less obstructed
  {   
    leftMotor.write(LForward);
    rightMotor.write(RBackward); 
    Serial.print("Right");
    delay(10);
    leftMotor.write(LForward);  // Then move forward just a bit
    rightMotor.write(RForward); // to try and clear the obstacle
    delay(200);
  }
   else //if they are equally obstructed
  {
    leftMotor.write(LBackward); 
    rightMotor.write(RForward); //turn 180 degrees
    Serial.print("Back");
    delay(500);
  }
}

long ping()
{
  sensor.start();                         // Start the sensor to take a distance measurement
  while(!sensor.isFinished()) continue;   // Wait until the sensor returns a reading. We need a valid value before we can continue.
  return sensor.getRange();               // The sensor has returned a reading, get it and return it to the caller.
}
