#include <Servo.h>

Servo servoMotor;

#define TRIG_PIN 7
#define ECHO_PIN 6

#define IN3_PIN 4
#define IN4_PIN 5

void setup()
{
 
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  servoMotor.attach(13);

  Serial.begin(9600);

}

void loop()
{
  moveForward();
  int distance = getDistance();
  Serial.print("Uzaklık: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 75)
  {
    servoMotor.write(180);
    delay(1111);
    servoMotor.write(0);
    delay(1000);
  }
  
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

  void turnLeft()
  {
    servoMotor.write(90);
    delay(2000);
  }

  void turnRight()
  {

    servoMotor.write(-120);  
    delay(2000);
  }

void moveForward()
{
 digitalWrite(IN3_PIN, HIGH);
}

