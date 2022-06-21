float TakeBottles(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    TankTurn(45);
    preTurnStop();
    AccelerationDist(100, 1);
    AccelerationLinePID(160, 1, 0, motor[rightMotor]);

    BrakeLeftRightMotor(1);
    delay(100);
    preTurnStop();

    TankTurn(180);

    BrakeLeftRightMotor(1);
    preTurnStop();

    startTask(motorWaterFullDown);

    AccelerationLinePID(40, 0);
    AccelerationDist(50, 0, motor[rightMotor]);

    BrakeLeftRightMotor(1);
    delay(50);

    AccelerationDist(-160);
    BrakeLeftRightMotor(1);
    
    startTask(setNormAfterWaterFullDown);
    delay(200);

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

float readIndicators(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    AccelerationLinePID(110, 0, 0.01);
    ReadIndicator(33, 15);

    float enc_left_motor = fabs(nMotorEncoder[leftMotor]);
	float enc_right_motor = fabs(nMotorEncoder[rightMotor]);

	float moved_motors = 0;
	float now_millimeters = 0;

    while(now_millimeters < 15.5) {
		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

    left_room_indicator  = get_colorMarker_left(ht_results[0]);
    right_room_indicator = get_colorMarker_right(ht_results[1]);

    RightWheelTurn(90);
    AccelerationLinePID(50, 0, 0, 10, acceleration, 0, 90, 0, 10);

    #if DEBUG == 1
        eraseDisplay();
        displayString(7, "left indicator: %d", ht_results[0]);
        displayString(10, "right indicator: %d", ht_results[1]);
    #endif

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

    AccelerationLinePID(degrees - 10, 0, 1, min_speed_const, acceleration - 0.01, 70, 0, 0, 10);

    float speed = fabs(motor[leftMotor]);

    while ((results_sensors.firstSensor > 40) || (results_sensors.secondSensor > 40)){
		DrivePID(speed, 70, 0, 0);
    }

    if (now_cubes == 0){
        motor[grabMotor] = 0;
    }
    
    AccelerationDist(30, 1, speed);
    
    speed = fabs(motor[leftMotor]);

    AccelerationLinePID(170, 0.82, 0, speed, acceleration, 70, 0, 0, 10);

    speed = fabs(motor[leftMotor]);

    AccelerationDist(200, 0, speed);
}

void getCube(short angle = 90){ // 1 - Right room, -1 - Left room
    preTurnStop();
    TankTurn(angle);
    preTurnStop();
    startTask(prepareForCube);
    delay(100);
    startTask(motorGrabFullDown);
    AccelerationDist(20, 0, 13, 13);
    AccelerationDist(27, 0, 11, 11);
    BrakeLeftRightMotor(1);
    delay(100);
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
    delay(100);
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
        preTurnStop();
        AccelerationDist(-47, 0);
        preTurnStop();
        delay(200);
        TankTurn(-50);
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
    AccelerationDist(70);
    AccelerationDist(14, 0, min_speed_const, 11);
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
    BrakeLeftRightMotor(1);
    waitTask(&taskFlag_BallDrop);
    delay(200);
    preTurnStop();

    startTask(normalizeCentMotor);

    TankTurn(-113 + add_angle);
    preTurnStop();
    AccelerationDist(115);

    fromRightRoomToLeft(160);
}

void WaterRightRoom(byte cube = 0){
    if (cube){
        getCube();
        startTask(normalizeCentMotor);
        waitTask(&taskFlag_normalizeCentMotor);
    }
    else{
        preTurnStop();
        TankTurn(90);
        AccelerationDist(47, 0);
        BrakeLeftRightMotor(1);
        delay(50);
    }

    startTask(dropBottleOnTable);
    if (right_bottle){
        LeftWheelTurn(-30);
    }
    else{
        RightWheelTurn(-30);
    }

    BrakeLeftRightMotor(1);
    delay(100);
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
        LeftWheelTurn(-98.5);
        AccelerationDist(130);
        left_bottle = 0;
    }
    fromRightRoomToLeft(160);
}

float RightRoom(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    AccelerationDist(185);

    ReadRightWash(30, 20);

    BrakeLeftRightMotor(1);
    delay(100);

    short cube = get_colorWash_right(ht_results[1]);
    cubes[0] = cube;
    
    AccelerationDist(-65, 0.3);
    if (right_room_indicator == 2){
        BallRightRoom(cube);
    }
    else{
        WaterRightRoom(cube);
    }

    #if DEBUG == 1
        BrakeLeftRightMotor(1);
        delay(100);
        eraseDisplay();
        displayTextLine(6, "raw %d", ht_results[1]);
        displayTextLine(8, "color %d", cube);
        BrakeLeftRightMotor(1);
        delay(6000);
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
        preTurnStop();
        delay(100);
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
        add_angle = -4.5;
    }

    waitTask(&taskFlag_motorGrabFullDown);
    AccelerationDist(83);
    AccelerationDist(18, 0, min_speed_const, 11);
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
    BrakeLeftRightMotor(1);
    waitTask(&taskFlag_BallDrop);
    delay(200);
    preTurnStop();



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
        add_angle = 38;
        startTask(normalizeCentMotor);
        delay(200);
        motor[grabMotor] = 0;
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
        startTask(normalizeCentMotor);
        waitTask(&taskFlag_normalizeCentMotor);
        delay(200);
    }
    else if (cube){
        getCube(-90);
        startTask(normalizeCentMotor);
        waitTask(&taskFlag_normalizeCentMotor);
    }
    else{
        preTurnStop();
        TankTurn(-90);
        AccelerationDist(47, 0);
        BrakeLeftRightMotor(1);
        delay(50);
    }

    startTask(dropBottleOnTable);
    if (left_bottle){
        RightWheelTurn(-30);
    }
    else{
        LeftWheelTurn(-30);
    }

    BrakeLeftRightMotor(1);
    delay(100);
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
        BrakeLeftRightMotor(1);
        delay(5000);
        RightWheelTurn(-93);
        BrakeLeftRightMotor(1);
        delay(5000);
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

    ReadLeftWash(30, 20);
    preTurnStop();
    delay(100);
    motor[grabMotor] = 0;

    short cube = get_colorWash_left(ht_results[0]);
    cubes[1] = cube;

    if ((now_cubes) && (left_room_indicator == 2) && (cube)){
        startTask(motorGrabFullDown);
        TankTurn(15);
        BrakeLeftRightMotor(1);
        waitTask(&taskFlag_motorGrabFullDown);
        motor[grabMotor] = -100;
        preTurnStop();
        delay(100);
        startTask(normalizeCentMotor);
        AccelerationDist(50, 0);
        BrakeLeftRightMotor(1);
        delay(200);
        preTurnStop();
        AccelerationDist(-50, 0);
        preTurnStop();
        delay(50);
        TankTurn(-15);
        motor[grabMotor] = 0;
        preTurnStop();
        delay(50);
    }

    AccelerationDist(-65, 0.3);
    if (left_room_indicator == 2){
        BallLeftRoom(cube);
    }
    else{
        WaterLeftRoom(cube);
    }

    #if DEBUG == 1
        eraseDisplay();
        displayTextLine(6, "raw %d", ht_results[0]);
        displayTextLine(8, "color %d", cube);
        BrakeLeftRightMotor(1);
        delay(2000);
    #endif

    #if TIMER == 1
        return getTimerValue(T2) - start_time;
    #else
        return 0;
    #endif
}

