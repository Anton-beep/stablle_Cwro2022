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

void resetError(){
  pr_error = 0;
  pr_error_tacho = 0;
  integral_sum = 0;
}
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
    readSensorRaw(htcs2Ptrleft,  data);
    readSensorRaw(htcs2Ptrright, data);
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
  while (true)
  {
    SensorsToPercent();
    displayCenteredTextLine(6, "sen1: %d sen2: %d", SensorRaw[leftSensor], SensorRaw[rightSensor]);
    displayCenteredTextLine(8, "sen1: %d sen2: %d", results_sensors.firstSensor, results_sensors.secondSensor);
    delay(100);
  }
}

void swap(long *ptr1, long *ptr2)
{
  long buffer = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = buffer;
}

typedef struct
{
  long *pointer;
  long len;
} Array;

void arr_fill(Array arr, int val)
{
  for (int i = 0; i < arr.len; i++)
  {
    arr.pointer[i] = val;
  }
}

int arr_push_back(Array arr, int val)
{
  for (int i = 0; i < arr.len; i++)
  {
    if (arr.pointer[i] == -228)
    {
      arr.pointer[i] = val;
      return 1;
    }
  }
  return 0;
}

int arr_cutFirst(Array arr)
{
  int val = arr.pointer[0];
  arr.pointer[0] = -228;

  for (int i = 1; i < arr.len; i++)
  {
    swap(&arr.pointer[i - 1], &arr.pointer[i]);
  }

  return val;
}

void test_arr_operations()
{
  Array my_arr;
  int arr[7];
  my_arr.pointer = &arr;
  my_arr.len = 7;

  arr_fill(my_arr, -228);
  for (int i = 0; i < my_arr.len; i++)
  {
    arr_push_back(my_arr, i + 10);
  }

  displayCenteredTextLine(5, "after push_back");
  displayCenteredTextLine(10, "%d %d %d %d %d %d %d", my_arr.pointer[0], my_arr.pointer[1], my_arr.pointer[2], my_arr.pointer[3], my_arr.pointer[4], my_arr.pointer[5], my_arr.pointer[6]);
  waitForButtonPress();
  eraseDisplay();

  for (int i = 0; i < my_arr.len; i++)
  {
    displayCenteredTextLine(5, "%d", arr_cutFirst(my_arr));
    flushButtonMessages();
    waitForButtonPress();
    eraseDisplay();
  }

  displayCenteredTextLine(5, "after cut");
  displayCenteredTextLine(10, "%d %d %d %d %d %d %d", my_arr.pointer[0], my_arr.pointer[1], my_arr.pointer[2], my_arr.pointer[3], my_arr.pointer[4], my_arr.pointer[5], my_arr.pointer[6]);
}

int arr_find(Array arr, int element)
{
  // ind of element or -1 if element not in array
  for (int i = 0; i < arr.len; i++)
  {
    if (arr.pointer[i] == element)
    {
      return i;
    }
  }
  return -1;
}

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

typedef struct
{
  int first;
  int second;
} pair;

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
