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
    acceleration = 0.02;
    AccelerationLinePID(degrees - 30, 1, 0.5, min_speed_const, acceleration - 0.01, 77, 0, 0, 10);
    AccelerationDist(30);
    AccelerationLinePID(170, 0, 0.5, min_speed_const, acceleration - 0.01, 77, 0, 0, 10);
    acceleration = 0.055;
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
    NOW_ANGLE = 180;
    AbsTurn(227);
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
    AccelerationLinePID(25, 1, 0.5, min_speed_const, acceleration, 0, 70, 0, 10);
    LeftWheelTurn(17);
    preTurnStop(50);
    AccelerationLinePID(100, 1);
    TankTurn(180);
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
        LeftWheelTurn(-97.5);
        AccelerationDist(130);
        left_bottle = 0;
    }
    fromRightRoomToLeft(160);
}

void DropPeople(short index){
    acceleration = 0.01;
    acceleration_turn = 0.035;
    if (index == 0){
        TankTurn(180);
        preTurnStop();
        startTask(motorWaterFullDownPeople);
        delay(100);
        waitTask(&taskFlag_motorWaterFullDown);
        preTurnStop();
        RightWheelTurn(-30);
        preTurnStop();
        RightWheelTurn(30);
        preTurnStop()
        startTask(normalizeCentMotor);
        delay(200);
    }
    else if(index == 2){
        TankTurn(180);
        preTurnStop();
        startTask(motorWaterFullDownPeople);
        delay(100);
        waitTask(&taskFlag_motorWaterFullDown);
        preTurnStop();

        LeftWheelTurn(-30);
        preTurnStop();
        LeftWheelTurn(30);
        preTurnStop();
        startTask(normalizeCentMotor);
        delay(200);        
    }
    else if(index == 1){
        startTask(prepareForDropFirst);
        waitTask(&taskFlag_prepareForDropFirst);
        preTurnStop();
        
        LeftWheelTurn(-60);
        preTurnStop();
        AccelerationDist(100);
        preTurnStop();

        AccelerationDist(-100);
        preTurnStop();
        startTask(normalizeCentMotor);
        waitTask(&taskFlag_normalizeCentMotor);

        preTurnStop();

        LeftWheelTurn(60);
        preTurnStop();
        TankTurn(180);
    }
    else{
        TankTurn(180);
    }
    acceleration = 0.05;
    acceleration_turn = 0.04;
}

float RightRoom(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    AccelerationDist(100, 0.4);
    preTurnStop();

    short correct = -1; 
    for (int i = 0; i < 3; i++){
        if (rightRoomTables[bibob] == people[i]){
            correct = i;
        }
    }
    
    DropPeople(correct);
    preTurnStop(200)
    fromRightRoomToLeft(80);

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
        AccelerationDist(-35);
        preTurnStop();

        startTask(motorGrabFullDown);
        motor[grabMotor] = -60;
        delay(100);
        motor[grabMotor] = 0;
        waitTask(&taskFlag_motorGrabFullDown);

        motor[grabMotor] = 80;
        delay(200);
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
        waitTask(&taskFlag_normalizeCentMotor);
        delay(250);
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

    AccelerationDist(100, 0.4);
    preTurnStop();

    short correct = -1; 
    for (int i = 0; i < 3; i++){
        if (leftRoomTables[bibob] == people[i]){
            correct = i;
        }
    }
    
    DropPeople(correct);
    preTurnStop(200);
    AccelerationLinePID(50, 1, 0.5, min_speed_const, acceleration, 0, 70, 0, 10);

    #if LOGGING == 1
        writeLeftRoomInfo(ht_results[0], cube);
    #endif

    #if TIMER == 1
        return getTimerValue(T2) - start_time;
    #else
        return 0;
    #endif
}

