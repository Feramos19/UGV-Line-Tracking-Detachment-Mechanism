// Black Line Follower - With Drop Down Servo Mec
#include <Servo.h>   
Servo myservo;   
int servo = 12;      // Servo Pin Connected to Pin 11 
int Right_IR=8;      //Right sensor
int Left_IR=10;      //Left sensor
// Angle Positions for Servo
float Locked_angle = 110;    // Locked in position
float Release_angle = 40;
#define RIN1 3       // Right Motor 
#define RIN2 2
#define LIN1 5       // Left Motor
#define LIN2 4

void setup() {
  // Start Serial Monitor
  Serial.begin(9600);
  // Attach Servo
  myservo.attach(servo);   
  // Setup pin modes
  pinMode(servo, OUTPUT);         // Servo
  pinMode(Right_IR,INPUT);        // Right Sensor Input
  pinMode(Left_IR,INPUT);         // Left Sensor Input
  pinMode(RIN1,OUTPUT);           // Motor 1
  pinMode(RIN2,OUTPUT);           // Motor 1
  pinMode(LIN1,OUTPUT);           // Motor 2
  pinMode(LIN2,OUTPUT);           // Motor 2
  // Lock Servo
  myservo.write(Locked_angle);  
  // Delay for 30 seconds to take off
  delay(3000);
}
 
void loop() {
  //Read IRs States:
  int RightIR_State = digitalRead(Right_IR);
  int LeftIR_State = digitalRead(Left_IR);
 
  // 1. If both IR sensors are on white (zero), then move straight
  if (RightIR_State == LOW && LeftIR_State == LOW){     
    // Read Servo State
    int  servoState = myservo.read();
    // Unlock Servo
    if (servoState>90){
      delay(2000);                      // Delay for 2s, so that we can land
      myservo.write(Release_angle);     // Release 
      delay(2000);                     // Delay for 10s, gives time to detach drone
      //myservo.detach();                 // Disconnect Servo    

      // MAYBE ADD SOMETHING FOR UGV TO FIX ITSELF IF LANDED AT BAD POSITION
      }
    
    // Move right motor forward    
    digitalWrite(RIN1, LOW);
    digitalWrite(RIN2, HIGH);
    // Move left motor forward
    digitalWrite(LIN1, LOW);
    digitalWrite(LIN2, HIGH);    
    }
    else if ((RightIR_State == HIGH && LeftIR_State == LOW)){ //If right side sensor is on black, make a right
    // Read Servo State
    int  servoState = myservo.read();
    //Unlock Servo
    if (servoState>90){
      delay(2000);                      // Delay for 2s, so that we can land
      myservo.write(Release_angle);     // Release 
      delay(2000);                     // Delay for 10s, gives time to detach drone
      //myservo.detach();                 // Disconnect Servo    

      // MAYBE ADD SOMETHING FOR UGV TO FIX ITSELF IF LANDED AT BAD POSITION
      }

    // Make a right: - Left forward / Right backwards
    digitalWrite(RIN1, HIGH);
    digitalWrite(RIN2, LOW);
    digitalWrite(LIN1, LOW);
    digitalWrite(LIN2, HIGH); 
    }
    else if ((RightIR_State == LOW && LeftIR_State == HIGH)){ //If left side sensor is on black, make a left
    // Read Servo State
    int  servoState = myservo.read();
    // Unlock Servo
    if (servoState>90){
      delay(2000);                      // Delay for 2s, so that we can land
      myservo.write(Release_angle);     // Release 
      delay(2000);                     // Delay for 10s, gives time to detach drone
      //myservo.detach();                 // Disconnect Servo    

      // MAYBE ADD SOMETHING FOR UGV TO FIX ITSELF IF LANDED AT BAD POSITION
      }
    
    // Make a right: - Left backwards / Right forwards
    digitalWrite(RIN1, LOW);
    digitalWrite(RIN2, HIGH);
    digitalWrite(LIN1, HIGH);
    digitalWrite(LIN2, LOW); 
    }
    else {
   
    // Turn off motors
    digitalWrite(RIN1, LOW);
    digitalWrite(RIN2, LOW);
    digitalWrite(LIN1, LOW);
    digitalWrite(LIN2, LOW);     
    }
}
