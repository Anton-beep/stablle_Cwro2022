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
    ReadIndicator(35, motor[rightMotor]);

    BrakeLeftRightMotor(1);
    delay(100)

    left_room_indicator  = get_colorMarker_left(ht_results[0]);
    right_room_indicator = get_colorMarker_right(ht_results[1]);

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


float EntranceRightRoom(short ResultAngle){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    AccelerationLinePID(15, 0, 0);
    RightWheelTurn(90);
    AccelerationLinePID(50, 0, 0, min_speed_const, acceleration, 0, 70, 0);

    NOW_ANGLE = ResultAngle;

    #if DEBUG == 1
        BrakeLeftRightMotor(1);
        delay(2000);
    #endif

    #if TIMER == 1
        return getTimerValue(T2) - start_time;
    #else
        return 0;
    #endif
}

float RightRoom(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    AccelerationDist(190);
    ReadRightWash(30, 20);

    BrakeLeftRightMotor(1);
    int cube = get_colorWash_right(ht_results[1]);
    
    if (right_room_indicator == 2){
        BallRightRoom();
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

void BallRightRoom(byte cube = 0){
    AccelerationDist(-65);
    preTurnStop();
    TankTurn(90);

    if (cube){
        startTask(motorGrabFullDown);
        startTask(prepareForCube);
        AccelerationDist(50); //debug
        BrakeLeftRightMotor(1);
        waitTask(&taskFlag_motorGrabFullDown);
        waitTask(&taskFlag_prepareForCube);
        takeCube();
    }

    if (cube == 0){
        AccelerationDist(50); //debug
        startTask(prepareForBall);
    }

    startTask(motorGrabFullDown);
    LeftWheelTurn(90);
    AccelerationDist(50); //debug
    BrakeLeftRightMotor(1);
    waitTask(&taskFlag_motorGrabFullDown);
    waitTask(&taskFlag_prepareForBall);
    closeBall();
    resetError();

    TankTurn(-80);
    startTask(BallDrop);
    AccelerationDist(100); //debug
    BrakeLeftRightMotor(1);
    waitTask(&taskFlag_BallDrop);
    AccelerationDist(-50); //debug
    preTurnStop();
    TankTurn(-100);
    AccelerationDist(100);//debug
}