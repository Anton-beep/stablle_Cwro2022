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

task setNormAfterWaterFullDown(){
    taskFlag_setNormAfterWaterFullDown = 1;
    moveMotor(centMotor, 220, 30, 1);
    resetMotorEncoder(centMotor);
    motor[centMotor] = 0;
    taskFlag_setNormAfterWaterFullDown = 0;
    stopTask(setNormAfterWaterFullDown);
}

task motorWaterFullDown(){
    taskFlag_motorWaterFullDown = 1;
    int past_enc_centMotor = fabs(nMotorEncoder[centMotor]);
    sleep(200);
    setMotorSpeed(centMotor, -100);
    sleep(100);
    while (fabs(nMotorEncoder[centMotor]) - fabs(past_enc_centMotor) > 1){
        past_enc_centMotor = nMotorEncoder[centMotor];
        sleep(10);
    }
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
        sleep(20);
        setMotorSpeed(centMotor, 100);
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
    moveMotor(centMotor, 190, 100, 1);
    stopMotor(centMotor, 1);
    moveMotor(grabMotor, -140, -100, 1);

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

    moveMotor(grabMotor, -250, -100, 1);

    taskFlag_OneCubePreBall = 0;
}

task normalizeCentMotor()
{
    taskFlag_normalizeCentMotor = 1;

    stopMotor(centMotor, 1);
    float start_deg = fabs(nMotorEncoder[centMotor]);
    short sign =   getSign(nMotorEncoder[centMotor]);
    short deg = nMotorEncoder[centMotor] * -1;
	motor[centMotor] = -25 * sign;
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

    moveMotor(grabMotor, 155, 100, 1);
    motor[grabMotor] = 0;
    stopMotor(grabMotor, 1);

    taskFlag_prepareForCube = 0;
    stopTask(prepareForCube);
}

task prepareForBall(){
    taskFlag_prepareForBall = 1;

    moveMotor(grabMotor, 300, 100, 1);
    motor[grabMotor] = 0;

    taskFlag_prepareForBall = 0;
    stopTask(prepareForBall);
}

task dropBottleOnTable(){
    taskFlag_dropBottleOnTable = 1;
    stopMotor(centMotor, 1);
    moveMotor(centMotor, 110, -20, 0);
    stopMotor(centMotor, 1);
    taskFlag_dropBottleOnTable = 0;
    stopTask(dropBottleOnTable);
}

void takeCube()
{
    moveMotor(grabMotor, 135, 40, 1);
}

void takeSecondCube(){
    setMotorSpeed(grabMotor, 70);
    sleep(300);
}

void closeBall(){
    setMotorSpeed(grabMotor, 70);
    sleep(500);
}