#ifndef GPSPRINT_H
#define GPSPRINT_H

#include <stdio.h>
#include <gps.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)

void PrintGpsData( struct gps_data_t* gpsdata);

void FillSatUsedList (bool* usedList, struct gps_data_t* gpsdata);

void PrintSatelliteDetails (struct satellite_t* skyview, bool used);

#endif
