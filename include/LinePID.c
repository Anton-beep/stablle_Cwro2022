void DrivePID(int speed, float firstElement = 0, float secondElement = 0, short reverse = 0){
	results_sensors = SensorsToPercent();

	firstElement =  firstElement  ? firstElement  : results_sensors-> firstSensor;
	secondElement = secondElement ? secondElement : results_sensors->secondSensor;

	float error = reverse ? secondElement - firstElement : firstElement - secondElement;

	float actionP = error * Kp_norm * (speed / max_speed_const);
	float actionI = (error + pr_error) * Ki_norm;
	float actionD = (error - pr_error) * Kd_norm * (speed / max_speed_const);
	float steer = actionP + actionI + actionD;
	pr_error = error;

	motor[leftMotor] = -speed + steer;
	motor[rightMotor] = speed + steer;
	delay(2);
}

void AccelerationLinePID (float len_millimeters, int line_stop = 0, float speed_up_part = 0.5, float start_speed = min_speed_const, float accel = acceleration, float firstElement = 0, float secondElement = 0, short reverse = 1){
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
	float start_time = getTimerValue(T1);
	float speed = start_speed;
	float enc_left_motor = nMotorEncoder[leftMotor];
	float enc_right_motor = nMotorEncoder[rightMotor];

	float moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
	float now_millimeters = DegreesToMillimeters(moved_motors);

	while (now_millimeters < len_millimeters * speed_up_part)
	{
		speed = SpeedCounter(start_speed, 1, getTimerValue(T1) - start_time, accel);
		if (speed > max_speed_const)
		{
			speed = max_speed_const;
		}
		DrivePID(speed, firstElement, secondElement, reverse);
		float moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

	float max_part_speed = speed;
	start_time = getTimerValue(T1);
	while (now_millimeters < len_millimeters)
	{
		speed = SpeedCounter(max_part_speed, -1, getTimerValue(T1) - start_time, accel);
		if (speed < min_speed_const)
		{
			speed = min_speed_const;
		}
		DrivePID(speed, firstElement, secondElement, reverse);
		float moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

	if (line_stop == 1)
	{
		playTone(1500, 10);
		if ((firstElement == 0) && (secondElement == 0)){
			while ((results_sensors->firstSensor > 27) || (results_sensors->secondSensor > 27)){
			DrivePID(start_speed);
			}
		}
		else if (firstElement == 0){
			while (results_sensors->secondSensor > 80){
			DrivePID(start_speed);
			}
		}
		else{
			while (results_sensors->firstSensor > 80){
			DrivePID(start_speed);
			}
		}
	}
}

void AccelerationDist(float len_millimeters, float speed_up_part = 0.5, float start_speed = min_speed_const, float accel = acceleration){
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
	float start_time = getTimerValue(T1);
	float speed = start_speed;
	float enc_left_motor = nMotorEncoder[leftMotor];
	float enc_right_motor = nMotorEncoder[rightMotor];

	float moved_motors = 0;
	float now_millimeters = 0;

	SyncedMotorsPair turn_pair;

	turn_pair.max_motor_element = rightMotor;
	turn_pair.min_motor_element = leftMotor;

	turn_pair.speed_cof = -1;

	turn_pair.max_motor_enc = enc_right_motor;
	turn_pair.min_motor_enc = enc_left_motor;

	int sgn_speed = sgn(len_millimeters);
	len_millimeters = fabs(len_millimeters);
	speed *= sgn_speed;
	start_speed *= sgn_speed;

	while (now_millimeters < len_millimeters * speed_up_part)
	{
		speed = SpeedCounter(start_speed, sgn_speed, getTimerValue(T1) - start_time, accel);
		if (fabs(speed) > max_speed_const)
		{
			speed = max_speed_const * sgn_speed;
		}

		DrivePIDTacho(speed, turn_pair);

		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

	float max_part_speed = speed;
	start_time = getTimerValue(T1);
	char flag = 1;
	while (now_millimeters < len_millimeters)
	{
		if (flag)
		{
			speed = SpeedCounter(max_part_speed, sgn_speed * -1, getTimerValue(T1) - start_time, accel);
		}
		if (fabs(speed) < min_speed_const)
		{
			speed = min_speed_const * sgn_speed;
			flag = 0;
		}

		DrivePIDTacho(speed, turn_pair);

		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}
}
