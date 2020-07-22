//#include <Arduino.h>
//#include <Servo.h>
//int volume1_val = 0;
//int volume2_val = 0;
//float throttle = 0.0;
//float pitch = 0.0;
//Servo servo1;
//Servo servo2;
//Servo servo3;
//Servo brushlessmotor;
//
//float rc = 0.0;
//float a = 0.95;
//
//int limit_servo_command_value(float value) {
//  float limit_max = 1900.0;
//  float limit_min = 1100.0;
//  if (value <= limit_min) {
//    return (int)limit_min;
//  } else if (value >= limit_max) {
//    return (int)limit_max;
//  } else {
//    return (int)value;
//  }
//}
//
//void setup()
//{
//  Serial.begin(9600);
//  servo1.attach(2);
//  servo2.attach(3);
//  servo3.attach(4);
//  brushlessmotor.attach(5);
//
//  brushlessmotor.writeMicroseconds(1000);
//  servo1.writeMicroseconds(1900);
//  servo2.writeMicroseconds(1100);
//  servo3.writeMicroseconds(1100);
//  delay(10000);
//  Serial.println('OK');
//}
//
//void loop()
//{
//  volume1_val = analogRead(A0);
//  volume2_val = analogRead(A1);
//  //  volume2_val=800.0;
//  throttle = a * throttle + (1.0 - a) * (float)volume1_val;
//  pitch = a * pitch + (1.0 - a) * (float)volume2_val;
//  pitch = 600.0;
//  throttle = 600.0;
//
//
//  Serial.println(limit_servo_command_value(2000.0 - pitch));
//  servo1.writeMicroseconds(limit_servo_command_value(2000.0 - pitch));
//  servo2.writeMicroseconds(limit_servo_command_value(pitch + 1000.0));
//  servo3.writeMicroseconds(limit_servo_command_value(pitch + 1000.0));
//  brushlessmotor.writeMicroseconds(limit_servo_command_value(throttle + 1000.0));
//  delay(20);
//}

#include <Arduino.h>
#include <Servo.h>
int volume1_val = 0;
int volume2_val = 0;
float throttle = 0.0;
int throttle_command = 0;
float first_pitch = 330.0;
float pitch = first_pitch;
int servo1_command = 1500;
int servo2_command = 1500;
int servo3_command = 1500;
Servo servo1;
Servo servo2;
Servo servo3;
Servo brushlessmotor;
float rc = 0.0;
float a = 0.95;


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
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  brushlessmotor.attach(5);

  servo1_command = limit_servo_command_value(2000.0 - first_pitch);
  servo2_command = limit_servo_command_value(1000.0 + first_pitch);
  servo3_command = limit_servo_command_value(1000.0 + first_pitch);

  brushlessmotor.writeMicroseconds(1000);
  servo1.writeMicroseconds(servo1_command);
  servo2.writeMicroseconds(servo2_command);
  servo3.writeMicroseconds(servo3_command);
  delay(8000);
}

void loop()
{
  //  volume1_val = analogRead(A0);
  //  volume2_val = analogRead(A1);
  //  throttle = a * throttle + (1.0 - a) * (float)volume1_val;
  //  pitch = a * pitch + (1.0 - a) * (float)volume2_val;

  if ( Serial.available() ) {
    char key;     // 受信データがあるか？
    key = Serial.read();            // 1文字だけ読み込む
    if (key == '+') {
      pitch += 10;
    }
    else if (key == '-') {
      pitch -= 10;
    }
  }


  servo1_command = limit_servo_command_value(2000.0 - pitch);
  servo2_command = limit_servo_command_value(1000.0 + pitch);
  servo3_command = limit_servo_command_value(1000.0 + pitch);
  throttle = 800.0;
  throttle_command = limit_servo_command_value(1000.0 + throttle);

  Serial.print("pitch=");
  Serial.print(pitch);
   Serial.print(',');
  Serial.print(servo1_command);;
  Serial.print(',');
  Serial.print(servo2_command);
  Serial.print(',');
  Serial.println(servo3_command);

  servo1.writeMicroseconds(servo1_command);
  servo2.writeMicroseconds(servo2_command);
  servo3.writeMicroseconds(servo3_command);
  brushlessmotor.writeMicroseconds(throttle_command);
  delay(10);
}



