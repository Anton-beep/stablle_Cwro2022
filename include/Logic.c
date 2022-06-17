float TakeBottles(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    TankTurn(45);

    BrakeLeftRightMotor(1);
    delay(500);

    AccelerationDist(150, 1)
    AccelerationLinePID(130, 1);

    BrakeLeftRightMotor(1);
    delay(500);

    TankTurn(180);
    resetError();

    BrakeLeftRightMotor(1);
    delay(500);

    startTask(motorWaterFullDown);
    AccelerationLinePID(50, 0, 0);
    AccelerationDist(50, 0)

    BrakeLeftRightMotor(1);
    delay(500);

    AccelerationDist(-150, 0);

    startTask(setNormAfterWaterFullDown);

    BrakeLeftRightMotor(1);
    delay(200);

    AccelerationLinePID(80);

    BrakeLeftRightMotor(0);
    delay(20);

    PointTurn(250, 0, 90, 1);
    AccelerationLinePID(340, 1, 0.7);

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
    ReadIndicator(35, 20);

    BrakeLeftRightMotor(1);
    delay(100)

    long left_room_indicator  = get_colorMarker_left(ht_results[0]);
    long right_room_indicator = get_colorMarker_right(ht_results[1]);

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


float EntranceRightRoom(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    AccelerationLinePID(15, 0, 0, 17);
    RightWheelTurn(90);
    AccelerationLinePID(50, 0, 0, min_speed_const, acceleration, 0, 70, 0);

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

    AccelerationDist(200);
    BrakeLeftRightMotor(1);
    delay(200);
    ReadRightWash(33, 20);

    BrakeLeftRightMotor(1);
    int cube = get_colorWash_right(ht_results[1]);
    displayTextLine(6, "raw %d", ht_results[1]);
    displayTextLine(8, "color %d", cube);

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

void BallRightRoom(){
    TankTurn(45);
    startTask(motorGrabFullDown);
    AccelerationDist(50);
    BrakeLeftRightMotor(1);
    
    waitTask(&taskFlag_motorGrabFullDown);
    startTask(closeAndHoldGraber);

    waitTask(&taskFlag_closeAndHoldGraber);
    startTask(normalizeCentMotor);

    AccelerationDist(-50);
    TankTurn(-95);
    startTask(BallDrop);
    AccelerationDist(35);
    BrakeLeftRightMotor(1);
    waitTask(&taskFlag_BallDrop)
    startTask(normalizeCentMotor);
    AccelerationDist(-35);
}