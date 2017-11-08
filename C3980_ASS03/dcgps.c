/*------------------------------------------------------------------------------
--	Source File:	dcgps.c
--
--	Program:        Wireless GPS Program
--
--	Functions:
--					int main (void)
--
--	Date:			Nov 2 2017
--
--	Designer:		Jeffrey Chou
--
--	Programmer:		Jeffrey Chou
--
--	Notes:
--	The program is a location finding application that uses the gpsd utility 
--  along with assocaited C service library.
--
--	The dcgps code is responsible for running the program, initializing variables, and
--	freeing them when the program terminates.
--
------------------------------------------------------------------------------*/

#include "dcgps.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


/*------------------------------------------------------------------------------
--	Function:		main
--
--	Date:			Nov 2 2017
--
--	Designer:		Jeffrey Chou
--
--	Programmer:		Jeffrey Chou
--
--	Interface:		int main (void)
--
--	Returns:		if program runs successfully, return 0
--					else return another integer
--
--	Notes:
--	Runs the program
--
------------------------------------------------------------------------------*/
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

