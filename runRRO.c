#pragma config(Sensor, S3,     leftSensor,     sensorLightActive)
#pragma config(Sensor, S4,     rightSensor,    sensorLightActive)
#pragma config(Sensor, S1,     HTleft,         sensorI2CCustom)
#pragma config(Sensor, S2,     HTright,        sensorI2CCustom)
#pragma config(Motor,  motorA,          leftMotor,     tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightMotor,    tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          grabMotor,     tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          centMotor,     tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard

//#include "header/hitechnic-EOPD.h"
#include "header/hitechnic-colour-v2.h"
#include <include/Init.c>
#include "header/logging.h"
#include <include/SensorsTools.c>
#include <include/MovementTools.c>
#include <include/Tools.c>
#include <include/colorsDetection.c>
#include <include/TachoPID.c>
#include <include/LinePID.c>
#include <include/Turns.c>
#include <include/Manipulators.c>
#include <include/Route.c>
#include <include/scanning.c>
#include <include/Logic.c>

task main()
{
	setSoundVolume(10);
	check_battery();
	setSoundVolume(10);
	stopMotor(grabMotor, 1);

	InitMarkerCallibrationRaw();
	InitWashCallibrationRaw();
	InitCallibrationFamesInfoRaw();

	initSensor(&colorRightSensor, HTright, HTCS2_MODE_ACTIVE);
	initSensor(&colorLeftSensor,  HTleft,  HTCS2_MODE_ACTIVE);

	#if CALIBRATE == 1
		LCDWriteInfoNXTSen();
		calibrateLeftRightHT(&colorLeftSensor, &colorRightSensor, &FamesRawRight);
	#endif

	motor[grabMotor] = -30;
	TakeBottles();
	motor[grabMotor] = 0;
	nMotorEncoder[grabMotor] = 0;

	readIndicators(20);
	RightRoom();
	LeftRoom();
	fromFirstPairRoomsToFrames();
	AccelerationLinePID(20, 1, 0);
	frames();
	bibob++;
	now_cubes = 0;
	cubes[0] = 0;
	cubes[1] = 0;
	fromFramesToSecondPairRooms();
	readIndicators(15);
	RightRoom();
	LeftRoom();
	fromSecondPairRoomsToFrames();
	frames(0);
	finish();
	BrakeLeftRightMotor(1);

	sleep(2000);
	#if LOGGING == 1
		fileClose(fileHandle);
	#endif
	}
