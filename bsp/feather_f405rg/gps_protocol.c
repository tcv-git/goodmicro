// gps_protocol.c
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

#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "debug_printf.h"
#include "gps_protocol.h"

#define FIELD_COUNT_MAX  32u


static void gps_parse_gpgll(char **fields);
static void gps_parse_gprmc(char **fields);
static void gps_parse_gpvtg(char **fields);
static void gps_parse_gpgga(char **fields);
static void gps_parse_gpgsa(char **fields);
static void gps_parse_gpgsv(char **fields);


void gps_protocol_parse(char *line)
{{{
  size_t length = strlen(line);

  while ((length > 0) && isspace(line[length - 1]))
  {
    length--;
  }

  if ((length < 4) || (line[0] != '$') || (line[length - 3] != '*'))
  {
    debug_printf("invalid format\n");
    return;
  }

  uint8_t checksum = 0;
  unsigned int i;

  for (i = 1; i < (length - 3); i++)
  {
    checksum ^= (uint8_t)line[i];
  }

  if ((toupper(line[length - 2]) != "0123456789ABCDEF"[checksum >> 4])
   || (toupper(line[length - 1]) != "0123456789ABCDEF"[checksum & 0xF]))
  {
    debug_printf("invalid checksum\n");
    return;
  }

  line[length - 3] = '\0';

  char *next = &line[1];

  char        *fields[FIELD_COUNT_MAX + 1];
  unsigned int field_count;

  for (field_count = 0; field_count < FIELD_COUNT_MAX; field_count++)
  {
    fields[field_count] = next;

    char *end = strchr(next, ',');

    if (end)
    {
      end[0] = '\0';
      next = &end[1];
    }
    else
    {
      break;
    }
  }

  if (field_count == FIELD_COUNT_MAX)
  {
    debug_printf("too many fields\n");
    return;
  }

  field_count++;

  fields[field_count] = NULL;

  if      (!strcasecmp(fields[0], "GPGLL") && (field_count ==  7)){  gps_parse_gpgll(fields);  }
  else if (!strcasecmp(fields[0], "GPRMC") && (field_count == 13)){  gps_parse_gprmc(fields);  }
  else if (!strcasecmp(fields[0], "GPVTG") && (field_count ==  9)){  gps_parse_gpvtg(fields);  }
  else if (!strcasecmp(fields[0], "GPGGA") && (field_count == 15)){  gps_parse_gpgga(fields);  }
  else if (!strcasecmp(fields[0], "GPGSA") && (field_count == 18)){  gps_parse_gpgsa(fields);  }
  else if (!strcasecmp(fields[0], "GPGSV") && (field_count == 20)){  gps_parse_gpgsv(fields);  }
  else
  {
    debug_printf("unknown type '%s'[%u]\n", fields[0], field_count);
    return;
  }
}}}

static bool parse_latitude(const char *string_latitude, const char *string_latitude_dir, int32_t *p_latitude_decimilliminutes)
{{{
  while (isspace(*string_latitude))
  {
    string_latitude++;
  }

  if ((string_latitude[0] < '0') || (string_latitude[0] > '9')
   || (string_latitude[1] < '0') || (string_latitude[1] > '9')
   || (string_latitude[2] < '0') || (string_latitude[2] > '9')
   || (string_latitude[3] < '0') || (string_latitude[3] > '9')
   || (string_latitude[4] != '.')
   || (string_latitude[5] < '0') || (string_latitude[5] > '9'))
  {
    //debug_printf("invalid latitude\n");
    return false;
  }

  int32_t decimilliminutes = 0;

  decimilliminutes += ((string_latitude[0] - '0') * 10 * 60 * 10000);
  decimilliminutes += ((string_latitude[1] - '0')      * 60 * 10000);
  decimilliminutes += ((string_latitude[2] - '0')      * 10 * 10000);
  decimilliminutes += ((string_latitude[3] - '0')           * 10000);
  decimilliminutes += ((string_latitude[5] - '0')            * 1000);

  if ((string_latitude[6] >= '0') && (string_latitude[6] <= '9'))
  {
    decimilliminutes += ((string_latitude[6] - '0') * 100);

    if ((string_latitude[7] >= '0') && (string_latitude[7] <= '9'))
    {
      decimilliminutes += ((string_latitude[7] - '0') * 10);

      if ((string_latitude[8] >= '0') && (string_latitude[8] <= '9'))
      {
        decimilliminutes += (string_latitude[8] - '0');
      }
    }
  }

  if (!strcasecmp(string_latitude_dir, "N"))
  {
    *p_latitude_decimilliminutes = decimilliminutes;
    return true;
  }
  else if (!strcasecmp(string_latitude_dir, "S"))
  {
    *p_latitude_decimilliminutes = -decimilliminutes;
    return true;
  }
  else
  {
    //debug_printf("invalid latitude direction\n");
    return false;
  }
}}}

