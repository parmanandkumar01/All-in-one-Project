#include <Servo.h>

#include "AFMotor.h"

#include <NewPing.h>
//----------------------------------------
//        define upper ir sensor for huamn follower and  monitoring data
//--------------------------------------

    #define  RIGHT 2    // connect a ir sensor of right uper side of car
    #define  LEFT A2    // connect a ir sensor of left upper side  of car

 //  for monitoring data
        int flag1 = 0;
        int flag2 = 0;
        int timer1;
        int timer2;
        int Speedm;
        float Time;
         int distancem=5 ;
//----------------------------------------------
//             down ir sensor for line follower
//-----------------------------------------------------------------
    #define Dleft A5   // connect a ir sensor of left downward side  of car
    #define Dmiddle A4  // connect a ir sensor of left downward  side  of car
    #define Dright  A3  // connect a ir sensor of left downward  side  of car

//----------------------------------------------
 //            ultrasonic sensor data explain
 //-------------------------------------------            
      #define TRIGGER_PIN  A0  // ultrasonic sensor can be operate using a single pin 
      #define ECHO_PIN     A1 // so connect both pin of of sensor on single of arduino
     
      int distance_L, distance_F, distance_R;
      unsigned  distance; // this is use to normally read distance

      NewPing sonar(TRIGGER_PIN, ECHO_PIN);
//-------------------------------------------------
//            for control servo motor data explain
//-------------------------------------------------
       Servo myservo;
       int pos =0;
//-----------------------------------------
//        for l293d motor driver controll 
//----------------------------------------
      const int MOTOR_1 = 1; 
      const int MOTOR_2 = 2; 
      const int MOTOR_3 = 3; 
      const int MOTOR_4 = 4; 
      int LSpeed = 0; // controll m1 and m2 speed of motor which is left side 
      int RSpeed = 0; // controll m2 and m3 speed of motor which is right side
      AF_DCMotor motor1(MOTOR_1, MOTOR12_64KHZ); // create motor object, 64KHz pwm
      AF_DCMotor motor2(MOTOR_2, MOTOR12_64KHZ); // create motor object, 64KHz pwm
      AF_DCMotor motor3(MOTOR_3, MOTOR12_64KHZ); // create motor object, 64KHz pwm
      AF_DCMotor motor4(MOTOR_4, MOTOR12_64KHZ); // create motor object, 64KHz pwm

//-----------------------------------------------------
//     for incoming all different data from android
//----------------------------------------------------
        int mode;
        int xAxis =140, yAxis=140;
     
      
        int function;


void setup() {

 
// intial possition of servo motor is set 
       myservo.attach(10); // servo motor attach at pin 10
       for(pos = 90; pos <= 180; pos += 1){
      myservo.write(pos);
      delay(15);
      }
       
      for(pos = 180; pos >= 0; pos-= 1) {
      myservo.write(pos);
      delay(15);
      }
      
      for(pos = 0; pos<=90; pos += 1) {
      myservo.write(pos);
      delay(15);
       }
  
// for reading value from ultrasonic sensor we have to explain pin mode
           pinMode (TRIGGER_PIN, OUTPUT);
           pinMode (ECHO_PIN, INPUT );
// define pine mode of upper ir sensor

           pinMode(RIGHT, INPUT);
           pinMode(LEFT, INPUT);
// define for line follower ir sensor
           pinMode(Dleft, INPUT);pinMode(Dmiddle, INPUT);
           pinMode(Dright , INPUT);


 // inital speed of all dc motor is set 0
          motor1.setSpeed(LSpeed);   // set the motor speed to 0-255
          motor2.setSpeed(LSpeed);
          motor3.setSpeed(RSpeed);
          motor4.setSpeed(RSpeed);  
// serial monitor is initalize
          Serial.begin(9600);
          delay(500); 
} // void setup end colon


