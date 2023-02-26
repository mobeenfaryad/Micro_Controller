#include <Servo.h>        // Include Servo Library
#include <NewPing.h>      // Include Newping Library
int L_L = 5;  //limit left motor
int M_L_B = 2; //left motor BACKWARD
int M_L_F = 3; //left motor FORWARD
int M_R_F = 4; //right motr FORWARD
int M_R_B = 7; //right motor BACKWAR
int R_L = 6;  //limit right motor
int  sw = 8;//switch for changing mode
int R_S = A0; //right  sensor
int C_S = A1; //centre sensor
int L_S = A2; //left sensor
int a;
#define TRIGGER_PIN  A3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 250 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 250cm.

Servo servo_motor;  // Servo's name
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
boolean goesForward = false;
int distance = 100;
void setup()
{
pinMode(sw,INPUT);
pinMode(M_R_B, OUTPUT);
pinMode(M_R_F, OUTPUT);
pinMode(M_L_F, OUTPUT);
pinMode(M_L_B, OUTPUT);
pinMode(R_L, OUTPUT);
pinMode(L_L, OUTPUT);
pinMode(L_S, INPUT);
pinMode(C_S, INPUT);
pinMode(R_S, INPUT);

  servo_motor.attach(9);   // Attachs the servo on pin 9 to servo object.
  servo_motor.write(115);   // Set at 115 degrees. 
  delay(2000);              // Wait for 2s.
  distance = readPing();    // Get Ping Distance.
  delay(100);               // Wait for 100ms.
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  
  if(digitalRead (sw)==HIGH)
  {a=1;}
  else 
  if(digitalRead (sw)==LOW)
  {a=0;}
  
  analogWrite(L_L, 100); 
analogWrite(R_L, 92); 
delay(200);
  
}

void loop()
{  
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
if(a==1)
{
if (digitalRead(L_S) == 0)
{
digitalWrite(M_L_B, LOW);
digitalWrite(M_L_F, HIGH);
digitalWrite(M_R_F, LOW);
digitalWrite(M_R_B, LOW); 
}
else
if (digitalRead(R_S) == 0) 
{
digitalWrite(M_L_B, LOW);
digitalWrite(M_L_F, LOW);
digitalWrite(M_R_F, HIGH);
digitalWrite(M_R_B, LOW); 
}
}
else
if(a==0)
{
analogWrite(L_L, 120); 
analogWrite(R_L, 115); 
delay(200);
  if (distance <= 30)
  {
    digitalWrite(M_L_B, LOW);
    digitalWrite(M_L_F, LOW);
    digitalWrite(M_R_F, LOW);
    digitalWrite(M_R_B, LOW);  
    delay(300);
    digitalWrite(M_R_F, LOW);
    digitalWrite(M_R_B, HIGH);
    digitalWrite(M_L_F, LOW);
    digitalWrite(M_L_B, HIGH);
    delay(400);
    digitalWrite(M_L_B, LOW);
    digitalWrite(M_L_F, LOW);
    digitalWrite(M_R_F, LOW);
    digitalWrite(M_R_B, LOW);  
    delay(300);
    distanceRight = lookRight();
    delay(230);
    distanceLeft = lookLeft();
    delay(230);
    if (distanceRight >= distanceLeft)
    {
      digitalWrite(M_R_F, LOW);
      digitalWrite(M_R_B, HIGH);
      digitalWrite(M_L_F, HIGH);
      digitalWrite(M_L_B, LOW);
      delay(410);
      digitalWrite(M_L_B, LOW);
      digitalWrite(M_L_F, LOW);
      digitalWrite(M_R_F, LOW);
      digitalWrite(M_R_B, LOW);  
    }
    else
    if(distanceLeft>distanceRight)
    {
       digitalWrite(M_R_F, HIGH);
       digitalWrite(M_R_B, LOW);
       digitalWrite(M_L_F, LOW);
       digitalWrite(M_L_B, HIGH);
       delay(410);
       digitalWrite(M_L_B, LOW);
       digitalWrite(M_L_F, LOW);
       digitalWrite(M_R_F, LOW);
       digitalWrite(M_R_B, LOW);  
    }
  }
  else
  {
    digitalWrite(M_R_F, HIGH);
    digitalWrite(M_R_B, LOW);
    digitalWrite(M_L_F, HIGH);
    digitalWrite(M_L_B, LOW);
  }
    distance = readPing();
}}


int lookRight()     // Look Right Function for Servo Motor
{  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(70);
  return distance;
}
int lookLeft()      // Look Left Function for Servo Motor 
{
  servo_motor.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int readPing()      // Read Ping Function for Ultrasonic Sensor.
{
  delay(100);                 // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = sonar.ping_cm();   //Send ping, get ping distance in centimeters (cm).
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}
