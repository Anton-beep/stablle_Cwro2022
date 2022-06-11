/*
    COLORS:
    0 - NULL
    1 - r
    2 - g
    3 - b
    4 - yellow
    5 - black
    6 - white
*/

int leftRoom_blue(short markerLeft)
{
    startTask(openGraber);
    // датчики вроде спереди
    AccelerationLinePID(110);
    AccelerationDist(105, 0);
    resetErrors_PIDTacho();
    ReadLeftWash(30, 18);
    resetErrors_PIDTacho();

    BrakeLeftRightMotor(1);
    delay(50);
    // считали - записали
    int leftRoom_wash = get_colorWash_left(ht_results[0]);

    AccelerationDistSlow(23.5, 0.001, 18);
    BrakeLeftRightMotor(1);
    delay(50);
    eraseDisplay();
    displayCenteredTextLine(8, "%d", ht_results[0]);
    displayCenteredTextLine(10, "%d", leftRoom_wash);

    BrakeLeftRightMotor(1);
    delay(2000);

    // AccelerationDistSlow(-10.7);

    TankTurnSlow(-90);
    BrakeLeftRightMotor(1);
    sleep(100);

    if (leftRoom_wash != 0)
    {
        // кубик есть, надо его съесть
        startTask(prepareGraberForCube);
        startTask(motorGraberFullDown);
        sleep(300);
        AccelerationDistSlow(100);
        BrakeLeftRightMotor(1);
        wait_task(&taskFlag_motorGraberFullDown);
        delay(100);
        startTask(takeCube);
        wait_task(&taskFlag_takeCube);
        delay(50);
        if (markerLeft == 6)
        {
            startTask(normalizeCentMotor);
        }
    }

    if (markerLeft == 6)
    {
        if (leftRoom_wash != 0)
        {
            AccelerationDist(-20);
            BrakeLeftRightMotor(1);
            sleep(100);
        }
        else
        {
            AccelerationDistSlow(70);
            BrakeLeftRightMotor(1);
            sleep(100);
        }
        // вода
        // возмонжо нужно отъехать назад/вперед
        if (global_water_left != 0)
        {
            // левая вода
            RightWheelTurn(-30);
            BrakeLeftRightMotor(1);
            wait_task(&taskFlag_normalizeCentMotor);
            startTask(waterOnTable);
            wait_task(&taskFlag_waterOnTable);
            global_water_left = 0;
            AccelerationDist(20);
            BrakeLeftRightMotor(1);
            startTask(normalizeCentMotor);
            sleep(300);
            AccelerationDist(-30);
            BrakeLeftRightMotor(1);
            TankTurn(-72);
            BrakeLeftRightMotor(1);
            sleep(300);
            AccelerationDist(20);
            AccelerationLinePIDFast(130, 1);
            MoveBeforeTurn(0);
        }
        else
        {
            // правая вода
            LeftWheelTurn(-26);
            BrakeLeftRightMotor(1);
            wait_task(&taskFlag_normalizeCentMotor);
            startTask(waterOnTable);
            wait_task(&taskFlag_waterOnTable);
            global_water_right = 0;
            AccelerationDist(20);
            BrakeLeftRightMotor(1);
            startTask(normalizeCentMotor);
            sleep(300);
            AccelerationDist(-30);
            BrakeLeftRightMotor(1);
            TankTurn(-139);
            BrakeLeftRightMotor(1);
            sleep(300);
            AccelerationDist(20);
            AccelerationLinePIDFast(130, 1);
            MoveBeforeTurn(0);
        }
    }
    else if (markerLeft == 2)
    {
        // шарик
        if (leftRoom_wash != 0)
        {
            AccelerationDistSlow(-23);
        }
        else
        {
            AccelerationDistSlow(61);
        }
        BrakeLeftRightMotor(1);
        wait_task(&taskFlag_normalizeCentMotor);

        if (leftRoom_wash == 0)
        {
            moveMotor(centMotor, 280, 100, 1);
        }

        sleep(300);
        TankTurnSlow(60.5);
        BrakeLeftRightMotor(1);
        sleep(150);
        AccelerationDistSlow(80);
        BrakeLeftRightMotor(1);
        sleep(50);
        startTask(closeAndHoldGraber);
        wait_task(&taskFlag_closeAndHoldGraber);
        startTask(normalizeCentMotorFAST);
        TankTurn(93);
        BrakeLeftRightMotor(1);
        sleep(100);
        AccelerationDist(98);
        BrakeLeftRightMotor(1);
        if (leftRoom_wash == 0)
        {
            startTask(downGraberForONEBall);
            wait_task(&taskFlag_downGraberForONEBall);
            startTask(openGraber);
            sleep(300);
        }
        else
        {
            startTask(downGraberForBallAndCube);
            wait_task(&taskFlag_downGraberForBallAndCube);
            startTask(openBall);
            wait_task(&taskFlag_openBall);
        }
        startTask(normalizeCentMotorFAST);
        wait_task(&taskFlag_normalizeCentMotorFAST);
        BrakeLeftRightMotor(1);
        TankTurn(115);
        BrakeLeftRightMotor(1);
        sleep(300);
        AccelerationDistFast(180);
        AccelerationLinePID(70, 1);
        MoveBeforeTurn(0);
    }
    return leftRoom_wash;
}

