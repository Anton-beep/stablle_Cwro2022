byte taskFlag_setNormAfterWaterFullDown = 0;
byte taskFlag_motorWaterFullDown = 0;
byte taskFlag_motorGrabFullDown = 0;
byte taskFlag_closeAndHoldGraber = 0;
byte taskFlag_normalizeCentMotor = 0;
byte taskFlag_BallDrop = 0;
byte taskFlag_prepareForCube = 0;
byte taskFlag_prepareForBall = 0;
byte taskFlag_dropBottleOnTable = 0;

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
    sleep(100);
    while (fabs(nMotorEncoder[centMotor]) - fabs(past_enc_centMotor) > 1){
        past_enc_centMotor = nMotorEncoder[centMotor];
        sleep(10);
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

    stopMotor(centMotor, 1)
    moveMotor(centMotor, 190, 100, 1);
    stopMotor(centMotor, 1);
    moveMotor(grabMotor, -100, -100, 1);

    taskFlag_BallDrop = 0;
    stopTask(BallDrop);
}

task normalizeCentMotor()
{
    taskFlag_normalizeCentMotor = 1;

    stopMotor(centMotor, 1);
    moveMotor(centMotor, getMotorEncoder(centMotor) * -1, getSign(getMotorEncoder(centMotor)) * -25, 1);
    stopMotor(centMotor, 1);

    motor[centMotor] = 0;
    taskFlag_normalizeCentMotor = 0;
    stopTask(normalizeCentMotor);
}

task prepareForCube(){
    taskFlag_prepareForCube = 1;

    moveMotor(grabMotor, 210, 100, 1);
    motor[grabMotor] = 0;

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
    stopMotor(centMotor, 1)
    moveMotor(centMotor, 108, -20, 0);
    stopMotor(centMotor, 1);
    taskFlag_dropBottleOnTable = 0;
    stopTask(dropBottleOnTable);
}

void takeCube()
{
    moveMotor(grabMotor, 160, 70, 1);
}

void closeBall(){
    setMotorSpeed(grabMotor, 70);
    sleep(500);
}