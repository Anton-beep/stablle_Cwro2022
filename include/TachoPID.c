float SteerCounterTacho(float speed, SyncedMotorsPair MotorPair, short tankTurn = 0){
	float mot_max = MotorAbsMovedDegrees(MotorPair.max_motor_element, MotorPair.max_motor_enc);
	float mot_min = MotorAbsMovedDegrees(MotorPair.min_motor_element, MotorPair.min_motor_enc);
	float error;

	if (MotorPair.speed_cof == 0){
		error = 0;
	}
	else{
		error = (fabs(mot_max * MotorPair.speed_cof) - mot_min) / (fabs(MotorPair.speed_cof) + 1);
	}

	integral_sum += error;
	if (integral_sum > 100) {
		integral_sum = 100;
	}
	else if(integral_sum < -100){
		integral_sum = -100;
	}

	float actionP = tankTurn ? error * Kp_tank                    : error * Kp_tacho;
	float actionI = tankTurn ? integral_sum * Ki_tank             : integral_sum * Ki_tacho;
	float actionD = tankTurn ? (error - pr_error_tacho) * Kd_tank : (error - pr_error_tacho) * Kd_tacho;

	float steer = actionP + actionI + actionD;

	pr_error_tacho = error;

	return steer;
}

void DrivePIDTacho(int speed, SyncedMotorsPair MotorPair, short tankTurn = 0) {
	float steer = SteerCounterTacho(speed, MotorPair, tankTurn);
	short sgn_speed = sgn(speed);

	float speed_fab_max = fabs(speed);
	float speed_fab_min = fabs(speed * MotorPair.speed_cof);

	motor[MotorPair.max_motor_element] = (speed_fab_max - steer) * sgn_speed;
	motor[MotorPair.min_motor_element] = (speed_fab_min + steer) * sgn_speed * sgn(MotorPair.speed_cof);

	delay(2);
}

void resetErrors_PIDTacho(){
	pr_error_tacho = 0;
}