int rightRoom_yellow(short markerRight)
{
    startTask(openGraber);
    // датчики вроде спереди
    AccelerationLinePID(115);
    AccelerationDist(102, 0);
    resetErrors_PIDTacho();
    ReadRightWash(30, 18);
    resetErrors_PIDTacho();

    BrakeLeftRightMotor(1);
    delay(50);
    // считали - записали
    int rightRoom_wash = get_colorWash_right(ht_results[1]);

    AccelerationDistSlow(23.5, 0.001, 18);
    BrakeLeftRightMotor(1);
    delay(50);
    eraseDisplay();
    displayCenteredTextLine(8, "%d", ht_results[1]);
    displayCenteredTextLine(10, "%d", rightRoom_wash);

    BrakeLeftRightMotor(1);
    delay(2000);

    // AccelerationDistSlow(-10.7);

    TankTurnSlow(90);
    BrakeLeftRightMotor(1);
    sleep(100);

    if (rightRoom_wash != 0)
    {
        // кубик есть, надо его съесть
        startTask(prepareGraberForCube);
        startTask(motorGraberFullDown);
        sleep(300);
        AccelerationDistSlow(100);
        BrakeLeftRightMotor(0);
        wait_task(&taskFlag_motorGraberFullDown);
        delay(100);
        startTask(takeCube);
        wait_task(&taskFlag_takeCube);
        delay(50);
        if (markerRight == 6)
        {
            startTask(normalizeCentMotor);
        }
    }

    if (markerRight == 6)
    {
        if (rightRoom_wash != 0)
        {
            AccelerationDist(-20);
            BrakeLeftRightMotor(1);
            sleep(100);
        }
        else
        {
            sleep(300);
            AccelerationDistSlow(70);
            BrakeLeftRightMotor(1);
            sleep(100);
        }
        // вода
        // возмонжо нужно отъехать назад/вперед
        if (global_water_right != 0)
        {
            // правая вода
            LeftWheelTurn(-35);
            BrakeLeftRightMotor(1);
            wait_task(&taskFlag_normalizeCentMotor);
            startTask(waterOnTable);
            wait_task(&taskFlag_waterOnTable);
            global_water_right = 0;
            AccelerationDist(20);
            BrakeLeftRightMotor(1);
            startTask(normalizeCentMotor);
            sleep(300);
            AccelerationDist(-30);
            BrakeLeftRightMotor(1);
            TankTurn(72);
            BrakeLeftRightMotor(1);
            sleep(300);
            AccelerationDist(20);
            AccelerationLinePIDFast(130, 1);
            MoveBeforeTurn(1);
        }
        else
        {
            // левая вода
            RightWheelTurn(-21);
            BrakeLeftRightMotor(1);
            wait_task(&taskFlag_normalizeCentMotor);
            startTask(waterOnTable);
            wait_task(&taskFlag_waterOnTable);
            global_water_left = 0;
            AccelerationDist(20);
            BrakeLeftRightMotor(1);
            startTask(normalizeCentMotor);
            sleep(300);
            AccelerationDist(-30);
            BrakeLeftRightMotor(1);
            TankTurn(139);
            BrakeLeftRightMotor(1);
            sleep(300);
            AccelerationDist(20);
            AccelerationLinePIDFast(130, 1);
            MoveBeforeTurn(1);
        }
    }
    else if (markerRight == 2)
    {
        // шарик
        if (rightRoom_wash != 0)
        {
            AccelerationDistSlow(-23);
        }
        else
        {
            AccelerationDistSlow(61);
        }
        BrakeLeftRightMotor(1);
        wait_task(&taskFlag_normalizeCentMotor);
        
        if (rightRoom_wash == 0)
        {
            moveMotor(centMotor, 280, 100, 1);
        }
        sleep(300);
        TankTurnSlow(-60.5);
        BrakeLeftRightMotor(1);
        sleep(150);
        AccelerationDistSlow(80);
        BrakeLeftRightMotor(1);
        sleep(50);
        startTask(closeAndHoldGraber);
        wait_task(&taskFlag_closeAndHoldGraber);
        startTask(normalizeCentMotorFAST);
        TankTurn(-93);
        BrakeLeftRightMotor(1);
        sleep(100);
        AccelerationDist(98);
        BrakeLeftRightMotor(1);
        if (rightRoom_wash == 0)
        {
            startTask(downGraberForONEBall);
            wait_task(&taskFlag_downGraberForONEBall);
            startTask(openGraber);
            sleep(300);
        }
        else
        {
            startTask(downGraberForBallAndCube);
            wait_task(&taskFlag_downGraberForBallAndCube);
            startTask(openBall);
            wait_task(&taskFlag_openBall);
        }
        startTask(normalizeCentMotorFAST);
        wait_task(&taskFlag_normalizeCentMotorFAST);
        BrakeLeftRightMotor(1);
        TankTurn(-115);
        BrakeLeftRightMotor(1);
        sleep(300);
        AccelerationDistFast(180);
        AccelerationLinePID(70, 1);
        MoveBeforeTurn(0);
    }
    return rightRoom_wash;
}

