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
--	The gpsprint code is responsible for printing out data from the gps_data structure
--  after if has been grabbed by the read function.
--
------------------------------------------------------------------------------*/

#include "gpsprint.h"


/*------------------------------------------------------------------------------
--	Function:		PrintGpsData
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
    bool hasFix = false;
    
    time_t t = (time_t) gpsdata->fix.time;
    struct tm* time = localtime(&t);

    printf("\n%d-%d-%dT%d:%d:%d",time->tm_year + 1900, time->tm_mon, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec);
    if(gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.latitude) == 0 && isnan(gpsdata->fix.longitude) == 0 )
    {
        printf(" Latitude: %f%c Longitude: %f%c\n\n", 
        fabs(gpsdata->fix.latitude), (gpsdata->fix.latitude < 0)? 'S': 'N',
        fabs(gpsdata->fix.longitude), (gpsdata->fix.longitude < 0)? 'W': 'E');
        hasFix = true;
    }
    else
    {
        printf(" Latitude: n/a Longitude: n/a\n\n");
    }

    if(gpsdata->satellites_visible != 0)
    {
        for(int i = 0; i < MAX_POSSIBLE_SATS; ++i )
        {
            if(i < gpsdata->satellites_visible)
            {
                if(hasFix == true)
                {
                    if(gpsdata->skyview[i].used)
                    {

                        PrintSatelliteDetails(&gpsdata->skyview[i]);
                    }
                }
                else
                {
                    PrintSatelliteDetails(&gpsdata->skyview[i]);
                }
            }
        }
    }

    gps_clear_fix(&gpsdata->fix);
     
}


/*------------------------------------------------------------------------------
--	Function:		PrintSatelliteDetails
--
--	Date:			Nov 2 2017
--
--	Designer:		Jeffrey Chou
--
--	Programmer:		Jeffrey Chou
--
--	Interface:		void PrintSatelliteDetails( struct satellite_t* skyview)
--						struct satellite_t* skyview: a pointer to the data structure
--
--	Returns:		void
--
--	Notes:
--	Prints out the data stored in the satellite_t structure, which is in the 
--  gps_data_t strucuture. This structure holds all of the data on satellites
--
------------------------------------------------------------------------------*/
void PrintSatelliteDetails(struct satellite_t* skyview)
{
    printf("PRN: %3d Elevation: %02d Azimuth: %03d SNR: %02d Used: %c\n",
    skyview->PRN, skyview->elevation, skyview->azimuth, (int)skyview->ss, ((skyview->used)? 'Y': 'N'));

}


