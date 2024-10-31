void New()
{
  switch (runSt)
  {
    case 0:
      Serial.println("Stop");
      if (XYst == 0)
      gripper(170, 170, 0.5);
      stopValue();
      in_speed = 0;
      sensorSt = 0;
      runSt = 1;
      break;
  
    case 1:
    Serial.println("Jalan ditempat");
    starValue();
    startDirection();
    totalSteep = 0;
    // jarakDepan = getDistancePing(1);
    // jarakBelakang = getDistancePing(0);
    // jarakKiri = getDistanceTof(2);
    // jarakKanan = getDistanceTof(0);
    runSt = 3; // Start
    break;


   case 3:
    Serial.println("MAJU");
    in_speed = 20; 
    in_pz = -15;

    if (totalSteep == 10) {
        stopValue();
        Serial.println("STOP");
    }
    break; 

// Untuk memanggil fungsi moveSingleLeg
//       for (byte legNumber = 1; legNumber <= 6; legNumber++) {
//     Serial.println(legNumber);
//     moveSingleLeg1(legNumber);
//     delay(100);
// }

// Untuk memanggil fungsi moveSingleLeg1
// for (byte legNumber = 1; legNumber <= 6; legNumber++) {
//     Serial.println(legNumber); 
//     moveSingleLeg(legNumber);
//     delay(100);
// }
      break;
  }
}
