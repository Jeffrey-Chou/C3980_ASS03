#include "gpsprint.h"

void PrintGpsData( struct gps_data_t* gpsdata)
{
    bool hasFix = false;
    bool* usedList = 0;

    FillSatUsedList(usedList, gpsdata);

    printf("Time:%f",gpsdata->fix.time);
    if(gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.latitude) == 0 && isnan(gpsdata->fix.longitude) == 0 )
    {
        printf(" Latitude: %f%c Longitude: %f%c\n", 
        gpsdata->fix.latitude, (gpsdata->fix.latitude < 0)? 'S': 'N',
        gpsdata->fix.longitude, (gpsdata->fix.longitude < 0)? 'W': 'E');
        hasFix = true;
    }
    else
    {
        printf("n/a n/a\n");
    }

    if(gpsdata->satellites_visible != 0)
    {
        for(int i = 0; i < MAX_POSSIBLE_SATS; ++i )
        {
            if(i < gpsdata->satellites_visible)
            {
                if(hasFix)
                {
                    if(usedList[i])
                    {
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

    if(usedList != 0)
    {
        free(usedList);
    }
    
}

void FillSatUsedList( bool* usedList, struct gps_data_t* gpsdata)
{
    usedList = malloc(sizeof(bool) * MAXCHANNELS);

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
    skyview->PRN,skyview->elevation, skyview->azimuth, skyview->ss, (used)? 'Y': 'N');

}


