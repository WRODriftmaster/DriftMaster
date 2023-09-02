#include <Servo.h>

Servo servoMotor;

#define TRIG_PIN 7
#define ECHO_PIN 6



#define IN3_PIN 4
#define IN4_PIN 5

bool IsGreen = false;



int count = 0;

void setup()
{
  
 // Renk sensörü pinleri
  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
  pinMode(OUT_PIN, INPUT);

  // Ultrasonik sensör pinleri
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Motor sürücü pinleri
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  servoMotor.attach(13);

  // UART iletişimi başlat
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

  // Renk değerlerini seri monitöre yazdırma
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

 // Ultrasonik sensörden uzaklık ölçümü yapma
  int distance = getDistance();
  Serial.print("Uzaklık: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 73)
  {
    count++;
    servoMotor.write(180);
    delay(1230);
    servoMotor.write(0);
    delay(1000);
  }
  if (count == 12)
  {
    digitalWrite(IN3_PIN, LOW);
    delay(10000);
    stop();
  }
}

int process_red_value()
{
  digitalWrite(S2_PIN, LOW);
  digitalWrite(S3_PIN, LOW);
  delay(10); // Stabilizasyon için küçük bir gecikme
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}

int process_green_value()
{
  digitalWrite(S2_PIN, HIGH);
  digitalWrite(S3_PIN, HIGH);
  delay(10); // Stabilizasyon için küçük bir gecikme
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}

int process_blue_value()
{
  digitalWrite(S2_PIN, LOW);
  digitalWrite(S3_PIN, HIGH);
  delay(10); // Stabilizasyon için küçük bir gecikme
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

void stop()
{
  digitalWrite(IN3_PIN, LOW);
}
