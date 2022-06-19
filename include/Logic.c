float TakeBottles(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    TankTurn(45);
    AccelerationDist(100, 1);
    AccelerationLinePID(160, 1, 0, motor[rightMotor]);

    BrakeLeftRightMotor(1);
    delay(250);

    TankTurn(180);

    BrakeLeftRightMotor(1);
    resetError();

    startTask(motorWaterFullDown);

    AccelerationLinePID(30, 0, 1);
    AccelerationDist(50, 0, motor[rightMotor]);

    BrakeLeftRightMotor(1);
    delay(50);

    AccelerationDist(-150);
    BrakeLeftRightMotor(1);

    startTask(setNormAfterWaterFullDown);
    delay(50)

    AccelerationLinePID(80);

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

    AccelerationLinePID(110, 0, 0.01, motor[rightMotor]);
    ReadIndicator(33, 15);

    float enc_left_motor = fabs(nMotorEncoder[leftMotor]);
	float enc_right_motor = fabs(nMotorEncoder[rightMotor]);

	float moved_motors = 0;
	float now_millimeters = 0;

    while(now_millimeters < 16) {
		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

    left_room_indicator  = get_colorMarker_left(ht_results[0]);
    right_room_indicator = get_colorMarker_right(ht_results[1]);

    RightWheelTurn(90);
    AccelerationLinePID(50, 0, 0, 10, acceleration, 0, 80, 0, 8);

    #if DEBUG == 1
        BrakeLeftRightMotor(1);
        eraseDisplay();
        displayString(7, "left indicator: %d", ht_results[0]);
        displayString(10, "right indicator: %d", ht_results[1]);
        delay(5000);
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

void getCube(short angle = 90){ // 1 - Right room, -1 - Left room
    preTurnStop();
    TankTurn(90);
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
}

void getCubeLeft(short angle = -90){ // 1 - Right room, -1 - Left room
    preTurnStop();
    TankTurn(-180);
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
        delay(100);
        AccelerationDist(-47, 0);
        preTurnStop();
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
    AccelerationDist(85);
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
    

    

    if ((now_cubes) && (right_room_indicator == 2) && (cube)){
        TankTurn(35);
        preTurnStop();

        stopMotor(centMotor, 1);
        stopTask(prepareForBall);
        stopTask(prepareForCube);

        startTask(motorGrabFullDown);
        motor[grabMotor] = -60;
        delay(100);
        motor[grabMotor] = 0;
        waitTask(&taskFlag_motorGrabFullDown);

        motor[grabMotor] = 80;
        delay(200)
        add_angle = -40
        startTask(normalizeCentMotor);
        delay(200)
        motor[grabMotor] = 0;
    }
    else{
        startTask(normalizeCentMotor);
        preTurnStop();
    }

    TankTurn(-111 + add_angle);
    preTurnStop();
    AccelerationDist(115);

    AccelerationLinePID(170, 1, 0.5, min_speed_const, acceleration, 70, 0, 0, 10);
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
        RightWheelTurn(-25);
    }

    BrakeLeftRightMotor(1);
    delay(100);
	waitTask(&taskFlag_dropBottleOnTable);
    motor[centMotor] = -10;
    delay(100);

    AccelerationDist(50);
    motor[centMotor] = 0;
    startTask(normalizeCentMotor);
    preTurnStop();
    if (right_bottle){
        LeftWheelTurn(-63);
        AccelerationDist(75);
        AccelerationLinePID(160, 1, 0.5, min_speed_const, acceleration, 70, 0, 0, 10);
        right_bottle = 0;
    }
    else {
        RightWheelTurn(22);
        LeftWheelTurn(-98.5);
        AccelerationDist(130);
        AccelerationLinePID(160, 1, 0.5, min_speed_const, acceleration, 70, 0, 0, 10);
        left_bottle = 0;
    }
}

float RightRoom(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    AccelerationDist(200);
    ReadRightWash(30, 20);

    BrakeLeftRightMotor(1);
    delay(100);

    int cube = get_colorWash_right(ht_results[1]);


    right_room_indicator = 2; //key:hardcode
    cube = 1;
    now_cubes = 0;

    if ((now_cubes) && (right_room_indicator == 2) && (cube)){
        startTask(motorGrabFullDown);
        TankTurn(-15);
        BrakeLeftRightMotor(1);
        waitTask(&taskFlag_motorGrabFullDown);
        motor[grabMotor] = -100;
        preTurnStop();
        delay(100);
        startTask(normalizeCentMotor);
        AccelerationDist(50, 0);
        BrakeLeftRightMotor(1);
        delay(200);
        preTurnStop()
        AccelerationDist(-50, 0);
        preTurnStop();
        delay(50);
        TankTurn(15);
        motor[grabMotor] = 0;
        preTurnStop();
    }

    AccelerationDist(-65, 0.3);
    if (right_room_indicator == 2){
        BallRightRoom(cube);
    }
    else{
        WaterRightRoom(cube);
    }

    #if DEBUG == 1
        displayTextLine(6, "raw %d", ht_results[1]);
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

void BallLeftRoom(byte cube = 0){
    short add_angle = 0;

    if (cube){
        getCubeLeft(-90);
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
        add_angle = -3;
    }
    
    waitTask(&taskFlag_motorGrabFullDown);
    AccelerationDist(85);
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
    

    

    if ((now_cubes) && (right_room_indicator == 2) && (cube)){
        TankTurn(-35);
        preTurnStop();

        stopMotor(centMotor, 1);
        stopTask(prepareForBall);
        stopTask(prepareForCube);

        startTask(motorGrabFullDown);
        motor[grabMotor] = -60;
        delay(100);
        motor[grabMotor] = 0;
        waitTask(&taskFlag_motorGrabFullDown);

        motor[grabMotor] = 80;
        delay(200)
        add_angle = 40
        startTask(normalizeCentMotor);
        delay(200)
        motor[grabMotor] = 0;
    }
    else{
        startTask(normalizeCentMotor);
        preTurnStop();
    }

    TankTurn(111 + add_angle);
    preTurnStop();
    AccelerationDist(115);

    AccelerationLinePID(170, 1, 0.5, min_speed_const, acceleration, 70, 0, 0, 10);
}