#include "gps-utils.h"
#include <stdlib.h>

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

void cleanup(struct gps_data_t* gpsdata) 
{
  gps_stream(gpsdata,WATCH_DISABLE,NULL);
  gps_close(gpsdata);
  free(gpsdata);
}
