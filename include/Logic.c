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
    AccelerationLinePID(47, 0, 0, 10, acceleration, 0, 82, 0, 10);

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

    startTask(prepareForCube);
    startTask(motorGrabFullDown);
    AccelerationDist(45, 0, 16, 13, 0.05);
    preTurnStop(100);
    waitTask(&taskFlag_motorGrabFullDown);

    takeCube();
    now_cubes++;
}

void getSecondCube(){
    preTurnStop();
    TankTurn(-90);
    preTurnStop();
    AccelerationDist(-20, 0);
    startTask(motorGrabFullDown);
    preTurnStop();
    waitTask(&taskFlag_motorGrabFullDown);
    motor[grabMotor] = 60;
    AccelerationDist(67, 0);
    preTurnStop();
    now_cubes++;
}

void BallRightRoom(byte cube = 0){
    short add_angle = 0;
    if (cube){
        getCube();
    }
    else{
        preTurnStop();
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
        AccelerationDist(-43, 0);
        preTurnStop();
        TankTurn(-52);
        preTurnStop();
    }
    else{
        startTask(motorGrabFullDown);
        TankTurn(37);
        preTurnStop();
        add_angle = -3;
    }

    waitTask(&taskFlag_motorGrabFullDown);
    waitTask(&taskFlag_OneCubePreBall);
    waitTask(&taskFlag_prepareForBall);

    AccelerationDist(74, 0.5,  min_speed_const,  min_speed_const, 0.02);
    AccelerationDist(17, 0, min_speed_const, 11);
    preTurnStop();
    closeBall();
    startTask(normalizeCentMotor);
    TankTurn(-98);
    preTurnStop();
    waitTask(&taskFlag_normalizeCentMotor);

    startTask(BallDrop);
    AccelerationDist(45);
    preTurnStop();
    waitTask(&taskFlag_BallDrop);

    startTask(normalizeCentMotor);
    TankTurn(-117 + add_angle);
    preTurnStop();
    waitTask(&taskFlag_normalizeCentMotor);

    AccelerationDist(115);
    fromRightRoomToLeft(160);
}

void fromFramesToSecondPairRooms(){
    preTurnStop();
    AbsTurn(230);
    preTurnStop();
    AccelerationDist(230);
    motor[leftMotor] = -12;
    motor[rightMotor] = 12;
    results_sensors.firstSensor = 100;
    while (results_sensors.firstSensor > 20){
        SensorsToPercent();
    }
    preTurnStop();
    RightWheelTurn(28);
    AccelerationLinePID(25, 1, 0.5, min_speed_const, acceleration, 0, 70, 0, 10);
    LeftWheelTurn(17);
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
        delay(50);
        waitTask(&taskFlag_normalizeCentMotor);
        delay(200);
    }

    startTask(dropBottleOnTable);

    if (right_bottle){
        LeftWheelTurn(-25);
    }
    else{
        RightWheelTurn(-25);
    }

    preTurnStop(100);
	waitTask(&taskFlag_dropBottleOnTable);

    moveMotor(centMotor, -50, -10, 1);

    AccelerationDist(50);
    startTask(normalizeCentMotor);
    preTurnStop();

    if (right_bottle){
        LeftWheelTurn(-69);
        AccelerationDist(75);
        right_bottle = 0;
    }
    else {
        RightWheelTurn(25);
        LeftWheelTurn(-93);
        AccelerationDist(130);
        left_bottle = 0;
    }
    fromRightRoomToLeft(160);
}

