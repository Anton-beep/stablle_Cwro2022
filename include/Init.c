const float Kp_slow = 0.11;
const float Ki_slow = 0;
const float Kd_slow = 5;

const float Kp_norm = 0.85;
const float Ki_norm = 0;
const float Kd_norm = 19;

const float Kp_tacho = 0.5;
const float Ki_tacho = 0.001;
const float Kd_tacho = 17;

const float axleTrack = 175.25;
const float wheelDiameter = 80;
const float BetweenSensorsAndMiddle = 75.5;

const float left_min_sensor = 2310;
const float right_min_sensor = 2272;

const float left_max_sensor = 1724;
const float right_max_sensor = 1624;

const float max_speed_const = 80;
const float min_speed_const = 17;

const float acceleration_slow = 0.001;      // speed_points/ms^2
const float acceleration = 0.04;            // speed_points/ms^2
const float acceleration_fast = 0.068;
const float acceleration_superFast = 0.125;

const float acceleration_turnSlow = 0.03;
const float acceleration_turn = 0.065;
const float acceleration_turnFast = 0.09;
const float acceleration_turnSuperFast = 0.12;

long ht_results[2];

float integral_sum = 0;
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
	MarkerInfoRawLeft.red_max =   30;
	MarkerInfoRawLeft.green_max = 53;
	MarkerInfoRawLeft.blue_max =  36;

	MarkerInfoRawLeft.red_min =   18;
	MarkerInfoRawLeft.green_min = 35;
	MarkerInfoRawLeft.blue_min =  26;

	MarkerInfoRawRight.red_max =   27;
	MarkerInfoRawRight.green_max = 48;
	MarkerInfoRawRight.blue_max =  34;

	MarkerInfoRawRight.red_min =   15;
	MarkerInfoRawRight.green_min = 31;
	MarkerInfoRawRight.blue_min =  22;
}

void InitWashCallibrationRaw (){
	WashInfoRawLeft.red_max =   32;
	WashInfoRawLeft.green_max = 55;
	WashInfoRawLeft.blue_max =  38;

	WashInfoRawLeft.red_min =   16;
	WashInfoRawLeft.green_min = 36;
	WashInfoRawLeft.blue_min =  27;

	WashInfoRawRight.red_max =   27;
	WashInfoRawRight.green_max = 48;
	WashInfoRawRight.blue_max =  33;

	WashInfoRawRight.red_min =   14;
	WashInfoRawRight.green_min = 30;
	WashInfoRawRight.blue_min =  22;
}

int global_frames_first;
int global_frames_second;
int global_frames_third;
