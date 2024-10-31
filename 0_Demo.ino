/*
  File ini merupakan File demo untuk menjalankan dan testing robot dari pihak penjual.

  Semua fungsi pada file ini dapat dijalankan pada loop program utama!
*/

void demo_01()
{
  switch (runSt)
  {
  case 0:
    if (XYst == 0)
      gripper(170, 180, 0.5); // delay(200);
    stopValue();
    in_speed = 12;
    sensorSt = 0;
    runSt = 1;
    break;
  case 1:
    starValue();
    gripper(40, 70, 1);
    delay(500);
    gripper(170, 180, 0.5); // delay(100);
    totalSteep = 0;
    // sensorSt = 1;
    // runSt = 2;
    runSt = 8;
    // setupCompass();
    break;
  case 20:
    if (totalSteep < 15)
    {
      // arah(0);
      if (totalSteep == 1)
        in_pz = -10;
      if (totalSteep == 2)
        in_pz = -20;

      // if (totalSteep == 12) in_pz = -10;
      // if (totalSteep == 13) in_pz = -5;
      // if (totalSteep == 14) in_pz = 0;
    }
    else
    {
      // runSt = 3;
      // totalSteep = 0;
    }
    break;
  case 2:
    if (totalSteep < 15)
    {
      // arah(0);
      if (totalSteep == 1)
        in_pz = -10;
      if (totalSteep == 2)
        in_pz = -15;

      if (totalSteep == 12)
        in_pz = -10;
      if (totalSteep == 13)
        in_pz = -5;
      if (totalSteep == 14)
        in_pz = 0;
    }
    else
    {
      runSt = 3;
      totalSteep = 0;
    }
    break;
  case 3:
    if (totalSteep < 15)
    {
      // arah(0);
      if (totalSteep == 1)
        in_pz = 10;
      if (totalSteep == 2)
        in_pz = 15;

      if (totalSteep == 12)
        in_pz = 10;
      if (totalSteep == 13)
        in_pz = 5;
      if (totalSteep == 14)
        in_pz = 0;
    }
    else
    {
      runSt = 4;
      totalSteep = 0;
    }
    break;
  case 4:
    if (totalSteep < 10)
    {
      // arah(0);
      if (totalSteep == 1)
        in_px = 5;
      if (totalSteep == 2)
        in_px = 10;
      if (totalSteep == 3)
        in_px = 15;

      if (totalSteep == 7)
        in_px = 10;
      if (totalSteep == 8)
        in_px = 5;
      if (totalSteep == 9)
        in_px = 0;
    }
    else
    {
      runSt = 5;
      totalSteep = 0;
    }
    break;

  case 5:
    if (totalSteep < 15)
    {
      // arah(0);
      if (totalSteep == 1)
        in_px = -5;
      if (totalSteep == 2)
        in_px = -10;
      if (totalSteep == 3)
        in_px = -15;

      if (totalSteep == 2)
        in_px = -10;
      if (totalSteep == 13)
        in_px = -5;
      if (totalSteep == 14)
        in_px = -0;
    }
    else
    {
      runSt = 6;
      totalSteep = 0;
    }
    break;

  case 6:
    gripper(40, 70, 1);
    delay(200);
    gripper(40, 40, 1);
    delay(200);
    gripper(170, 40, 1);
    delay(200);
    runSt = 7;
    break;

  case 7:
    if (totalSteep < 7)
    {
      if (totalSteep == 1)
        in_pz = 5;
      if (totalSteep == 2)
        in_pz = 10;
      if (totalSteep == 3)
        in_pz = 15;

      if (totalSteep == 4)
        in_pz = 10;
      if (totalSteep == 5)
        in_pz = 5;
      if (totalSteep == 6)
        in_pz = 0;
    }
    else
    {
      runSt = 8;
      sensorSt = 0;
      totalSteep = 0;
    }
    break;

  case 8:
    gyroSt = 1;
    in_py = -20;
    in_lift = 30;
    in_speed = 15;
    if (totalSteep < 10)
    {
      getGyro();
      Serial.print("yaw: ");
      Serial.println(yaw);
      in_yaw = -7;
      // if (totalSteep == 1)
      //   in_yaw = -3;
      // if (totalSteep == 2)
      //   in_yaw = -5;
      // if (totalSteep == 3)
      //   in_yaw = -7;
      // if (totalSteep == 7)
      //   in_yaw = -5;
      // if (totalSteep == 8)
      //   in_yaw = -3;
      // if (totalSteep == 9)
      //   in_yaw = 0;
    }
    else if (totalSteep < 20)
    {
      getGyro();
      Serial.print("yaw: ");
      Serial.println(yaw);
      in_yaw = 7;
    }
    else
    {
      totalSteep = 0;
      // setupCompass();
      gripper(40, 20, 1);
      delay(200);
      gripper(40, 70, 1);
      delay(500);
      gripper(170, 180, 1); // delay(200);
      // runSt = 9;
      runSt = 0;
    }
    break;
  case 9:
    sensorSt = 1;
    if (totalSteep >= 50)
    {
      beep();
      beep();
      runSt = 0;
      sensorSt = 0;
    }
    else
      jarak_4_sisi(15, 20);
    break;
  }
}

