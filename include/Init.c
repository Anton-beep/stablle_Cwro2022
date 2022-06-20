#define TIMER 0
#define LOGGING 0
#define DEBUG 0

const float Kp_norm = 0.25;
const float Ki_norm = 0;
const float Kd_norm = 10;

const float Kp_tacho = 1;
const float Ki_tacho = 0.002;
const float Kd_tacho = 20;

const float Kp_tank = 0.3;
const float Ki_tank = 0.001;
const float Kd_tank = 15;

const float axleTrack = 178;
const float wheelDiameter = 80;
const float BetweenSensorsAndMiddle = 75.5;

const float left_min_sensor = 2316;
const float right_min_sensor = 2300;

const float left_max_sensor = 1724;
const float right_max_sensor = 1684;

const float max_speed_const = 80;
const float min_speed_const = 16;

const float acceleration = 0.04;

long left_room_indicator = -1;
long right_room_indicator = -1;

const float acceleration_turn = 0.04;

short firstCube_color = -1;
short secondCube_color = -1;

byte left_bottle  = 1;
byte right_bottle = 1;
byte now_cubes = 0;
long ht_results[2];

float integral_sum = 0;
float NOW_ANGLE = 45;
float pr_error = 0;
float pr_error_tacho = 0;
short framesColor[3] = {0, 0, 0};

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
	FamesRawRight.red_max = 25;
	FamesRawRight.green_max = 47;
	FamesRawRight.blue_max = 33;

	FamesRawRight.red_min = 17;
	FamesRawRight.green_min = 36;
	FamesRawRight.blue_min = 26;

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// N? N?N?N? ??N????i????N???N? ??????N?N?N????i??, ???i???i?????i??N??????i??N?N? ??????????N??? ??N??i?????? ???? N??i??N??????? N??i???????i??, ?i???i??N??i?????i???i?? N???N?N???
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void InitMarkerCallibrationRaw() {
	MarkerInfoRawLeft.red_max =   104;
	MarkerInfoRawLeft.green_max = 154;
	MarkerInfoRawLeft.blue_max =  100;

	MarkerInfoRawLeft.red_min =   20;
	MarkerInfoRawLeft.green_min = 39;
	MarkerInfoRawLeft.blue_min =  29;

	MarkerInfoRawRight.red_max =   119;
	MarkerInfoRawRight.green_max = 179;
	MarkerInfoRawRight.blue_max =  116;

	MarkerInfoRawRight.red_min =   17;
	MarkerInfoRawRight.green_min = 36;
	MarkerInfoRawRight.blue_min =  28;
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
