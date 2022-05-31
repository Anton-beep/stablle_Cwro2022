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
    // датчики вроде спереди
    AccelerationLinePID(175);
    AccelerationDist(45);
    ReadLeftWash(50, 35);
    // считали - записали
    int leftRoom_wash = get_colorWash_left(ht_results[0]);

    // сначала небольшой отъезд назад, это будет стартом всего (где-то тут начинается просто переписывание старого кода)
    AccelerationDistSlow(-10.7);
    BrakeLeftRightMotor(1);
    sleep(350);

    if (leftRoom_wash != 0)
    {
        // кубик есть, надо его съесть
        startTask(prepareGraberForCube);
        RightWheelTurn(-90);
        BrakeLeftRightMotor(1);
        sleep(100);
        startTask(motorGraberFullDown);
        wait_task(taskFlag_motorGraberFullDown);
        startTask(takeCube);
        wait_task(taskFlag_takeCube);
        startTask(normalizeCentMotor);
    }

    if (markerLeft == 6)
    {
        // вода
        // возмонжо нужно отъехать назад/вперед
        if (global_water_left != 0)
        {
            // левая вода
            RightWheelTurn(31);
            wait_task(taskFlag_normalizeCentMotor);
            startTask(waterOnTable);
            wait_task(taskFlag_waterOnTable);
            global_water_left = 0;
            AccelerationDist(80);
            BrakeLeftRightMotor(1);
            startTask(normalizeCentMotor);
            sleep(300);
            TankTurn(-100);
            BrakeLeftRightMotor(1);
            sleep(300);
            AccelerationDistFast(100);
            AccelerationLinePID(30, 1);
            MoveBeforeTurn();
        }
        else
        {
            // правая вода
            RightWheelTurn(31);
            wait_task(taskFlag_normalizeCentMotor);
            startTask(waterOnTable);
            wait_task(taskFlag_waterOnTable);
            global_water_right = 0;
            AccelerationDist(80);
            BrakeLeftRightMotor(1);
            startTask(normalizeCentMotor);
            sleep(300);
            TankTurn(-110);
            BrakeLeftRightMotor(1);
            sleep(300);
            AccelerationDistFast(100);
            AccelerationLinePID(30, 1);
            MoveBeforeTurn();
        }
    }
    else if (markerLeft == 2)
    {
        // шарик
        LeftWheelTurn(90);
        BrakeLeftRightMotor(1);
        sleep(300);
        AccelerationDist(-29);
        BrakeLeftRightMotor(1);
        startTask(motorGraberFullDown);
        AccelerationDistSlow(23);
        BrakeLeftRightMotor(1);
        wait_task(taskFlag_motorGraberFullDown);
        if (leftRoom_wash != 0)
        {
            // вспоминаем про кубик
            startTask(closeAndHoldGraber);
            wait_task(taskFlag_closeAndHoldGraber);
        }
        else
        {
            startTask(closeAndHoldGraber);
            wait_task(taskFlag_closeAndHoldGraber);
        }
        LeftWheelTurn(86.5);
        if (leftRoom_wash != 0)
        {
            AccelerationDist(26);
            startTask(downGraberForONEBall);
            wait_task(taskFlag_downGraberForONEBall);
            startTask(openBall);
            wait_task(taskFlag_openBall);
        }
        else
        {
            AccelerationDist(131);
            startTask(downGraberForBallAndCube);
            wait_task(taskFlag_downGraberForBallAndCube);
            startTask(openGraber);
            wait_task(taskFlag_openGraber);
        }
        TankTurn(96.3);
        BrakeLeftRightMotor(1);
        sleep(300);
        AccelerationDistFast(80.5);
        AccelerationLinePID(20, 1);
        MoveBeforeTurn();
    }
    return leftRoom_wash;
}

