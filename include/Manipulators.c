byte taskFlag_setNormAfterWaterFullDown = 0;
byte taskFlag_motorWaterFullDown = 0;
byte taskFlag_motorGrabFullDown = 0;
byte taskFlag_closeAndHoldGraber = 0;
byte taskFlag_normalizeCentMotor = 0;
byte taskFlag_BallDrop = 0;
byte taskFlag_prepareForCube = 0;
byte taskFlag_prepareForBall = 0;
byte taskFlag_dropBottleOnTable = 0;
byte taskFlag_OneCubePreBall = 0;
byte taskFlag_prepareForDropFirst = 0;

task setNormAfterWaterFullDown(){
    taskFlag_setNormAfterWaterFullDown = 1;

    stopMotor(centMotor, 1);
    float start_deg = fabs(nMotorEncoder[centMotor]);
    short sign =   getSign(nMotorEncoder[centMotor]);
    short deg = 220 * -1;
	motor[centMotor] = -15 * sign;
	while (MotorAbsMovedDegrees(centMotor, start_deg) < (fabs(deg))){
        if (getSign(nMotorEncoder[centMotor]) != sign){
            break;
        }
    }
    stopMotor(centMotor, 1);

    resetMotorEncoder(centMotor);

    taskFlag_setNormAfterWaterFullDown = 0;
    stopTask(setNormAfterWaterFullDown);
}

task motorWaterFullDown(){
    taskFlag_motorWaterFullDown = 1;
    int past_enc_centMotor = fabs(nMotorEncoder[centMotor]);
    setMotorSpeed(centMotor, -100);
    sleep(200);
    while (fabs(nMotorEncoder[centMotor]) - fabs(past_enc_centMotor) > 1){
        past_enc_centMotor = nMotorEncoder[centMotor];
        sleep(10);
    }
    sleep(100);
    taskFlag_motorWaterFullDown = 0;
    stopTask(motorWaterFullDown);
}

task motorGrabFullDown(){
    taskFlag_motorGrabFullDown = 1;
    int past_enc_centMotor = fabs(nMotorEncoder[centMotor]);
    setMotorSpeed(centMotor, 100);
    sleep(200);
    while (fabs(nMotorEncoder[centMotor]) - fabs(past_enc_centMotor) > 1){
        past_enc_centMotor = nMotorEncoder[centMotor];
        setMotorSpeed(centMotor, 100);
        sleep(50);
    }
    taskFlag_motorGrabFullDown = 0;
    stopTask(motorGrabFullDown);
}

task closeAndHoldGraber()
{
    taskFlag_closeAndHoldGraber = 1;

    setMotorSpeed(grabMotor, 100);
    sleep(1400);
    setMotorSpeed(grabMotor, 100);
    
    taskFlag_closeAndHoldGraber = 0;
    stopTask(closeAndHoldGraber);
}

task BallDrop(){
    taskFlag_BallDrop = 1;

    stopMotor(centMotor, 1);
    moveMotor(centMotor, 212, 70, 1);
    stopMotor(centMotor, 1);
    delay(25);
    moveMotor(grabMotor, -130, -90, 0);
    delay(100);
    taskFlag_BallDrop = 0;
    stopTask(BallDrop);
}

task OneCubePreBall(){
    taskFlag_OneCubePreBall = 1;

    int past_enc_grabMotor = fabs(nMotorEncoder[grabMotor]);
    motor[grabMotor] = 100;
    sleep(100);
    while (fabs(nMotorEncoder[grabMotor]) - fabs(past_enc_grabMotor) > 1){
        past_enc_grabMotor = nMotorEncoder[grabMotor];
        sleep(10);
    }
    stopMotor(grabMotor, 1);

    moveMotor(grabMotor, -235, -100, 1);

    taskFlag_OneCubePreBall = 0;
}

task normalizeCentMotor()
{
    taskFlag_normalizeCentMotor = 1;

    stopMotor(centMotor, 1);
    float start_deg = fabs(nMotorEncoder[centMotor]);
    short sign =   getSign(nMotorEncoder[centMotor]);
    short deg = nMotorEncoder[centMotor] * -1;
	motor[centMotor] = -35 * sign;
	while (MotorAbsMovedDegrees(centMotor, start_deg) < (fabs(deg))){
        if (getSign(nMotorEncoder[centMotor]) != sign){
            break;
        }
    }
    stopMotor(centMotor, 1);

    motor[centMotor] = 0;
    taskFlag_normalizeCentMotor = 0;
    stopTask(normalizeCentMotor);
}

task prepareForCube(){
    taskFlag_prepareForCube = 1;

    moveMotor(grabMotor, 300, 40, 1);
    stopMotor(grabMotor, 1);

    taskFlag_prepareForCube = 0;
    stopTask(prepareForCube);
}

task prepareForBall(){
    taskFlag_prepareForBall = 1;

    moveMotor(grabMotor, 300, 70, 1);
    motor[grabMotor] = 0;

    taskFlag_prepareForBall = 0;
    stopTask(prepareForBall);
}

task dropBottleOnTable(){
    taskFlag_dropBottleOnTable = 1;
    stopMotor(centMotor, 1);
    moveMotor(centMotor, 115, -15, 0);
    stopMotor(centMotor, 1);
    taskFlag_dropBottleOnTable = 0;
    stopTask(dropBottleOnTable);
}

task prepareForDropFirst(){
    taskFlag_prepareForDropFirst = 1;

    stopMotor(centMotor, 1);
    moveMotor(centMotor, 220, 60, 0);
    stopMotor(centMotor, 1);

    taskFlag_prepareForDropFirst = 0;

    stopTask(prepareForDropFirst);
}

task openGrabMotor(){
    motor[grabMotor] = -30;
    delay(2000);
    motor[grabMotor] = 0;
    stopTask(openGrabMotor);
}

void takeCube()
{
    moveMotor(grabMotor, 160, 40, 1);
}

void closeBall(){
    setMotorSpeed(grabMotor, 70);
    sleep(500);
}


/*
float driveMotorPID(int speed, int degrees, int startEncoder, tMotor motorName, short stop){
    error = degrees - (nMotorEncoder[motorName] - startEncoder);

    float actionP =  error * 5;
    float actionI = (error + error_manip) * 0.2;
    float actionD = (error - error_manip) * 10;

    float steer = actionP + actionI + actionD;

    error_manip = error;

    return steer
}
void moveMotorPID(int speed, int degrees, int startEncoder, tMotor motorName, short stop){
    float error = 1000;
    while (fabs(error)){
        float steer = driveMotorPID(speed, degrees, startEncoder, motorName);

        pr_error = error;
        if ((fabs(speed + steer)) > (speed)){
            motor[motorName] = speed * getSign(steer);
        }
        else{
            motor[motorName] = speed + steer;
        }

        
        delay(2);

        displayTextLine(4, "%d", error);
        displayTextLine(6, "%d", nMotorEncoder[motorName]);
        displayTextLine(8, "%d", steer);
        displayTextLine(10, "%d", startEncoder);
    }

    stopMotor(motorName, stop);
}
*/