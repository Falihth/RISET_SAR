/*
  Riset robot yang kami lakukan hanya dengan menggunakan sensor Compass GY-271
  sebagai penunjuk arah robot dalam melewati rintangan.
*/

void lombaCompass()
{
  switch (runSt)
  {
  case 0: // Diam
    Serial.println("Stop");
    if (XYst == 0)
      gripper(170, 170, 0.5); // delay(200);
    stopValue();
    in_speed = 12;
    sensorSt = 0;
    break;

  case 1: // Jalan ditempat
    Serial.println("Jalan ditempat");
    starValue();
    startDirection();
    totalSteep = 0;
    // Serial.print("L ");
    // Serial.print(getDistanceTof(2), 1);
    // Serial.print(", R ");
    // Serial.print(getDistanceTof(0), 1);
    // Serial.print(", B ");
    // Serial.print(getDistancePing(0), 1);
    // Serial.print(", F ");
    // Serial.print(getDistancePing(1), 1);
    // Serial.print(", G ");
    // Serial.println(getDistancePing(4), 1);
    jarakDepan = getDistancePing(1);
    jarakBelakang = getDistancePing(0);
    jarakKiri = getDistanceTof(2);
    jarakKanan = getDistanceTof(0);
    getRelativeHeadings();
    headingMaju = relativeHeadings;
    // runSt = 3; // Start
    // runSt = 8; // Jalan lurus pada Area R-1-4
    // runSt = 9; // Area kelereng
    // runSt = 21; // Menuju tangga
    runSt = 24; // Naik tangga
    // runSt = 27; // Zona atas
    break;

    // Start
  case 3:
    sensorSt = 0;
    in_speed = 20;
    // Serial.print("F ");
    // Serial.print(jarakDepan);
    // Serial.print(", B ");
    // Serial.print(jarakBelakang);
    // Serial.print(", L ");
    // Serial.print(jarakKiri);
    // Serial.print(", R ");
    // Serial.println(jarakKanan);

    if (jarakDepan > 20) // Depan lebih dari 12 putar kiri 90°
    {
      Serial.println("Menghadap Depan putar kiri 90°");
      if (totalSteep < 6)
      {
        in_yaw = -7;
      }
      else if (totalSteep < 8)
      {
        in_yaw = 0;
        totalSteep = 0;
        runSt = 4;
        break;
      }
    }
    else if (jarakBelakang > 20) // Belakang lebih dari 12 putar kanan 90°
    {
      Serial.println("Menghadap Belakang putar kanan 90°");
      if (totalSteep < 5)
      {
        in_yaw = 7;
      }
      else if (totalSteep < 7)
      {
        in_yaw = 0;
        totalSteep = 0;
        runSt = 4;
        break;
      }
    }
    else if (jarakKiri > 20) // Kiri lebih dari 12 putar kiri 180°
    {
      Serial.println("Menghadap Kiri putar kiri 180°");
      if (totalSteep < 12)
      {
        in_yaw = -7;
      }
      else if (totalSteep < 16)
      {
        in_yaw = 0;
        totalSteep = 0;
        runSt = 4;
        break;
      }
    }
    else
    {
      Serial.println("Menghadap Kanan, saatnya keluar dari zona Start");
      in_yaw = 0;
      totalSteep = 0;
      runSt = 4;
    }
    break;

  case 4: // Keluar start dengan jalan miring ke kanan
    sensorSt = 1;
    in_speed = 40;
    if (getDistanceTof(2) <= 45)
    {
      Serial.println("Miring kanan");
      in_px = 15;
      in_yaw = -0.4;
      if (jarakBelakang > 12)
      {
        in_pz = 7;
        Serial.println("Mundur");
      }
      else if (jarakBelakang < 12)
      {
        in_pz = -7;
        Serial.println("Maju");
      }
      else
      {
        in_pz = 0;
        Serial.println("Pas tengah");
      }
    }
    else if (getDistanceTof(2) < 54)
    {
      in_px = 15;
      in_pz = 0;
    }
    else
    {
      gripper(60, 130, 1);
      delay(500);
      in_px = 0;
      in_pz = 0;
      in_yaw = 0;
      totalSteep = 0;
      runSt = 5;
    }
    break;

    // Area K-1
  case 5: // Ambil korban ke-1
    sensorSt = 0;
    if (getDistancePing(4) >= 5)
    { // jarak korban
      in_pz = -7;
    }
    else
    {
      Serial.println("Ambil korban ke-1");
      gripper(60, 10, 1);
      delay(500);
      gripper(100, 10, 0.5);
      delay(500);
      in_pz = 0;
      totalSteep = 0;
      runSt = 6;
    }
    break;

  case 6: // Mundur sambil membawa korban ke-1
    sensorSt = 0;
    in_speed = 10;
    if (getDistancePing(0) >= 14)
    {
      in_pz = 10;
    }
    else
    {
      Serial.println("Mundur sambil bawa korban ke-1");
      totalSteep = 0;
      in_pz = 0;
      gripper(180, 10, 0.5);
      delay(500);
      runSt = 7;
    }
    break;

  case 7: // Putar kanan 90°
    sensorSt = 0;
    in_speed = 10;
    if (totalSteep < 5)
    {
      in_yaw = 7;
    }
    else if (totalSteep < 6)
    {
      in_yaw = 0;
    }
    else
    {
      Serial.println("Putar kanan 90°");
      in_yaw = 0;
      totalSteep = 0;
      getRelativeHeadings();
      headingMaju = relativeHeadings;
      runSt = 8;
    }
    break;

    // Area R-1-4
  case 8: // Antar korban ke-1 ke Savezone 1
    getRelativeHeadings();
    sensorSt = 1;
    in_speed = 50;
    in_lift = 30;
    in_py = -20;
    if (totalSteep < 46)
    {
      // Serial.print("L ");
      // Serial.print(jarakKiri);
      // Serial.print(", F ");
      // Serial.print(jarakDepan);
      // Serial.print(", totalSteep ");
      // Serial.print(totalSteep);
      // Serial.print("Maju ");
      // Serial.print(headingMaju);
      // Serial.print(", Heading ");
      // Serial.println(relativeHeadings);

      in_pz = -15;

      // Memperbaiki posisi robot terhadap dinding samping
      if (jarakKanan < 15) // Biar agak ke kiri
      {
        in_px = -10;
        Serial.println("Ngiri");
      }
      else if (jarakKanan > 15) // Biar agak ke kiri
      {
        in_px = 10;
        Serial.println("Nganan");
      }
      else
      {
        Serial.println("Pas tengah");
        in_px = 0;
      }

      // Memperbaiki orientasi berdasarkan nilai heading dari kompas
      if (relativeHeadings < headingMaju)
      {
        in_yaw = -3;
        Serial.println("Putar ke kiri");
      }
      else if (relativeHeadings > headingMaju)
      {
        in_yaw = 3;
        Serial.println("Putar ke kanan");
      }
      else
      {
        in_yaw = 0;
      }
    }
    else if (jarakKiri <= 37 && jarakDepan >= 20)
    {
      in_pz = -15;
      if (totalSteep >= 40)
      {
        if (jarakKanan < 12) // Biar agak ke kiri
        {
          in_px = -10;
          Serial.println("Ngiri");
        }
        else if (jarakKanan > 12) // Biar agak ke kiri
        {
          in_px = 10;
          Serial.println("Nganan");
        }
        else
        {
          Serial.println("Pas tengah");
          in_px = 0;
        }

        // Memperbaiki orientasi berdasarkan nilai heading dari kompas
        if (relativeHeadings < headingMaju)
        {
          in_yaw = -3;
          Serial.println("Putar ke kiri");
        }
        else if (relativeHeadings > headingMaju)
        {
          in_yaw = 3;
          Serial.println("Putar ke kanan");
        }
        else
        {
          in_yaw = 0;
        }
      }
    }
    else
    {
      Serial.println("Persiapan untuk mengantarkan korban ke-1 ke Savezone 1");
      in_pz = 0;
      in_px = 0;
      in_yaw = 0;
      totalSteep = 0;
      runSt = 9;
    }
    break;

    // Area R-4 SZ-1
  case 9: // Putar kanan 45° dan antar korban ke-1 ke Savezone 1
    sensorSt = 0;
    in_lift = 30;
    in_py = -30;
    in_speed = 10;
    if (totalSteep < 3)
    {
      in_yaw = 6;
    }
    else if (totalSteep < 5)
    {
      in_yaw = 0;
    }
    else
    {
      Serial.println("Antar korban ke-1 ke Savezone 1");
      in_py = 5;
      delay(500);
      gripper(60, 10, 1);
      delay(500);
      gripper(60, 160, 1);
      delay(500);
      gripper(170, 160, 0.5);
      delay(500);
      in_yaw = 0;
      totalSteep = 0;
      runSt = 11;
    }
    break;

  case 11: // Mundur setelah meletakkan korban ke-1
    sensorSt = 0;
    in_py = -30;
    in_speed = 10;
    if (totalSteep < 2)
    {
      in_pz = 5;
      in_px = -5;
    }
    else
    {
      Serial.println("Mundur setelah meletakkan korban ke-1");
      in_pz = 0;
      in_px = 0;
      totalSteep = 0;
      runSt = 12;
    }
    break;

  case 12: // Putar kiri 135°
    sensorSt = 0;
    in_speed = 10;
    if (totalSteep < 9)
    {
      in_yaw = -7;
    }
    else if (totalSteep < 11)
    {
      in_yaw = 0;
    }
    else
    {
      Serial.println("Putar kiri 135°");
      in_yaw = 0;
      totalSteep = 0;
      getRelativeHeadings();
      headingMaju = relativeHeadings;
      runSt = 13;
    }
    break;

    // Area R-4-5
  case 13: // Maju hingga jarak sensor belakang 40 cm
    getRelativeHeadings();
    sensorSt = 1;
    in_speed = 50;
    if (totalSteep < 13) // jarakBelakang < 45 && jarakDepan < 35
    {
      // Serial.print("B ");
      // Serial.print(jarakBelakang);
      // Serial.print(", F ");
      // Serial.print(jarakDepan);
      // Serial.print("K ");
      // Serial.print(jarakKanan);
      // Serial.print(", totalSteep ");
      // Serial.println(totalSteep);
      // Serial.print(", Maju ");
      // Serial.print(headingMaju);
      // Serial.print(", Heading ");
      // Serial.println(relativeHeadings);

      in_pz = -15;

      if (jarakKanan < 12)
      {
        in_px = -7;
        Serial.println("Ngiri");
      }
      else if (jarakKanan > 12)
      {
        in_px = 7;
        Serial.println("Nganan");
      }
      else
      {
        Serial.println("Pas tengah");
        in_px = 0;
      }

      // Memperbaiki orientasi berdasarkan nilai heading dari kompas
      if (relativeHeadings < headingMaju)
      {
        in_yaw = -3;
        Serial.println("Putar ke kiri");
      }
      else if (relativeHeadings > headingMaju)
      {
        in_yaw = 3;
        Serial.println("Putar ke kanan");
      }
      else
      {
        in_yaw = 0;
      }
    }
    else
    {
      Serial.println("Maju hingga mencapai tempat korban 2");
      in_pz = 0;
      in_px = 0;
      in_yaw = 0;
      totalSteep = 0;
      runSt = 14;
    }
    break;

  case 14: // Putar kiri 90°
    sensorSt = 0;
    in_speed = 7;
    if (totalSteep < 7)
    {
      in_yaw = -7;
    }
    else if (totalSteep < 10)
    {
      in_yaw = 0;
    }
    else
    {
      Serial.println("Putar kiri 90°");
      gripper(50, 130, 1);
      delay(500);
      in_yaw = 0;
      totalSteep = 0;
      runSt = 15;
    }
    break;

    // Area K-2
  case 15: // Ambil korban ke-2
    sensorSt = 0;
    in_py = 0;
    in_speed = 8;
    if (getDistancePing(4) >= 5)
    { // jarak korban
      in_pz = -10;
      in_yaw = 1;
    }
    else
    {
      Serial.println("Ambil korban ke-2");
      gripper(50, 10, 1);
      delay(500);
      gripper(100, 10, 0.5);
      delay(500);
      gripper(180, 10, 0.5);
      delay(500);
      in_pz = 0;
      in_yaw = 0;
      totalSteep = 0;
      runSt = 16;
    }
    break;

  case 16: // Mundur sambil membawa korban ke-2
    sensorSt = 0;
    in_py = -30;
    in_speed = 20;
    if (getDistancePing(0) >= 22)
    {
      in_pz = 10;
    }
    else
    {
      Serial.println("Mundur sambil bawa korban ke-2");
      in_pz = 0;
      totalSteep = 0;
      runSt = 17;
    }
    break;

  case 17: // Putar kanan 90°
    sensorSt = 0;
    in_speed = 7;
    if (totalSteep < 6)
    {
      in_yaw = 7;
    }
    else if (totalSteep < 8)
    {
      in_yaw = 0;
    }
    else
    {
      Serial.println("Putar kanan 90°");
      in_yaw = 0;
      totalSteep = 0;
      getRelativeHeadings();
      headingMaju = relativeHeadings;
      runSt = 18;
    }
    break;

  case 18: // Persiapan untuk mengantarkan korban ke-2 ke Savezone 2
    getRelativeHeadings();
    sensorSt = 1;
    in_speed = 50;
    if (jarakDepan >= 12)
    {
      in_pz = -15;

      // if (jarakDepan >= 15)
      // {
      if (jarakKanan < 28)
      {
        in_px = -7;
        Serial.println("Ngiri");
      }
      else if (jarakKanan > 28)
      {
        in_px = 7;
        Serial.println("Nganan");
      }
      else
      {
        Serial.println("Pas tengah");
        in_px = 0;
      }
      // }

      // Memperbaiki orientasi berdasarkan nilai heading dari kompas
      if (relativeHeadings < headingMaju)
      {
        in_yaw = -3;
        Serial.println("Putar ke kiri");
      }
      else if (relativeHeadings > headingMaju)
      {
        in_yaw = 3;
        Serial.println("Putar ke kanan");
      }
      else
      {
        in_yaw = 0;
      }
    }
    else
    {
      Serial.println("Persiapan untuk mengantarkan korban ke-2 ke Savezone 2");
      in_pz = 0;
      in_px = 0;
      in_yaw = 0;
      totalSteep = 0;
      runSt = 19;
    }
    break;

    // Area SZ-2
  case 19: // Putar kanan 90° dan letakkan korban ke Savezone 2
    sensorSt = 0;
    in_speed = 10;
    if (totalSteep < 5)
    {
      in_yaw = 7;
    }
    else if (totalSteep < 7)
    {
      in_yaw = 0;
    }
    else
    {
      Serial.println("Antar korban ke-2 ke Savezone 2");
      gripper(90, 10, 1);
      delay(500);
      gripper(90, 140, 1);
      delay(500);
      gripper(170, 160, 0.5);
      delay(500);
      getRelativeHeadings();
      headingMaju = relativeHeadings;
      in_yaw = 0;
      totalSteep = 0;
      runSt = 21;
    }
    break;

  case 21: // Mundur setelah meletakkan korban ke-2 hingga tembok
    getRelativeHeadings();
    sensorSt = 1;
    in_speed = 50;
    in_lift = 30;
    in_py = -20;
    if (jarakBelakang > 11)
    {
      // Serial.print("B ");
      // Serial.print(jarakBelakang);
      // Serial.print(", Maju ");
      // Serial.print(headingMaju);
      // Serial.print(", Heading ");
      // Serial.println(relativeHeadings);

      in_pz = 15;

      if (jarakKiri > 4)
      {
        in_px = -7;
        Serial.println("Ngiri");
      }
      else if (jarakKiri < 4)
      {
        in_px = 7;
        Serial.println("Nganan");
      }
      else
      {
        Serial.println("Pas tengah");
        in_px = 0;
      }

      // Memperbaiki orientasi berdasarkan nilai heading dari kompas
      if (relativeHeadings < headingMaju)
      {
        in_yaw = -3;
        Serial.println("Putar ke kiri");
      }
      else if (relativeHeadings > headingMaju)
      {
        in_yaw = 3;
        Serial.println("Putar ke kanan");
      }
      else
      {
        in_yaw = 0;
      }
    }
    else
    {
      Serial.println("Mundur setelah meletakkan korban ke-2");
      totalSteep = 0;
      in_pz = 0;
      in_px = 0;
      in_yaw = 0;
      runSt = 22;
    }
    break;

  case 22: // Miring kanan hingga tembok
    getRelativeHeadings();
    sensorSt = 1;
    in_speed = 50;
    if (jarakKanan > 10)
    {
      // Serial.print("K ");
      // Serial.print(jarakKanan);
      // Serial.print(", Maju ");
      // Serial.print(headingMaju);
      // Serial.print(", Heading ");
      // Serial.println(relativeHeadings);

      in_px = 15;

      // Memperbaiki orientasi berdasarkan nilai heading dari kompas
      if (relativeHeadings < headingMaju)
      {
        in_yaw = -3;
        Serial.println("Putar ke kiri");
      }
      else if (relativeHeadings > headingMaju)
      {
        in_yaw = 3;
        Serial.println("Putar ke kanan");
      }
      else
      {
        in_yaw = 0;
      }
    }
    else
    {
      Serial.println("Miring kanan hingga tembok");
      totalSteep = 0;
      in_px = 0;
      in_yaw = 0;
      runSt = 23;
    }
    break;

    // Area R-6-7
  case 23: // Mundur hingga tangga
    getRelativeHeadings();
    sensorSt = 1;
    in_speed = 50;
    if (jarakBelakang > 13)
    {
      // Serial.print("B ");
      // Serial.print(jarakBelakang);
      // Serial.print(", Maju ");
      // Serial.print(headingMaju);
      // Serial.print(", Heading ");
      // Serial.println(relativeHeadings);

      in_pz = 15;

      if (jarakKanan < 8)
      {
        in_px = -7;
        Serial.println("Ngiri");
      }
      else if (jarakKanan > 8)
      {
        in_px = 7;
        Serial.println("Nganan");
      }
      else
      {
        Serial.println("Pas tengah");
        in_px = 0;
      }

      // Memperbaiki orientasi berdasarkan nilai heading dari kompas
      if (relativeHeadings < headingMaju)
      {
        in_yaw = -3;
        Serial.println("Putar ke kiri");
      }
      else if (relativeHeadings > headingMaju)
      {
        in_yaw = 3;
        Serial.println("Putar ke kanan");
      }
      else
      {
        in_yaw = 0;
      }
    }
    else
    {
      Serial.println("Mundur hingga ke tangga");
      in_pz = 0;
      in_px = 0;
      in_yaw = 0;
      totalSteep = 0;
      runSt = 24;
    }
    break;

  case 24: // Putar kanan 90°
    sensorSt = 0;
    in_speed = 10;
    if (totalSteep < 6)
    {
      in_yaw = 7;
    }
    else if (totalSteep < 7)
    {
      in_yaw = 0;
    }
    else
    {
      Serial.println("Putar kanan 90° ke tangga");
      // getRelativeHeadings();
      // headingMaju = relativeHeadings;
      in_yaw = 0;
      totalSteep = 0;
      runSt = 25;
    }
    break;

  case 25: // Persiapan naik ke tangga
    // getRelativeHeadings();
    sensorSt = 1;
    in_speed = 50;
    if (totalSteep < 10) // jarakBelakang > 12 // jarakDepan < 44
    {
      Serial.print("totalSteep ");
      Serial.print(totalSteep);
      // Serial.print(", Maju ");
      // Serial.print(headingMaju);
      // Serial.print(", Heading ");
      // Serial.println(relativeHeadings);
      Serial.print(", F ");
      Serial.println(jarakDepan);

      in_pz = 15;

      if (jarakKanan < 7)
      {
        in_px = -7;
        Serial.println("Ngiri");
      }
      else if (jarakKanan > 7)
      {
        in_px = 7;
        Serial.println("Nganan");
      }
      else
      {
        Serial.println("Pas tengah");
        in_px = 0;
      }

      // // Memperbaiki orientasi berdasarkan nilai heading dari kompas
      // if (relativeHeadings < headingMaju)
      // {
      //   in_yaw = -3;
      //   Serial.println("Putar ke kiri");
      // }
      // else if (relativeHeadings > headingMaju)
      // {
      //   in_yaw = 3;
      //   Serial.println("Putar ke kanan");
      // }
      // else
      // {
      //   in_yaw = 0;
      // }
    }
    else if (totalSteep > 8 && jarakDepan < 40)
    {
      Serial.print("totalSteep ");
      Serial.print(totalSteep);
      Serial.print(", F ");
      Serial.println(jarakDepan);

      in_pz = 15;

      if (jarakKanan < 7)
      {
        in_px = -7;
        Serial.println("Ngiri");
      }
      else if (jarakKanan > 7)
      {
        in_px = 7;
        Serial.println("Nganan");
      }
      else
      {
        Serial.println("Pas tengah");
        in_px = 0;
      }
    }
    else
    {
      Serial.println("Persiapan naik ke tangga");
      // getRelativeHeadings();
      // headingMaju = relativeHeadings;
      in_pz = 0;
      in_px = 0;
      in_yaw = 0;
      totalSteep = 0;
      runSt = 26;
    }
    break;

    // Area R9-10
  case 26: // Naiki tangga
    // getRelativeHeadings();
    sensorSt = 1;
    in_speed = 20;
    in_lift = 30;
    in_py = 0;
    in_pitch = 7;
    if (totalSteep < 45)
    {
      // Serial.print("B ");
      // Serial.print(jarakBelakang);
      // Serial.print(", R ");
      // Serial.print(jarakKanan);
      // Serial.print(", totalSteep ");
      // Serial.println(totalSteep);

      in_px = 20;

      // Memperbaiki posisi robot terhadap dinding samping
      if (jarakBelakang < 10)
      {
        in_pz = -7;
        Serial.println("Maju");
      }
      else if (jarakBelakang > 10)
      {
        in_pz = 7;
        Serial.println("Mundur");
      }
      else
      {
        Serial.println("Pas tengah");
        in_pz = 0;
      }

      // // Memperbaiki orientasi berdasarkan nilai heading dari kompas
      // if (relativeHeadings < headingMaju)
      // {
      //   in_yaw = -3;
      //   Serial.println("Putar ke kiri");
      // }
      // else if (relativeHeadings > headingMaju)
      // {
      //   in_yaw = 3;
      //   Serial.println("Putar ke kanan");
      // }
      // else
      // {
      //   in_yaw = 0;
      // }
    }
    else if (totalSteep > 33 && jarakKanan > 20)
    {
      in_px = 20;

      // Memperbaiki posisi robot terhadap dinding samping
      if (jarakBelakang < 10)
      {
        in_pz = -7;
        Serial.println("Maju");
      }
      else if (jarakBelakang > 10)
      {
        in_pz = 7;
        Serial.println("Mundur");
      }
      else
      {
        Serial.println("Pas tengah");
        in_pz = 0;
      }
    }
    else
    {
      Serial.println("Persiapan untuk mengantarkan korban ke-4 ke Savezone 4");
      in_pz = 0;
      in_px = 0;
      in_yaw = 0;
      in_pitch = 0;
      totalSteep = 0;
      runSt = 27;
    }
    break;

  case 27: // Putar kanan 110°
    sensorSt = 0;
    in_lift = 30;
    in_py = -20;
    in_speed = 10;
    if (totalSteep < 7)
    {
      in_yaw = 7;
    }
    else if (totalSteep < 8)
    {
      in_yaw = 0;
    }
    else
    {
      Serial.println("Putar kanan 110° setelah melewati tangga");
      gripper(60, 150, 1);
      delay(500);
      in_yaw = 0;
      totalSteep = 0;
      runSt = 28;
    }
    break;

  case 28: // Ambil korban ke-5
    sensorSt = 1;
    in_speed = 20;
    in_lift = 30;
    in_py = -10;
    in_roll = 5;
    if (getDistancePing(4) >= 5)
    { // jarak korban
      in_pz = -10;
      in_yaw = 1;
    }
    else
    {
      Serial.println("Ambil korban ke-5");
      gripper(50, 10, 1);
      delay(500);
      gripper(110, 10, 1);
      delay(500);
      gripper(170, 10, 0.5);
      delay(500);
      in_pz = 0;
      in_yaw = 0;
      totalSteep = 0;
      runSt = 29;
    }
    break;

  case 29: // Putar kiri 25°
    sensorSt = 0;
    in_speed = 10;
    if (totalSteep < 3)
    {
      in_yaw = -7;
    }
    else if (totalSteep < 4)
    {
      in_yaw = 0;
    }
    else
    {
      Serial.println("Putar kiri 25° setelah melewati tangga");
      in_yaw = 0;
      totalSteep = 0;
      runSt = 31;
    }
    break;

  case 31: // Menyejajarkan posisi
    sensorSt = 1;
    in_py = -20;
    in_lift = 30;
    in_roll = 0;
    in_speed = 15;
    if (jarakDepan < 36)
    {
      Serial.print("F ");
      Serial.println(jarakDepan);
      in_pz = 8;
    }
    else if (jarakDepan > 39)
    {
      Serial.print("F ");
      Serial.println(jarakDepan);
      in_pz = -6;
    }
    else
    {
      Serial.println("Menyejajarkan posisi untuk menyeberang lembah longsor");
      in_pz = 0;
      totalSteep = 0;
      runSt = 32;
    }
    break;

  case 32: // Jalan miring kiri melewati lembah longsor sampai tembok
    sensorSt = 1;
    in_speed = 30;
    if (jarakKiri > 30)
    {
      Serial.print("F ");
      Serial.print(jarakDepan);
      Serial.print(", L ");
      Serial.print(jarakKiri);

      in_px = -20;
      in_yaw = -2;
    }
    else if (jarakKiri > 10)
    {
      Serial.print(", L ");
      Serial.print(jarakKiri);

      in_px = -20;
      in_yaw = 0;
    }
    else
    {
      Serial.println("Jalan miring kiri melewati lembah longsor sampai tembok");
      in_px = 0;
      in_yaw = 0;
      totalSteep = 0;
      runSt = 33;
    }
    break;

  case 33: // Letakkan korban pada Savezone 5
    sensorSt = 0;
    in_py = 0;
    in_speed = 20;
    if (getDistancePing(0) < 31)
    {
      in_pz = -15;
    }
    else
    {
      Serial.println("Antar korban ke-5 ke Savezone 5");
      gripper(100, 10, 1);
      delay(500);
      gripper(100, 140, 1);
      delay(500);
      gripper(170, 160, 0.5);
      delay(500);
      in_pz = 0;
      totalSteep = 0;
      runSt = 34;
    }
    break;

  case 34: // Mundur ke garis finish dan diam 10 detik
    sensorSt = 0;
    in_speed = 20;
    if (getDistancePing(0) > 20)
    {
      in_pz = 15;
    }
    else
    {
      Serial.println("Finish - diam 10 detik!!");
      beep();
      beep();
      beep();
      in_pz = 0;
      totalSteep = 0;
      runSt = 0;
    }
    break;
  }
}