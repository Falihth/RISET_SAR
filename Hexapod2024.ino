#include <1_variable.h>

/*
  Hexapod_Kinematik_H04_03a July 2021
  Hexapod_Kinematik_H04_2022 Mei-2022
  Hexapod_Kinematik_H05a_2022 Dec-2022

  Inspiration from OscarLiang.com
  https://oscarliang.com/inverse-kinematics-implementation-hexapod-robots/

  Hexapod_Kinematik_H06_2023 April 2023
  Hexapod_Kinematik_H06_2023 Edited Jan 2024
  by Saiful Jamaan, P. hD

  Ini adalah File utama yang menjalankan setiap fungsi untuk menjalankan robot hexapod.
  Fokus utama pada file ini adalah menjalankan fungsi-fungsi pada void loop()
*/


int runSt = 0;
byte printSt = 1;
float jarakKiri, jarakKanan, jarakDepan, jarakBelakang, jarakGrip, jarakKorban;
int pushButtonPin = 36;
byte pushSt = 0;
byte tofSt = 0;
byte pingSt = 0;

unsigned long timer = 0;
const int timePickUp = 10000;
byte pickUp = 0;

void setup()
{
  beep();
  Serial.begin(115200);
  Serial3.begin(9600);
  Serial.println("Hexapod KRSRI 2024");
  pinMode(pushButtonPin, INPUT_PULLUP);
  // setupXY(); // remote by Android (Uncomment untuk melakukan kalibrasi dengan aplikasi android RemoteXY)
  EEPROM_ARR(2);
  setupTof();
  setupGyro();
  setupCompass();
  initialisai();
  activeServo();
  beep();
  beep();
  Serial.println("Setup Ok");
  Serial.println();
}

void loop()
{
  pushButton();
  // Uncomment line dibawah ini untuk menjalankan demo robot (Uncomment salah satu saja!)
  // demo_01(); // Test demo run
  // demo_02(); // Test demo gripper
  // demo_03(); // Test demo Gyro
  // demo_04();

  // lombaCompass(); // Riset robot hanya menggunakan sensor kompas
  // lombaGyro(); // Riset robot hanya menggunakan sensor Gyro
  // langsungFinish(); // Strategi langsung finish dengan menghiraukan semua korban
  New();

  if (runSt == 0)
  {
    testSensor();
    loopGyro();
  }
  // daser(); // Serial Communication
  // loopXY(); // setting by Android (Uncomment untuk melakukan kalibrasi dengan aplikasi android RemoteXY)
  RUNNING();
}

void RUNNING()
{
  readSensor();
  getGyro();
  variableLimit();
  if (steep < in_nOS)
  {
    steep++;
    delay(in_delay);
  }
  else
  {
    steep = 1;
    delay(in_delay);
    totalSteep++;
  }
  for (byte fn = 1; fn <= 6; fn++)
  {
    dinamicMovement(fn);
  }
}

float rRH = 0;
int per = 1;
void readSensor()
{
  if (sensorSt == 1)
  {
    if (steep == 3)
    {
      jarakKorban = getDistancePing(4);
    }
    if (steep == 6)
    {
      jarakKanan = getDistanceTof(0);
    }
    if (steep == 6)
    {
      jarakDepan = getDistancePing(1);
    }
    if (steep == 9)
    {
      jarakKiri = getDistanceTof(2);
    }
    if (steep == 12)
    {
      jarakBelakang = getDistancePing(0);
    }

    if (compasSt == 1)
    {
      if (steep > 1)
      {
        getRelativeHeadings();
        rRH += relativeHeadings;
        per++;
      }
      else
      {
        teganganBaterai();
        relativeHeadings = (rRH / per); // + 15;
        rRH = 0;
        per = 1;
        Serial.print("rHs ");
        Serial.println(relativeHeadings, 1);
      }
    }
  }
}

