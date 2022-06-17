float SpeedCounter(float speed, int acceleration_value, int time_delta, float accel = acceleration)
{
	// acceleration value - 1 || -1, speed up or speed down
	float now_speed = speed + accel * time_delta * acceleration_value;
	return now_speed;
}

float DegreesToMillimeters(float degrees_input)
{
	float millimiters = degrees_input * PI * wheelDiameter / 360;
	return millimiters;
}

void BrakeLeftRightMotor(char stop_type = 0)
{
	if (stop_type)
	{
		setMotorBrakeMode(leftMotor, motorBrake);
		setMotorBrakeMode(rightMotor, motorBrake);
	}
	else
	{
		setMotorBrakeMode(leftMotor, motorCoast);
		setMotorBrakeMode(rightMotor, motorCoast);
	}
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;

	#if DEBUG == 1
		playSound(soundBlip);
	#endif
}

float MotorAbsMovedDegrees(tMotor motor_name, float start_value)
{
	float moved = (fabs(nMotorEncoder[motor_name]) - start_value);
	moved = fabs(moved);
	return moved;
}

float MotorsAbsMovedDegreesLR(float start_degrees_left, float start_degrees_right)
{
	float moved = (MotorAbsMovedDegrees(leftMotor, 	start_degrees_left) + MotorAbsMovedDegrees(rightMotor, start_degrees_right)) / 2;
	return moved;
}


void stopMotor(tMotor motor_name, char stop_type = 0)
{
	if (stop_type)
	{
		setMotorBrakeMode(motor_name, motorBrake);
	}
	else
	{
		setMotorBrakeMode(motor_name, motorCoast);
	}
	setMotorSpeed(motor_name, 0);
}

void moveMotor(tMotor motor, int deg, int speed, char stop)
{
	int start_deg = fabs(nMotorEncoder[motor]);
	setMotorSpeed(motor, speed);
	while (MotorAbsMovedDegrees(motor, start_deg) < fabs(deg))
	{
		displayCenteredTextLine(8, "%d", MotorAbsMovedDegrees(motor, start_deg));
	};
	stopMotor(motor, stop);
}

void preTurnStop(int time = 50){
	BrakeLeftRightMotor(1);
    resetError();
    delay(time);
}