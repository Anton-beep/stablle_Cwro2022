void SensorsToPercent()
{
	results_sensors.firstSensor = (float)(SensorRaw[leftSensor] - left_min_sensor) /    (left_max_sensor - left_min_sensor) * 100;
	results_sensors.secondSensor = (float)(SensorRaw[rightSensor] - right_min_sensor) / (right_max_sensor - right_min_sensor) * 100;

	if (results_sensors.firstSensor > 100)
		results_sensors.firstSensor = 100;

	if (results_sensors.secondSensor > 100)
		results_sensors.secondSensor = 100;

	if (results_sensors.secondSensor < -100)
		results_sensors.secondSensor = -100;

	if (results_sensors.firstSensor < -100)
		results_sensors.firstSensor = -100;
}
