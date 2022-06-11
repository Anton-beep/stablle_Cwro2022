float SteerCounterTacho(float speed, SyncedMotorsPair MotorPair){
	float mot_max = MotorAbsMovedDegrees(MotorPair.max_motor_element, MotorPair.max_motor_enc);
	float mot_min = MotorAbsMovedDegrees(MotorPair.min_motor_element, MotorPair.min_motor_enc);
	float error;

	if (MotorPair.speed_cof == 0){
		error = 0;
	}
	else{
		error =  (fabs(mot_max * MotorPair.speed_cof) - mot_min) / (fabs(MotorPair.speed_cof) + 1);
	}

	integral_sum += error;
	if (integral_sum > 100) {
		integral_sum = 100;
	}
	else if(integral_sum < -100){
		integral_sum = -100;
	}

	float actionP = error * Kp_tacho;
	float actionI = integral_sum * Ki_tacho;
	float actionD = (error - pr_error_tacho) * Kd_tacho;

	float steer = actionP + actionI + actionD;

	pr_error_tacho = error;

	return steer;
}

float SteerCounterTacho_smallKOF(float speed, SyncedMotorsPair MotorPair){
	float mot_max = MotorAbsMovedDegrees(MotorPair.max_motor_element, MotorPair.max_motor_enc);
	float mot_min = MotorAbsMovedDegrees(MotorPair.min_motor_element, MotorPair.min_motor_enc);
	float error;

	if (MotorPair.speed_cof == 0){
		error = 0;
	}
	else{
		error =  (fabs(mot_max * MotorPair.speed_cof) - mot_min) / (fabs(MotorPair.speed_cof) + 1);
	}

	float actionP = error * Kp_tacho * (speed / 60) * 0.25;
	float actionI = (error + pr_error_tacho) * Ki_tacho * 0.25;
	float actionD = (error - pr_error_tacho) * Kd_tacho * 0.25;

	float steer = actionP + actionI + actionD;

	pr_error_tacho = error;

	return steer;
}

void DrivePIDTacho(int speed, SyncedMotorsPair MotorPair, int seconds = 0) {
	float steer = SteerCounterTacho(speed, MotorPair);
	short sgn_speed = sgn(speed);

	float speed_fab_max = fabs(speed);
	float speed_fab_min = fabs(speed * MotorPair.speed_cof);

	setMotorSpeed(MotorPair.max_motor_element, (speed_fab_max - steer) * sgn_speed);
	setMotorSpeed(MotorPair.min_motor_element, (speed_fab_min + steer) * sgn_speed * sgn(MotorPair.speed_cof));

	delay(seconds);
}

void DrivePIDTacho_smallKOF(int speed, SyncedMotorsPair MotorPair, int seconds = 2) {
	float steer = SteerCounterTacho_smallKOF(speed, MotorPair);
	short sgn_speed = sgn(speed);

	float speed_fab_max = fabs(speed);
	float speed_fab_min = fabs(speed * MotorPair.speed_cof);

	setMotorSpeed(MotorPair.max_motor_element, (speed_fab_max - steer) * sgn_speed);
	setMotorSpeed(MotorPair.min_motor_element, (speed_fab_min + steer) * sgn_speed * sgn(MotorPair.speed_cof));

	delay(seconds);
}

void moveDriveSync(int deg, short speed, char stop){
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	int start_deg_left = getMotorEncoder(leftMotor);
	int start_deg_right = getMotorEncoder(rightMotor);
	SyncedMotorsPair turn_pair;

	turn_pair.max_motor_element = rightMotor;
	turn_pair.min_motor_element = leftMotor;

	turn_pair.speed_cof = -1;

	turn_pair.max_motor_enc = getMotorEncoder(leftMotor);
	turn_pair.min_motor_enc = getMotorEncoder(rightMotor);

	while (MotorsAbsMovedDegreesLR(start_deg_left, start_deg_right) < fabs(deg))
	{
		DrivePIDTacho(speed, turn_pair);
	}
	BrakeLeftRightMotor(stop);
}

void resetErrors_PIDTacho(){
	pr_error_tacho = 0;
}