void fromFirstPairRoomsToFrames(){
    RightWheelTurn(92);
    AccelerationLinePID(20, 0, 1);
    AccelerationLinePID(270, 1, 0.48, fabs(motor[leftMotor]));
    AccelerationLinePID(213, 0);
    PointTurn(250, 0, 90, 1);
}

void drop1in1(){
    AbsTurn(90);
    startTask(prepareForDropFirst);
    LeftWheelTurn(90);
    BrakeLeftRightMotor(1);
    preTurnStop();
	waitTask(&taskFlag_prepareForDropFirst);
    AccelerationDist(-30, 0);
    BrakeLeftRightMotor(1);
    preTurnStop();
    motor[grabMotor] = -40;
    delay(120);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    AccelerationDist(30, 0);
    preTurnStop();
    LeftWheelTurn(-90);
}
void drop2in1(){
    AbsTurn(90);
    startTask(prepareForDropFirst);
    LeftWheelTurn(90);
    BrakeLeftRightMotor(1);
    preTurnStop();
	waitTask(&taskFlag_prepareForDropFirst);
    BrakeLeftRightMotor(1);
    preTurnStop();
    motor[grabMotor] = -60;
    delay(500);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    preTurnStop();
    LeftWheelTurn(-90);
}

void drop1in3(){
    AbsTurn(270);
    startTask(prepareForDropFirst);
    RightWheelTurn(90);
    BrakeLeftRightMotor(1);
    preTurnStop();
	waitTask(&taskFlag_prepareForDropFirst);
    AccelerationDist(-30, 0);
    BrakeLeftRightMotor(1);
    preTurnStop();
    motor[grabMotor] = -40;
    delay(120);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    AccelerationDist(30, 0);
    preTurnStop();
    RightWheelTurn(-90);
}
void drop2in3(){
    AbsTurn(270);
    startTask(prepareForDropFirst);
    RightWheelTurn(90);
    BrakeLeftRightMotor(1);
    preTurnStop();
	waitTask(&taskFlag_prepareForDropFirst);
    BrakeLeftRightMotor(1);
    preTurnStop();
    motor[grabMotor] = 0;
    motor[grabMotor] = -60;
    delay(500);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    preTurnStop();
    RightWheelTurn(-90);
}

