#include <Wire.h>
#include "my_Adafruit_PWMServoDriver.h"
#define SERVO_FREQ 200
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//------lateral_rotor-----
//lateral brushless motor pin
const int lateral_brushless_shiledpin = 1;
//lateral servo motor pin
const int lateral_servo1_shieldpin = 2;
const int lateral_servo2_shieldpin = 3;
const int lateral_servo3_shieldpin = 4;

float throttle = 0.0;
int throttle_command = 0;
float first_pitch = 330.0;
float pitch = first_pitch;
int servo1_command = 1500;
int servo2_command = 1500;
int servo3_command = 1500;

int limit_servo_command_value(float value)
{
  float limit_max = 1900.0;
  float limit_min = 1100.0;
  if (value <= limit_min)
  {
    return (int)limit_min;
  }
  else if (value >= limit_max)
  {
    return (int)limit_max;
  }
  else
  {
    return (int)value;
  }
}

void setup()
{
  Serial.begin(115200);

  servo1_command = limit_servo_command_value(2000.0 - first_pitch);
  servo2_command = limit_servo_command_value(1000.0 + first_pitch);
  servo3_command = limit_servo_command_value(1000.0 + first_pitch);

  pwm.writeMicroseconds(lateral_brushless_shiledpin, 1000.0);
  pwm.writeMicroseconds(lateral_servo1_shieldpin, servo1_command);
  pwm.writeMicroseconds(lateral_servo2_shieldpin, servo2_command);
  pwm.writeMicroseconds(lateral_servo3_shieldpin, servo3_command);
  delay(8000);
}

void loop()
{
  if (Serial.available())
  {
    char key;            // 受信データがあるか？
    key = Serial.read(); // 1文字だけ読み込む
    if (key == '+')
    {
      pitch += 10;
    }
    else if (key == '-')
    {
      pitch -= 10;
    }
  }

  servo1_command = limit_servo_command_value(2000.0 - pitch);
  servo2_command = limit_servo_command_value(1000.0 + pitch);
  servo3_command = limit_servo_command_value(1000.0 + pitch);
  throttle = 1800.0;
  throttle_command = limit_servo_command_value(throttle);

  Serial.print("pitch=");
  Serial.print(pitch);
  Serial.print(',');
  Serial.print(servo1_command);
  Serial.print(',');
  Serial.print(servo2_command);
  Serial.print(',');
  Serial.println(servo3_command);

  pwm.writeMicroseconds(lateral_brushless_shiledpin, throttle_command);
  pwm.writeMicroseconds(lateral_servo1_shieldpin, servo1_command);
  pwm.writeMicroseconds(lateral_servo2_shieldpin, servo2_command);
  pwm.writeMicroseconds(lateral_servo3_shieldpin, servo3_command);
  delay(10);
}