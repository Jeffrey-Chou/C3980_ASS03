/*
 * dcgps.c
 *
 * Copyright 2017 root <root@datacomm>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include "dcgps.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	size_t size;
	static struct fixsource_t source;
	struct gps_data_t* gpsdata = (struct gps_data_t*)malloc(sizeof(struct gps_data_t));

	size = sizeof(LOCAL_HOST);
	source.server = malloc(size);
	memcpy(source.server, LOCAL_HOST, size);

	size = sizeof(DEFAULT_GPSD_PORT);
	source.port = malloc(size);
	memcpy(source.port, DEFAULT_GPSD_PORT, size);


	if(gps_open(source.server, source.port, gpsdata) == -1)
	{
		errno=19;
        perror("Could Not Connect to GPS");
        cleanup(gpsdata);
        return -1;
	}

	unsigned int flags = WATCH_ENABLE;


	if(source.device != NULL)
	{
		flags |= WATCH_DEVICE;
	}

	 if (gps_stream(gpsdata,flags,0) == -1)
    {
      fprintf(stderr,"Error streaming to GPS device \n");
      cleanup(gpsdata);
      return -1;
    }
	else
    {
      //Grab Read and print satellite data
      if(gps_search_sat(gpsdata) == -1)
      {
        perror("Terminated");
        cleanup(gpsdata);
        return 0;
      }
    }
}