pair *Rooms_blueYellow()
{
    AccelerationLinePID(160, 1, 1);
    ReadIndicator(45, 40);
    AccelerationDist(60, 1, 40);
    AccelerationLinePID(50, 1, 0.3, 40);
    AccelerationDist(BetweenSensorsAndMiddle);
    BrakeLeftRightMotor(1);
    sleep(300);
    TankTurn(-90);
    BrakeLeftRightMotor(1);
    //узнаем цвет и записываем
    int marker_leftRoom = get_colorMarker_left(ht_results[0]);
    int marker_rightRoom = get_colorMarker_left(ht_results[1]);

    displayCenteredTextLine(8, "%d", ht_results[0]);
    displayCenteredTextLine(10, "%d", marker_leftRoom);
    displayCenteredTextLine(12, "%d", ht_results[1]);
    displayCenteredTextLine(14, "%d", marker_rightRoom);

    pair wash;
    // начинается левая (синяя комната)
    wash.first = leftRoom_blue(marker_leftRoom);

    // откидываем кубик на линии
    if (wash.first != 0)
    {
        BrakeLeftRightMotor(1);
        sleep(150);
        TankTurnFast(90);
        BrakeLeftRightMotor(1);
        startTask(motorGraberFullDown);
        sleep(150);
        AccelerationLinePIDFast(140, 1);
        AccelerationLinePID(60);
        BrakeLeftRightMotor(1);
        wait_task(&taskFlag_motorGraberFullDown);
        startTask(openGraberSlow);
        sleep(350);
        startTask(normalizeCentMotorFAST);
        AccelerationDist(-40);
        wait_task(&taskFlag_normalizeCentMotorFAST);
        TankTurn(193.5);
        BrakeLeftRightMotor(1);
        sleep(200);
        AccelerationLinePIDSlow(30, 1);
        MoveBeforeTurn(1);
        sleep(100);
        TankTurn(90);
        BrakeLeftRightMotor(1);
        sleep(300);
    }
    else
    {
        startTask(openGraber);
    }

    // старт правой (желтой) комнаты
    wash.second = rightRoom_yellow(marker_rightRoom);

    if (wash.first == 0 && wash.second != 0)
    {
        BrakeLeftRightMotor(1);
        TankTurn(-90);
        // первого кубика нет, но есть второй -> перехват второго
        BrakeLeftRightMotor(1);
        sleep(150);
        startTask(motorGraberFullDown);
        AccelerationLinePIDFast(70);
        BrakeLeftRightMotor(1);
        sleep(150);
        startTask(openGraberCubeRooms);
        sleep(300);
        AccelerationDistSlow(-38);
        BrakeLeftRightMotor(1);
        sleep(100);
        wait_task(&taskFlag_openGraberCubeRooms);
        startTask(closeAndHoldGraber);
        sleep(400);
        startTask(normalizeCentMotorFAST);
        // полетели
        AccelerationLinePIDSuperFast(380, 1);
    }
    else if (wash.first != 0 && wash.second != 0)
    {
        BrakeLeftRightMotor(1);
        startTask(motorGraberFullDown);
        sleep(150);
        TankTurn(-90);
        // оба кубика есть, надо съесть первый
        int buffer_ = wash.first;
        wash.first = wash.second;
        wash.second = buffer_;

        BrakeLeftRightMotor(1);
        sleep(150);
        AccelerationLinePID(142);
        startTask(closeAndHoldGraber);
        AccelerationDistSlow(30);
        AccelerationLinePIDSuperFast(160, 1);
        startTask(normalizeCentMotorFAST);
    }
    else if (wash.first != 0 && wash.second == 0)
    {
        BrakeLeftRightMotor(1);
        startTask(motorGraberFullDown);
        sleep(150);
        TankTurn(-90);
        // есть первый кубик, берем его во второй слот
        wash.second = wash.first;
        wash.first = 0;

        BrakeLeftRightMotor(1);
        sleep(150);
        AccelerationLinePID(115);
        AccelerationDistSlow(55);
        BrakeLeftRightMotor(1);
        sleep(100);
        startTask(closeAndHoldGraber);
        sleep(300);
        AccelerationDistSlow(30);
        startTask(normalizeCentMotorFAST);
        AccelerationLinePIDSuperFast(180, 1);
    }
    BrakeLeftRightMotor(1);
    sleep(300);
    startTask(normalizeCentMotor, 255);
    wait_task(&taskFlag_normalizeCentMotor)
        // порядок возвращаемых кубиков: ближний к основнаию робота захват - первый, дальний - второй

        return &wash;
    // комнаты закончили смотря на синюю комнату на перекрестке
    // дальше идет выгрузка стирки
    // переход в стирку (см. main)
}

