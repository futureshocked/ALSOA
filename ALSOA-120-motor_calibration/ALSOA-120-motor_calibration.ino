/*  <--- Arduino Robot Servo motors Wheels calibration --->
 * 
 * This sketch assists in calibrating the resting position of the continuous rotation servo.
 * You can also use it to test your servos.
 * 
 * Components  used in this sketch
 * ----------
 *  - Arduino Uno
 *  - Breadboard  
 *  - 2 x Continuous Rotation Servo (SpringRC SM-S4303R)
 *  - 1 x 330μF capacitors 
 *    
 *  Libraries
 *  ---------
 *  - Servo.h
 *
 * Connections 
 * -----------
 *  For the both motors:
 *  - Connect the black wire to GND rail on the breadboard
 *  - Connect the red wire to 6V rail on the breadboard. You can 
 *    get 6V from a 1.5V AA x 4 alkaline battery pack.
 *  
 *  For the left motor:
 *  - Connect the white wire to digital pin 10
 *  
 *  For the right motor:
 *  - Connect the white wire to digital pin 11
 *  
 *  For the breadboard:
 *  - Connect the GND rail of the breaboard to the GND pin of the Arduino
 *  
 *  For the capacitors:
 *  - Plug the capacitor directly on the power rail of the breadboard. If you are
 *    using an electrolitic capacitor, beware of the polarity.
 *  
 *  
 * 
 * Other information
 * -----------------
 *  Always remember to plug in the Servo Motors batteries first and then the Arduino batteries.
 *  

 *  
 *  Created on February 7 2017 by Evangelos Chantzis
 *  Updated on June 14 2017 by Peter Dalmaris
 * 
 */

#include <Servo.h> //include Servo library

const int RForward = 120;   //the speed of the servo, maximum speed is 180
const int RBackward = 60;   

const int LForward = 60; 
const int LBackward = 120; 

const int RNeutral = 90;    //centered position
const int LNeutral = 90;

Servo leftMotor;  //declare motors
Servo rightMotor;

void setup() {
  rightMotor.attach(11);  //attach motors to proper pins
  leftMotor.attach(10);
}

void loop() {

  // Uncomment each of the following lines, one by one, in order to 
  // calibrate the motors and ensure that they move as expected.
  // Always start with the neutral positions, where the motors are not moving.
// leftMotor.write(LNeutral); //stop
// rightMotor.write(RNeutral);
// delay(1500);

// leftMotor.write(LForward); //forward
// rightMotor.write(RForward);   
// delay(1500);
//  
// leftMotor.write(LBackward); //left turn
// rightMotor.write(RForward); 
// delay(1250);
//  
// leftMotor.write(LForward); //right turn
// rightMotor.write(RBackward);
// delay(1250);
//  
 
}