static bool parse_longitude(const char *string_longitude, const char *string_longitude_dir, int32_t *p_longitude_decimilliminutes)
{{{
  while (isspace(*string_longitude))
  {
    string_longitude++;
  }

  if ((string_longitude[0] < '0') || (string_longitude[0] > '9')
   || (string_longitude[1] < '0') || (string_longitude[1] > '9')
   || (string_longitude[2] < '0') || (string_longitude[2] > '9')
   || (string_longitude[3] < '0') || (string_longitude[3] > '9')
   || (string_longitude[4] < '0') || (string_longitude[4] > '9')
   || (string_longitude[5] != '.')
   || (string_longitude[6] < '0') || (string_longitude[6] > '9'))
  {
    //debug_printf("invalid longitude\n");
    return false;
  }

  int32_t decimilliminutes = 0;

  decimilliminutes += ((string_longitude[0] - '0') * 100 * 60 * 10000);
  decimilliminutes += ((string_longitude[1] - '0') *  10 * 60 * 10000);
  decimilliminutes += ((string_longitude[2] - '0')       * 60 * 10000);
  decimilliminutes += ((string_longitude[3] - '0')       * 10 * 10000);
  decimilliminutes += ((string_longitude[4] - '0')            * 10000);
  decimilliminutes += ((string_longitude[6] - '0')             * 1000);

  if ((string_longitude[7] >= '0') && (string_longitude[7] <= '9'))
  {
    decimilliminutes += ((string_longitude[7] - '0') * 100);

    if ((string_longitude[8] >= '0') && (string_longitude[8] <= '9'))
    {
      decimilliminutes += ((string_longitude[8] - '0') * 10);

      if ((string_longitude[9] >= '0') && (string_longitude[9] <= '9'))
      {
        decimilliminutes += (string_longitude[9] - '0');
      }
    }
  }

  if (!strcasecmp(string_longitude_dir, "E"))
  {
    *p_longitude_decimilliminutes = decimilliminutes;
    return true;
  }
  else if (!strcasecmp(string_longitude_dir, "W"))
  {
    *p_longitude_decimilliminutes = -decimilliminutes;
    return true;
  }
  else
  {
    //debug_printf("invalid longitude direction\n");
    return false;
  }
}}}

static bool parse_time(char *string_time, uint32_t *p_millisecond_of_day)
{{{
  while (isspace(*string_time))
  {
    string_time++;
  }

  if ((string_time[0] < '0') || (string_time[0] > '9')
   || (string_time[1] < '0') || (string_time[1] > '9')
   || (string_time[2] < '0') || (string_time[2] > '9')
   || (string_time[3] < '0') || (string_time[3] > '9')
   || (string_time[4] < '0') || (string_time[4] > '9')
   || (string_time[5] < '0') || (string_time[5] > '9'))
  {
    //debug_printf("invalid time\n");
    return false;
  }

  int32_t millisecond_of_day = 0;

  millisecond_of_day += ((string_time[0] - '0') * 10 * 60 * 60 * 1000);
  millisecond_of_day += ((string_time[1] - '0')      * 60 * 60 * 1000);
  millisecond_of_day += ((string_time[2] - '0')      * 10 * 60 * 1000);
  millisecond_of_day += ((string_time[3] - '0')           * 60 * 1000);
  millisecond_of_day += ((string_time[4] - '0')           * 10 * 1000);
  millisecond_of_day += ((string_time[5] - '0')                * 1000);

  if ((string_time[6] == '.') && (string_time[7] >= '0') && (string_time[7] <= '9'))
  {
    millisecond_of_day += ((string_time[7] - '0') * 100);

    if ((string_time[8] >= '0') && (string_time[8] <= '9'))
    {
      millisecond_of_day += ((string_time[8] - '0') * 10);

      if ((string_time[9] >= '0') && (string_time[9] <= '9'))
      {
        millisecond_of_day += (string_time[9] - '0');
      }
    }
  }

  *p_millisecond_of_day = millisecond_of_day;
  return true;
}}}