int leftRoom_red(int markerRight)
{
}

int rightRoom_green(int markerRight)
{
}

pair *Rooms_redGreen()
{
    return Rooms_blueYellow();
}

void readFrames()
{
    BrakeLeftRightMotor(1);
    sleep(300);

    // первая рамка
    TankTurn(-39.5);
    BrakeLeftRightMotor(1);
    readRightSen_noMove(20, &FamesFIRSTRawRight);
    global_frames_first = get_colorFrame_first(ht_results[1]);

    eraseDisplay();
    displayCenteredTextLine(8, "%d", ht_results[1]);
    displayCenteredTextLine(12, "%d", global_frames_first);

    // sleep(5000);

    TankTurn(-32.5);
    BrakeLeftRightMotor(1);
    readRightSen_noMove(20, &FamesSECONDRawRight);
    global_frames_second = get_colorFrame_second(ht_results[1]);

    eraseDisplay();
    displayCenteredTextLine(8, "%d", ht_results[1]);
    displayCenteredTextLine(12, "%d", global_frames_second);
    // sleep(5000);

    global_frames_third = get_thirdFrame_noReading(global_frames_first, global_frames_second);

    TankTurn(72);
    EditAngle(180);
}

void DropSecondCube(){
    AccelerationDistSlow(10);
    BrakeLeftRightMotor(1);
    startTask(downGraberForSecondCube);
    AbsTurn(180);
    BrakeLeftRightMotor(1);
    wait_task(&taskFlag_downGraberForSecondCube);
    delay(100);
    startTask(openSecondCube);
    wait_task(&taskFlag_openSecondCube);
    AccelerationDistSlow(-10);
    BrakeLeftRightMotor(1);
}

void DropFirstCube(){
    startTask(downGraberForFirstCube);

    AbsTurn(180);
    AccelerationDistSlow(48);
    BrakeLeftRightMotor(1);
    
    wait_task(&taskFlag_downGraberForFirstCube);


    moveMotor(grabMotor, 70, -100, 1);
    setMotorSpeed(grabMotor, -40);
    delay(250);

    AccelerationDistSlow(-48);
}

void DriftThirdFrame(){
    LeftWheelTurn(-60);
    RightWheelTurn(-67)
    AccelerationDistSlow(150);
    BrakeLeftRightMotor(1);
}

void DriftFirstFrame(){
    RightWheelTurn(-60);
    LeftWheelTurn(-67)
    AccelerationDistSlow(150);
    BrakeLeftRightMotor(1);
}

