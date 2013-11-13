#include "stdafx.h"
#include "SimulatedSensorSource.h"

SensorValues SimulatedSensorSource::read()
{
	return SensorValues(5, 3, 1);
}