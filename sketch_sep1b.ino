#include <Servo.h>

Servo servoMotor;

#define S0_PIN 8
#define S1_PIN 9
#define S2_PIN 10
#define S3_PIN 11
#define OUT_PIN 12

#define TRIG_PIN 7
#define ECHO_PIN 6

#define IN1_PIN 2
#define IN2_PIN 3
#define IN3_PIN 4
#define IN4_PIN 5

bool isGreenDetected = false;

bool isRedDetected = false;

void setup()
{
  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
  pinMode(OUT_PIN, INPUT);


  servoMotor.attach(13);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop()
{

  moveForward();

  int r, g, b;
  r = process_red_value();
  delay(200);
  g = process_green_value();
  delay(200);
  b = process_blue_value();
  delay(200);

  Serial.print("r = ");
  Serial.print(r);
  Serial.print(" ");
  Serial.print("g = ");
  Serial.print(g);
  Serial.print(" ");
  Serial.print("b = ");
  Serial.print(b);
  Serial.print(" ");
  Serial.println();

  int distance = getDistance();
  Serial.print("Uzaklık: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 20) 
    if (g >= 600 or g <= 670)
    {
      Serial.println("Colour Green");
      bool isGreenDetected = true;
      turnLeft();
      moveForward();
    }
    else if ( r >= 400 or r <= 425)
    {
      Serial.println("Colour Red");
      bool isRedDetected = true;
      turnRight();
      moveForward();
    }
    else if (isRedDetected = false and distance <= 35)
    {
      turnLeft();
      moveForward();
      turnRight();
      moveForward();
    }

  delay(100);
}

int process_red_value()
{
  digitalWrite(S2_PIN, LOW);
  digitalWrite(S3_PIN, LOW);
  delay(10);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}

int process_green_value()
{
  digitalWrite(S2_PIN, HIGH);
  digitalWrite(S3_PIN, HIGH);
  delay(10); 
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}

int process_blue_value()
{
  digitalWrite(S2_PIN, LOW);
  digitalWrite(S3_PIN, HIGH);
  delay(10); 
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}


int getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

void moveForward()
{
 digitalWrite(IN3_PIN, HIGH);
}

void turnLeft()
{
  servoMotor.write(90);
  delay(2000);
}

void turnRight()
{
  servoMotor.write(-120);
  delay(1000);
}