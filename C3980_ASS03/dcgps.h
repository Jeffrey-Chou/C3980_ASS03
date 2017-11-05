#ifndef DCGPS_H
#define DCGPS_H

#include <gps.h>
#include <stdio.h>
#include <stdlib.h>

#include "gps-utils.h"

#define LOCAL_HOST "127.0.0.1"

struct fixsource_t
{
	char* spec;
	char* server;
	char* port;
	char* device;
};

#endif
