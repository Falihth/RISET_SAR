/*
  File ini berisi perhitungan dari setiap sensor yang ada pada robot.
  Mulai dari sensor Ultrasonik HCSR-04, IR ToF, Compass GY-271 dan Gyro MPU6050.
*/

#include <NewPing.h>
#define nOP 5 // number of ping

int tPin[] = {29, 25, 44, 43, 17};
int ePin[] = {27, 24, 42, 41, 16};
int dMax[] = {80, 80, 50, 50, 50}; // jarak maksimum (mm)

NewPing pinG[nOP] = {
    NewPing(tPin[0], ePin[0], dMax[0]),
    NewPing(tPin[1], ePin[1], dMax[1]),
    NewPing(tPin[2], ePin[2], dMax[2]),
    NewPing(tPin[3], ePin[3], dMax[3]),
    NewPing(tPin[4], ePin[4], dMax[4]),
};

float getDistancePing(byte n)
{
  distancePing[n] = pinG[n].ping() / 57.0;
  if (distancePing[n] == 0)
    distancePing[n] = dMax[n]; /// 10;
  return distancePing[n];
}

//==========================================
#include <QMC5883LCompass.h>
QMC5883LCompass compass;

void setupCompass()
{
  compass.init();
  compass.setCalibrationOffsets(723.00, -471.00, 469.00);
  compass.setCalibrationScales(0.79, 0.80, 2.04);

  //================
  compasSt = 1;
  // delay(100);
  startDirection();
  // delay(100);
  Serial.println("setupCompass ");
}

void getDirection()
{
  // char direction[3];
  compass.read();
  azimuth = compass.getAzimuth();
  bearing = compass.getBearing(azimuth);
  // compass.getDirection(direction, azimuth);
}

void testBacaArah()
{
  getDirection();
  Serial.print("azimuth ");
  Serial.print(azimuth);
  Serial.print(", bearing ");
  Serial.println(bearing);
}

void makeHeadingShadow()
{
  getDirection();
  if (azimuth >= 0)
  {
    azimuth = azimuth;
  }
  else
  {
    azimuth = azimuth + 360;
  }
}

void startDirection()
{
  makeHeadingShadow();
  startHeadings = azimuth;
  int x = startHeadings;
  if (startHeadings != 180)
  {
    if (startHeadings < 180)
    {
      for (int i = 0; i <= 359; i++)
      {
        headingaSadow[i] = 180 - startHeadings + i;
        if (headingaSadow[i] > 359)
          headingaSadow[i] -= 360;
      }
    }
    if (startHeadings >= 180)
    {
      for (int i = 0; i <= 359; i++)
      {
        headingaSadow[i] = 180 - startHeadings + i;
        if (headingaSadow[i] < 0)
          headingaSadow[i] += 360;
      }
    }
  }
  else
  {
    for (int i = 0; i <= 359; i++)
    {
      headingaSadow[i] = i;
    }
  }
  Serial.print("startHeadings ");
  Serial.println(startHeadings); // Serial.print("/");
  Serial.print("bearing ");
  Serial.println(bearing); // Serial.print("/");
}

void getRelativeHeadings()
{
  for (int i = 1; i < 10; i++)
  {
    makeHeadingShadow();
    relativeHeadings += (180 - headingaSadow[azimuth]);
  }
  if (relativeHeadings <= 0)
  {
    relativeHeadings = relativeHeadings / 13.1;
  }
  else
  {
    relativeHeadings = relativeHeadings / 12;
  }
}

//================================================================

float vBat;
byte batSt = 0;
long t02, batAlert = 0;

void teganganBaterai()
{
  pinMode(A2, INPUT);
  t02 = millis();
  vBat = analogRead(A3) * 0.00667; // * calibFacV;
  if (millis() - t02 >= 1000)
  {
    batAlert++;
    if (vBat < 5.8)
    {
      if (batAlert % 5 == 0)
        beep();
    }
    else
    {
      if (vBat <= 6)
      {
        if (batAlert % 10 == 0)
          beep();
      }
    }
  }
  // Serial.print("vBat ");
  // Serial.println(vBat, 1);
}

//=========================================================
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor_L;
VL53L0X sensor_F;
VL53L0X sensor_R;

void setupTof()
{
  pinMode(A13, OUTPUT);
  digitalWrite(A13, LOW);
  pinMode(23, OUTPUT);
  digitalWrite(23, LOW);
  pinMode(26, OUTPUT);
  digitalWrite(26, LOW);
  Wire.begin();
  delay(100);
  digitalWrite(A13, HIGH);
  delay(150);
  sensor_L.init(true);
  delay(100);
  sensor_L.setAddress((uint8_t)01);
  delay(100);

  digitalWrite(23, HIGH);
  delay(150);
  sensor_F.init(true);
  delay(100);
  sensor_F.setAddress((uint8_t)02);

  digitalWrite(26, HIGH);
  delay(150);
  sensor_R.init(true);
  delay(100);
  sensor_R.setAddress((uint8_t)03);
  delay(100);

  sensor_L.startContinuous();
  sensor_F.startContinuous();
  sensor_R.startContinuous();
  tofSt = 1;
  Serial.println("setupTof ");
}

float getDistanceTof(byte n)
{
  if (tofSt == 1)
  {
    if (n == 2)
      distanceTof[n] = sensor_R.readRangeContinuousMillimeters() / float(10);
    if (n == 1)
      distanceTof[n] = sensor_F.readRangeContinuousMillimeters() / float(10);
    if (n == 0)
      distanceTof[n] = sensor_L.readRangeContinuousMillimeters() / float(10);
    return distanceTof[n];
  }
}

void loopTof()
{
  float TOF_L = sensor_L.readRangeContinuousMillimeters() / float(10);
  // float TOF_F = sensor_F.readRangeContinuousMillimeters() / float(10);
  float TOF_R = sensor_R.readRangeContinuousMillimeters() / float(10);

  Serial.print("jarak_L ");
  Serial.print(TOF_L, 1);
  // Serial.print("jarak_F ");
  // Serial.println(TOF_F, 1);
  Serial.print(", jarak_R ");
  Serial.println(TOF_R, 1);
  Serial.println();
  // delay(500);
}

//=========================================================
#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

void setupGyro()
{
  Wire.begin();

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  if (status != 0)
  {
    Serial.println("Failed to connect to Mpu6050.");
  }

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accel

  // gyroSt = 1;
  Serial.println("setupGyro");
}

void loopGyro()
{
  // mpu.update();
  Serial.println("---------------------------------------");
  Serial.print("X : ");
  Serial.print(mpu.getAngleX());
  Serial.print(", Y : ");
  Serial.print(mpu.getAngleY());
  Serial.print(", Z : ");
  Serial.println(mpu.getAngleZ());
  delay(500);
}

void getGyro()
{
  mpu.update();
  yaw = mpu.getAngleZ();
}

// void getGyro()
// {
//   if (gyroSt == 1)
//   {
//     mpu.update();
//     roll = mpu.getAngleX();
//     pitch = mpu.getAngleY();
//     yaw = mpu.getAngleZ();
//   }
// }