void demo_02()
{
  switch (runSt)
  {
  case 0:
    if (XYst == 0)
      gripper(170, 180, 1); // delay(200);
    stopValue();
    in_speed = 0.5;
    sensorSt = 0;
    break;

  case 1: // persiapan ambil korban
    starValue();
    gripper(60, 80, 1);
    delay(100);
    in_speed = 5; // kecepatan
    totalSteep = 0;
    sensorSt = 1;
    runSt = 2;
    break;

  case 2: // ambil korban
    sensorSt = 1;
    if (getDistancePing(4) >= 5)
    { // jarak korban
      in_pz = -5;
    }
    else
    {
      in_pz = 0;
      gripper(70, 20, 1);
      delay(500);
      gripper(90, 20, 0.2);
      delay(500);
      totalSteep = 0;
      runSt = 3;
    }
    break;

  case 3: // mundur bbrp langkah setelah nambil korban
    in_speed = 3;
    sensorSt = 0;
    if (totalSteep < 5)
    {
      in_pz = 10;
    }
    else
    {
      totalSteep = 0;
      in_pz = 0;
      gripper(170, 20, 0.5);
      delay(500);
      runSt = 4;
    }
    break;

  case 4: // antar korban
    in_speed = 5;
    if (totalSteep < 5)
    {
      in_yaw = 7;
    }
    else if (totalSteep < 10)
    {
      in_yaw = 0;
      in_pz = -10;
    }
    else
    {
      gripper(70, 20, 0.5);
      delay(500);
      gripper(70, 80, 0.5);
      delay(500);
      runSt = 5;
      in_pz = 0;
      totalSteep = 0;
    }
    break;

  case 5: // mundur bbrp langkah setelah narok korban
    if (totalSteep < 3)
    {
      in_pz = 10;
    }
    else
    {
      in_pz = 0;
      in_speed = 2;
      gripper(170, 180, 1);
      delay(500);
      runSt = 6;
      totalSteep = 0;
    }
    break;

  case 6:
    in_speed = 5;
    if (totalSteep < 5)
    {
      in_yaw = 7;
    }
    else if (totalSteep < 10)
    {
      in_yaw = 0;
      in_pz = -10;
    }
    else
    {
      runSt = 7;
      in_pz = 0;
      totalSteep = 0;
    }
    break;
  }
}

void demo_03()
{ // test compas
  switch (runSt)
  {
  case 0:
    if (XYst == 0)
      gripper(170, 180, 1); // delay(200);
    stopValue();
    in_speed = 0.5;
    sensorSt = 0;
    break;

  case 1:
    starValue();
    totalSteep = 0;
    sensorSt = 1;
    in_speed = 4;
    runSt = 2;
    break;

  case 2:
    softStar();

    break;
  case 3:
    arah(0);
    break;
  }
}

void softStar()
{
  if (totalSteep <= 1)
  {
    in_lift = 5;
    in_speed += 1;
  }
  else if (totalSteep <= 3)
  {
    in_lift = 10;
    in_speed += 1;
    in_pz = -10;
  }
  else if (totalSteep <= 5)
  {
    in_speed += 1;
    in_pz = -15;
  }
  else
  {
    runSt += 1;
    totalSteep = 0;
    startDirection();
  }
}

void strategi_1()
{
  if (runSt == 1)
  {
    starValue();
    steep = 0;
    runSt = 2;
  }

  if (runSt == 2)
  {
    // jarak_4_sisi(10, 20);
    arah(0);
    RUNNING();
  }
}

