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
		readSensorRaw(&colorLeftSensor,  &MarkerInfoRawLeft);
		readSensorRaw(&colorRightSensor, &MarkerInfoRawRight);

		sum_rl += colorLeftSensor.red_calibrated;
		sum_gl += colorLeftSensor.green_calibrated;
		sum_bl += colorLeftSensor.blue_calibrated;

		sum_rr += colorRightSensor.red_calibrated;
		sum_gr += colorRightSensor.green_calibrated;
		sum_br += colorRightSensor.blue_calibrated;

		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

	ht_results[0] = sum_rl + sum_gl + sum_bl;
	ht_results[1] = sum_rr + sum_gr + sum_br;
}

void ReadLeftWash(short len_millimeters, short speed){
	motor[motorA] = -speed;
	motor[motorB] = speed;

	float enc_left_motor = fabs(nMotorEncoder[leftMotor]);
	float enc_right_motor = fabs(nMotorEncoder[rightMotor]);

	float moved_motors = 0;
	float now_millimeters = 0;

	int sum_ht = 0;

	while(now_millimeters < len_millimeters) {
		readSensorRaw(&colorLeftSensor,  &WashInfoRawLeft);

		sum_ht += colorLeftSensor.red_calibrated + colorLeftSensor.green_calibrated + colorLeftSensor.blue_calibrated;

		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

	ht_results[0] = sum_ht;
}

void ReadRightWash(short len_millimeters, short speed){
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
		readSensorRaw(&colorRightSensor,  &WashInfoRawRight);

		sum_rr += colorRightSensor.red_calibrated;
		sum_gr += colorRightSensor.green_calibrated;
		sum_br += colorRightSensor.blue_calibrated;

		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

	ht_results[1] = sum_rr + sum_gr + sum_br;
}

void readRightSen_noMove(int count_times, CalibrationHiTechData* calibration){
	int sum_rr = 0;
	int sum_gr = 0;
	int sum_br = 0;
	
	for (int i = 0; i < count_times; i++){
		readSensorRaw(&colorRightSensor, calibration);

		sum_rr += colorRightSensor.red_calibrated;
		sum_gr += colorRightSensor.green_calibrated;
		sum_br += colorRightSensor.blue_calibrated;
		delay(7);
	}

	ht_results[1] = sum_rr + sum_gr + sum_br;
}

void readLeftSen_noMove(int count_times, CalibrationHiTechData* calibration){
	int sum_rr = 0;
	int sum_gr = 0;
	int sum_br = 0;
	
	for (int i = 0; i < count_times; i++){
		readSensorRaw(&colorLeftSensor, calibration);

		sum_rr += colorLeftSensor.red_calibrated;
		sum_gr += colorLeftSensor.green_calibrated;
		sum_br += colorLeftSensor.blue_calibrated;
	}

	ht_results[0] = sum_rr + sum_gr + sum_br;
}