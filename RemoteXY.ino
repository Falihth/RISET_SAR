/*
  File ini digunakan untuk menghidupkan bluetooth dan melakukan kalibrasi kaki-kaki robot melalui aplikasi RemoteXY
*/

#define REMOTEXY_MODE__HARDSERIAL

#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_SERIAL Serial3
#define REMOTEXY_SERIAL_SPEED 9600

// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] = // 174 bytes
    {255, 5, 0, 33, 0, 167, 0, 17, 0, 0, 0, 60, 1, 200, 126, 1, 1, 17, 0, 4,
     36, 54, 168, 10, 160, 2, 94, 4, 36, 36, 168, 10, 160, 2, 94, 4, 36, 20, 168, 10,
     160, 2, 94, 129, 0, 40, 18, 6, 17, 70, 101, 109, 117, 114, 0, 129, 0, 22, 18, 6,
     17, 84, 105, 98, 105, 97, 0, 129, 0, 58, 15, 6, 17, 67, 111, 120, 97, 0, 3, 0,
     84, 106, 20, 134, 2, 26, 129, 6, 108, 4, 6, 17, 49, 0, 67, 22, 22, 16, 6, 4,
     2, 26, 11, 67, 22, 40, 16, 6, 4, 2, 26, 11, 67, 22, 58, 16, 6, 4, 2, 26,
     11, 129, 24, 108, 4, 6, 17, 50, 0, 129, 42, 108, 4, 6, 17, 51, 0, 129, 60, 108,
     4, 6, 17, 52, 0, 129, 78, 108, 4, 6, 17, 53, 0, 129, 96, 108, 4, 6, 17, 54,
     0, 1, 154, 86, 46, 14, 1, 2, 31, 83, 65, 86, 69, 0};

// this structure defines all the variables and events of your control interface
struct
{

  // input variables
  int8_t slider_c1;    // =-100..100 slider position
  int8_t slider_f1;    // =-100..100 slider position
  int8_t slider_t1;    // =-100..100 slider position
  uint8_t select_2;    // =0 if select position A, =1 if position B, =2 if position C, ...
  uint8_t button_save; // =1 if button pressed, else =0

  // output variables
  char text_t[11]; // string UTF8 end zero
  char text_f[11]; // string UTF8 end zero
  char text_c[11]; // string UTF8 end zero

  // other variable
  uint8_t connect_flag; // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

void setupXY()
{
  RemoteXY_Init();
  RemoteXY.slider_c1 = map(calA[1], -15, 15, -100, 100);
  RemoteXY.slider_f1 = map(calB[1], -15, 15, -100, 100);
  RemoteXY.slider_t1 = map(calC[1], -15, 15, -100, 100);
  Serial.println("setupXY ");
}

int legCal = 1, oldLegCal = 0;
// float newLift, newYaw, newSpeed;
// float oldLift, oldYaw, oldSpeed, oldPitch, oldRoll, oldPz, oldPx, oldPy, oldArm, oldGrip;

void loopXY()
{
  RemoteXY_Handler();
  XYst = RemoteXY.connect_flag;
  if (XYst == 1)
  {
    actionXY();
    calibXY();
  }
}

void actionXY()
{
}

void calibXY()
{
  for (int n = 0; n <= 5; n++)
  {
    if (RemoteXY.select_2 == n)
    {
      legCal = n + 1;
      if (legCal != oldLegCal)
      {
        RemoteXY.slider_c1 = mapFloat(calA[legCal], -15, 15, -100, 100);
        RemoteXY.slider_f1 = mapFloat(calB[legCal], -15, 15, -100, 100);
        RemoteXY.slider_t1 = mapFloat(calC[legCal], -15, 15, -100, 100);
        dtostrf(calA[legCal], 0, 1, RemoteXY.text_c);
        dtostrf(calB[legCal], 0, 1, RemoteXY.text_f);
        dtostrf(calC[legCal], 0, 1, RemoteXY.text_t);

        Serial.print("legCal ");
        Serial.println(legCal);
        beep();
        oldLegCal = legCal;

        // calA[legCal] = mapFloat(RemoteXY.slider_c1, -100, 100, -15, 15);
        // calB[legCal] = mapFloat(RemoteXY.slider_f1, -100, 100, -15, 15);
        // calC[legCal] = mapFloat(RemoteXY.slider_t1, -100, 100, -15, 15);
      }
    }
  }
  if (RemoteXY.button_save != 0)
  {
    EEPROM.writeFloat(4 * legCal + 347, calA[legCal]);
    EEPROM.writeFloat(4 * legCal + 371, calB[legCal]);
    EEPROM.writeFloat(4 * legCal + 395, calC[legCal]);
    beep();
  }
  calA[legCal] = mapFloat(RemoteXY.slider_c1, -100, 100, -15, 15);
  calB[legCal] = mapFloat(RemoteXY.slider_f1, -100, 100, -15, 15);
  calC[legCal] = mapFloat(RemoteXY.slider_t1, -100, 100, -15, 15);
}
