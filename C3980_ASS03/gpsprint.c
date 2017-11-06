/*------------------------------------------------------------------------------
--	Source File:	gpsprint.c
--
--	Program:        Wireless GPS Program
--
--	Functions:
--					void PrintGpsData (struct gps_data_t* gpsdata)
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
--	This code is responsible for printing out data from the gps_data structure
--  after if has been grabbed by the read function.
--
------------------------------------------------------------------------------*/

#include "gpsprint.h"


/*------------------------------------------------------------------------------
--	Function:		InitWindow
--
--	Date:			Nov 2 2017
--
--	Designer:		Jeffrey Chou
--
--	Programmer:		Jeffrey Chou
--
--	Interface:		void PrintGpsData( struct gps_data_t* gpsdata)
--						struct gps_data_t* gpsdata: a pointer to the data structure
--
--	Returns:		void
--
--	Notes:
--	Prints out the data stored in the gps_data_t strucuture.
--
------------------------------------------------------------------------------*/
void PrintGpsData( struct gps_data_t* gpsdata)
{
    printf("Time:%f",gpsdata->fix.time);
    if(gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.latitude) == 0)
    {
        printf(" Latitude: %f%c", gpsdata->fix.latitude, (gpsdata->fix.latitude < 0)? 'S': 'N');
    }
    else
    {
        printf("n/a ");
    }

    if(gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.longitude) == 0)
    {
        printf(" Longitude: %f%c\n", gpsdata->fix.longitude, (gpsdata->fix.longitude < 0)? 'W': 'E');
    }
    else
    {
        printf("n/a\n");
    }
    
    if(gpsdata->satellites_visible != 0)
    {
        for(int i = 0; i < MAX_POSSIBLE_SATS; ++i )
        {
            if(i < gpsdata->satellites_visible)
            {
                printf("PRN: %3d Elevation: %02d Azimuth: %03d SNR: %02f\n",
                gpsdata->skyview[i].PRN,gpsdata->skyview[i].elevation, gpsdata->skyview[i].azimuth, gpsdata->skyview[i].ss);
            }
        }
    }
    
}