static void gps_parse_gpgll(char ** fields)
{{{
  char *string_latitude      = fields[1];
  char *string_latitude_dir  = fields[2];
  char *string_longitude     = fields[3];
  char *string_longitude_dir = fields[4];
  char *string_time          = fields[5];
  char *string_valid         = fields[6];

  int32_t  latitude_decimilliminutes;
  int32_t  longitude_decimilliminutes;
  uint32_t millisecond_of_day;

  bool status = !strcasecmp(string_valid, "A");

  if (status)
  {
    status = parse_latitude(string_latitude, string_latitude_dir, &latitude_decimilliminutes);
  }

  if (status)
  {
    status = parse_longitude(string_longitude, string_longitude_dir, &longitude_decimilliminutes);
  }

  if (status)
  {
    status = parse_time(string_time, &millisecond_of_day);
  }

  if (status)
  {
    debug_printf("GLL %i %i %u\n", (int)latitude_decimilliminutes, (int)longitude_decimilliminutes, (unsigned int)millisecond_of_day);
  }
}}}

static void gps_parse_gprmc(char ** fields)
{{{
  char *string_time          = fields[ 1];
  char *string_valid         = fields[ 2];
  char *string_latitude      = fields[ 3];    // WANT
  char *string_latitude_dir  = fields[ 4];    // WANT
  char *string_longitude     = fields[ 5];    // WANT
  char *string_longitude_dir = fields[ 6];    // WANT
  char *string_ground_speed  = fields[ 7];    // WANT
  char *string_bearing       = fields[ 8];
  char *string_date          = fields[ 9];
  char *string_variation     = fields[10];
  char *string_variation_dir = fields[11];
  char *string_mode          = fields[12]; // optional

  int32_t  latitude_decimilliminutes;
  int32_t  longitude_decimilliminutes;
  uint32_t millisecond_of_day;

  bool status = !strcasecmp(string_valid, "A");

  if (status)
  {
    status = parse_latitude(string_latitude, string_latitude_dir, &latitude_decimilliminutes);
  }

  if (status)
  {
    status = parse_longitude(string_longitude, string_longitude_dir, &longitude_decimilliminutes);
  }

  if (status)
  {
    status = parse_time(string_time, &millisecond_of_day);
  }

  if (status)
  {
    debug_printf("RMC %i %i %u\n", (int)latitude_decimilliminutes, (int)longitude_decimilliminutes, (unsigned int)millisecond_of_day);
  }

  (void)string_ground_speed;
  (void)string_bearing;
  (void)string_date;
  (void)string_variation;
  (void)string_variation_dir;
  (void)string_mode;
}}}

static void gps_parse_gpvtg(char ** fields)
{{{
  char *string_bearing_true            = fields[1];
  char *string_bearing_true_true       = fields[2];
  char *string_bearing_mag             = fields[3];
  char *string_bearing_mag_mag         = fields[4];
  char *string_ground_speed_knots      = fields[5];
  char *string_ground_speed_knots_unit = fields[6];
  char *string_ground_speed_kph        = fields[7];
  char *string_ground_speed_kph_unit   = fields[8];
  char *string_mode                    = fields[12]; // optional

  (void)string_bearing_true;
  (void)string_bearing_true_true;
  (void)string_bearing_mag;
  (void)string_bearing_mag_mag;
  (void)string_ground_speed_knots;
  (void)string_ground_speed_knots_unit;
  (void)string_ground_speed_kph;
  (void)string_ground_speed_kph_unit;
  (void)string_mode;
}}}

