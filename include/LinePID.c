float SteerCounter(int speed)
{
	if ((getMotorSpeed(motorB) + fabs(motorA)) / 2 < 32)
	{
		results_sensors = SensorsToPercent();

		float error = results_sensors->secondSensor - results_sensors->firstSensor;

		float actionP = error * Kp_slow;
		float actionI = (error + pr_error) * Ki_slow;
		float actionD = (error - pr_error) * Kd_slow;
		float steer = actionP + actionI + actionD;
		pr_error = error;
		return steer;
	}
	else
	{
		results_sensors = SensorsToPercent();

		float error = results_sensors->secondSensor - results_sensors->firstSensor;

		float actionP = error * Kp_norm;
		float actionI = (error + pr_error) * Ki_norm;
		float actionD = (error - pr_error) * Kd_norm;
		float steer = actionP + actionI + actionD;
		pr_error = error;
		return steer;
	}
}

void DrivePID(int speed)
{
	float steer = SteerCounter(speed);
	setMotorSpeed(leftMotor, -speed + steer);
	setMotorSpeed(rightMotor, speed + steer);
	delay(2);
}

void AccelerationLinePID(float len_millimeters, int line_stop = 0, float speed_up_part = 0.5, float start_speed = min_speed_const, float accel = acceleration)
{
	float start_time = getTimerValue(T1);
	float speed = start_speed;
	float enc_left_motor = getMotorEncoder(leftMotor);
	float enc_right_motor = getMotorEncoder(rightMotor);

	float moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
	float now_millimeters = DegreesToMillimeters(moved_motors);

	while (now_millimeters < len_millimeters * speed_up_part)
	{
		speed = SpeedCounter(start_speed, 1, getTimerValue(T1) - start_time, accel);
		if (speed > max_speed_const)
		{
			speed = max_speed_const;
		}
		DrivePID(speed);
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
		DrivePID(speed);
		float moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

	if (line_stop == 1)
	{
		playTone(1500, 10);
		while ((results_sensors->firstSensor > 27 || (results_sensors->secondSensor > 27))
		{
			DrivePID(start_speed);
		}
	}
}

void AccelerationDist(float len_millimeters, float speed_up_part = 0.5, float start_speed = min_speed_const, float accel = acceleration)
{
	float start_time = getTimerValue(T1);
	float speed = start_speed;
	float enc_left_motor = getMotorEncoder(leftMotor);
	float enc_right_motor = getMotorEncoder(rightMotor);

	float moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
	float now_millimeters = DegreesToMillimeters(moved_motors);

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

		float moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
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

		float moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}
}

void AccelerationLinePIDSlow(float len_millimeters, int line_stop = 0, float speed_up_part = 0.5, float start_speed = min_speed_const)
{
	AccelerationLinePID(len_millimeters, line_stop, speed_up_part, start_speed, acceleration_slow);
}

void AccelerationLinePIDFast(float len_millimeters, int line_stop = 0, float speed_up_part = 0.5, float start_speed = min_speed_const)
{
	AccelerationLinePID(len_millimeters, line_stop, speed_up_part, start_speed, acceleration_fast);
}

void AccelerationLinePIDSuperFast(float len_millimeters, int line_stop = 0, float speed_up_part = 0.5, float start_speed = min_speed_const)
{
	AccelerationLinePID(len_millimeters, line_stop, speed_up_part, start_speed, acceleration_superFast);
}

void AccelerationDistSlow(float len_millimeters, float speed_up_part = 0.5, float start_speed = min_speed_const)
{
	AccelerationDist(len_millimeters, speed_up_part, start_speed, acceleration_slow);
}

void AccelerationDistFast(float len_millimeters, float speed_up_part = 0.5, float start_speed = min_speed_const)
{
	AccelerationDist(len_millimeters, speed_up_part, start_speed, acceleration_fast);
}