int rightRoom_yellow(short markerRight)
{
    // датчики вроде спереди
    AccelerationLinePID(175);
    AccelerationDist(45);
    ReadRightWash(50, 35);
    // считали - записали
    int rightRoom_wash = get_colorWash_right(ht_results[1]);

    // сначала небольшой отъезд назад, это будет стартом всего (где-то тут начинается просто переписывание старого кода)
    AccelerationDistSlow(-10.7);
    BrakeLeftRightMotor(1);
    sleep(350);

    if (rightRoom_wash != 0)
    {
        // кубик есть, надо его съесть
        startTask(prepareGraberForCube);
        LeftWheelTurn(90);
        BrakeLeftRightMotor(1);
        sleep(100);
        startTask(motorGraberFullDown);
        wait_task(taskFlag_motorGraberFullDown);
        startTask(takeCube);
        wait_task(taskFlag_takeCube);
        startTask(normalizeCentMotor);
    }

    if (markerRight == 6)
    {
        // вода
        // возмонжо нужно отъехать назад/вперед
        if (global_water_left != 0)
        {
            // левая вода
            LeftWheelTurn(-31);
            wait_task(taskFlag_normalizeCentMotor);
            startTask(waterOnTable);
            wait_task(taskFlag_waterOnTable);
            global_water_left = 0;
            AccelerationDist(80);
            BrakeLeftRightMotor(1);
            startTask(normalizeCentMotor);
            sleep(300);
            TankTurn(110);
            BrakeLeftRightMotor(1);
            sleep(300);
            AccelerationDistFast(100);
            AccelerationLinePID(30, 1);
            MoveBeforeTurn();
        }
        else
        {
            // правая вода
            LeftWheelTurn(-31);
            wait_task(taskFlag_normalizeCentMotor);
            startTask(waterOnTable);
            wait_task(taskFlag_waterOnTable);
            global_water_right = 0;
            AccelerationDist(80);
            BrakeLeftRightMotor(1);
            startTask(normalizeCentMotor);
            sleep(300);
            TankTurn(100);
            BrakeLeftRightMotor(1);
            sleep(300);
            AccelerationDistFast(100);
            AccelerationLinePID(30, 1);
            MoveBeforeTurn();
        }
    }
    else if (markerRight == 2)
    {
        // шарик
        RightWheelTurn(-90);
        BrakeLeftRightMotor(1);
        sleep(300);
        AccelerationDist(-29);
        BrakeLeftRightMotor(1);
        startTask(motorGraberFullDown);
        AccelerationDistSlow(23);
        BrakeLeftRightMotor(1);
        wait_task(taskFlag_motorGraberFullDown);
        if (rightRoom_wash != 0)
        {
            // вспоминаем про кубик
            startTask(closeAndHoldGraber);
            wait_task(taskFlag_closeAndHoldGraber);
        }
        else
        {
            startTask(closeAndHoldGraber);
            wait_task(taskFlag_closeAndHoldGraber);
        }
        RightWheelTurn(-86.5);
        if (rightRoom_wash != 0)
        {
            AccelerationDist(26);
            startTask(downGraberForONEBall);
            wait_task(taskFlag_downGraberForONEBall);
            startTask(openBall);
            wait_task(taskFlag_openBall);
        }
        else
        {
            AccelerationDist(131);
            startTask(downGraberForBallAndCube);
            wait_task(taskFlag_downGraberForBallAndCube);
            startTask(openGraber);
            wait_task(taskFlag_openGraber);
        }
        TankTurn(96.3);
        BrakeLeftRightMotor(1);
        sleep(300);
        AccelerationDistFast(80.5);
        AccelerationLinePID(20, 1);
        MoveBeforeTurn();
    }
    return rightRoom_wash;
}

pair *Rooms_blueYellow()
{
    AccelerationLinePIDFast(290);
    ReadIndicator(40, 60);
    AccelerationLinePID(175);
    MoveBeforeTurn(1);
    TankTurn(-90);
    BrakeLeftRightMotor(1);
    sleep(300);
    //узнаем цвет и записываем
    int marker_leftRoom = get_colorMarker_left(ht_results[0]);
    int marker_rightRoom = get_colorMarker_left(ht_results[1]);

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
        AccelerationLinePIDFast(180, 1);
        BrakeLeftRightMotor(1);
        wait_task(taskFlag_motorGraberFullDown);
        startTask(openGraber);
        wait_task(taskFlag_openGraber);
        startTask(normalizeCentMotor);
        AccelerationDist(-40);
        TankTurnFast(180);
        BrakeLeftRightMotor(1);
        sleep(150);
        AccelerationLinePID(10, 1);
        MoveBeforeTurn(1);
        sleep(100);
        TankTurn(90);
        BrakeLeftRightMotor(1);
        sleep(300);
    }

    // старт правой (желтой) комнаты
    wash.second = rightRoom_yellow(marker_rightRoom);

    BrakeLeftRightMotor(1);
    sleep(150);
    TankTurnFast(-90);
    if (wash.first == 0 && wash.second != 0)
    {
        // первого кубика нет, но есть второй -> перехват второго
        startTask(openGraber);
        sleep(200);
        AccelerationDistSlow(-20);
        startTask(closeAndHoldGraber);
        wait_task(taskFlag_closeAndHoldGraber);
        // полетели
        AccelerationLinePIDSuperFast(450, 1);
    }
    else if (wash.first != 0 && wash.second != 0)
    {
        // оба кубика есть, надо съесть первый
        int buffer_ = wash.first;
        wash.first = wash.second;
        wash.second = wash.first;

        AccelerationLinePIDFast(120);
        AccelerationLinePID(25);
        startTask(closeAndHoldGraber);
        AccelerationDistSlow(30);
        AccelerationLinePIDSuperFast(170, 1);
    }
    else if (wash.first != 0 && wash.second == 0)
    {
        // есть первый кубик, берем его во второй слот
        wash.second = wash.first;
        wash.first = 0;

        AccelerationLinePIDFast(120);
        AccelerationLinePID(25);
        startTask(closeAndHoldGraber);
        AccelerationDistSlow(30);
        AccelerationLinePIDSuperFast(170, 1);
    }

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
    sleep(400);

    // первая рамка
    TankTurn(-39.5);
    BrakeLeftRightMotor(1);
    sleep(300);
    readRightSen_noMove(50, &FamesInfoRawRight);
    global_frames_first = get_colorFrame_first(ht_results[1]);

    TankTurn(-32.5);
    BrakeLeftRightMotor(1);
    sleep(300);
    readRightSen_noMove(50, &FamesInfoRawRight);
    global_frames_second = get_colorFrame_second(ht_results[1]);

    global_frames_third = get_thirdFrame_noReading(global_frames_first, global_frames_second);

    EditAngle(108);
}

