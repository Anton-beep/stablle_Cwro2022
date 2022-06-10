const float Kp_slow = 0.11;
const float Ki_slow = 0;
const float Kd_slow = 5;

const float Kp_norm = 0.8;
const float Ki_norm = 0;
const float Kd_norm = 15;

const float Kp_tacho = 0.8;
const float Ki_tacho = 0.35;
const float Kd_tacho = 19;

const float axleTrack = 175.5;
const float wheelDiameter = 80;
const float BetweenSensorsAndMiddle = 75;

const float left_min_sensor = 2340;
const float right_min_sensor = 2312;

const float left_max_sensor = 1700;
const float right_max_sensor = 1640;

const float max_speed_const = 80;
const float min_speed_const = 17;

const float acceleration_slow = 0.001; // speed_points/ms^2
const float acceleration = 0.04; // speed_points/ms^2
const float acceleration_fast = 0.068;
const float acceleration_superFast = 0.125;

const float acceleration_turnSlow = 0.03;
const float acceleration_turn = 0.065;
const float acceleration_turnFast = 0.09;
const float acceleration_turnSuperFast = 0.12;

long ht_results[2];

float NOW_ANGLE = 45;
float pr_error = 0;
float pr_error_tacho = 0;

typedef struct {
	tMotor max_motor_element;
	tMotor min_motor_element;

	float speed_cof;

	float max_motor_enc;
	float min_motor_enc;
} SyncedMotorsPair;


typedef struct {
	float firstSensor;
	float secondSensor;
} Arraysensors;

typedef struct {
	char *commands;
	byte weight;
} weights_struct;

weights_struct* InitStructWeight (char *command, byte weight) {
	weights_struct *w_pointer;
	weights_struct w;

	w.commands = command;
	w.weight = weight;
	w_pointer = &w;

	return w_pointer;
}

Arraysensors *results_sensors = NULL;

tHTCS2 colorRightSensor;
tHTCS2 colorLeftSensor;

CalibrationHiTechData FamesFIRSTRawRight;
CalibrationHiTechData FamesSECONDRawRight;

CalibrationHiTechData MarkerInfoRawLeft;
CalibrationHiTechData MarkerInfoRawRight;

CalibrationHiTechData WashInfoRawLeft;
CalibrationHiTechData WashInfoRawRight;

void InitCallibrationFamesInfoRaw() {
	FamesFIRSTRawRight.red_max = 25;
	FamesFIRSTRawRight.green_max = 47;
	FamesFIRSTRawRight.blue_max = 33;

	FamesFIRSTRawRight.red_min = 17;
	FamesFIRSTRawRight.green_min = 36;
	FamesFIRSTRawRight.blue_min = 26;

	FamesSECONDRawRight.red_max = 22;
	FamesSECONDRawRight.green_max = 44;
	FamesSECONDRawRight.blue_max = 31;

	FamesSECONDRawRight.red_min = 17;
	FamesSECONDRawRight.green_min = 37;
	FamesSECONDRawRight.blue_min = 26;
	

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// я тут ошибочку допустил, калибровать минимум нужно по черной рамке, заранее сорян
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void InitMarkerCallibrationRaw() {
	MarkerInfoRawLeft.red_max = 34;
	MarkerInfoRawLeft.green_max = 57;
	MarkerInfoRawLeft.blue_max = 39;

	MarkerInfoRawLeft.red_min = 15;
	MarkerInfoRawLeft.green_min = 31;
	MarkerInfoRawLeft.blue_min = 24;

	MarkerInfoRawRight.red_max = 34;
	MarkerInfoRawRight.green_max = 58;
	MarkerInfoRawRight.blue_max = 39;

	MarkerInfoRawRight.red_min = 21;
	MarkerInfoRawRight.green_min = 39;
	MarkerInfoRawRight.blue_min = 28;
}

void InitWashCallibrationRaw (){
	WashInfoRawLeft.red_max = 30;
	WashInfoRawLeft.green_max = 51;
	WashInfoRawLeft.blue_max = 34;

	WashInfoRawLeft.red_min = 14;
	WashInfoRawLeft.green_min = 30;
	WashInfoRawLeft.blue_min = 23;

	WashInfoRawRight.red_max = 28;
	WashInfoRawRight.green_max = 49;
	WashInfoRawRight.blue_max = 33;

	WashInfoRawRight.red_min = 19;
	WashInfoRawRight.green_min = 38;
	WashInfoRawRight.blue_min = 26;
}

int global_frames_first;
int global_frames_second;
int global_frames_third;
