/*  <--- Robot light seeking subsystem calibration and testing--->
 * 
 * This sketch will help you to calibrate the light-seeking subsystem of the
 * robot.
 * 
 * Components  used in this sketch
 * ----------
 *  - Arduino Uno
 *  - Breadboard
 *  - 2 x Light Dependent Resistors (Photoresistors) 
 *  - 2 x 10 kΩ resistors  
 *  - 2 x LEDs
 *  - 2 x 330 Ω resistors
 *  - A potentiometer
 *    
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections 
 * -----------
 *  See schematic 090c, available for download from the downloadable resources
 *  for this lecture.
 * 
 * Other information
 * -----------------
 *  More about the photoresistors: https://en.wikipedia.org/wiki/Photoresistor
 *  
 *  
 *  Created on February 7 2017 by Evangelos Chantzis
 *  Modified on June 8 2017 by Peter Dalmaris
 * 
 */

const int RightLightSensor  = 0;  //declare the analog pins for the photoresistors
const int LeftLightSensor   = 2;
const int RightLEDIndicator = 5;  // This is digital pin
const int LeftLEDIndicator  = 4;  // This is digital pin
int       threshold_pot     = 4;  // Use this potentiometer to calibrate the threshold of
                                  // the sensors to the light source.
int       closeness         = 50; // This value defines when the left and right light
                                  // sensors detect light at a similar enough intensity
                                  // to indicate that the light source is straight ahead.                                  

int SensorLeft;
int SensorRight;
int SensorDifference;

void setup() {
  pinMode(LeftLightSensor,   INPUT);
  pinMode(RightLightSensor,  INPUT);
  pinMode(threshold_pot,     INPUT);
  pinMode(RightLEDIndicator, OUTPUT);
  pinMode(LeftLEDIndicator,  OUTPUT);
  Serial.begin(9600);
}

void loop() {

  int threshold = analogRead(threshold_pot);

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
  Serial.print(", Move:");

  // Check the conditions for moving forward
  if ( SensorLeft       <= threshold     && 
       SensorRight      <= threshold     && 
       SensorLeft       >= threshold/2   && 
       SensorRight      >= threshold/2   && 
       SensorDifference <= closeness) 
       {  
          Serial.print("Forward");
          digitalWrite(LeftLEDIndicator, HIGH);
          digitalWrite(RightLEDIndicator, HIGH);
          delay(10);  
        }

  //This condition indicates that the robot has reached the light source,
  //so it will stop
  else if ( SensorLeft       >= threshold && 
            SensorRight      >= threshold && 
            SensorDifference <= closeness) 
       {  
          Serial.print("STOP");
          digitalWrite(RightLEDIndicator, LOW);
          digitalWrite(LeftLEDIndicator, LOW);
          delay(10);
        }
        
  // If the left light sensor value is smaller than that of the right sensor, 
  // and the difference between the values is large, then
  // the light source is towards the left, so robot should turn left. 
  else if ( SensorLeft       <  SensorRight &&       
            SensorLeft       >= threshold/2 &&            
            SensorRight      >= threshold/2 ) 
            { 
              Serial.print("Right");
              digitalWrite(RightLEDIndicator, LOW);
              digitalWrite(LeftLEDIndicator, HIGH);
              delay(10);
            }

  // If the right light sensor value is smaller than that of the left sensor, 
  // and the difference between the values is large, then
  // the light source is towards the right, so robot should turn right. 
  else if ( SensorLeft       >  SensorRight  &&        
            SensorLeft       >= threshold/2  &&            
            SensorRight      >= threshold/2 ) 
            { 
                Serial.print("Left");
                digitalWrite(RightLEDIndicator, HIGH);
                digitalWrite(LeftLEDIndicator, LOW);
                delay(10);
            }

  //This condition indicates that both sensor of the robot are heading away from,
  //the light, so it should turn around
  else if ( SensorLeft  < threshold/2 && 
            SensorRight < threshold/2) 
            {                
                Serial.print("LOST");
                for (int i = 0; i <10; i++)  // Make the LEDs blink fast
                {
                digitalWrite(RightLEDIndicator, LOW);
                digitalWrite(LeftLEDIndicator, LOW);
                delay(50);
                digitalWrite(RightLEDIndicator, HIGH);
                digitalWrite(LeftLEDIndicator, HIGH);
                delay(50);
                }
            }
  
  Serial.println();
}
