float TakeBottles(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    TankTurn(45);
    preTurnStop();
    AccelerationDist(100, 1);
    AccelerationLinePID(160, 1, 0, motor[rightMotor]);

    preTurnStop();

    TankTurn(180);

    preTurnStop();

    startTask(motorWaterFullDown);

    AccelerationLinePID(40, 0);
    AccelerationDist(50, 0, motor[rightMotor]);

    preTurnStop();
    AccelerationDist(-160);

    startTask(setNormAfterWaterFullDown);
    preTurnStop();

    AccelerationLinePID(80);
    AccelerationDist(15);

    PointTurn(250, 0, 90, 1);

    AccelerationLinePID(370, 1, 0.6);

    #if TIMER == 1
        return getTimerValue(T2) - start_time;
    #else
        return 0;
    #endif
}

float readIndicators(short preTurnmm = 18){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    AccelerationLinePID(110, 0, 0.01);
    ReadIndicator(33, 15);

    float enc_left_motor =   fabs(nMotorEncoder[leftMotor]);
	float enc_right_motor = fabs(nMotorEncoder[rightMotor]);

	float moved_motors = 0;
	float now_millimeters = 0;

    while(now_millimeters < preTurnmm) {
		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

    left_room_indicator  = get_colorMarker_left(ht_results[0]);
    right_room_indicator = get_colorMarker_right(ht_results[1]);

    RightWheelTurn(90);
    AccelerationLinePID(50, 0, 0, 10, acceleration, 0, 82, 0, 10);

    #if LOGGING == 1
        writeIndicators(ht_results[0], ht_results[1]);
    #endif

    #if TIMER == 1
        return getTimerValue(T2) - start_time;
    #else
        return 0;
    #endif
}

void fromRightRoomToLeft(int degrees){
    if (now_cubes == 0){
        motor[grabMotor] = -60;
    }

    if (now_cubes == 1){
        startTask(OneCubePreBall);
    }

    AccelerationLinePID(degrees - 10, 0, 0.7, min_speed_const, acceleration - 0.01, 82, 0, 0, 10);

    float speed = fabs(motor[leftMotor]);

    while ((results_sensors.firstSensor > 50) || (results_sensors.secondSensor > 50)){
		DrivePID(speed, 82, 0, 0);
    }

    if (now_cubes == 0){
        motor[grabMotor] = 0;
    }
    
    AccelerationDist(30, 0.7, speed);
    
    speed = fabs(motor[leftMotor]);

    AccelerationLinePID(170, 0.82, 0, speed, acceleration, 82, 0, 0, 10);

    speed = fabs(motor[leftMotor]);

    AccelerationDist(203, 0, speed);
}

void getCube(short angle = 90){ // 1 - Right room, -1 - Left room
    preTurnStop();
    TankTurn(angle);
    preTurnStop();
    startTask(motorGrabFullDown);
    startTask(prepareForCube, 20);
    AccelerationDist(20, 0, 14, 14);
    AccelerationDist(27, 0.2, 13, 12);

    preTurnStop(100);

    waitTask(&taskFlag_motorGrabFullDown);
    waitTask(&taskFlag_prepareForCube);
    takeCube();
    now_cubes++;
}

void getSecondCube(){
    preTurnStop();
    TankTurn(-90);
    preTurnStop();
    AccelerationDist(-10, 0);
    startTask(motorGrabFullDown);
    preTurnStop();
    waitTask(&taskFlag_motorGrabFullDown);
    motor[grabMotor] = 60;
    AccelerationDist(57, 0);
    preTurnStop();
    delay(100);
    now_cubes++;
}

void BallRightRoom(byte cube = 0){
    short add_angle = 0;
    if (cube){
        getCube();
    }

    if (cube == 0){
        if (now_cubes){
            startTask(OneCubePreBall);
        }
        else{
            startTask(prepareForBall);
        }
    }

    if (cube){
        AccelerationDist(-47, 0);
        preTurnStop();
        TankTurn(-52);
        preTurnStop();
    }
    else{
        startTask(motorGrabFullDown);
        preTurnStop();
        TankTurn(37);
        preTurnStop();
        add_angle = -3;
    }

    waitTask(&taskFlag_motorGrabFullDown);
    AccelerationDist(75, 0.5,  min_speed_const,  min_speed_const, 0.02);
    AccelerationDist(17, 0, min_speed_const, 11);
    preTurnStop();
    closeBall();
    startTask(normalizeCentMotor);
    TankTurn(-98);
    preTurnStop();
    stopMotor(centMotor, 1);


    stopTask(prepareForBall);
    stopTask(prepareForCube);

    startTask(BallDrop);
    AccelerationDist(45);
    preTurnStop();
    waitTask(&taskFlag_BallDrop);
    startTask(normalizeCentMotor);

    TankTurn(-117 + add_angle);
    preTurnStop();
    AccelerationDist(115);

    fromRightRoomToLeft(160);
}

void fromFramesToSecondPairRooms(){
    preTurnStop();
    AbsTurn(223);
    preTurnStop();
    AccelerationDist(230);
    motor[leftMotor] = -12;
    motor[rightMotor] = 12;
    results_sensors.firstSensor = 100;
    while (results_sensors.firstSensor > 10){
        SensorsToPercent();
    }
    preTurnStop();
    RightWheelTurn(28);
    AccelerationLinePID(50, 1, 0.5, min_speed_const, acceleration, 0, 70, 0, 10);
    LeftWheelTurn(18);
    preTurnStop(50);
    AccelerationLinePID(100, 1);
}

void WaterRightRoom(byte cube = 0){
    if (cube){
        getCube();
    }
    else{
        preTurnStop();
        TankTurn(90);
        AccelerationDist(47, 0);
        preTurnStop(50);
    }

    if (cube){
        startTask(normalizeCentMotor);
        waitTask(&taskFlag_normalizeCentMotor);
        delay(200);
    }

    startTask(dropBottleOnTable);
    if (right_bottle){
        LeftWheelTurn(-30);
    }
    else{
        RightWheelTurn(-30);
    }

    preTurnStop(100);
	waitTask(&taskFlag_dropBottleOnTable);
    moveMotor(centMotor, -50, -10, 1);

    AccelerationDist(50);
    motor[centMotor] = 0;
    startTask(normalizeCentMotor);
    preTurnStop();
    if (right_bottle){
        LeftWheelTurn(-63);
        AccelerationDist(75);
        right_bottle = 0;
    }
    else {
        RightWheelTurn(22);
        LeftWheelTurn(-97.5);
        AccelerationDist(130);
        left_bottle = 0;
    }
    fromRightRoomToLeft(160);
}

float RightRoom(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    AccelerationDist(196, 0.4);

    preTurnStop(200);
    readRightSen_noMove(5, &WashInfoRawRight, 20);

    short cube = get_colorWash_right(ht_results[1]);
    cubes[0] = cube;
    
    AccelerationDist(-39, 0);
    if (right_room_indicator == 2){
        BallRightRoom(cube);
    }
    else{
        WaterRightRoom(cube);
    }

    #if LOGGING == 1
        writeRightRoomInfo(ht_results[1], cube);
    #endif

    #if TIMER == 1
        return getTimerValue(T2) - start_time;
    #else
        return 0;
    #endif
}

void BallLeftRoom(byte cube = 0){

    short add_angle = 0;

    if (cube){
        getCube(-90);
    }

    if (cube == 0){
        if (now_cubes){
            startTask(OneCubePreBall);
        }
        else{
            startTask(prepareForBall);
        }
    }

    if (cube){
        AccelerationDist(-47, 0);
        preTurnStop();
        TankTurn(50);
        preTurnStop();
    }
    else{
        startTask(motorGrabFullDown);
        preTurnStop();
        TankTurn(-37);
        preTurnStop();
        add_angle = 0;
    }

    waitTask(&taskFlag_motorGrabFullDown);
    AccelerationDist(88, 0.5,  min_speed_const,  min_speed_const, 0.02);
    AccelerationDist(12, 0, min_speed_const, 11);
    preTurnStop();
    closeBall();
    startTask(normalizeCentMotor);
    TankTurn(98);
    preTurnStop();
    stopMotor(centMotor, 1);


    stopTask(prepareForBall);
    stopTask(prepareForCube);

    startTask(BallDrop);
    AccelerationDist(45);
    preTurnStop();
    waitTask(&taskFlag_BallDrop);

    if ((now_cubes == 2) && (left_room_indicator == 2) && (cube)){
        TankTurn(-38);
        preTurnStop();
        AccelerationDist(-10);
        preTurnStop();

        stopMotor(centMotor, 1);
        stopTask(prepareForBall);
        stopTask(prepareForCube);

        startTask(motorGrabFullDown);
        motor[grabMotor] = -60;
        delay(100);
        motor[grabMotor] = 0;
        waitTask(&taskFlag_motorGrabFullDown);

        motor[centMotor] = 100;
        delay(200);
        motor[centMotor] = 0;

        motor[grabMotor] = 80;
        delay(200);
        add_angle = 42;
        startTask(normalizeCentMotor);
        delay(200);
        motor[grabMotor] = 0;
        short buffer = cubes[0];
        cubes[0] = cubes[1];
        cubes[1] = buffer;
    }
    else{
        startTask(normalizeCentMotor);
        preTurnStop();
    }

    TankTurn(116 + add_angle);
    preTurnStop();
    AccelerationDist(115);

    AccelerationLinePID(170, 1, 0.5, min_speed_const, acceleration, 0, 70, 0, 10);
}

void WaterLeftRoom(byte cube = 0){
    if ((now_cubes) && (cube)) {
        getSecondCube();
    }
    else if (cube){
        getCube(-90);
    }
    else{
        preTurnStop();
        TankTurn(-90);
        AccelerationDist(47, 0);
        preTurnStop(50);
    }

    if (cube){
        startTask(normalizeCentMotor);
        waitTask(&taskFlag_normalizeCentMotor);
        delay(200);
    }

    startTask(dropBottleOnTable);
    if (left_bottle){
        RightWheelTurn(-30);
    }
    else{
        LeftWheelTurn(-30);
    }

    BrakeLeftRightMotor(1);
	waitTask(&taskFlag_dropBottleOnTable);

    moveMotor(centMotor, -50, -10, 1);

    AccelerationDist(50);
    motor[centMotor] = 0;
    startTask(normalizeCentMotor);
    preTurnStop();
    if (left_bottle){
        RightWheelTurn(-63);
        AccelerationDist(75);
        left_bottle = 0;
    }
    else {
        LeftWheelTurn(30);
        RightWheelTurn(-93);
        AccelerationDist(130);
        right_bottle = 0;
    }

    AccelerationLinePID(170, 1, 0.5, min_speed_const, acceleration, 0, 70, 0, 10);
}

float LeftRoom(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    if (now_cubes == 0){
        motor[grabMotor] = -30;
    }

    preTurnStop(200);
    readLeftSen_noMove(5,  &WashInfoRawLeft, 20);

    motor[grabMotor] = 0;

    short cube = get_colorWash_left(ht_results[0]);
    cubes[1] = cube;
    short add_deg = 0;
    if ((now_cubes) && (left_room_indicator == 2) && (cube)){
        AccelerationDist(30, 0);
        preTurnStop();
        startTask(motorGrabFullDown);
        TankTurn(15);
        preTurnStop(0);
        waitTask(&taskFlag_motorGrabFullDown);
        motor[grabMotor] = -100;
        delay(100);
        startTask(normalizeCentMotor);
        AccelerationDist(50, 0);
        preTurnStop();
        AccelerationDist(-50, 0);
        preTurnStop();
        TankTurn(-15);
        motor[grabMotor] = 0;
        preTurnStop();
        add_deg = -30;
    }

    AccelerationDist(-39 + add_deg, 0);
    if (left_room_indicator == 2){
        BallLeftRoom(cube);
    }
    else{
        WaterLeftRoom(cube);
    }

    #if LOGGING == 1
        writeLeftRoomInfo(ht_results[0], cube);
    #endif

    #if TIMER == 1
        return getTimerValue(T2) - start_time;
    #else
        return 0;
    #endif
}

void fromFirstPairRoomsToFrames(){
    RightWheelTurn(104);
    pr_error = 0;
    AccelerationLinePID(290, 1, 0.7);
    AccelerationLinePID(217, 0, 0.5, fabs(motor[leftMotor]));
    float speed = fabs(motor[rightMotor]);
    PointTurn(250, 0, 90, 1, 0.3, speed);
}

void fromSecondPairRoomsToFrames(){
    RightWheelTurn(105);
    AccelerationLinePID(20, 0, 1);
    AccelerationLinePID(270, 1, 0.48);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();
    TankTurn(-20);
    preTurnStop();
    AccelerationDist(430);
    preTurnStop();
    TankTurn(-70);
    preTurnStop(50);
    AccelerationLinePID(60, 1);
    NOW_ANGLE = 360;
}

void drop1in1(){
    AbsTurn(90);
    preTurnStop(50);
    AccelerationDist(10, 0);
    preTurnStop();
    startTask(prepareForDropFirst);
    LeftWheelTurn(90);
    preTurnStop(200);
	waitTask(&taskFlag_prepareForDropFirst);
    AccelerationDist(-50, 0);
    motor[grabMotor] = -50;
    preTurnStop();
    delay(50);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    AccelerationDist(50, 0);
    LeftWheelTurn(-90);
    AccelerationDist(-10, 0);
}
void drop2in1(){
    AbsTurn(90);
    preTurnStop(50);
    AccelerationDist(10, 0);
    preTurnStop();
    startTask(prepareForDropFirst);
    LeftWheelTurn(90);
    preTurnStop(200);
	waitTask(&taskFlag_prepareForDropFirst);
    motor[grabMotor] = -60;
    delay(500);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    LeftWheelTurn(-90);
    AccelerationDist(-10, 0);
}

void drop1in3(){
    AbsTurn(270);
    preTurnStop(50);
    AccelerationDist(10, 0);
    preTurnStop();
    startTask(prepareForDropFirst);
    RightWheelTurn(90);
    preTurnStop();
	waitTask(&taskFlag_prepareForDropFirst);
    AccelerationDist(-50, 0);
    motor[grabMotor] = -50;
    preTurnStop();
    delay(50);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    AccelerationDist(50, 0);
    preTurnStop();
    RightWheelTurn(-90);
    AccelerationDist(-10, 0);
}
void drop2in3(){
    AbsTurn(270);
    preTurnStop(50);
    AccelerationDist(10, 0);
    preTurnStop();
    startTask(prepareForDropFirst);
    RightWheelTurn(90);
    preTurnStop(200);
	waitTask(&taskFlag_prepareForDropFirst);
    motor[grabMotor] = -60;
    delay(500);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    RightWheelTurn(-90);
    AccelerationDist(-10, 0);
}

void drop1in2(){
    AbsTurn(360);
    startTask(prepareForDropFirst);
    preTurnStop();
	waitTask(&taskFlag_prepareForDropFirst);
    AccelerationDist(20, 0);
    motor[grabMotor] = -50;
    preTurnStop();
    delay(50);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    AccelerationDist(-20, 0);
}
void drop2in2(){
    AbsTurn(360);
    startTask(prepareForDropFirst);
    preTurnStop();
	waitTask(&taskFlag_prepareForDropFirst);
    AccelerationDist(60, 0);
    motor[grabMotor] = -60;
    preTurnStop();
    delay(200);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    AccelerationDist(-60, 0);
}

void readFrames(){
    preTurnStop();
    TankTurn(-73);

    preTurnStop();
    readRightSen_noMove(10, &FamesRawRight);

    framesColor[0] = get_colorFrame_first(ht_results[1]);
    rawFrames[0] = ht_results[1];

    TankTurn(-35);

    preTurnStop();
    readRightSen_noMove(10, &FamesRawRight);
    framesColor[1] = get_colorFrame_second(ht_results[1]);
    rawFrames[1] = ht_results[1];

    framesColor[2] = (10 - framesColor[0] - framesColor[1]);

    TankTurn(108);
    preTurnStop();
    NOW_ANGLE = 360;

    #if LOGGING == 1
        writeFramesInfo(rawFrames, framesColor);
    #endif
}

void frames(short reading = 1){
    if (reading){
        readFrames();
    }

    preTurnStop();
    AccelerationDist(-20, 0);
    preTurnStop();

    if (cubes[0] == 0){
        cubes[0] = -1;
        
    }
    if (cubes[1] == 0){
        cubes[1] = -1;
    }
    
    if (cubes[1] != -1 && cubes[0] == -1){
        cubes[0] = cubes[1];
        cubes[1] = -1;
    }

    if (cubes[1] == framesColor[0]){
        drop1in1();
    }
    else if (cubes[1] == framesColor[1]){
        drop1in2();
    }
    else if (cubes[1] == framesColor[2]){
        drop1in3();
    }

    preTurnStop(250);

    if (cubes[0] == framesColor[0]){
        drop2in1();
    }
    else if (cubes[0] == framesColor[1]){
        drop2in2();
    }
    else if (cubes[0] == framesColor[2]){
        drop2in3();
    }  
    startTask(openGrabMotor); 
}

void finish(){
    preTurnStop();
    AbsTurn(180);
    preTurnStop();
    AccelerationLinePID(35);
    AccelerationDist(215);
    preTurnStop();
    TankTurn(45);
    preTurnStop();
    AccelerationDist(10);
}