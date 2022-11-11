/* 본 스케치는 arduino.cc의 JoghChi님이 작성하신 스케치입니다.*/

#include<Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial bt(3, 4);

const int MPU = 0x68; //MPU 6050 의 I2C 기본 주소
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ; //TMP-온도, GYX,GYY, GYZ - 기울기값
int16_t mapAcx, mapAcY ; // map 을 이용한 값 보정 변수

void setup() {
  Wire.begin();      //Wire 라이브러리 초기화
  Wire.beginTransmission(MPU); //MPU로 데이터 전송 시작
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     //MPU-6050 시작 모드로
  Wire.endTransmission(true);

  Serial.begin(9600);
  bt.begin(9600);
}

void mpu() {
  Wire.beginTransmission(MPU);    //데이터 전송시작
  Wire.write(0x3B);               // register 0x3B (ACCEL_XOUT_H), 큐에 데이터 기록
  Wire.endTransmission(false);    //연결유지
  Wire.requestFrom(MPU, 14, true); //MPU에 데이터 요청
  
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
}


void mpu_Bluetooth() {
  

  bt.print("X : ");
  bt.print(AcX);
  bt.print(",");
  bt.print(" Y : ");
  bt.print(AcY);
  bt.println();
  //코드 파일을 잃어버려서 복구중
}


void loop() {

  mpu();
  mpu_Bluetooth();
  delay (1000);
}
