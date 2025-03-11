#include <Arduino.h>
#include <Servo.h>
//////////////////////////////////////Servo Instances////////////////////////////////
Servo pan_servo; 
Servo tilt_servo;
//////////////////////////////////////Pin Asignments//////////////////////////////////
#define top_left A1 
#define top_right A3
#define bottom_left A2 
#define bottom_right A4 
#define pan_servo_pin 10 
#define tilt_servo_pin 9
/////////////////////////////////////Tuning Parameters////////////////////////////////  
const int tolerance = 10; //Difference between each quadrant, higher is less sensitive
const int cycle_time = 100; // Time before next control loop, higher is less sensitive
const int step_angle = 2; //Angle of servo movement for every loop, lower is less jerky
////////////////////////////////////Variable Declaration//////////////////////////////
int top_quadrant;
int bottom_quadrant;
int left_quadrant;
int right_quadrant;
int tilt_angle = 90;
int pan_angle = 90;

void setup() {
////////////////////////////////////Pin Modes//////////////////////////////////////////
  pinMode(top_left, INPUT);
  pinMode(top_right, INPUT);
  pinMode(bottom_left, INPUT);
  pinMode(bottom_right, INPUT);
////////////////////////////////////Servo Pin Asignment///////////////////////////////
  pan_servo.attach(pan_servo_pin);
  tilt_servo.attach(tilt_servo_pin);

  Serial.begin(9600); //Turns on the serial monitor and set it to 9600 baud
}

void loop() {
//////////////////////////////////////////////////////////////////////////////////////
  int top_left_data = analogRead(top_left); //       Read data from each photoressitor. "analogRead()" -
  int top_right_data = analogRead(top_right);//      is a function in arduino to read analog data from the
  int bottom_left_data = analogRead(bottom_left);//  "A" pin. Data ranges from 0-1023.
  int bottom_right_data = analogRead(bottom_right);
/////////////////////////////////////////////////////////////////////////////////////
  top_quadrant = (top_left_data + top_right_data)/2;//           Averages the value of each quadrant.
  bottom_quadrant = (bottom_left_data + bottom_right_data)/2;//  For exp: Top quadrant value is -
  left_quadrant = (top_left_data + bottom_left_data)/2;//        (top_left_photo + top_right_photo)/2
  right_quadrant = (top_right_data + bottom_right_data)/2;       

/////////////////////////////////////////////////////Tilt Algorithm///////////////////
  if((top_quadrant > bottom_quadrant) &&           
  abs(top_quadrant-bottom_quadrant) > tolerance){// If the top quadrant is "heavier" (Meaning more light is-
    if(tilt_angle - step_angle > 0){//              hitting it), and the difference between them in absolute-
      tilt_angle -= step_angle;//                   value is greater that tolerance, tilt servo up. 
      tilt_servo.write(tilt_angle);//move tilt servo to tilt angle
      Serial.println("Moving Up");//
    }
  }else if((top_quadrant < bottom_quadrant) && //    If the bottom quadrant is "heavier" (Meaning more light is-
  abs(top_quadrant-bottom_quadrant) > tolerance){//  hitting it), and the difference between them in absolute-
    if(tilt_angle + step_angle < 180){//             value is greater than tolerence, tilt servo down.
      tilt_angle += step_angle;
      tilt_servo.write(tilt_angle);//move tilt servo to tilt angle
      Serial.println("Moving Down");
    }
  }
/////////////////////////////////////////////////////////////////////////////////////
  if((right_quadrant > left_quadrant) &&//           If the right quadrant is "heavier" (Meaning more light is-
  abs(right_quadrant-left_quadrant) > tolerance){//  hitting it), and the difference between them in absolute-
    if(pan_angle + step_angle < 180){//              value is greater than tolerance, pan servo right.
      pan_angle += step_angle;
      pan_servo.write(pan_angle); //move pan servo to pan angle
      Serial.println("Moving Right");
    }
  }else if((right_quadrant < left_quadrant) &&//     If the left quadrnt is "heavier" (Meaning more light is-
  abs(right_quadrant-left_quadrant) > tolerance){//  hitting it), and the difference between them in absolute-
    if(pan_angle - step_angle > 0){//                value is greater than tolerance, pan servo left. 
      pan_angle -= step_angle;
      pan_servo.write(pan_angle);//move pan servo to pan angle
      Serial.println("Moving Left");
    }
  }

  delay(cycle_time); //delay the loop by cycle time.
}
