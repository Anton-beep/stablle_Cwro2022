#define TIMER 0
#define LOGGING 0
#define DEBUG 1

const float Kp_norm = 0.25;
const float Ki_norm = 0;
const float Kd_norm = 9;

const float Kp_tacho = 1;
const float Ki_tacho = 0.002;
const float Kd_tacho = 20;

const float Kp_tank = 0.6;
const float Ki_tank = 0.001;
const float Kd_tank = 15;

const float axleTrack = 178;
const float wheelDiameter = 80;
const float BetweenSensorsAndMiddle = 75.5;

const float left_min_sensor = 2532;
const float right_min_sensor = 2476;

const float left_max_sensor = 1788;
const float right_max_sensor = 1732;

const float max_speed_const = 80;
const float min_speed_const = 16;

const float acceleration = 0.04;

long left_room_indicator = -1;
long right_room_indicator = -1;

const float acceleration_turn = 0.04;

byte left_bottle  = 1;
byte right_bottle = 1;
byte now_cubes = 0;
long ht_results[2];

float integral_sum = 0;
float NOW_ANGLE = 45;
float pr_error = 0;
float pr_error_tacho = 0;

short framesColor[3] = {1000, 1000, 1000};
short cubes[2] = {-1, -1};

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

Arraysensors results_sensors;

tHTCS2 colorRightSensor;
tHTCS2 colorLeftSensor;

CalibrationHiTechData FamesRawRight;

CalibrationHiTechData MarkerInfoRawLeft;
CalibrationHiTechData MarkerInfoRawRight;

CalibrationHiTechData WashInfoRawLeft;
CalibrationHiTechData WashInfoRawRight;

void InitCallibrationFamesInfoRaw() {
	FamesRawRight.red_max = 70;
	FamesRawRight.green_max = 100;
	FamesRawRight.blue_max = 50;

	FamesRawRight.red_min = 22;
	FamesRawRight.green_min = 42;
	FamesRawRight.blue_min = 31;
}

void InitMarkerCallibrationRaw() {
	MarkerInfoRawLeft.red_max =   108;
	MarkerInfoRawLeft.green_max = 161;
	MarkerInfoRawLeft.blue_max =  104;

	MarkerInfoRawLeft.red_min =   19;
	MarkerInfoRawLeft.green_min = 39;
	MarkerInfoRawLeft.blue_min =  28;

	MarkerInfoRawRight.red_max =   146;
	MarkerInfoRawRight.green_max = 215;
	MarkerInfoRawRight.blue_max =  132;

	MarkerInfoRawRight.red_min =   15;
	MarkerInfoRawRight.green_min = 33;
	MarkerInfoRawRight.blue_min =  24;
}

void InitWashCallibrationRaw (){
	WashInfoRawLeft.red_max =   168;
	WashInfoRawLeft.green_max = 249;
	WashInfoRawLeft.blue_max =  155;

	WashInfoRawLeft.red_min =   16;
	WashInfoRawLeft.green_min = 38;
	WashInfoRawLeft.blue_min =  30;

	WashInfoRawRight.red_max =   144;
	WashInfoRawRight.green_max = 213;
	WashInfoRawRight.blue_max =  129;

	WashInfoRawRight.red_min =   17;
	WashInfoRawRight.green_min = 36;
	WashInfoRawRight.blue_min =  23;
}
