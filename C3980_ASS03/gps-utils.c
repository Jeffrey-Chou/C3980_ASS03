/*------------------------------------------------------------------------------
--	Source File:	gps-utils.c
--
--	Program:        Wireless GPS Program
--
--	Functions:
--					int gps_search_sat (struct gps_data_t* gpsdata)
--
--	Date:			Nov 2 2017
--
--	Designer:		  Alfred Swinton
--
--	Programmer:		Alfred Swinton
--
--	Notes:
--	The program is a location finding application that uses the gpsd utility 
--  along with assocaited C service library.
--
--	The gps-utils code grabs data from the gpsd daemon and sends the data 
--  to a print function
--
------------------------------------------------------------------------------*/

#include "gps-utils.h"
#include <stdlib.h>


/*------------------------------------------------------------------------------
--	Function:		gps_search_sat
--
--	Date:			Nov 2 2017
--
--	Designer:		  Alfred Swinton
--
--	Programmer:		Alfred Swinton
--
--	Interface:		int gps_search_sat(struct gps_data_t* gpsdata)
--						struct gps_data_t* gpsdata: a pointer to the data structure
--
--	Returns:		-1 on exit
--
--	Notes:
--	Waits for the gpsd daemon to have data and stores it in the gps_data_t 
--  struture when it does. Sends the structure to the print function once 
--  the data is grabbed.
--
------------------------------------------------------------------------------*/
int gps_search_sat(struct gps_data_t* gpsdata) 
{
  int timeouts = 0;
  
  while (true) 
  {
    //Wait for new gps signals, fail on ten consecutive timeouts
    if (!gps_waiting(gpsdata, 3000000)) 
    {
      fprintf(stderr,"GPS timeout \n");
      ++timeouts;
      if (timeouts >= 3)
      {
      errno = 16;
      return -1;
      }

    } 
    else 
    {
      //Read info from gps signals
      timeouts = 0;

      if (gps_read(gpsdata) == -1) 
      {
        fprintf(stderr,"Error Reading Device Failed \n");
        errno = 5;
        return -1;
      } 
      else 
      {
        if(gpsdata->fix.mode > 0)
        PrintGpsData(gpsdata);
      }
    }
  }
}

/*------------------------------------------------------------------------------
--	Function:		cleanup
--
--	Date:			Nov 2 2017
--
--	Designer:		  Alfred Swinton
--
--	Programmer:		Alfred Swinton
--
--	Interface:		void cleanup(struct gps_data_t* gpsdata)
--						struct gps_data_t* gpsdata: a pointer to the data structure
--
--	Returns:		void
--
--	Notes:
--	Closes the connection to the gpsd daemon and frees the memory used for the
--  data structure.
--
------------------------------------------------------------------------------*/
void cleanup(struct gps_data_t* gpsdata) 
{
  gps_stream(gpsdata,WATCH_DISABLE,NULL);
  gps_close(gpsdata);
  free(gpsdata);
}
