#ifndef GPSPRINT_H
#define GPSPRINT_H

#include <stdio.h>
#include <gps.h>
#include <math.h>

#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)
void PrintGpsData( struct gps_data_t* gpsdata);

#endif
