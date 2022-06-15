float TakeBottles(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    TankTurn(45);
    AccelerationLinePID(250, 1, 0);
    TankTurn(180);

    startTask(motorWaterFullDown);
    AccelerationLinePID(100, 0, 0);
    BrakeLeftRightMotor(1);
    delay(100);
    AccelerationDist(-150, 0);

    startTask(setNormAfterWaterFullDown);

    BrakeLeftRightMotor(1);
    delay(200);

    AccelerationLinePID(70);

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

    AccelerationLinePID(110, 0, 0.01, motor[rightMotor]);
    ReadIndicator(35, 20);

    BrakeLeftRightMotor(1);
    delay(100)

    float left_room_indicator  = get_colorMarker_left(ht_results[0]);
    float right_room_indicator = get_colorMarker_right(ht_results[1]);

    #if DEBUG == 1
        BrakeLeftRightMotor(1);
        eraseDisplay();
        displayString(7, "left indicator: %d", ht_results[0]);
        displayString(10, "right indicator: %d", ht_results[1]);
        delay(5000);
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

    AccelerationLinePID(10, 0, 0, 17);
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