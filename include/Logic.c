void fromFramesToFirstPairRooms(){
    preTurnStop(90);
    AbsTurn(180);
    AccelerationLinePID(40);
    AccelerationDist(15);
    PointTurn(-200, 0, -89.5, 1, 0.4);
    AccelerationLinePID(250, 1);

}

void fromFramesToSecondPairRooms(){
    preTurnStop();
    AbsTurn(180);
    preTurnStop();
    AccelerationLinePID(23);
    PointTurn(200, 0, 88, 1, 0.5);
    AccelerationLinePID(25, 1, 0.5, min_speed_const, acceleration, 0, 70, 0, 10);
    LeftWheelTurn(17);
    preTurnStop(50);
    AccelerationLinePID(100, 1);
}

void getInsideRight(){
    AccelerationLinePID(160, 0, 0);
    preTurnStop();
    RightWheelTurn(90);

    AccelerationLinePID(47, 0, 0, 10, acceleration, 0, 82, 0, 10);

    AccelerationDist(187, 0.4);
}

void getInsideLeft(){
    AccelerationLinePID(160, 0, 0);
    preTurnStop();
    LeftWheelTurn(90);
    AccelerationLinePID(47, 0, 0, 10, acceleration, 82, 0, 0, 10);

    AccelerationDist(187, 0.4);
}

void fromFirstPairRoomsToFrames(){
    preTurnStop(90);
    RightWheelTurn(100);
	LeftWheelTurn(10);
    pr_error = 0;
    AccelerationLinePID(250, 1, 0.5);
    AccelerationLinePID(210, 0, 0.5);
    AccelerationDist(55, 0, fabs(motor[leftMotor]));
    PointTurn(200, 0, 89.5, 1, 0.4);
}