static void gps_parse_gpgga(char ** fields)
{{{
  char *string_time                  = fields[ 1];
  char *string_latitude              = fields[ 2];
  char *string_latitude_dir          = fields[ 3];
  char *string_longitude             = fields[ 4];
  char *string_longitude_dir         = fields[ 5];
  char *string_fix_type              = fields[ 6];
  char *string_satellite_count       = fields[ 7];
  char *string_horizontal_dilution   = fields[ 8];
  char *string_altitude              = fields[ 9];
  char *string_altitude_unit         = fields[10];
  char *string_geoid_separation      = fields[11];
  char *string_geoid_separation_unit = fields[12];
  char *string_time_since_reference  = fields[13];
  char *string_reference_station_id  = fields[14];

  (void)string_time;
  (void)string_latitude;
  (void)string_latitude_dir;
  (void)string_longitude;
  (void)string_longitude_dir;
  (void)string_fix_type;
  (void)string_satellite_count;
  (void)string_horizontal_dilution;
  (void)string_altitude;                // WANT
  (void)string_altitude_unit;           // WANT
  (void)string_geoid_separation;
  (void)string_geoid_separation_unit;
  (void)string_time_since_reference;
  (void)string_reference_station_id;
}}}

static void gps_parse_gpgsa(char ** fields)
{{{
  char *string_mode_manual_auto    = fields[ 1];
  char *string_mode_fix            = fields[ 2];
  char *string_satellite_id0       = fields[ 3];
  char *string_satellite_id1       = fields[ 4];
  char *string_satellite_id2       = fields[ 5];
  char *string_satellite_id3       = fields[ 6];
  char *string_satellite_id4       = fields[ 7];
  char *string_satellite_id5       = fields[ 8];
  char *string_satellite_id6       = fields[ 9];
  char *string_satellite_id7       = fields[10];
  char *string_satellite_id8       = fields[11];
  char *string_satellite_id9       = fields[12];
  char *string_satellite_id10      = fields[13];
  char *string_satellite_id11      = fields[14];
  char *string_position_dilution   = fields[15];
  char *string_horizontal_dilution = fields[16];
  char *string_vertical_dilution   = fields[17];

  (void)string_mode_manual_auto;
  (void)string_mode_fix;
  (void)string_satellite_id0;
  (void)string_satellite_id1;
  (void)string_satellite_id2;
  (void)string_satellite_id3;
  (void)string_satellite_id4;
  (void)string_satellite_id5;
  (void)string_satellite_id6;
  (void)string_satellite_id7;
  (void)string_satellite_id8;
  (void)string_satellite_id9;
  (void)string_satellite_id10;
  (void)string_satellite_id11;
  (void)string_position_dilution;   // WANT
  (void)string_horizontal_dilution; // WANT
  (void)string_vertical_dilution;   // WANT
}}}

static void gps_parse_gpgsv(char ** fields)
{{{
  char *string_message_count        = fields[ 1];
  char *string_message_number       = fields[ 2];
  char *string_satellite_count      = fields[ 3];
  char *string_satellite0_number    = fields[ 4];
  char *string_satellite0_elevation = fields[ 5];
  char *string_satellite0_azimith   = fields[ 6];
  char *string_satellite0_snr       = fields[ 7];
  char *string_satellite1_number    = fields[ 8];
  char *string_satellite1_elevation = fields[ 9];
  char *string_satellite1_azimith   = fields[10];
  char *string_satellite1_snr       = fields[11];
  char *string_satellite2_number    = fields[12];
  char *string_satellite2_elevation = fields[13];
  char *string_satellite2_azimith   = fields[14];
  char *string_satellite2_snr       = fields[15];
  char *string_satellite3_number    = fields[16];
  char *string_satellite3_elevation = fields[17];
  char *string_satellite3_azimith   = fields[18];
  char *string_satellite3_snr       = fields[19];

  (void)string_message_count;
  (void)string_message_number;
  (void)string_satellite_count;
  (void)string_satellite0_number;
  (void)string_satellite0_elevation;
  (void)string_satellite0_azimith;
  (void)string_satellite0_snr;
  (void)string_satellite1_number;
  (void)string_satellite1_elevation;
  (void)string_satellite1_azimith;
  (void)string_satellite1_snr;
  (void)string_satellite2_number;
  (void)string_satellite2_elevation;
  (void)string_satellite2_azimith;
  (void)string_satellite2_snr;
  (void)string_satellite3_number;
  (void)string_satellite3_elevation;
  (void)string_satellite3_azimith;
  (void)string_satellite3_snr;
}}}
