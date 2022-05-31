const float Kp_slow = 0.165;
const float Ki_slow = 0;
const float Kd_slow = 3.3;

const float Kp_norm = 0.155;
const float Ki_norm = 0;
const float Kd_norm = 4.3;

const float Kp_tacho = 0.485;
const float Ki_tacho = 0.20;
const float Kd_tacho = 16;

const float axleTrack = 175.5;
const float wheelDiameter = 80;
const float BetweenSensorsAndMiddle = 75;

const float left_min_sensor = 2248;
const float right_min_sensor = 2296;

const float left_max_sensor = 1540;
const float right_max_sensor = 1640;

const float max_speed_const = 80;
const float min_speed_const = 19;

const float acceleration_slow = 0.01; // speed_points/ms^2
const float acceleration = 0.05; // speed_points/ms^2
const float acceleration_fast = 0.095;
const float acceleration_superFast = 0.125;

const float acceleration_turn = 0.07;
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

CalibrationHiTechData FamesInfoRawLeft;
CalibrationHiTechData FamesInfoRawRight;

CalibrationHiTechData MarkerInfoRawLeft;
CalibrationHiTechData MarkerInfoRawRight;

CalibrationHiTechData WashInfoRawLeft;
CalibrationHiTechData WashInfoRawRight;

void InitCallibrationFamesInfoRaw() {
	FamesInfoRawLeft.red_max = 255;
	FamesInfoRawLeft.green_max = 255;
	FamesInfoRawLeft.blue_max = 255;

	FamesInfoRawLeft.red_min = 255;
	FamesInfoRawLeft.green_min = 255;
	FamesInfoRawLeft.blue_min = 255;

	FamesInfoRawRight.red_max = 255;
	FamesInfoRawRight.green_max = 255;
	FamesInfoRawRight.blue_max = 255;

	FamesInfoRawRight.red_min = 255;
	FamesInfoRawRight.green_min = 255;
	FamesInfoRawRight.blue_min = 255;
}

void InitMarkerCallibrationRaw() {
	MarkerInfoRawLeft.red_max = 118;
	MarkerInfoRawLeft.green_max = 174;
	MarkerInfoRawLeft.blue_max = 111;

	MarkerInfoRawLeft.red_min = 21;
	MarkerInfoRawLeft.green_min = 42;
	MarkerInfoRawLeft.blue_min = 39;

	MarkerInfoRawRight.red_max = 143;
	MarkerInfoRawRight.green_max = 215;
	MarkerInfoRawRight.blue_max = 137;

	MarkerInfoRawRight.red_min = 17;
	MarkerInfoRawRight.green_min = 34;
	MarkerInfoRawRight.blue_min = 25;
}

void InitWashCallibrationRaw (){
	WashInfoRawLeft.red_max = 113;
	WashInfoRawLeft.green_max = 168;
	WashInfoRawLeft.blue_max = 112;

	WashInfoRawLeft.red_min = 19;
	WashInfoRawLeft.green_min = 39;
	WashInfoRawLeft.blue_min = 31;

	WashInfoRawRight.red_max = 156;
	WashInfoRawRight.green_max = 164;
	WashInfoRawRight.blue_max = 110;

	WashInfoRawRight.red_min = 19;
	WashInfoRawRight.green_min = 41;
	WashInfoRawRight.blue_min = 32;
}

int global_frames_first;
int global_frames_second;
int global_frames_third;