void loop(){   

//if some date is sent, reads it and saves in state
           while(Serial.available() > 0){       
             xAxis= Serial.read(); // use primary for controll all data 
             delay(10); 
             yAxis= Serial.read(); // use for controll joystic
           }delay(10); 

      //Receive data for mode selection that is in the range of 1 to 10
           if(xAxis <= 10){mode = xAxis;  } 
       
      // Receive the speed that is send by controller in the range of 201 to 256 
            else if(xAxis>220){int sp = xAxis; LSpeed = RSpeed = map(sp,221,255,130,255);


          motor1.setSpeed(LSpeed);   // set the motor speed to 0-255
          motor2.setSpeed(LSpeed);
          motor3.setSpeed(RSpeed);
          motor4.setSpeed(RSpeed);
         }
     
      //Receive function of different controlling method
            else if(xAxis>10 && xAxis<60 ){ function = xAxis;}  ;










                                                       
                                                   
 // select different mode and working operation

 if (mode==1){
  
//===============================================================================
//                                    joistic mode
//=============================================================================== 
        
        if (xAxis > 130 && xAxis <150 && yAxis > 130 && yAxis <150){Stop();}
        
        
   if (yAxis > 130 && yAxis <150){    
              
              if (xAxis < 130){turnLeft();
              LSpeed = map(xAxis, 130, 60, 130, 255);
              RSpeed= map(xAxis, 130, 60, 130, 255);    
              }
              
              if (xAxis > 150) {turnRight();
              LSpeed = map(xAxis, 150, 220, 130, 255);
              RSpeed = map(xAxis, 150, 220, 130, 255); 
              }
              
              }
 else if (xAxis > 130 && xAxis <150){
        
                        if (yAxis < 130){forword();
                       LSpeed = map(yAxis, 130, 60, 130, 255);
                       RSpeed = map(yAxis, 130, 60, 130, 255);
                         }
                        if (yAxis > 150){backword();
                        LSpeed = map(yAxis, 150, 220, 130, 255);
                       RSpeed = map(yAxis, 150, 220, 130, 255);
                        }
                         }

         
 else{
        
        if (yAxis < 130){forword();}
        if (yAxis > 150){backword();}
        
        if (xAxis < 130){
        LSpeed = map(xAxis, 130, 60, 255, 130);
        RSpeed = 255; 
         }
         
        if (xAxis > 150){
        LSpeed = 255;
       RSpeed = map(xAxis, 150, 220, 255, 130); 
          } 
         } 
         
      motor1.setSpeed(LSpeed);        
      motor2.setSpeed(LSpeed);
      motor3.setSpeed(RSpeed);
      motor4.setSpeed(RSpeed);

Serial.print(LSpeed);Serial.println(RSpeed);
 }

else if ( mode==2){


//===============================================================================
//   switch Control//accelerometer control// voice control//four button Command
//===============================================================================   
     if(function == 11){forword(); }  // if the function is '11' the DC motor will go forward
else if(function == 12){backword();}  // if the function is '12' the motor will Reverse
else if(function == 13){turnLeft();}  // if the function is '13' the motor will turn left
else if(function == 14){turnRight();} // if the function is '14' the motor will turn right
else if(function == 15){Stop(); }     // if the function is '15' the motor will Stop
/////////////////////////////////////END\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//===============================================================================
//                  Remain two  Voice Control Command
//===============================================================================
else if(function == 16){turnLeft();  delay(400);  function = 15;}
else if(function == 17){turnRight(); delay(400);  function = 15;}
}

/////////////////////////////////////END\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//--------------------------------------------------------------------------------------------------------
//                                          obstakel avoiding robot
//------------------------------------------------------------------------------------------------------
 else if (mode==3){
delay(10);
distance_F = sonar.ping_cm(); // read distance from ultra sonic sensor
delay(10);
 if (distance_F > 35){ Serial.println("210"); Serial.print(":");Serial.println(distance_F); LSpeed = RSpeed=150;forword();  delay(200);}       // turn the motor forward with 180 speed

 
 // if not then check condition
  if (distance_F >= 2  && distance_F <= 35  ){ different_direction_distance();}
   
      motor1.setSpeed(LSpeed);        
      motor2.setSpeed(LSpeed);
      motor3.setSpeed(RSpeed);
      motor4.setSpeed(RSpeed);

     
 }
  ///////////////////////////////////////////////////end//////////////////////////////////////////////////
//------------------------------------------------------------------------------------------------------------
//                                        monitored object
//-------------------------------------------------------------------------------------------------------------
else if(mode==4){


if(digitalRead (LEFT) == LOW && digitalRead (RIGHT) == HIGH && flag1==0){Serial.print("207");Serial.print(":"); Serial.print("0") ;timer1 = millis(); flag1=1;}

if(digitalRead (RIGHT) == LOW && digitalRead (LEFT) == HIGH && flag2==0){Serial.print("208");Serial.print(":"); Serial.print("0"); timer2 = millis();flag2=1;}

if (flag1==1 && flag2==1){   
     if(timer1 > timer2){Time = timer1 - timer2;}
 if(timer2 > timer1){Time = timer2 - timer1;}
 Time=Time/1000;//convert millisecond to second
 Speedm=(distancem/Time);//v=d/t
 Speedm=Speedm*3600;//multiply by seconds per hr
 Speedm=Speedm/1000;//division by meters per Km
 if (Speedm>0 && Speedm<200) {Serial.print("0");Serial.print(Speedm); Serial.print(":"); }  
delay(1000);
Serial.print("209");Serial.print(":");Serial.print("0") ;
flag2=0;
flag1=0;
timer1=0;
timer2=0;
}

}
//--------------------------------------------------------------------------------------------------------
//                                            human follower
//------------------------------------------------------------------------------------------------------
 // for resettion purpose all the previous condition make sure zero
else if(mode==5){

 
// speed of both motor zero
 myservo.write(90); // set the ulrasonic sensor in forward direction
int Right_Value = digitalRead(RIGHT);
int Left_Value  = digitalRead(LEFT);
distance = sonar.ping_cm();
    if((Right_Value==1) && (distance>=10 && distance<=30)&&(Left_Value==1)){LSpeed = RSpeed=200;  forword();}
else if((Right_Value==0) && (Left_Value==1)){ LSpeed = RSpeed=230; turnRight();}
else if((Right_Value==1) && (Left_Value==0)){LSpeed = RSpeed=230; turnLeft();}
else if((Right_Value==1) && (Left_Value==1)){ LSpeed = RSpeed=0;Stop();}
else if(distance > 5 && distance < 10){LSpeed = RSpeed=0; Stop();}
else if(distance < 5){LSpeed = RSpeed=230; backword();}

  
      motor1.setSpeed(LSpeed);        
      motor2.setSpeed(LSpeed);
      motor3.setSpeed(RSpeed);
      motor4.setSpeed(RSpeed);


      
}

//---------------------------------------------------------------------------------------
//                                line follower
//-----------------------------------------------------------------------------------------

else if(mode==6){
 
if ( (digitalRead(Dleft) == HIGH)&&(digitalRead(Dmiddle) == HIGH)&&(digitalRead(Dright) == HIGH)){LSpeed = RSpeed=0 ; Stop();}  // no path is found
else if ((digitalRead(Dleft) ==LOW)&&(digitalRead(Dmiddle) == LOW)&&(digitalRead(Dright) ==LOW)){LSpeed = RSpeed=0 ; Stop(); }   //path finish


 else if ((digitalRead(Dleft) == LOW)&&(digitalRead(Dmiddle) == HIGH)&&(digitalRead(Dright) == LOW)){LSpeed = RSpeed=150 ; forword();}  // fo go ahead
 
 else if ((digitalRead(Dleft) == HIGH)&&(digitalRead(Dmiddle) == LOW)&&(digitalRead(Dright) == LOW)){LSpeed = RSpeed=150 ; turnLeft();}  //sharp left
else if ((digitalRead(Dleft) == HIGH)&&(digitalRead(Dmiddle) ==HIGH)&&(digitalRead(Dright) == HIGH)) {LSpeed = RSpeed=150 ; turnLeft();}  // soft left
 
else if ((digitalRead(Dleft) ==LOW)&&(digitalRead(Dmiddle) == LOW)&&(digitalRead(Dright) == HIGH)){LSpeed = RSpeed=150 ; turnRight();} // sharp right
else if ((digitalRead(Dleft) == LOW)&&(digitalRead(Dmiddle) ==HIGH)&&(digitalRead(Dright) == HIGH)){LSpeed = RSpeed=150 ; turnRight();} //soft right
 


      motor1.setSpeed(LSpeed);        
      motor2.setSpeed(LSpeed);
      motor3.setSpeed(RSpeed);
      motor4.setSpeed(RSpeed);

}

 
 //---------------------------------------------------------------------------------------------------------------------------------------
 //                                 default mode reset mode
 //-------------------------------------------------------------------------------------------------------------------------------------
 
else if(mode==10){
 myservo.write(90);
   Stop();
 xAxis=125;yAxis=125;
 LSpeed = RSpeed=0;
 motor1.setSpeed(LSpeed);        
      motor2.setSpeed(LSpeed);
      motor3.setSpeed(RSpeed);
      motor4.setSpeed(RSpeed);
 Stop() ;
}


 
 // this syntax is switch case
 
} // this syntax of void loop







 void different_direction_distance(){
    
    LSpeed = RSpeed=0;
    motor1.setSpeed(LSpeed);        
      motor2.setSpeed(LSpeed);
      motor3.setSpeed(RSpeed);
      motor4.setSpeed(RSpeed);
   Stop();
   // stop the motor and check distance
   
    myservo.write(0);
    delay(300);
    distance_L = sonar.ping_cm(); Serial.print("211"); Serial.print(":");Serial.print( distance_L);    
  
    myservo.write(170);
    delay(500);
    distance_R = sonar.ping_cm();Serial.print("212"); Serial.print(":");Serial.print( distance_R); 

  
    myservo.write(90);
    delay(300);
   compareDistance();
   
}