void fromFirstPairRoomsToSecond(){
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop(100);
    TankTurn(90);
    pr_error = 0;
    AccelerationLinePID(600, 0, 0.5);
    AccelerationDist(300);
    AccelerationLinePID(525, 1, 0.5);
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

void Balls(){
    AccelerationLinePID(20, 1);
    preTurnStop();
    AccelerationDist(BetweenSensorsAndMiddle, 0);
    preTurnStop();
    TankTurn(-90);
    AccelerationLinePID(240, 0);
    preTurnStop();
    startTask(prepareForBall);
    startTask(motorGrabFullDown);
    waitTask(&taskFlag_motorGrabFullDown);
    closeBall();
    startTask(normalizeCentMotor);
    waitTask(&taskFlag_normalizeCentMotor);
    AccelerationDist(-130, 0);
    TankTurn(90);
    preTurnStop();
    startTask(BallDrop);
    waitTask(&taskFlag_BallDrop);
    startTask(normalizeCentMotor);
    waitTask(&taskFlag_normalizeCentMotor);
    motor[grabMotor] = -30;
    TankTurn(90);
    preTurnStop();
    AccelerationLinePID(20, 1);
    motor[grabMotor] = 0;
    AccelerationLinePID(240 + BetweenSensorsAndMiddle, 0)

    preTurnStop();
    startTask(prepareForBall);
    startTask(motorGrabFullDown);
    waitTask(&taskFlag_motorGrabFullDown);
    closeBall();
    startTask(normalizeCentMotor);
    waitTask(&taskFlag_normalizeCentMotor);
    AccelerationDist(-130, 0);
    TankTurn(-90);
    preTurnStop();
    startTask(BallDrop);
    waitTask(&taskFlag_BallDrop);
    startTask(normalizeCentMotor);
    waitTask(&taskFlag_normalizeCentMotor);
    motor[grabMotor] = -30;
    TankTurn(-90);
    preTurnStop();
    AccelerationLinePID(20, 1);
    AccelerationDist(BetweenSensorsAndMiddle, 0);
    TankTurn(-90);
    fromFramesToSecondPairRooms();
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
    AccelerationDist(70, 0);
    motor[grabMotor] = -60;
    preTurnStop();
    delay(200);
    motor[grabMotor] = 0;
    startTask(normalizeCentMotor);
    AccelerationDist(-70, 0);
}

void readFrames(){
    preTurnStop();
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
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();
    TankTurn(90);
    preTurnStop();

    short finish = 10; 
    for (int i = 0; i < 3; i++){
        finish -= people[i];
    }

    AccelerationLinePID(350, 1);

    if (finish == 1 || finish == 2){
        AccelerationLinePID(250, 0);
        if (finish == 1){
            TankTurn(90);
        }
        else{
            TankTurn(-90);
        }
    }
    else{
        AccelerationLinePID(640, 0);
        if (finish == 4){
            TankTurn(90);
        }
        else{
            TankTurn(-90);
        }
    }
    preTurnStop();
    AccelerationDist(200);
    preTurnStop();
}

void readPeople(int count_times, int timer = 5){
    TankTurn(45);
    preTurnStop();
    AccelerationDist(100, 1);
    AccelerationLinePID(140, 1, 0, motor[rightMotor]);
    AccelerationDist(20);
    preTurnStop();

    short raw[3];
    preTurnStop();
	TankTurn(-90);
    preTurnStop();
	AccelerationDist(-40, 0, 0.01);
    preTurnStop(500);
	readRightSen_noMoveRGB(count_times, &FamesRawRight,timer);

    eraseDisplay();
    displayString(8,  "%d", rgb[0]);
    displayString(10, "%d", rgb[1]);
    displayString(12, "%d", rgb[2]);
    delay(0);

    raw[0] = ht_results[1];
    people[0] =  get_people_color()
    AccelerationDist(95, 0, 0.01);
    preTurnStop(500);

    readRightSen_noMoveRGB(count_times, &FamesRawRight, timer);
    eraseDisplay();
    displayString(8,  "%d", rgb[0]);
    displayString(10, "%d", rgb[1]);
    displayString(12, "%d", rgb[2]);
    delay(0);

    raw[1] = ht_results[1];
    people[1] =  get_people_color()
    AccelerationDist(85, 0, 0.01);
    preTurnStop(500);
    readRightSen_noMoveRGB(count_times, &FamesRawRight, timer);

    eraseDisplay();
    displayString(8,  "%d", rgb[0]);
    displayString(10, "%d", rgb[1]);
    displayString(12, "%d", rgb[2]);
    delay(0);


    raw[2] = ht_results[1];
    people[2] =  get_people_color();
    eraseDisplay();
    displayString(8,  "%d", raw[0]);
    displayString(10, "%d", raw[1]);
    displayString(12, "%d", raw[2]);
    delay(0);

    eraseDisplay();
    displayString(8,  "%d", people[0]);
    displayString(10, "%d", people[1]);
    displayString(12, "%d", people[2]);
    delay(2000);

    acceleration = 0.03;

    AccelerationDist(-140);
    preTurnStop();
    TankTurn(-90);
    preTurnStop();
    acceleration = 0.01;
    AccelerationLinePID(60, 0);
    startTask(motorWaterFullDown);
    AccelerationDist(50, 0, motor[rightMotor]);
    acceleration = 0.02;
    preTurnStop();
    waitTask(&taskFlag_motorWaterFullDown);

    AccelerationDist(-160);
    startTask(setNormAfterWaterFullDown);
    delay(200);
    preTurnStop();
    
    AccelerationLinePID(80);
    preTurnStop();
    TankTurn(180);
    preTurnStop();
    AccelerationLinePID(10, 1);
    AccelerationLinePID(32);
    preTurnStop();

    startTask(prepareForDropFirst);
    waitTask(&taskFlag_prepareForDropFirst);
    preTurnStop();

    LeftWheelTurn(60);
    preTurnStop();

    startTask(normalizeCentMotor);
    waitTask(&taskFlag_normalizeCentMotor);

    preTurnStop();

    LeftWheelTurn(-60);
    preTurnStop();
    TankTurn(180);

    acceleration = 0.055;

    AccelerationLinePID(62);

    PointTurn(250, 0, 90, 1);

    AccelerationLinePID(370, 1, 0.6);
}