void starValue()
{
  in_dirrection = 0; // arah belok
  in_px = 0;         // kiri kanan
  // in_py = 5;         // tinggi body (ground clearence)
  in_py = -10;
  in_pz = 0;    // maju mundur
  in_pitch = 0; // angkat kiri kanan
  in_roll = 0;  // angkat depan belakang
  in_yaw = 0;   // putar kiri kanan
  // in_lift = 16; // angkat kaki saat melangkah
  in_lift = 20;
  in_speed = 5; // kecepatan
  in_delay = 0;
  in_gama = 45;
}

void stopValue()
{
  in_px = 0;    // kiri kanan
  in_py = 0;    // atas bawah
  in_pz = 0;    // maju mundur
  in_pitch = 0; // putar kiri kanan
  in_roll = 0;  // putar muka belakang
  in_yaw = 0;   // putar kiri kanan
  in_lift = 0;  // angkat kaki
}

long oldMillis, countStart; //
void pushButton()
{
  if (digitalRead(pushButtonPin) == LOW)
  {
    if (pushSt == 0)
    {
      if (runSt == 0)
      {
        runSt = 10;
        setupCompass();
        countStart = 2;
      }
      else
      {
        runSt = 0;
        beep();
        beep();
      }
      pushSt = 1;
    }
    delay(100);
  }
  else
  {
    pushSt = 0;
  }

  if (runSt == 10)
  {
    if (millis() - oldMillis >= 1000)
    {
      oldMillis = millis();
      countStart--;
      beep();
      if (pushSt == 0)
      {
        if (countStart == 0)
          runSt = 1;
      }
      else
      {
        if (countStart == 0)
        {
          stopValue();
          for (byte fn = 1; fn <= 6; fn++)
          {
            dinamicMovement(fn);
          }
          runSt = 0;
          steep = 0;
        }
      }
      Serial.print("runSt ");
      Serial.println(runSt);
    }
  }
}

void testSensor()
{
  if (tofSt == 1)
  {
    Serial.print("jarak_L ");
    Serial.print(getDistanceTof(2), 1);
    Serial.print(", R ");
    Serial.print(getDistanceTof(0), 1);
    Serial.print(", B ");
    Serial.print(getDistancePing(0), 1);
    Serial.print(", F ");
    Serial.print(getDistancePing(1), 1);
    Serial.print(", G ");
    Serial.print(getDistancePing(4), 1);
  }

  if (compasSt == 1)
  {
    getRelativeHeadings();
    Serial.print(", Heading ");
    Serial.println(relativeHeadings);
    testBacaArah();
  }
  Serial.println();
  delay(500);
}


//untuk tes setiap kaki robot!!!
void moveSingleLeg(byte legNumber) {
    
    if (legNumber < 1 || legNumber > 6) return;
    in_dirrection = 0;
    in_px = 0;        
    in_py = -4;         
    in_pz = -15;        
    in_pitch = 0;     
    in_roll = 0;      
    in_yaw = 0;        
    in_lift = 20;      
    in_speed = 20;      

    dinamicMovement(legNumber);
    delay(in_delay);
}

//untuk tes setiap kaki robot!!!
void balik(byte legNumber) {
    if (legNumber < 1 || legNumber > 6) return;
    in_px = 0;    
    in_py = 0;    
    in_pz = 0;    
    in_pitch = 0; 
    in_roll = 0;  
    in_yaw = 0;   
    in_lift = 0;  

    dinamicMovement(legNumber);

    delay(in_delay);
}

//untuk tes setiap kaki robot!!!
void moveSingleLeg1(byte legNumber) {
    
    if (legNumber < 1 || legNumber > 6) return;

    in_dirrection = 0; 
    in_px = 0;         
    in_py = 4;         
    in_pz = 15;         
    in_pitch = 0;      
    in_roll = 0;       
    in_yaw = 0;        
    in_lift = 20;      
    in_speed = 20;      

    dinamicMovement(legNumber);
    delay(in_delay);
}

