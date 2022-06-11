#ifndef __HTEOPD_H__
#define __HTEOPD_H__

#pragma systemFile

#ifndef __COMMON_H__
#include "common.h"
#endif

// This ensures the correct sensor types are used.
#if defined(EV3)
TSensorTypes HTEOPDLRType = sensorLightActive;
TSensorTypes HTEOPDSRType = sensorLightInactive;
#endif

typedef struct
{
  tI2CData I2CData;
  short processed;
  long raw;
  bool shortRange;
} tHTEOPD, *tHTEOPDPtr;

bool initSensor(tHTEOPDPtr hteopdPtr, tSensors port);
bool readSensor(tHTEOPDPtr hteopdPtr);
bool configSensor(tHTEOPDPtr hteopdPtr);


/**
 * Initialise the sensor's data struct and port
 *
 * @param hteopdPtr pointer to the sensor's data struct
 * @param port the sensor port
 * @return true if no error occured, false if it did
 */

bool initSensor(tHTEOPDPtr hteopdPtr, tSensors port)
{
  memset(hteopdPtr, 0, sizeof(tHTEOPDPtr));
  hteopdPtr->I2CData.port = port;
  hteopdPtr->I2CData.type = HTEOPDLRType;
  hteopdPtr->shortRange = false;

  if (SensorType[hteopdPtr->I2CData.port] != hteopdPtr->I2CData.type)
    SensorType[hteopdPtr->I2CData.port] = hteopdPtr->I2CData.type;

  return true;
}

/**
 * Read all the sensor's data
 *
 * @param hteopdPtr pointer to the sensor's data struct
 * @return true if no error occured, false if it did
 */

bool readSensor(tHTEOPDPtr hteopdPtr)
{
    memset(hteopdPtr->I2CData.request, 0, sizeof(hteopdPtr->I2CData.request));
    hteopdPtr->raw = 4095 - SensorRaw[hteopdPtr->I2CData.port];
	  hteopdPtr->processed = round(sqrt((hteopdPtr->raw / 4) * 10));
    return true;
}


/**
 * Configure the sensor for either short or long range mode
 *
 * @param hteopdPtr pointer to the sensor's data struct
 * @return true if no error occured, false if it did
 */

bool configSensor(tHTEOPDPtr hteopdPtr)
{
    if (hteopdPtr->shortRange)
        SensorType[hteopdPtr->I2CData.port] = HTEOPDSRType;
    else
        SensorType[hteopdPtr->I2CData.port] = HTEOPDLRType;
	return true;
}

#endif // __HTEOPD_H__

/* @} */
/* @} */