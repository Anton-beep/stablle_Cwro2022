// flags for tasks
int taskFlag_motorWaterFullDown = 0;
int taskFlag_normalizeCentMotor = 0;
int taskFlag_normalizeCentMotorFAST = 0;
int taskFlag_motorGraberFullDown = 0;
int taskFlag_setNormAfterWaterFullDown = 0;
int taskFlag_openGraber = 0;
int taskFlag_prepareGraberForCube = 0;
int taskFlag_takeCube = 0;
int taskFlag_waterOnTable = 0;
int taskFlag_openBall = 0;
int taskFlag_downGraberForONEBall = 0;
int taskFlag_downGraberForBallAndCube = 0;
int taskFlag_closeAndHoldGraber = 0;
int taskFlag_openSecondCube = 0;
int taskFlag_downGraberForSecondCube = 0;
int taskFlag_downGraberForFirstCube = 0;
int taskFlag_openGraberCubeRooms = 0;
int taskFlag_slowOpenGraberForRoomsCube = 0;
int taskFlag_motorGraberDownTakeBall = 0;
int taskFlag_openGraberSlow = 0;

// water
int global_water_left = 0;
int global_water_right = 0;

// tasks

task normalizeCentMotor()
{
    taskFlag_normalizeCentMotor = 1;

    stopMotor(centMotor, 1);

    moveMotor(centMotor, getMotorEncoder(centMotor) * -1, getSign(getMotorEncoder(centMotor)) * -30, 1);

    taskFlag_normalizeCentMotor = 0;
}

task normalizeCentMotorFAST()
{
    taskFlag_normalizeCentMotorFAST = 1;

    stopMotor(centMotor, 1);

    moveMotor(centMotor, getMotorEncoder(centMotor) * -1, getSign(getMotorEncoder(centMotor)) * -80, 1);

    taskFlag_normalizeCentMotorFAST = 0;
}

task motorWaterFullDown()
{
    taskFlag_motorWaterFullDown = 1;

    setMotorSpeed(centMotor, -100);
    int past_enc_centMotor = getMotorEncoder(centMotor);
    sleep(100);
    while (fabs(getMotorEncoder(centMotor)) - fabs(past_enc_centMotor) > 1)
    {
        past_enc_centMotor = getMotorEncoder(centMotor);
        setMotorSpeed(centMotor, -100);
        sleep(100);
    }
    sleep(100);

    taskFlag_motorWaterFullDown = 0;
}

task slowOpenGraberForRoomsCube()
{
    taskFlag_slowOpenGraberForRoomsCube = 1;

    setMotorSpeed(grabMotor, -50);
    sleep(500);

    taskFlag_slowOpenGraberForRoomsCube = 0;
}

task setNormAfterWaterFullDown()
{
    taskFlag_setNormAfterWaterFullDown = 1;

    moveMotor(centMotor, 250, 30, 1);
    resetMotorEncoder(centMotor);

    taskFlag_setNormAfterWaterFullDown = 0;
}

task motorGraberFullDown()
{
    taskFlag_motorGraberFullDown = 1;

    setMotorSpeed(centMotor, 100);
    sleep(100);
    setMotorSpeed(centMotor, 100);
    sleep(100);
    setMotorSpeed(centMotor, 100);
    sleep(1000);
    stopMotor(centMotor, 1);

    taskFlag_motorGraberFullDown = 0;
}

task openGraber()
{
    taskFlag_openGraber = 1;

    setMotorSpeed(grabMotor, -100);
    int past_enc_grabMotor = getMotorEncoder(grabMotor);
    sleep(500);
    while (fabs(getMotorEncoder(grabMotor)) - fabs(past_enc_grabMotor) > 1)
    {
        past_enc_grabMotor = getMotorEncoder(grabMotor);
        setMotorSpeed(grabMotor, -100);
        sleep(150);
    }

    setMotorSpeed(grabMotor, 10);
    sleep(100);
    setMotorSpeed(grabMotor, -5);
    sleep(500);
    stopMotor(grabMotor, 0);

    taskFlag_openGraber = 0;
}

task openGraberSlow()
{
    taskFlag_openGraberSlow = 1;

    setMotorSpeed(grabMotor, -60);
    int past_enc_grabMotor = getMotorEncoder(grabMotor);
    sleep(500);
    while (fabs(getMotorEncoder(grabMotor)) - fabs(past_enc_grabMotor) > 1)
    {
        past_enc_grabMotor = getMotorEncoder(grabMotor);
        setMotorSpeed(grabMotor, -60);
        sleep(150);
    }

    setMotorSpeed(grabMotor, 10);
    sleep(100);
    setMotorSpeed(grabMotor, -5);
    sleep(500);
    stopMotor(grabMotor, 0);

    taskFlag_openGraberSlow = 0;
}

task prepareGraberForCube()
{
    taskFlag_prepareGraberForCube = 1;

    moveMotor(grabMotor, 270, 100, 1);

    taskFlag_prepareGraberForCube = 0;
}

task takeCube()
{
    taskFlag_takeCube = 1;

    moveMotor(grabMotor, 120, 100, 1);

    taskFlag_takeCube = 0;
}

task waterOnTable()
{
    taskFlag_waterOnTable = 1;

    setMotorSpeed(centMotor, -100);
    int past_enc_centMotor = getMotorEncoder(centMotor);
    sleep(80);
    while (fabs(getMotorEncoder(centMotor)) - fabs(past_enc_centMotor) > 1)
    {
        past_enc_centMotor = getMotorEncoder(centMotor);
        setMotorSpeed(centMotor, -100);
        sleep(80);
    }
    sleep(100);

    taskFlag_waterOnTable = 0;
}

task downGraberForONEBall()
{
    taskFlag_downGraberForONEBall = 1;

    moveMotor(centMotor, 200, 70, 1);
    sleep(50);

    taskFlag_downGraberForONEBall = 0;
}

task downGraberForBallAndCube()
{
    taskFlag_downGraberForBallAndCube = 1;

    moveMotor(centMotor, 200, 50, 1);
    sleep(50);

    taskFlag_downGraberForBallAndCube = 0;
}

task openBall()
{
    taskFlag_openBall = 1;

    moveMotor(grabMotor, 250, -100, 1);

    taskFlag_openBall = 0;
}

task closeAndHoldGraber()
{
    taskFlag_closeAndHoldGraber = 1;

    setMotorSpeed(grabMotor, 100);
    sleep(1400);
    setMotorSpeed(grabMotor, 100);

    taskFlag_closeAndHoldGraber = 0;
}

task openSecondCube()
{
    taskFlag_openSecondCube = 1;

    moveMotor(grabMotor, 150, -100, 1);

    taskFlag_openSecondCube = 0;
}

task downGraberForSecondCube()
{
    taskFlag_downGraberForSecondCube = 1;

    moveMotor(centMotor, 290, 60, 1);
    sleep(500);

    taskFlag_downGraberForSecondCube = 0;
}

task downGraberForFirstCube()
{
    taskFlag_downGraberForFirstCube = 1;

    moveMotor(centMotor, -45, -70, 0);

    taskFlag_downGraberForFirstCube = 0;
}

task openGraberCubeRooms()
{
    taskFlag_openGraberCubeRooms = 1;

    moveMotor(grabMotor, -100, -100, 1);

    taskFlag_openGraberCubeRooms = 0;
}

/*
task motorGraberDownTakeBall()
{
    taskFlag_motorGraberDownTakeBall = 1;

    moveMotor(centMotor, 380, 100, 1);

    taskFlag_motorGraberDownTakeBall = 0;
}
*/