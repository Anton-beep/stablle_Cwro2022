void ReadIndicator(short len_millimeters, short speed){
	motor[motorA] = -speed;
	motor[motorB] = speed;

	float enc_left_motor = fabs(nMotorEncoder[leftMotor]);
	float enc_right_motor = fabs(nMotorEncoder[rightMotor]);

	float moved_motors = 0;
	float now_millimeters = 0;

	int sum_rl = 0;
	int sum_gl = 0;
	int sum_bl = 0;

	int sum_rr = 0;
	int sum_gr = 0;
	int sum_br = 0;
	
	while(now_millimeters < len_millimeters) {
		readSensor(&colorLeftSensor,  &MarkerInfoRawLeft);
		readSensor(&colorRightSensor, &MarkerInfoRawRight);

		sum_rl += colorLeftSensor.red_calibrated;
		sum_gl += colorLeftSensor.green_calibrated;
		sum_bl += colorLeftSensor.blue_calibrated;

		sum_rr += colorRightSensor.red_calibrated;
		sum_gr += colorRightSensor.green_calibrated;
		sum_br += colorRightSensor.blue_calibrated;

		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

	ht_results[0] = (sum_rl + sum_gl + sum_bl);
	ht_results[1] = (sum_rr + sum_gr + sum_br);
}

void ReadLeftWash(short len_millimeters, short speed){
	BrakeLeftRightMotor(0);
	motor[motorA] = -speed;
	motor[motorB] = speed;

	float enc_left_motor = fabs(nMotorEncoder[leftMotor]);
	float enc_right_motor = fabs(nMotorEncoder[rightMotor]);

	float moved_motors = 0;
	float now_millimeters = 0;

	int sum_ht = 0;

	while(now_millimeters < len_millimeters) {
		readSensor(&colorLeftSensor,  &WashInfoRawLeft);

		sum_ht += colorLeftSensor.red_calibrated + colorLeftSensor.green_calibrated + colorLeftSensor.blue_calibrated;

		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

	ht_results[0] = sum_ht;
	BrakeLeftRightMotor(0);
}

void ReadRightWash(short len_millimeters, short speed){
	BrakeLeftRightMotor(0);
	motor[motorA] = -speed;
	motor[motorB] = speed;

	float enc_left_motor = fabs(nMotorEncoder[leftMotor]);
	float enc_right_motor = fabs(nMotorEncoder[rightMotor]);

	float moved_motors = 0;
	float now_millimeters = 0;

	int sum_rr = 0;
	int sum_gr = 0;
	int sum_br = 0;

	while(now_millimeters < len_millimeters) {
		readSensor(&colorRightSensor,  &WashInfoRawRight);

		sum_rr += colorRightSensor.red_calibrated;
		sum_gr += colorRightSensor.green_calibrated;
		sum_br += colorRightSensor.blue_calibrated;

		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

	ht_results[1] = sum_rr + sum_gr + sum_br;
	BrakeLeftRightMotor(0);
}

void readRightSen_noMove(int count_times, CalibrationHiTechData* calibration, int timer = 100){
	int sum_w = 0;
	
	for (int i = 0; i < count_times; i++){
		readSensor(&colorRightSensor, calibration);

		#if LOGGING == 1
			char w[10];
			sprintf(w, "%d", colorRightSensor.white);
			fileWriteData(fileHandle, w,  strlen(w) + 1);
			fileWriteData(fileHandle, end, strlen(end) + 1);
		#endif

		sum_w += colorRightSensor.white;
		delay(timer);
	}

	ht_results[1] = (sum_w) / (count_times);
}

void readLeftSen_noMove(int count_times, CalibrationHiTechData* calibration, int timer = 100){
	int sum_w = 0;
	
	for (int i = 0; i < count_times; i++){
		readSensor(&colorLeftSensor, calibration);

		#if LOGGING == 1
			char w[10];
			sprintf(w, "%d", colorLeftSensor.white);
			fileWriteData(fileHandle, w,  strlen(w) + 1);
			fileWriteData(fileHandle, end, strlen(end) + 1);
		#endif

		sum_w += colorLeftSensor.white;
		delay(timer);
	}

	ht_results[0] = (sum_w) / (count_times);
}

void readRightSen_noMoveRGB(int count_times, CalibrationHiTechData* calibration, int timer = 100){
	int sum_rr = 0;
	int sum_gr = 0;
	int sum_br = 0;
	
	for (int i = 0; i < count_times; i++){
		readSensor(&colorRightSensor,  &WashInfoRawRight);

		#if LOGGING == 1
			char r[10];
			char g[10];
			char b[10];
			
			sprintf(r, "%d", colorRightSensor.red);
			sprintf(g, "%d", colorRightSensor.green);
			sprintf(b, "%d", colorRightSensor.blue);

			fileWriteData(fileHandle, r,  strlen(r) + 1);
			fileWriteData(fileHandle, g,  strlen(g) + 1);
			fileWriteData(fileHandle, b,  strlen(b) + 1);

			fileWriteData(fileHandle, end, strlen(end) + 1);
		#endif


		sum_rr += colorRightSensor.red;
		sum_gr += colorRightSensor.green;
		sum_br += colorRightSensor.blue;
	}

	rgb[0] = sum_rr / count_times;
	rgb[1] = sum_gr / count_times;
	rgb[2] = sum_br / count_times;

	ht_results[1] = (sum_rr + sum_gr + sum_br) / (count_times);
}

void readLeftSen_noMoveRGB(int count_times, CalibrationHiTechData* calibration, int timer = 100){
	int sum_rr = 0;
	int sum_gr = 0;
	int sum_br = 0;
	
	for (int i = 0; i < count_times; i++){
		readSensor(&colorLeftSensor,  &WashInfoRawLeft);

		#if LOGGING == 1
			char r[10];
			char g[10];
			char b[10];

			sprintf(r, "%d", colorLeftSensor.red);
			sprintf(g, "%d", colorLeftSensor.green);
			sprintf(b, "%d", colorLeftSensor.blue);

			fileWriteData(fileHandle, r,  strlen(r) + 1);
			fileWriteData(fileHandle, g,  strlen(g) + 1);
			fileWriteData(fileHandle, b,  strlen(b) + 1);

			fileWriteData(fileHandle, end, strlen(end) + 1);
		#endif

		sum_rr += colorLeftSensor.red;
		sum_gr += colorLeftSensor.green;
		sum_br += colorLeftSensor.blue;
	}

	rgb[0] = sum_rr / count_times;
	rgb[1] = sum_gr / count_times;
	rgb[2] = sum_br / count_times;

	ht_results[0] = (sum_rr + sum_gr + sum_br) / (count_times);
}

void ReadIndicatorExtended(short len_millimeters, short speed){
	motor[motorA] = -speed;
	motor[motorB] = speed;

	float enc_left_motor = fabs(nMotorEncoder[leftMotor]);
	float enc_right_motor = fabs(nMotorEncoder[rightMotor]);

	float moved_motors = 0;
	float now_millimeters = 0;
	int counter = 0;
	
	int sum_rl = 0;
	int sum_gl = 0;
	int sum_bl = 0;

	int sum_rr = 0;
	int sum_gr = 0;
	int sum_br = 0;
	
	while(now_millimeters < len_millimeters) {
		readSensor(&colorLeftSensor,  &MarkerInfoRawLeft);
		readSensor(&colorRightSensor, &MarkerInfoRawRight);

		sum_rl += colorLeftSensor.red;
		sum_gl += colorLeftSensor.green;
		sum_bl += colorLeftSensor.blue;

		sum_rr += colorRightSensor.red;
		sum_gr += colorRightSensor.green;
		sum_br += colorRightSensor.blue;

		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
		counter ++;
	}

	rgbLeft[0] =  sum_rl / counter;
	rgbLeft[1] =  sum_gl / counter;
	rgbLeft[2] =  sum_bl / counter;

	rgbRight[0] = sum_rr / counter;
	rgbRight[1] = sum_gr / counter;
	rgbRight[2] = sum_br / counter;

	ht_results[0] = (sum_rl + sum_gl + sum_bl) / counter;
	ht_results[1] = (sum_rr + sum_gr + sum_br) / counter;
}