void compareDistance(){
  if (distance_L > distance_R){turnRight();
  // turn it on going left
LSpeed = RSpeed=255;
    motor1.setSpeed(LSpeed);        
      motor2.setSpeed(LSpeed);
      motor3.setSpeed(RSpeed);
      motor4.setSpeed(RSpeed);
  
 delay(500);
  }
  else if (distance_R > distance_L){turnLeft();
    // the other right
  LSpeed = RSpeed=255;
    motor1.setSpeed(LSpeed);        
      motor2.setSpeed(LSpeed);
      motor3.setSpeed(RSpeed);
      motor4.setSpeed(RSpeed);
  delay(500);
  }
  else{
  backword();     // the other way 
  LSpeed = RSpeed=250;
    motor1.setSpeed(LSpeed);        
      motor2.setSpeed(LSpeed);
      motor3.setSpeed(RSpeed);
      motor4.setSpeed(RSpeed);
   delay(300);

   // after getting practical change this case
 turnLeft(); // turn it on going left
LSpeed = RSpeed=250;
    motor1.setSpeed(LSpeed);        
      motor2.setSpeed(LSpeed);
      motor3.setSpeed(RSpeed);
      motor4.setSpeed(RSpeed);
 
   delay(500);
  }

  
}



void forword(){
motor1.run(FORWARD); // turn it on going forward
motor2.run(FORWARD); 
motor3.run(FORWARD); 
motor4.run(FORWARD);
}

void backword(){
motor1.run(BACKWARD); // the other way
motor2.run(BACKWARD);
motor3.run(BACKWARD); 
motor4.run(BACKWARD); 
}

void turnRight(){
motor1.run(FORWARD); // the other right
motor2.run(FORWARD); 
motor3.run(BACKWARD); 
motor4.run(BACKWARD);
}

void turnLeft(){
motor1.run(BACKWARD); // turn it on going left
motor2.run(BACKWARD);
motor3.run(FORWARD); 
motor4.run(FORWARD); 
}

void Stop(){
 motor1.run(RELEASE); // stopped
 motor2.run(RELEASE);
 motor3.run(RELEASE);
 motor4.run(RELEASE);
}
