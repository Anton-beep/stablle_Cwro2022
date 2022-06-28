#define TIMER 0
#define LOGGING 1
#define DEBUG 0
#define CALIBRATE 0

const float Kp_norm = 0.3;
const float Ki_norm = 0.001;
const float Kd_norm = 17;

const float oneSensorCof = 1.75;

const float Kp_tacho = 4.2;
const float Ki_tacho = 0.001;
const float Kd_tacho = 18;

const float Kp_tank = 0.8;
const float Ki_tank = 0.001;
const float Kd_tank = 15;

const float axleTrack = 178;
const float wheelDiameter = 80;
const float BetweenSensorsAndMiddle = 75.5;

const float left_min_sensor =  2260;
const float right_min_sensor = 2272;

const float left_max_sensor = 1656;
const float right_max_sensor = 1684;

const float max_speed_const = 80;
const float min_speed_const = 15.5;

const float acceleration = 0.052;

long left_room_indicator = -1;
long right_room_indicator = -1;
long rawFrames[3] = {0, 0, 0};

short rgb[3] = {0, 0, 0};

int error_manip = 0;
short bibob = 0;

const float acceleration_turn = 0.04;

byte left_bottle  = 1;
byte right_bottle = 1;
byte now_cubes = 0;
float ht_results[2];

float integral_sum = 0;
float NOW_ANGLE = 45;
float pr_error = 0;
float pr_error_tacho = 0;

long framesColor[3] = {1000, 1000, 1000};
short cubes[2] = {-1, -1};

short rightRoomTables[2] = {4, 2};
short leftRoomTables[2] =  {3, 1};

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

Arraysensors results_sensors;

tHTCS2 colorRightSensor;
tHTCS2 colorLeftSensor;

CalibrationHiTechData FamesRawRight;

CalibrationHiTechData MarkerInfoRawLeft;
CalibrationHiTechData MarkerInfoRawRight;

CalibrationHiTechData WashInfoRawLeft;
CalibrationHiTechData WashInfoRawRight;

void InitCallibrationFamesInfoRaw() {
	FamesRawRight.red_max = 36;
	FamesRawRight.green_max = 36;
	FamesRawRight.blue_max = 36;

	FamesRawRight.red_min = 2;
	FamesRawRight.green_min = 4;
	FamesRawRight.blue_min = 5;
}

void InitMarkerCallibrationRaw() {
	MarkerInfoRawLeft.red_max =   38;
	MarkerInfoRawLeft.green_max = 36;
	MarkerInfoRawLeft.blue_max =  35;

	MarkerInfoRawLeft.red_min =   1;
	MarkerInfoRawLeft.green_min = 1;
	MarkerInfoRawLeft.blue_min =  1;

	MarkerInfoRawRight.red_max =   40;
	MarkerInfoRawRight.green_max = 38;
	MarkerInfoRawRight.blue_max =  38;

	MarkerInfoRawRight.red_min =   0;
	MarkerInfoRawRight.green_min = 1;
	MarkerInfoRawRight.blue_min =  1;
}

void InitWashCallibrationRaw (){
	WashInfoRawLeft.red_max =   95;
	WashInfoRawLeft.green_max = 90;
	WashInfoRawLeft.blue_max =  79;

	WashInfoRawLeft.red_min =   0;
	WashInfoRawLeft.green_min = 1;
	WashInfoRawLeft.blue_min =  2;

	WashInfoRawRight.red_max =   115;
	WashInfoRawRight.green_max = 109;
	WashInfoRawRight.blue_max =  92;

	WashInfoRawRight.red_min =   2;
	WashInfoRawRight.green_min = 2;
	WashInfoRawRight.blue_min =  1;
}