void jarak_4_sisi(int j1, int j2)
{
  if (j2 < j1 + 5)
    j2 = j1 + 5;
  in_lift = 6;
  if (jarakDepan <= j1)
  {
    in_pz = 15; // Mundur
  }

  if (jarakBelakang <= j1)
  {
    in_pz = -15; // Maju
  }

  if ((jarakBelakang > j2) and (jarakDepan > j2))
  {
    in_pz = 0;
  }

  if (jarakKiri <= j1)
  {
    in_px = 15; // Geser Kanan
  }

  if (jarakKanan <= j1)
  {
    in_px = -15; // Geser Kiri
  }

  if ((jarakKiri > j2) and (jarakKanan > j2))
  {
    in_px = 0;
  }

  if (((jarakKiri > j2) and (jarakKanan > j2)) and ((jarakBelakang > j2) and (jarakDepan > j2)))
  {
    in_speed = 8;
  }
  else
    in_speed = 10;

  if (jarakKorban <= 15)
  {
    gripper(170, 20, 1); //(Arm, Grip, Speed)
  }
  else
  {
    gripper(170, 180, 1); //(Arm, Grip, Speed)
  }
}

void arah(float d)
{
  // d = d + 7.0; //Koreksi arah
  double Pu = -0.15;
  if (compasSt == 1)
  {
    in_yaw = yawPid(d, relativeHeadings, 1.8, 0.5 * Pu, 0.125 * Pu); // belok
  }
  else
  {
    in_yaw = d; // belok
  }
  Serial.print("in_yaw ");
  Serial.println(in_yaw);
}

void demo_04()
{
  switch (runSt)
  {
  case 0:
    if (XYst == 0)
      gripper(170, 180, 0.5); // delay(200);
    stopValue();
    in_speed = 12;
    sensorSt = 0;
    break;
    // case 0:
    //   if (XYst == 0)
    //     gripper(170, 180, 1); // delay(200);
    //   stopValue();
    //   in_speed = 0.5;
    //   sensorSt = 0;
    //   break;

  case 1: // persiapan ambil korban
    starValue();
    gripper(60, 80, 1);
    delay(100);
    in_speed = 5; // kecepatan
    totalSteep = 0;
    sensorSt = 1;
    runSt = 2;
    break;

  case 2: // ambil korban
    sensorSt = 1;
    if (getDistancePing(4) >= 5)
    { // jarak korban
      in_pz = -5;
    }
    else
    {
      in_pz = 0;
      gripper(70, 20, 1);
      delay(500);
      gripper(90, 20, 0.2);
      delay(500);
      totalSteep = 0;
      runSt = 3;
    }
    break;

  case 3: // mundur bbrp langkah setelah ngambil korban
    in_speed = 3;
    sensorSt = 0;
    if (totalSteep < 5)
    {
      in_pz = 10;
    }
    else
    {
      totalSteep = 0;
      in_pz = 0;
      gripper(170, 20, 0.5);
      delay(500);
      runSt = 4;
    }
    break;

  case 4: // antar korban
    in_speed = 5;
    if (totalSteep < 5)
    {
      in_yaw = 7;
    }
    else if (totalSteep < 10)
    {
      in_yaw = 0;
      in_pz = -10;
    }
    else
    {
      gripper(70, 20, 0.5);
      delay(500);
      gripper(70, 80, 0.5);
      delay(500);
      runSt = 5;
      in_pz = 0;
      totalSteep = 0;
    }
    break;

  case 5: // mundur bbrp langkah setelah narok korban
    if (totalSteep < 3)
    {
      in_pz = 10;
    }
    else
    {
      in_pz = 0;
      in_speed = 2;
      gripper(170, 180, 1);
      delay(500);
      runSt = 6;
      totalSteep = 0;
    }
    break;

  case 6:
    in_speed = 5;
    if (totalSteep < 5)
    {
      in_yaw = 7;
    }
    else if (totalSteep < 10)
    {
      in_yaw = 0;
      in_pz = -10;
    }
    else
    {
      runSt = 6;
      totalSteep = 0;
    }

  case 7:
    if (totalSteep < 15)
    {
      // arah(0);
      if (totalSteep == 1)
        in_pz = -10;
      if (totalSteep == 2)
        in_pz = -15;

      if (totalSteep == 12)
        in_pz = -10;
      if (totalSteep == 13)
        in_pz = -5;
      if (totalSteep == 14)
        in_pz = 0;
    }
    else
    {
      runSt = 8;
      totalSteep = 0;
    }
    break;
  }
}