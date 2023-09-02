#include <Servo.h>

Servo servoMotor;

#define TRIG_PIN 7
#define ECHO_PIN 6

#define IN3_PIN 4
#define IN4_PIN 5

int count = 0;

void setup()
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  servoMotor.attach(13);

}

void loop()
{

  moveForward();

  int distance = getDistance();
  Serial.print("Uzaklık: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 70)
  {
    count++;
    servoMotor.write(180);
  }
  if (count == 12)
  {
    digitalWrite(IN3_PIN, LOW);
    delay(10000);
    stop();
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
void moveForward()
{
 digitalWrite(IN3_PIN, HIGH);
}

void stop()
{
  digitalWrite(IN3_PIN, LOW);
}
