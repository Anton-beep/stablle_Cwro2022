short readDudeNearBlueRoom(){
    AbsTurn(360);
    AccelerationLinePID(342 - BetweenSensorsAndMiddle);

    while (results_sensors.firstSensor > 5){
        SensorsToPercent();
    }

    AccelerationLinePID(BetweenHTAndWheels + 30);
    preTurnStop();
    //reading
    return 0;
}

short readDudeNearBlueRoomNearWash(){
    AbsTurn(360);
    AccelerationLinePID(342 - BetweenSensorsAndMiddle);

    while (results_sensors.firstSensor > 5){
        SensorsToPercent();
    }

    preTurnStop();
    //reading
    return 0;
}

short readDudeNearYellowRoom(){
    AbsTurn(180);
    AccelerationLinePID(310 - BetweenSensorsAndMiddle);

    while (results_sensors.secondSensor > 5){
        SensorsToPercent();
    }

    AccelerationLinePID(BetweenHTNXT + 54);
    preTurnStop();
    //reading
    return 0;
}

short readDudeNearYellowRoomNearBottles(){
    AbsTurn(180);
    AccelerationLinePID(310 - BetweenSensorsAndMiddle);

    while (results_sensors.secondSensor > 5){
        SensorsToPercent();
    }

    AccelerationLinePID(52);
    preTurnStop();
    //reading
    return 0;
}

short readDudeNearRedRoom(){
    AbsTurn(180);
    AccelerationLinePID(150);
    preTurnStop(2000);
    //reading
    return 0;
}

short readDudeNearRedRoom(){
    AbsTurn(180);
    AccelerationLinePID(150);
    preTurnStop(2000);
    //reading
    return 0;
}