void frames(int cube1, int cube2)
{
    // тот же принцип, как и у комнат, первый слот - ближний к основанию, второй - дальний
    // второй кубик
    startTask(downGraberForSecondCube);
    AbsTurn(findAngleFrameForCube(cube2));
    BrakeLeftRightMotor(1);
    sleep(400);
    AccelerationDistSlow(5.5);
    BrakeLeftRightMotor(1);
    sleep(400);
    wait_task(taskFlag_downGraberForSecondCube);
    startTask(openSecondCube);
    wait_task(openSecondCube);
    AccelerationDistSlow(-5.5);
    BrakeLeftRightMotor(1);
    sleep(400);

    if (cube1 != 0)
    {
        // первый кубик
        startTask(downGraberForFirstCube);
        AbsTurn(findAngleFrameForCube(cube1));
        BrakeLeftRightMotor(1);
        sleep(400);
        AccelerationDistSlow(22.3);
        BrakeLeftRightMotor(1);
        sleep(400);
        wait_task(taskFlag_downGraberForFirstCube);
        startTask(openGraber);
        wait_task(openGraber);
        AccelerationDistSlow(22.3);
        BrakeLeftRightMotor(1);
        sleep(400);
    }
    AbsTurn(180);
}

// movements без комнат

void start()
{
    TankTurn(45);
    AccelerationDist(70);
    AccelerationLinePIDFast(100, 1);
    BrakeLeftRightMotor(1);
    sleep(300);
    TankTurn(180);
    BrakeLeftRightMotor(1);
    sleep(300);
    AccelerationLinePID(70);
    BrakeLeftRightMotor(1);
    startTask(motorWaterFullDown);
    wait_task(taskFlag_motorWaterFullDown);
    sleep(300);
    AccelerationDistSlow(-100);
    BrakeLeftRightMotor(0);
    startTask(normalizeCentMotor);
    sleep(600);
    // дуга и выезжаем налево, на линию центр
    AccelerationDist(35);
    PointTurn(375, -10, -90, 1);
    // начинается комната
}

void moveFromFirstPairRoomsToFrames()
{
    PointTurn(375, -10, 90, 1);
    AccelerationLinePID(10, 1);
    // работаем с рамками
}

void moveFromFramesToSecondPair()
{
    // здесь мы должны смотреть на рамки и повернутся
    TankTurn(180);
    BrakeLeftRightMotor(1);
    sleep(300);
    AccelerationLinePID(50);
    BrakeLeftRightMotor(1);
    sleep(450);
    TankTurn(60);
    BrakeLeftRightMotor(1);
    sleep(450);
    AccelerationDist(300);
    TankTurn(30);
    BrakeLeftRightMotor(1);
    sleep(450);
}

void moveFromSecondPairRoomsToFrames()
{
    // вторпя комната окончена, мы на перекрестке
    TankTurn(30);
    BrakeLeftRightMotor(1);
    sleep(450);
    AccelerationDist(300);
    BrakeLeftRightMotor(1);
    sleep(450);
    TankTurn(60);
    BrakeLeftRightMotor(1);
    sleep(450);
    AccelerationLinePID(50);
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
