void New()
{
  Serial.println(totalSteep);
  switch (runSt)
  {
    case 0:
      Serial.println("Stop");
      if (XYst == 0)
      gripper(170, 170, 0.5);
      stopValue();
      in_speed = 0;
      sensorSt = 0;
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
     in_pz = 0;
    in_px = 0;
    in_yaw = 0;

    if (totalSteep > 10) {
        in_px = 5;
        Serial.println("KANAN");
        runSt = 4; 
    }

    break; 

 case 4:
    static bool hasResetTotalSteep = false; 

    if (!hasResetTotalSteep) {
        totalSteep = 0;
        hasResetTotalSteep = true; 
    }

    in_speed = 15;
    in_yaw = 3;
    Serial.println("Muter");

    if (totalSteep == 10) {
        runSt = 5;
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

      case 5:
       static bool reset = false;

    if (!reset) {
        totalSteep = 0;
        reset = true; 
    }
      in_speed = 20;
      in_px = -5;
      Serial.println("KIRI");
      if (totalSteep == 20){
        runSt = 0;
      }
      break;
  }
}
