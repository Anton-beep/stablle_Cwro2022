// flags for tasks
int taskFlag_motorWaterFullDown = 0;
int taskFlag_normalizeCentMotor = 0;
int taskFlag_motorGraberFullDown = 0;
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

// water
int global_water_left = 0;
int global_water_right = 0;

// tasks
task normalizeCentMotor()
{
    taskFlag_normalizeCentMotor = 1;

    moveMotor(centMotor, getMotorEncoder(centMotor), getSign(getMotorEncoder(centMotor)) * 100, 1);

    taskFlag_normalizeCentMotor = 0;
}

task motorWaterFullDown()
{
    taskFlag_motorWaterFullDown = 1;

    setMotorSpeed(centMotor, -100);
    sleep(1000);
    stopMotor(centMotor, 1);

    taskFlag_motorWaterFullDown = 0;
}

task motorGraberFullDown()
{
    taskFlag_motorGraberFullDown = 1;

    setMotorSpeed(centMotor, 100);
    sleep(1000);
    stopMotor(centMotor, 1);

    taskFlag_motorGraberFullDown = 0;
}

task openGraber()
{
    taskFlag_openGraber = 1;

    setMotorSpeed(grabMotor, 100);
    sleep(1000);
    stopMotor(grabMotor, 1);

    taskFlag_openGraber = 0;
}

task prepareGraberForCube()
{
    taskFlag_prepareGraberForCube = 1;

    moveMotor(grabMotor, -200, -100, 1);

    taskFlag_prepareGraberForCube = 0;
}

task takeCube()
{
    taskFlag_takeCube = 1;

    moveMotor(grabMotor, -100, -100, 1);

    taskFlag_takeCube = 0;
}

task waterOnTable()
{
    taskFlag_waterOnTable = 1;

    setMotorSpeed(centMotor, -100);
    sleep(100);
    setMotorSpeed(centMotor, -30);
    sleep(600);
    stopMotor(centMotor, 0);
    sleep(100);

    taskFlag_waterOnTable = 0;
}

task downGraberForONEBall(){
    taskFlag_downGraberForONEBall = 1;

    moveMotor(centMotor, 400, 100, 1);
    sleep(500);

    taskFlag_downGraberForONEBall = 0;
}

task downGraberForBallAndCube(){
    taskFlag_downGraberForBallAndCube = 1;

    moveMotor(centMotor, 400, 100, 1);
    sleep(500);

    taskFlag_downGraberForBallAndCube = 0;
}

task openBall()
{
    taskFlag_openBall = 1;

    moveMotor(grabMotor, 100, 200, 1);

    taskFlag_openBall = 0;
}

task closeAndHoldGraber(){
    taskFlag_closeAndHoldGraber = 1;

    setMotorSpeed(grabMotor, -100);
    sleep(1000);
    setMotorSpeed(grabMotor, -65);

    taskFlag_closeAndHoldGraber = 0;
}

task openSecondCube(){
    taskFlag_openSecondCube = 1;

    moveMotor(grabMotor, 100, 100, 1);

    taskFlag_openSecondCube = 0;
}

task downGraberForSecondCube(){
    taskFlag_downGraberForSecondCube = 1;

    moveMotor(centMotor, 200, 100, 1);
    sleep(600);

    taskFlag_downGraberForSecondCube = 0;
}

task downGraberForFirstCube(){
    taskFlag_downGraberForFirstCube = 1;

    moveMotor(centMotor, 150, 100, 1);
    sleep(600);

    taskFlag_downGraberForFirstCube = 0;
}
