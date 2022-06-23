void check_battery()
{
  float volt = getBatteryVoltage();
  setSoundVolume(90);
  displayCenteredBigTextLine(12, "%f", volt);
  if (!(volt > 8.1 && volt < 8.25))
  {
    playSound(soundDownwardTones);
    playSound(soundException);
  }
}

#if CALIBRATE == 1
  void LCDWriteInfoHitech(tHTCS2Ptr htcs2Ptr, CalibrationPtr data)
  {
    eraseDisplay();
    while (true)
    {
      readSensor(htcs2Ptr, data);
      displayCenteredTextLine(6, "R: %d G: %d B: %d", htcs2Ptr->red, htcs2Ptr->green, htcs2Ptr->blue);
      displayCenteredTextLine(8, "R_c: %d G_c: %d B_c: %d", htcs2Ptr->red_calibrated, htcs2Ptr->green_calibrated, htcs2Ptr->blue_calibrated);
      displayCenteredTextLine(10, "H: %d S: %d V: %d", htcs2Ptr->hue, htcs2Ptr->saturation, htcs2Ptr->value);
      displayCenteredTextLine(12, "H_c: %d S_c: %d V_c: %d", htcs2Ptr->hue_calibrated, htcs2Ptr->saturation_calibrated, htcs2Ptr->value_calibrated);
      sleep(2);
    }
  }

  void calibrateLeftRightHT(tHTCS2Ptr htcs2Ptrleft, tHTCS2Ptr htcs2Ptrright, CalibrationPtr data){
    eraseDisplay();
    while (true)
    {
      readSensor(htcs2Ptrleft,  data);
      readSensor(htcs2Ptrright, data);
      displayCenteredTextLine(6, "left R: %d G: %d B: %d W: %d", htcs2Ptrleft->red, htcs2Ptrleft->green, htcs2Ptrleft->blue, htcs2Ptrleft->white);
      displayCenteredTextLine(8, "right R: %d G: %d B: %d W: %d", htcs2Ptrright->red, htcs2Ptrright->green, htcs2Ptrright->blue, htcs2Ptrright->white);
      sleep(2);
    }
  }

  // LCDWriteInfoHitechRaw(&colorLeftSensor, &MarkerInfoRawLeft);
  // LCDWriteInfoHitechRaw(&colorRightSensor, &MarkerInfoRawRight);
  void LCDWriteInfoHitechRaw(tHTCS2Ptr htcs2Ptr, CalibrationPtr data)
  {
    eraseDisplay();
    while (true)
    {
      readSensorRaw(htcs2Ptr, data);
      displayCenteredTextLine(6, "R: %d G: %d B: %d W: %d", htcs2Ptr->red, htcs2Ptr->green, htcs2Ptr->blue, htcs2Ptr->white);
      displayCenteredTextLine(8, "R_c: %d G_c: %d B_c: %d", htcs2Ptr->red_calibrated, htcs2Ptr->green_calibrated, htcs2Ptr->blue_calibrated);
      displayCenteredTextLine(12, "H_c: %d S_c: %d V_c: %d", htcs2Ptr->hue_calibrated, htcs2Ptr->saturation_calibrated, htcs2Ptr->value_calibrated);
      sleep(2);
    }
  }

  void LCDWriteInfoNXTSen()
  {
    eraseDisplay();
    BrakeLeftRightMotor(0);
    while (getButtonPress(buttonEnter) == 0)
    {
      SensorsToPercent();
      displayCenteredTextLine(6, "sen1: %d sen2: %d", SensorRaw[leftSensor], SensorRaw[rightSensor]);
      displayCenteredTextLine(8, "sen1: %d sen2: %d", results_sensors.firstSensor, results_sensors.secondSensor);
      delay(100);
    }
  }
#endif

int getSign(int number)
{
  if (number < 0)
  {
    return -1;
  }
  else
  {
    return 1;
  }
}

void waitTask(byte* taskFlag)
{
  while (*taskFlag == 1){
    sleep(50);
	}
}

/*
void EOPD_data()
{
  eraseDisplay();

  displayCenteredTextLine(0, "HiTechnic");
  displayCenteredBigTextLine(1, "EOPD");
  displayCenteredTextLine(5, "Press enter to");
  displayCenteredTextLine(6, "switch between");
  displayCenteredTextLine(7, "ranges");
  sleep(2000);
  eraseDisplay();

  // Create struct to hold sensor data
  tHTEOPD eopdSensor;

  // Initialise and configure struct and port
  // Default mode for the EOPD is short range
  initSensor(&eopdSensor, S4);

  while(true) {
    if (time1[T1] > 1000) {
      if (eopdSensor.shortRange == false) {
        // set the sensor to short range and display this
      	eopdSensor.shortRange = true;
      	configSensor(&eopdSensor);
        displayClearTextLine(1);
        displayTextLine(1, "Short range");
      } else {
        // set the sensor to long range and display this
      	eopdSensor.shortRange = false;
      	configSensor(&eopdSensor);
        displayClearTextLine(1);
        displayTextLine(1, "Long range");
      }
      playSound(soundBeepBeep);
      while(bSoundActive)
      time1[T1] = 0;
    }

      while(!getButtonPress(buttonEnter)) {
    	  readSensor(&eopdSensor);

        displayClearTextLine(3);
        displayClearTextLine(4);
        displayTextLine(4, "Proc:  %4d", eopdSensor.processed);
        displayTextLine(3, "Raw :  %4d", eopdSensor.raw);
        sleep(50);
    }
  }
}
*/