void fromSecondPairRoomsToFrames(){
    preTurnStop(90);
    RightWheelTurn(100);
	LeftWheelTurn(10);
    AccelerationLinePID(300, 1, 0.48);
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

void readFramesStart(){
    TankTurn(45);
    preTurnStop();
    AccelerationDist(100, 1);
    AccelerationLinePID(160, 1, 0, motor[rightMotor]);
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

    TankTurn(181);

    preTurnStop(100);
    readLeftSen_noMove(20, &FamesRawRight, 5);
    framesColor[2] = get_colorFrame_third(ht_results[0]);
    rawFrames[2] = ht_results[0];

    NOW_ANGLE = 360;

    TankTurn(107.8);

    Kp_norm = 0.56;
    AccelerationDist(-40, 0);
    preTurnStop(280);
    AccelerationLinePID(90, 0);
    Kp_norm = 0.42;

    AccelerationDist(320);
    AccelerationLinePID(40, 1);
    preTurnStop();

    #if LOGGING == 1
        writeFramesInfo(rawFrames, framesColor);
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

float readIndicatorsExtended(short preTurnmm = 18){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    AccelerationLinePID(110, 0, 0.01);
    ReadIndicatorExtended(33, 15);

    float enc_left_motor =   fabs(nMotorEncoder[leftMotor]);
	float enc_right_motor = fabs(nMotorEncoder[rightMotor]);

	float moved_motors = 0;
	float now_millimeters = 0;

    while(now_millimeters < preTurnmm) {
		moved_motors = MotorsAbsMovedDegreesLR(enc_left_motor, enc_right_motor);
		now_millimeters = DegreesToMillimeters(moved_motors);
	}

    left_room_indicator  = get_indicator_extended_color_left(ht_results[0], rgbLeft);
    right_room_indicator = get_indicator_extended_color_left(ht_results[1], rgbRight);

    #if LOGGING == 1
        writeIndicatorsExtended(left_room_indicator,right_room_indicator, rgbLeft, rgbRight);
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

    AccelerationLinePID(degrees - 10, 1, 0.6, min_speed_const, acceleration - 0.01, 82, 0, 0, 10);

    if (now_cubes == 0){
        motor[grabMotor] = 0;
    }

    AccelerationLinePID(200, 0, 0.5, min_speed_const + 2, acceleration - 0.01, 82, 0, 0, 10);

    AccelerationDist(203, 0.35);
}

void getCube(short angle = 90){ // 1 - Right room, -1 - Left room
    preTurnStop();
    TankTurn(angle);

    startTask(prepareForCube);
    startTask(motorGrabFullDown);
    preTurnStop();

    AccelerationDist(25, 0, 15, 10, 0.004);
    AccelerationDist(25, 0, 11, 9.5, 0.0001);
    preTurnStop(50);

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
    }

    waitTask(&taskFlag_motorGrabFullDown);
    waitTask(&taskFlag_OneCubePreBall);
    waitTask(&taskFlag_prepareForBall);

    AccelerationDist(85, 0.24, min_speed_const,  10.5, 0.04);
    preTurnStop();
    closeBall();
    startTask(normalizeCentMotor);
    TankTurn(-98);
    preTurnStop();
    waitTask(&taskFlag_normalizeCentMotor);

    startTask(BallDrop);
    AccelerationDist(53);
    preTurnStop();
    waitTask(&taskFlag_BallDrop);

    startTask(normalizeCentMotor);
    TankTurn(-119 + add_angle);
    preTurnStop();
    waitTask(&taskFlag_normalizeCentMotor);

    AccelerationDist(115);
    fromRightRoomToLeft(160);
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

    if (right_bottle){
        LeftWheelTurn(-65);
        AccelerationDist(75);
        right_bottle = 0;
    }
    else {
        RightWheelTurn(25);
        LeftWheelTurn(-99);
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

    if (((cube != framesColor[0]) && (cube != framesColor[1]) && (cube != framesColor[2])) && cube != 0){
        cube = 0;
        additional_room = way;
        playSound(soundBeepBeep);
    }
    else{
        cubes[0] = cube;
    }
    

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

    AccelerationDist(96, 0.22,  min_speed_const,  10.5, 0.04);

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
        AccelerationDist(-45);
        preTurnStop();

        startTask(motorGrabFullDown);
        waitTask(&taskFlag_motorGrabFullDown);

        AccelerationDist(30);
        preTurnStop(100);
        motor[grabMotor] = 80;
        delay(250);
        add_angle = 41;
        startTask(normalizeCentMotor);
        delay(300);
        stopMotor(grabMotor, 1);
        motor[grabMotor] = 0;
        short buffer = cubes[0];
        cubes[0] = cubes[1];
        cubes[1] = buffer;
        AccelerationDist(15);
        preTurnStop();
    }
    else{
        startTask(normalizeCentMotor);
        preTurnStop();
    }

    TankTurn(119 + add_angle);
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

    if (left_bottle){
        RightWheelTurn(-66);
        AccelerationDist(75);
        left_bottle = 0;
    }
    else {
        LeftWheelTurn(25);
        RightWheelTurn(-99);
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

    if (((cube != framesColor[0]) && (cube != framesColor[1]) && (cube != framesColor[2])) && cube != 0){
        cube = 0;
        additional_room = way;
        playSound(soundBeepBeep);
    }
    else{
        cubes[1] = cube;
    }
    
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
    delay(300);
    AccelerationDist(-60);
    preTurnStop();
    waitTask(&taskFlag_motorWaterFullDown);
    startTask(normalizeCentMotor);
    AccelerationLinePID(105);
    AccelerationDist(215);
    preTurnStop();
    TankTurn(45);
    preTurnStop();
    AccelerationDist(10);
}

void getBall(){
    if ((additional_room == 0) || (additional_room == 1)){
        fromFramesToFirstPairRooms();
    }
    else{
        fromFramesToSecondPairRooms();
    }
    
    
    if ((additional_room == 0) || (additional_room == 2)){
        getInsideRight();
        preTurnStop(50);
        startTask(motorGrabFullDown);
        TankTurn(43);
        preTurnStop();
        waitTask(&taskFlag_motorGrabFullDown);
        AccelerationDist(63, 0.22,  min_speed_const,  10.5, 0.04);
        preTurnStop();
        closeBall();
        startTask(normalizeCentMotor);
        TankTurn(180);
        preTurnStop();
        AccelerationDist(63);
        preTurnStop();
        TankTurn(-43.3);
        preTurnStop();
        AccelerationDist(190);

        AccelerationLinePID(25, 1, 0.5, min_speed_const, acceleration - 0.01, 70, 0, 0, 10);

        preTurnStop(90);
        LeftWheelTurn(100);
        RightWheelTurn(10);
    }
    else{
        getInsideLeft();
        preTurnStop(50);
        startTask(motorGrabFullDown);
        TankTurn(-43);
        preTurnStop();
        waitTask(&taskFlag_motorGrabFullDown);
        AccelerationDist(63, 0.22,  min_speed_const,  10.5, 0.04);
        preTurnStop();
        closeBall();
        startTask(normalizeCentMotor);
        TankTurn(180);
        preTurnStop();
        AccelerationDist(63);
        preTurnStop();
        TankTurn(43.3);
        preTurnStop();
        AccelerationDist(190);

        AccelerationLinePID(25, 1, 0.5, min_speed_const, acceleration, 0, 70, 0, 10);

        preTurnStop(90);
        RightWheelTurn(100);
        LeftWheelTurn(10);
    }
    

    if ((additional_room == 0) || (additional_room == 1)){
        pr_error = 0;
        AccelerationLinePID(250, 1, 0.5);
        AccelerationLinePID(210, 0, 0.5);
        AccelerationDist(55, 0, fabs(motor[leftMotor]));
        PointTurn(200, 0, 89.5, 1, 0.4);
    }
    else{
        AccelerationLinePID(300, 1, 0.48);
        AccelerationDist(BetweenSensorsAndMiddle);
        preTurnStop();
        TankTurn(-20);
        preTurnStop();
        AccelerationDist(423);
        preTurnStop();
        TankTurn(-70);
        preTurnStop();
        NOW_ANGLE = 360;
    }

    AccelerationLinePID(20, 1, 0);
    preTurnStop(150);
    AccelerationDist(-10, 0);
    preTurnStop();
    NOW_ANGLE = 360;    

    if (framesColor[0] == framesColor[1])
        drop1in2();
    else if (framesColor[0] == framesColor[2]) {
        drop1in3();
    }
    else if (framesColor[1] == framesColor[2]) {
        drop1in3();
    }

    finish();
}

float TakeBottles(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    startTask(motorWaterFullDown);
    waitTask(&taskFlag_motorWaterFullDown);
    startTask(setNormAfterWaterFullDown);
    waitTask(&taskFlag_setNormAfterWaterFullDown)
    nMotorEncoder[centMotor] = 0;

    TankTurn(45);
    preTurnStop();
    startTask(motorGrabFullDown);
    waitTask(&taskFlag_motorGrabFullDown);

    stopMotor(grabMotor, 1);
    nMotorEncoder[grabMotor] = 0;
	stopMotor(grabMotor, 0);
    moveMotor(grabMotor, 187, 70, 1);
    
    preTurnStop();
    Kp_norm = 0.3;
    AccelerationDist(100, 1);
    AccelerationLinePID(40, 1, 0, motor[rightMotor]);
    preTurnStop(200);
    Kp_norm = 0.5;

    AccelerationDist(80, 0);
    preTurnStop(200);
    
    startTask(normalizeCentMotor);

    AccelerationDist(-80, 0);
    motor[grabMotor] = -30;
    preTurnStop();
   

    TankTurn(180);
    preTurnStop();
    AccelerationDist(-80, 0);

    preTurnStop(200);
    AccelerationLinePID(120, 0);
    AccelerationDist(380);
    AccelerationLinePID(20, 1);

    TankTurn(-32);
    preTurnStop();

    startTask(prepareForCube);
    startTask(motorGrabFullDown);
    preTurnStop();

    AccelerationDist(25, 0, 15, 10, 0.004);
    AccelerationDist(65, 0, 11, 11, 0.0001);
    preTurnStop(50);
    waitTask(&taskFlag_motorGrabFullDown);
    takeCube();

    startTask(normalizeCentMotor);

    AccelerationDist(-90, 0);
    preTurnStop();
    waitTask(&taskFlag_normalizeCentMotor);

    TankTurn(62);
    AccelerationDist(-30, 0);
    preTurnStop();
    moveMotor(centMotor, 240, 100, 1);
    stopMotor(centMotor, 1);
    preTurnStop();
    AccelerationDist(40, 0);
    preTurnStop();

    motor[grabMotor] = 60;
    delay(500);
    motor[grabMotor] = 0;

    preTurnStop(200);

    AccelerationDist(-10, 0);
    startTask(normalizeCentMotor);
    preTurnStop(200);
    TankTurn(-210);

    AccelerationDist(-80);
    preTurnStop(200);
    AccelerationLinePID(150, 0);
    AccelerationDist(300);
    AccelerationLinePID(20, 1);

    preTurnStop();

    TankTurn(24);
    preTurnStop();
    AccelerationDist(45);
    preTurnStop();
    startTask(BallDrop);
    waitTask(&taskFlag_BallDrop);
    AccelerationDist(-45);
    preTurnStop();

    moveMotor(centMotor, 40, -100, 1);
    stopMotor(centMotor, 1);

    TankTurn(-48);
    preTurnStop();
    AccelerationDist(80);
    preTurnStop();
    motor[grabMotor] = -50;
    delay(300);

    AccelerationDist(-80);
    preTurnStop();
    startTask(normalizeCentMotor);
    TankTurn(24);
    preTurnStop();
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop()
    TankTurn(90);
    preTurnStop()
    AccelerationLinePID(150, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop()
    TankTurn(90);
    preTurnStop()
    AccelerationLinePID(200, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();
    TankTurn(-90);
    preTurnStop();
    AccelerationLinePID(100, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    TankTurn(90);
    preTurnStop();

    startTask(motorGrabFullDown);
    waitTask(&taskFlag_motorGrabFullDown);

    AccelerationLinePID(20, 0);
    preTurnStop();

    motor[grabMotor] = 70;
    delay(1200);
    AccelerationDist(-20);
    preTurnStop();
    TankTurn(90);
    preTurnStop();
    AccelerationLinePID(100, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();
    TankTurn(90)
    preTurnStop();
    moveMotor(centMotor, 140, -100, 1);
    stopMotor(centMotor, 1);
    AccelerationLinePID(250);
    preTurnStop();
    TankTurn(90);
    preTurnStop();
    AccelerationDist(500);
    preTurnStop();

    LeftWheelTurn(34);
    preTurnStop();
    LeftWheelTurn(-16);
    preTurnStop();
    stopMotor(centMotor, 1);
    motor[centMotor] = 100;
    delay(500);
    stopMotor(centMotor, 1);

    motor[centMotor] = -20;
    delay(50);
    motor[centMotor] = 0;
    delay(200)

    motor[grabMotor] = -30;
    delay(200);
    LeftWheelTurn(-16);
    startTask(normalizeCentMotor);
    delay(200);
    
    preTurnStop();

    
    preTurnStop();
    AccelerationDist(35);
    preTurnStop();
    TankTurn(83);
    preTurnStop();
    delay(500);
    AccelerationLinePID(100, 1);
    AccelerationLinePID(150, 0);
    AccelerationDist(380, 0);
    preTurnStop();
    TankTurn(-90);

    motor[centMotor] = -100;
    delay(500);
    motor[centMotor] = 0;

    AccelerationDist(-130);
    preTurnStop();

    startTask(normalizeCentMotor);
    preTurnStop();

    AccelerationDist(130);
    preTurnStop();
    TankTurn(-90);

    preTurnStop();
    AccelerationDist(380);
    AccelerationLinePID(30, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();

    TankTurn(-90);
    AccelerationLinePID(400, 1);
    AccelerationLinePID(220, 0)
    AccelerationDist(380);
    AccelerationLinePID(420, 1);

    AccelerationDist(BetweenSensorsAndMiddle);
    TankTurn(90);
    preTurnStop();

    startTask(motorGrabFullDown);
    waitTask(&taskFlag_motorGrabFullDown);

    AccelerationLinePID(20, 0);
    preTurnStop();

    motor[grabMotor] = 70;
    delay(1200);
    AccelerationDist(-20);
    preTurnStop();
    TankTurn(90);
    preTurnStop();
    AccelerationLinePID(100, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();
    TankTurn(90)
    preTurnStop();
    moveMotor(centMotor, 140, -100, 1);
    stopMotor(centMotor, 1);
    AccelerationLinePID(250);
    preTurnStop();
    TankTurn(90);
    preTurnStop();
    AccelerationDist(500);
    preTurnStop();

    LeftWheelTurn(34);
    preTurnStop();
    LeftWheelTurn(-16);
    preTurnStop();
    stopMotor(centMotor, 1);
    motor[centMotor] = 100;
    delay(500);
    stopMotor(centMotor, 1);

    motor[centMotor] = -20;
    delay(50);
    motor[centMotor] = 0;
    delay(200)

    motor[grabMotor] = -30;
    delay(200);
    LeftWheelTurn(-16);
    startTask(normalizeCentMotor);
    delay(200);
    
    preTurnStop();

    
    preTurnStop();
    AccelerationDist(35);
    preTurnStop();
    TankTurn(83);
    preTurnStop();
    delay(500);
    AccelerationLinePID(100, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();

    TankTurn(90);
    preTurnStop();
    
    AccelerationLinePID(450, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();

    TankTurn(-90);
    preTurnStop();
    AccelerationLinePID(350, 0);
    preTurnStop();
    TankTurn(-90);
    preTurnStop();
    startTask(motorGrabFullDown);
    AccelerationDist(400);
    LeftWheelTurn(40)
    AccelerationDist(200);
}

void leftRoomBottle(){
    TankTurn(-90);
    AccelerationDist(-150, 0);
    AccelerationDist(700);

}

void test(){
    AccelerationLinePID(100, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    TankTurn(90);
    preTurnStop();

    startTask(motorGrabFullDown);
    waitTask(&taskFlag_motorGrabFullDown);

    AccelerationLinePID(20, 0);
    preTurnStop();

    motor[grabMotor] = 70;
    delay(1200);
    AccelerationDist(-20);
    preTurnStop();
    TankTurn(90);
    preTurnStop();
    AccelerationLinePID(100, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();
    TankTurn(90)
    preTurnStop();
    moveMotor(centMotor, 140, -100, 1);
    stopMotor(centMotor, 1);
    AccelerationLinePID(250);
    preTurnStop();
    TankTurn(90);
    preTurnStop();
    AccelerationDist(500);
    preTurnStop();

    LeftWheelTurn(34);
    preTurnStop();
    LeftWheelTurn(-16);
    preTurnStop();
    stopMotor(centMotor, 1);
    motor[centMotor] = 100;
    delay(500);
    stopMotor(centMotor, 1);

    motor[centMotor] = -20;
    delay(50);
    motor[centMotor] = 0;
    delay(200)

    motor[grabMotor] = -30;
    delay(200);
    LeftWheelTurn(-16);
    startTask(normalizeCentMotor);
    delay(200);
    
    preTurnStop();

    
    preTurnStop();
    AccelerationDist(35);
    preTurnStop();
    TankTurn(83);
    preTurnStop();
    delay(500);
    AccelerationLinePID(100, 1);
    AccelerationLinePID(150, 0);
    AccelerationDist(380, 0);
    preTurnStop();
    TankTurn(-90);

    motor[centMotor] = -100;
    delay(500);
    motor[centMotor] = 0;

    AccelerationDist(-130);
    preTurnStop();

    startTask(normalizeCentMotor);
    preTurnStop();

    AccelerationDist(130);
    preTurnStop();
    TankTurn(-90);

    preTurnStop();
    AccelerationDist(380);
    AccelerationLinePID(30, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();

    TankTurn(-90);
    AccelerationLinePID(400, 1);
    AccelerationLinePID(220, 0)
    AccelerationDist(380);
    AccelerationLinePID(420, 1);

    AccelerationDist(BetweenSensorsAndMiddle);
    TankTurn(90);
    preTurnStop();

    startTask(motorGrabFullDown);
    waitTask(&taskFlag_motorGrabFullDown);

    AccelerationLinePID(20, 0);
    preTurnStop();

    motor[grabMotor] = 70;
    delay(1200);
    AccelerationDist(-20);
    preTurnStop();
    TankTurn(90);
    preTurnStop();
    AccelerationLinePID(100, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();
    TankTurn(90)
    preTurnStop();
    moveMotor(centMotor, 140, -100, 1);
    stopMotor(centMotor, 1);
    AccelerationLinePID(250);
    preTurnStop();
    TankTurn(90);
    preTurnStop();
    AccelerationDist(500);
    preTurnStop();

    LeftWheelTurn(34);
    preTurnStop();
    LeftWheelTurn(-16);
    preTurnStop();
    stopMotor(centMotor, 1);
    motor[centMotor] = 100;
    delay(500);
    stopMotor(centMotor, 1);

    motor[centMotor] = -20;
    delay(50);
    motor[centMotor] = 0;
    delay(200)

    motor[grabMotor] = -30;
    delay(200);
    LeftWheelTurn(-16);
    startTask(normalizeCentMotor);
    delay(200);
    
    preTurnStop();

    
    preTurnStop();
    AccelerationDist(35);
    preTurnStop();
    TankTurn(83);
    preTurnStop();
    delay(500);
    AccelerationLinePID(100, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();

    TankTurn(90);
    preTurnStop();
    
    AccelerationLinePID(450, 1);
    AccelerationDist(BetweenSensorsAndMiddle);
    preTurnStop();

    TankTurn(-90);
    preTurnStop();
    AccelerationLinePID(350, 0);
    startTask(motorGrabFullDown);
    AccelerationDist(400);
    LeftWheelTurn(40)
    AccelerationDist(200);
}