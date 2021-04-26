// main.c
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

/*
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all copyright and other intellectual property rights
  in them.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  If you use, modify or distribute this software then you do so at your own
  risk.  If you do not pass on this warning then you may be responsible for any
  problems encountered by those who obtain the software through you.
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "debug_printf.h"
#include "gps_uart.h"
#include "gps_protocol.h"


static const char *format_decimilliminutes(char *buffer, size_t buffer_size, int32_t decimilliminutes)
{
  unsigned int microdegrees = (((llabs(decimilliminutes) * 5) + 1) / 3);

  unsigned int degrees = (microdegrees / 1000000u);

  unsigned int remainder = (microdegrees - (degrees * 1000000u));

  snprintf(buffer, buffer_size, "%c%u.%06u", ((decimilliminutes < 0) ? '-' : '+'), degrees, remainder);

  return buffer;
}

static const char *format_millisecond_of_day(char *buffer, size_t buffer_size, uint32_t millisecond_of_day)
{
  unsigned int second_of_day = (millisecond_of_day / 1000u);

  unsigned int millisecond = (millisecond_of_day - (second_of_day * 1000));

  unsigned int minute_of_day = (second_of_day / 60);

  unsigned int second = (second_of_day - (minute_of_day * 60));

  unsigned int hour_of_day = (minute_of_day / 60);

  unsigned int minute = (minute_of_day - (hour_of_day * 60));

  if (hour_of_day > 99)
  {
    hour_of_day = 99;
  }

  if ((hour_of_day == 24) && (minute_of_day == 0) && (second_of_day == 0))
  {
    hour_of_day = 23;
    minute      = 59;
    second      = 60;
  }

  snprintf(buffer, buffer_size, "%02u:%02u:%02u.%03u", hour_of_day, minute, second, millisecond);

  return buffer;
}


int main(void)
{
  debug_uart_init();
  gps_uart_init();

  for (;;)
  {
    char * line = gps_uart_get_line();

    struct gps_message message;

    bool status = false;

    if (line)
    {
      status = gps_protocol_parse(line, &message);

      gps_uart_release_line();
    }

    if (status)
    {
      switch (message.type)
      {
        case GPS_GPGLL:
          (void)message.data.gpgll.data_valid;
          (void)message.data.gpgll.millisecond_of_day;
          (void)message.data.gpgll.latitude_decimilliminutes;
          (void)message.data.gpgll.longitude_decimilliminutes;

          debug_printf("GLL\n");
          break;

        case GPS_GPRMC:
          (void)message.data.gprmc.data_valid;
          (void)message.data.gprmc.millisecond_of_day;
          (void)message.data.gprmc.latitude_decimilliminutes;
          (void)message.data.gprmc.longitude_decimilliminutes;
          (void)message.data.gprmc.groundspeed_milliknots;
          (void)message.data.gprmc.date_days;
          (void)message.data.gprmc.magnetic_variation_millidegrees;

          if (message.data.gprmc.data_valid)
          {
            char time_of_day[16];
            char latitude[16];
            char longitude[16];

            debug_printf("RMC %s %s %s\n",
                         format_millisecond_of_day(time_of_day, sizeof time_of_day, message.data.gprmc.millisecond_of_day),
                         format_decimilliminutes(latitude, sizeof latitude, message.data.gprmc.latitude_decimilliminutes),
                         format_decimilliminutes(longitude, sizeof longitude, message.data.gprmc.longitude_decimilliminutes));
          }
          else
          {
            debug_printf("RMC no fix\n");
          }
          break;

        case GPS_GPVTG:
          (void)message.data.gpvtg.course_millidegrees_true;
          (void)message.data.gpvtg.course_millidegrees_magnetic;
          (void)message.data.gpvtg.groundspeed_milliknots;
          (void)message.data.gpvtg.groundspeed_metres_per_hour;

          debug_printf("VTG\n");
          break;

        case GPS_GPGGA:
          (void)message.data.gpgga.millisecond_of_day;
          (void)message.data.gpgga.latitude_decimilliminutes;
          (void)message.data.gpgga.longitude_decimilliminutes;
          (void)message.data.gpgga.fix;
          (void)message.data.gpgga.satellite_count;
          (void)message.data.gpgga.horizontal_dilution_milli;
          (void)message.data.gpgga.altitude_mm;
          (void)message.data.gpgga.geoid_separation_mm;
          (void)message.data.gpgga.diff_update_age_ms;
          (void)message.data.gpgga.diff_station_id;

          debug_printf("GGA\n");
          break;

        case GPS_GPGSA:
          (void)message.data.gpgsa.manual_mode;
          (void)message.data.gpgsa.dimensions;
          (void)message.data.gpgsa.satellite_id[ 0];
          (void)message.data.gpgsa.satellite_id[ 1];
          (void)message.data.gpgsa.satellite_id[ 2];
          (void)message.data.gpgsa.satellite_id[ 3];
          (void)message.data.gpgsa.satellite_id[ 4];
          (void)message.data.gpgsa.satellite_id[ 5];
          (void)message.data.gpgsa.satellite_id[ 6];
          (void)message.data.gpgsa.satellite_id[ 7];
          (void)message.data.gpgsa.satellite_id[ 8];
          (void)message.data.gpgsa.satellite_id[ 9];
          (void)message.data.gpgsa.satellite_id[10];
          (void)message.data.gpgsa.satellite_id[11];
          (void)message.data.gpgsa.position_dilution_milli;
          (void)message.data.gpgsa.horizontal_dilution_milli;
          (void)message.data.gpgsa.vertical_dilution_milli;

          debug_printf("GSA\n");
          break;

        case GPS_GPGSV:
          (void)message.data.gpgsv.message_count;
          (void)message.data.gpgsv.message_number;
          (void)message.data.gpgsv.satellite_count;
          (void)message.data.gpgsv.satellite_id      [0];
          (void)message.data.gpgsv.elevation_degrees [0];
          (void)message.data.gpgsv.azimuth_degrees   [0];
          (void)message.data.gpgsv.snr_dbhz          [0];
          (void)message.data.gpgsv.satellite_id      [1];
          (void)message.data.gpgsv.elevation_degrees [1];
          (void)message.data.gpgsv.azimuth_degrees   [1];
          (void)message.data.gpgsv.snr_dbhz          [1];
          (void)message.data.gpgsv.satellite_id      [2];
          (void)message.data.gpgsv.elevation_degrees [2];
          (void)message.data.gpgsv.azimuth_degrees   [2];
          (void)message.data.gpgsv.snr_dbhz          [2];
          (void)message.data.gpgsv.satellite_id      [3];
          (void)message.data.gpgsv.elevation_degrees [3];
          (void)message.data.gpgsv.azimuth_degrees   [3];
          (void)message.data.gpgsv.snr_dbhz          [3];

          debug_printf("GSV\n");
          break;
      }
    }
  }
}