void drop1in2(){
    AbsTurn(360);
    startTask(prepareForDropFirst);
    BrakeLeftRightMotor(1);
    preTurnStop();
	waitTask(&taskFlag_prepareForDropFirst);
    AccelerationDist(30, 0);
    BrakeLeftRightMotor(1);
    preTurnStop();
    motor[grabMotor] = -40;
    delay(120);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    AccelerationDist(-30, 0);
    preTurnStop();
}
void drop2in2(){
    AbsTurn(360);
    startTask(prepareForDropFirst);
    BrakeLeftRightMotor(1);
    preTurnStop();
	waitTask(&taskFlag_prepareForDropFirst);
    AccelerationDist(60, 0);
    BrakeLeftRightMotor(1);
    preTurnStop();
    motor[grabMotor] = -60;
    delay(500);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    AccelerationDist(-60, 0);
    preTurnStop();
}

void readFrames(){
    preTurnStop();
    AccelerationDist(-20, 0);
    preTurnStop();
    TankTurn(-90);
    preTurnStop();
    AccelerationDist(-50, 0);
    preTurnStop();
    readRightSen_noMove(40, &FamesRawRight);
    framesColor[0] = get_colorFrame_first(ht_results[1]);
    AccelerationDist(100, 0);
    preTurnStop();

    readRightSen_noMove(40, &FamesRawRight);
    framesColor[1] = get_colorFrame_first(ht_results[1]);

    framesColor[2] = (10 - framesColor[0] - framesColor[1]);
    AccelerationDist(-50, 0);
    preTurnStop();
    NOW_ANGLE = 270;
}

void frames(){
    readFrames();
    delay(2000);
    
    eraseDisplay();
    displayTextLine(6, "frame 1 %d",  framesColor[0]);
    displayTextLine(8, "frame 2 %d",  framesColor[1]);
    displayTextLine(12, "frame 3 %d", framesColor[2]);


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

    displayTextLine(12, "cube 1 %d", cubes[1]);
    displayTextLine(12, "cube 2 %d", cubes[0]);

    BrakeLeftRightMotor(1);
    delay(6000);

    if (cubes[1] == framesColor[0]){
        drop1in1();
    }
    else if (cubes[1] == framesColor[1]){
        drop1in2();
    }
    else if (cubes[1] == framesColor[2]){
        drop1in3();
    }

    preTurnStop();

    if (cubes[0] == framesColor[0]){
        drop2in1();
    }
    else if (cubes[0] == framesColor[1]){
        drop2in2();
    }
    else if (cubes[0] == framesColor[2]){
        playSound(soundBeepBeep);
        drop2in3();
    }
    
}