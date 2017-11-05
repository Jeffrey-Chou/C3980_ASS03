#ifndef GPS_UTILS_H
#define GPS_UTILS_H

#include <gps.h>
#include <errno.h>
#include "gpsprint.h"

int gps_search_sat(struct gps_data_t* gpsdata);
void cleanup(struct gps_data_t* gpsdata);

#endif