float RightRoom(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    AccelerationDist(202, 0.4);

    preTurnStop(100);
    readRightSen_noMoveRGB(20, &WashInfoRawRight, 5);
    
    short cube = get_wash_color_right(ht_results[1]);
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
//key
void BallLeftRoom(byte cube = 0){
    short add_angle = 0;

    if (cube){
        getCube(-90);
    }

    if (cube == 0){
        if (now_cubes){
        }
        else{
            startTask(prepareForBall);
        }
    }

    preTurnStop(50);
    waitTask(&taskFlag_motorGrabFullDown);
    waitTask(&taskFlag_OneCubePreBall);
    waitTask(&taskFlag_prepareForBall);

    if (cube){
        AccelerationDist(-43, 0);
        preTurnStop();
        TankTurn(50);
        preTurnStop();
    }
    else{
        startTask(motorGrabFullDown);
        TankTurn(-37);
        preTurnStop();
        waitTask(&taskFlag_motorGrabFullDown);
    }

    AccelerationDist(81, 0.5,  min_speed_const,  min_speed_const, 0.02);
    AccelerationDist(15, 0, min_speed_const, 11);
    preTurnStop();
    closeBall();
    startTask(normalizeCentMotor);
    TankTurn(98);
    preTurnStop();
    waitTask(&taskFlag_normalizeCentMotor);

    startTask(BallDrop);
    AccelerationDist(50);
    preTurnStop();
    waitTask(&taskFlag_BallDrop);

    if ((now_cubes == 2) && (left_room_indicator == 2) && (cube)){
        TankTurn(-38);
        preTurnStop();
        AccelerationDist(-25);
        preTurnStop();

        startTask(motorGrabFullDown);
        motor[grabMotor] = -60;
        delay(100);
        motor[grabMotor] = 0;
        waitTask(&taskFlag_motorGrabFullDown);

        motor[grabMotor] = 80;
        delay(150);
        add_angle = 44;
        startTask(normalizeCentMotor);
        delay(200);
        motor[grabMotor] = 0;
        short buffer = cubes[0];
        cubes[0] = cubes[1];
        cubes[1] = buffer;
        AccelerationDist(25);
        preTurnStop();
    }
    else{
        startTask(normalizeCentMotor);
        preTurnStop();
    }

    TankTurn(116 + add_angle);
    preTurnStop();
    waitTask(&taskFlag_normalizeCentMotor);
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
        AccelerationDist(45, 0);
        preTurnStop(50);
    }

    if (cube){
        startTask(normalizeCentMotor);
        delay(50);
        waitTask(&taskFlag_normalizeCentMotor);
        delay(200);
    }

    startTask(dropBottleOnTable);
    if (left_bottle){
        RightWheelTurn(-25);
    }
    else{
        LeftWheelTurn(-25);
    }

    BrakeLeftRightMotor(1);
	waitTask(&taskFlag_dropBottleOnTable);

    moveMotor(centMotor, -50, -10, 1);

    AccelerationDist(50);
    motor[centMotor] = 0;
    startTask(normalizeCentMotor);
    preTurnStop();
    if (left_bottle){
        RightWheelTurn(-69);
        AccelerationDist(75);
        left_bottle = 0;
    }
    else {
        LeftWheelTurn(25);
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

    preTurnStop(100);
    readLeftSen_noMoveRGB(20,  &WashInfoRawLeft, 5);

    motor[grabMotor] = 0;

    short cube = get_wash_color_left(ht_results[0]);

    cubes[1] = cube;
    short add_deg = 0;
    if ((now_cubes) && (left_room_indicator == 2) && (cube)){
        AccelerationDist(30, 0);
        preTurnStop();

        startTask(motorGrabFullDown);
        TankTurn(15);
        preTurnStop();
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
        waitTask(&taskFlag_normalizeCentMotor);
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
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop(100);
    TankTurn(90);
    pr_error = 0;
    AccelerationLinePID(320, 1, 0.7);
    AccelerationLinePID(209, 0, 0.5, fabs(motor[leftMotor]));
    AccelerationDist(47, 0, fabs(motor[leftMotor]));
    PointTurn(200, 0, 90, 1, 0.4);
}

void fromSecondPairRoomsToFrames(){
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();
    TankTurn(90);
    preTurnStop();
    AccelerationLinePID(420, 1, 0.48);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();
    TankTurn(-20);
    preTurnStop();
    AccelerationDist(423);
    preTurnStop();
    TankTurn(-70);
    preTurnStop();
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
    preTurnStop();
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
    preTurnStop(250);
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
    preTurnStop();
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
    preTurnStop(250);
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
    AccelerationDist(15, 0);
    preTurnStop();
    motor[grabMotor] = -50;
    preTurnStop();
    delay(50);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    AccelerationDist(-15, 0);
}
void drop2in2(){
    AbsTurn(360);
    startTask(prepareForDropFirst);
    preTurnStop();
	waitTask(&taskFlag_prepareForDropFirst);
    AccelerationDist(70, 0);
    preTurnStop();
    motor[grabMotor] = -60;
    preTurnStop();
    delay(200);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    AccelerationDist(-70, 0);
}

void readFrames(){
    TankTurn(-73);

    preTurnStop(100);
    readRightSen_noMove(20, &FamesRawRight, 5);

    framesColor[0] = get_colorFrame_first(ht_results[1]);
    rawFrames[0] = ht_results[1];

    TankTurn(-35);

    preTurnStop(100);
    readRightSen_noMove(20, &FamesRawRight, 5);
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
    preTurnStop(150);
    if (reading){
        readFrames();
    }

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
    startTask(motorWaterFullDown);
    preTurnStop();
    delay(300);
    AccelerationDist(-60);
    preTurnStop();
    waitTask(&taskFlag_motorWaterFullDown);
    startTask(normalizeCentMotor);
    AccelerationLinePID(105);
    AccelerationDist(225);
    preTurnStop();
    TankTurn(45);
    preTurnStop();
    AccelerationDist(10);
}