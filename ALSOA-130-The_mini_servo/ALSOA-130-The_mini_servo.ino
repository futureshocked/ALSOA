/*  <--- Arduino Ultrasonic Distance sensor with micro Servo --->
 * 
 * This sketch causes a micro servo to
 * turn left, right and center.
 * 
 * Components  used in this sketch
 * ----------
 *  - Arduino Uno
 *  - Breadboard  
 *  - 1 x Micro generic Servo 
 *  - 1 x 100μF capacitor 
 *    
 *  Libraries
 *  ---------
 *  - Servo.h
 *
 * Connections 
 * -----------
 *  - Connect the motor black wire to GND rail on the breadboard
 *  - Connect the motor red wire to 5V rail on the breadboard
 *  - Connect the motor white wire to digital pin 6
 *  
 *  For the breadboard:
 *  - Connect the GND rail of the breaboard to the GND pin of the Arduino
 *  - Connect the 5V rail of the breaboard to the 5V pin of the Arduino
 *  
 *  For the capacitors:
 *  - Plug the capacitor directly on the power rail of the breadboard. If you are
 *    using an electrolitic capacitor, beware of the polarity.
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

Servo panMotor;  //micro servo with the distance sensor on it

void setup()
{
  panMotor.attach(6); 
  panMotor.write(90); //center the pan servo

  Serial.begin(9600);
  Serial.println("This monitor will show us which way the servo motor has turned");
}

void loop(){
    panMotor.write(0);       // Turn to the right
    Serial.println("Right");
    delay(500);
    panMotor.write(180);     //Turn to the left
    Serial.println("Left"); 
    delay(500);
    panMotor.write(90);      //Turn to center
    Serial.println("Center");
    delay(500);
}
