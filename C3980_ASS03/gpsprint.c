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
    bool usedList[MAXCHANNELS];

    FillSatUsedList(usedList, gpsdata);
    time_t t = (time_t) gpsdata->fix.time;
    struct tm* time = localtime(&t);

    printf("\n%d-%d-%dT%d:%d:%d",time->tm_year + 1900, time->tm_mon, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec);
    if(gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.latitude) == 0 && isnan(gpsdata->fix.longitude) == 0 )
    {
        printf(" Latitude: %f%c Longitude: %f%c\n", 
        gpsdata->fix.latitude, (gpsdata->fix.latitude < 0)? 'S': 'N',
        gpsdata->fix.longitude, (gpsdata->fix.longitude < 0)? 'W': 'E');
        hasFix = true;
    }
    else
    {
        printf(" Latitude: n/a Longitude: n/a\n");
    }

    if(gpsdata->satellites_visible != 0)
    {
        for(int i = 0; i < MAX_POSSIBLE_SATS; ++i )
        {
            if(i < gpsdata->satellites_visible)
            {
                if(hasFix == true)
                {
                    printf("entered if with boolean %d\n", usedList[i]);
                    if(usedList[i] == true)
                    {
                        printf("")
                        PrintSatelliteDetails(&gpsdata->skyview[i], usedList[i]);
                    }
                }
                else
                {
                    PrintSatelliteDetails(&gpsdata->skyview[i], usedList[i]);
                }
            }
        }
    }

    
}

void FillSatUsedList( bool* usedList, struct gps_data_t* gpsdata)
{

    for(int i = 0; i < MAXCHANNELS; ++i)
    {
        usedList[i] = false;
        for(int j = 0; j < gpsdata->satellites_used; ++j)
        {
            if(gpsdata->skyview[j].used == gpsdata->skyview[i].PRN)
            {
                usedList[i] = true;
            }
        }
    }
}

void PrintSatelliteDetails(struct satellite_t* skyview, bool used)
{
    printf("PRN: %3d Elevation: %02d Azimuth: %03d SNR: %02f Used: %c\n",
    skyview->PRN, skyview->elevation, skyview->azimuth, skyview->ss, ((used == true)? 'Y': 'N'));

}