void DriftThirdToSecond(){
    AccelerationDistSlow(-150);
    RightWheelTurn(60);
    LeftWheelTurn(61);
    BrakeLeftRightMotor(1);
}

void DriftFirstToSecond(){
    AccelerationDistSlow(-150);
    LeftWheelTurn(60);
    RightWheelTurn(61);
    BrakeLeftRightMotor(1);
}

void DropSecondCubeInFrame(int cubeCol)
{
    if (cubeCol == global_frames_first)
    {
        DriftFirstFrame();
        DropSecondCube();
        DriftFirstToSecond();
    }
    else if (cubeCol == global_frames_second)
    {
        DropSecondCube();
    }
    else
    {
        DriftThirdFrame();
        DropSecondCube();
        DriftThirdToSecond();
    }
}

void DropFirstCubeInFrame(int cubeCol)
{
    if (cubeCol == global_frames_first)
    {
        DriftFirstFrame();
        DropFirstCube();
        DriftFirstToSecond();
    }
    else if (cubeCol == global_frames_second)
    {
        DropFirstCube();
    }
    else
    {
        DriftThirdFrame();
        DropFirstCube();
        DriftThirdToSecond();
    }
}

void frames(int cube1, int cube2)
{
    EditAngle(180);

    displayCenteredTextLine(8, "%d", cube1);
    displayCenteredTextLine(10, "%d", cube2);
    // sleep(5000);

    // тот же принцип, как и у комнат, первый слот - ближний к основанию, второй - дальний
    DropSecondCubeInFrame(cube2);
    delay(200);

    if (cube1 != 0)
    {
        DropFirstCubeInFrame(cube1);
    }
    
    startTask(normalizeCentMotorFAST);
    startTask(openGraber);
    sleep(200);
    BrakeLeftRightMotor(1);
}

// movements без комнат

void start()
{
    TankTurn(45);
    BrakeLeftRightMotor(1);
    sleep(200);
    AccelerationDist(110);
    AccelerationLinePID(100, 1);
    AccelerationDistSlow(20);
    BrakeLeftRightMotor(1);
    sleep(200);
    TankTurn(185);
    BrakeLeftRightMotor(1);
    sleep(200);
    AccelerationLinePIDSlow(60);
    startTask(motorWaterFullDown);
    AccelerationDistSlow(35);
    BrakeLeftRightMotor(1);
    wait_task(&taskFlag_motorWaterFullDown);
    sleep(200);
    AccelerationDistSlow(-110);
    BrakeLeftRightMotor(0);
    startTask(setNormAfterWaterFullDown);
    sleep(400);
    // дуга и выезжаем налево, на линию центр
    AccelerationDistSlow(37.1);
    PointTurn(275, 0, 87, 1);
    AccelerationLinePID(50, 1);
    AccelerationDistFast(40, 1);
    MoveBeforeTurn(0);
    // начинается комната
}

void moveFromFirstPairRoomsToFrames()
{
    AccelerationLinePID(220);
    PointTurn(230, 0, 90, 1);
    AccelerationLinePID(50, 1);
    BrakeLeftRightMotor(1);
    sleep(300);
    // работаем с рамками
}

void moveFromFramesToSecondPair()
{
    // здесь мы должны смотреть на рамки и повернутся
    AbsTurn(360);
    BrakeLeftRightMotor(1);
    sleep(200);
    AccelerationLinePIDSlow(50);
    BrakeLeftRightMotor(1);
    sleep(200);
    TankTurn(56.65);
    BrakeLeftRightMotor(1);
    sleep(250);
    AccelerationDist(450);
    BrakeLeftRightMotor(1);
    sleep(250);
    TankTurn(33.35);
    BrakeLeftRightMotor(1);
    sleep(250);
    AccelerationLinePIDSlow(40);
}

void moveFromSecondPairRoomsToFrames()
{
    // вторпя комната окончена, мы на перекрестке
    TankTurn(-30);
    BrakeLeftRightMotor(1);
    sleep(50);
    AccelerationDist(550);
    BrakeLeftRightMotor(1);
    sleep(450);
    TankTurn(-60);
    BrakeLeftRightMotor(1);
    sleep(50);
    AccelerationLinePID(10, 1);
    // работаем по рамкам
}

void finish()
{
    TankTurn(180);
    BrakeLeftRightMotor(1);
    sleep(300);
    AccelerationDist(300);
    TankTurn(-45);
    BrakeLeftRightMotor(1);
    sleep(300);
}
