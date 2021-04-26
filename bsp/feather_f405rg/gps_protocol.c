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

#define FIELD_COUNT_MAX  20u

static bool parse_fix(const char *str, enum gps_fix *p_fix)
{{{
  if (!strcmp(str, "0")) { *p_fix = GPS_FIX_NONE; return true;  }
  if (!strcmp(str, "1")) { *p_fix = GPS_FIX_GPS;  return true;  }
  if (!strcmp(str, "2")) { *p_fix = GPS_FIX_DGPS; return true;  }

  debug_printf("gps_protocol invalid fix mode\n");
  return false;
}}}

static bool parse_dims(const char *str, enum gps_dims *p_dimensions)
{{{
  if (!strcmp(str, "1")) { *p_dimensions = GPS_DIMS_NONE; return true;  }
  if (!strcmp(str, "2")) { *p_dimensions = GPS_DIMS_2D;   return true;  }
  if (!strcmp(str, "3")) { *p_dimensions = GPS_DIMS_3D;   return true;  }

  debug_printf("gps_protocol invalid fix type\n");
  return false;
}}}

static bool parse_mode(const char *str, enum gps_mode *p_mode)
{{{
  if (!strcmp(str, "A")) { *p_mode = GPS_MODE_AUTO; return true;  }
  if (!strcmp(str, "D")) { *p_mode = GPS_MODE_DIFF; return true;  }
  if (!strcmp(str, "E")) { *p_mode = GPS_MODE_EST;  return true;  }

  debug_printf("gps_protocol invalid operating mode\n");
  return false;
}}}

static bool parse_valid(const char *str, bool *p_valid)
{{{
  if (!strcasecmp(str, "A")) { *p_valid = true;  return true;  }
  if (!strcasecmp(str, "V")) { *p_valid = false; return true;  }

  debug_printf("gps_protocol invalid data valid field\n");
  return false;
}}}

static bool parse_manual(const char *str, bool *p_manual)
{{{
  if (!strcasecmp(str, "M")) { *p_manual = true;  return true;  }
  if (!strcasecmp(str, "A")) { *p_manual = false; return true;  }

  debug_printf("gps_protocol invalid manual mode field\n");
  return false;
}}}

static bool parse_time(char *string_time, uint32_t *p_millisecond_of_day)
{{{
  if ((string_time[0] < '0') || (string_time[0] > '9')
   || (string_time[1] < '0') || (string_time[1] > '9')
   || (string_time[2] < '0') || (string_time[2] > '9')
   || (string_time[3] < '0') || (string_time[3] > '9')
   || (string_time[4] < '0') || (string_time[4] > '9')
   || (string_time[5] < '0') || (string_time[5] > '9'))
  {
    debug_printf("gps_protocol invalid time\n");
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

static bool parse_latitude(const char *string_latitude, const char *string_latitude_dir, int32_t *p_latitude_decimilliminutes)
{{{
  if ((string_latitude[0] < '0') || (string_latitude[0] > '9')
   || (string_latitude[1] < '0') || (string_latitude[1] > '9')
   || (string_latitude[2] < '0') || (string_latitude[2] > '9')
   || (string_latitude[3] < '0') || (string_latitude[3] > '9')
   || (string_latitude[4] != '.')
   || (string_latitude[5] < '0') || (string_latitude[5] > '9'))
  {
    debug_printf("gps_protocol invalid latitude\n");
    return false;
  }

  int32_t decimilliminutes = 0;

  decimilliminutes += ((string_latitude[0] - '0') * 10 * 60 * 10000);
  decimilliminutes += ((string_latitude[1] - '0')      * 60 * 10000);
  decimilliminutes += ((string_latitude[2] - '0')      * 10 * 10000);
  decimilliminutes += ((string_latitude[3] - '0')           * 10000);
  decimilliminutes += ((string_latitude[5] - '0')           *  1000);

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
    debug_printf("gps_protocol invalid latitude direction\n");
    return false;
  }
}}}

static bool parse_longitude(const char *string_longitude, const char *string_longitude_dir, int32_t *p_longitude_decimilliminutes)
{{{
  if ((string_longitude[0] < '0') || (string_longitude[0] > '9')
   || (string_longitude[1] < '0') || (string_longitude[1] > '9')
   || (string_longitude[2] < '0') || (string_longitude[2] > '9')
   || (string_longitude[3] < '0') || (string_longitude[3] > '9')
   || (string_longitude[4] < '0') || (string_longitude[4] > '9')
   || (string_longitude[5] != '.')
   || (string_longitude[6] < '0') || (string_longitude[6] > '9'))
  {
    debug_printf("gps_protocol invalid longitude\n");
    return false;
  }

  int32_t decimilliminutes = 0;

  decimilliminutes += ((string_longitude[0] - '0') * 100 * 60 * 10000);
  decimilliminutes += ((string_longitude[1] - '0') *  10 * 60 * 10000);
  decimilliminutes += ((string_longitude[2] - '0')       * 60 * 10000);
  decimilliminutes += ((string_longitude[3] - '0')       * 10 * 10000);
  decimilliminutes += ((string_longitude[4] - '0')            * 10000);
  decimilliminutes += ((string_longitude[6] - '0')            *  1000);

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
    debug_printf("gps_protocol invalid longitude direction\n");
    return false;
  }
}}}

static bool parse_gpgll(char **fields, struct gps_gpgll *gpgll)
{{{
  char *string_latitude      = fields[1];
  char *string_latitude_dir  = fields[2];
  char *string_longitude     = fields[3];
  char *string_longitude_dir = fields[4];
  char *string_time          = fields[5];
  char *string_valid         = fields[6];

  bool status = parse_valid(string_valid, &gpgll->data_valid)
             && parse_time(string_time, &gpgll->millisecond_of_day)
             && parse_latitude(string_latitude, string_latitude_dir, &gpgll->latitude_decimilliminutes)
             && parse_longitude(string_longitude, string_longitude_dir, &gpgll->longitude_decimilliminutes);

  return status;
}}}

static bool parse_gprmc(char **fields, struct gps_gprmc *gprmc)
{{{
  char *string_time          = fields[ 1];
  char *string_valid         = fields[ 2];
  char *string_latitude      = fields[ 3];
  char *string_latitude_dir  = fields[ 4];
  char *string_longitude     = fields[ 5];
  char *string_longitude_dir = fields[ 6];
  char *string_ground_speed  = fields[ 7];
  char *string_bearing       = fields[ 8];
  char *string_date          = fields[ 9];
  char *string_variation     = fields[10];
  char *string_variation_dir = fields[11];
  char *string_mode          = fields[12];

  (void)string_ground_speed;
  (void)string_bearing;
  (void)string_date;
  (void)string_variation;
  (void)string_variation_dir;

  bool status = parse_valid(string_valid, &gprmc->data_valid)
             && parse_time(string_time, &gprmc->millisecond_of_day);

  if (status && gprmc->data_valid)
  {
    status = parse_latitude(string_latitude, string_latitude_dir, &gprmc->latitude_decimilliminutes)
          && parse_longitude(string_longitude, string_longitude_dir, &gprmc->longitude_decimilliminutes)
          && parse_mode(string_mode, &gprmc->mode);
  }

#if 0
  if (!status)
  {
    debug_printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
        fields[ 0], fields[ 1], fields[ 2], fields[ 3], fields[ 4],
        fields[ 5], fields[ 6], fields[ 7], fields[ 8], fields[ 9],
        fields[10], fields[11], fields[12]);
  }
#endif

  return status;
}}}

static bool parse_gpvtg(char **fields, struct gps_gpvtg *gpvtg)
{{{
  char *string_bearing_true            = fields[1];
  char *string_bearing_true_true       = fields[2];
  char *string_bearing_mag             = fields[3];
  char *string_bearing_mag_mag         = fields[4];
  char *string_ground_speed_knots      = fields[5];
  char *string_ground_speed_knots_unit = fields[6];
  char *string_ground_speed_kph        = fields[7];
  char *string_ground_speed_kph_unit   = fields[8];
  char *string_mode                    = fields[9];

  if (strcasecmp(string_bearing_true_true, "T")
   || strcasecmp(string_ground_speed_knots_unit, "N")
   || strcasecmp(string_ground_speed_kph_unit, "K"))
  {
    return false;
  }

  if (strcasecmp(string_bearing_mag_mag, "M"))
  {
    gpvtg->coarse_magnetic_valid = false;
  }
  else
  {
    gpvtg->coarse_magnetic_valid = true;
  }

  (void)string_bearing_true;
  (void)string_bearing_mag;
  (void)string_ground_speed_knots;
  (void)string_ground_speed_kph;
  (void)string_mode;

  return true;
}}}

static bool parse_gpgga(char **fields, struct gps_gpgga *gpgga)
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

  bool status = parse_fix(string_fix_type, &gpgga->fix)
             && parse_time(string_time, &gpgga->millisecond_of_day)
             && parse_latitude(string_latitude, string_latitude_dir, &gpgga->latitude_decimilliminutes)
             && parse_longitude(string_longitude, string_longitude_dir, &gpgga->longitude_decimilliminutes);

  (void)string_satellite_count;
  (void)string_horizontal_dilution;
  (void)string_altitude;
  (void)string_altitude_unit;
  (void)string_geoid_separation;
  (void)string_geoid_separation_unit;
  (void)string_time_since_reference;
  (void)string_reference_station_id;

  return status;
}}}

static bool parse_gpgsa(char **fields, struct gps_gpgsa *gpgsa)
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

  bool status = parse_manual(string_mode_manual_auto, &gpgsa->manual_mode)
             && parse_dims(string_mode_fix, &gpgsa->dimensions);

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
  (void)string_position_dilution;
  (void)string_horizontal_dilution;
  (void)string_vertical_dilution;

  return status;
}}}

static bool parse_gpgsv(char **fields, struct gps_gpgsv *gpgsv)
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

  return true;
}}}

bool gps_protocol_parse(char *line, struct gps_message *message)
{{{
  size_t length = strlen(line);

  while ((length > 0) && isspace(line[length - 1]))
  {
    length--;
  }

  if ((length < 4) || (line[0] != '$') || (line[length - 3] != '*'))
  {
    debug_printf("gps_protocol invalid format\n");
    return false;
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
    debug_printf("gps_protocol invalid checksum\n");
    return false;
  }

  line[length - 3] = '\0';

  char *next = &line[1];

  char        *fields[FIELD_COUNT_MAX + 1];
  unsigned int field_count;

  for (field_count = 0; field_count < FIELD_COUNT_MAX; field_count++)
  {
    while (*next == ' ')
    {
      next++;
    }

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
    debug_printf("gps_protocol too many fields\n");
    return false;
  }

  field_count++;

  fields[field_count] = NULL;

  if      (!strcasecmp(fields[0], "GPGLL") && (field_count ==  7)){  message->type = GPS_GPGLL;  return parse_gpgll(fields, &message->data.gpgll);  }
  else if (!strcasecmp(fields[0], "GPRMC") && (field_count == 13)){  message->type = GPS_GPRMC;  return parse_gprmc(fields, &message->data.gprmc);  }
  else if (!strcasecmp(fields[0], "GPVTG") && (field_count ==  9)){  message->type = GPS_GPVTG;  return parse_gpvtg(fields, &message->data.gpvtg);  }
  else if (!strcasecmp(fields[0], "GPGGA") && (field_count == 15)){  message->type = GPS_GPGGA;  return parse_gpgga(fields, &message->data.gpgga);  }
  else if (!strcasecmp(fields[0], "GPGSA") && (field_count == 18)){  message->type = GPS_GPGSA;  return parse_gpgsa(fields, &message->data.gpgsa);  }
  else if (!strcasecmp(fields[0], "GPGSV") && (field_count == 20)){  message->type = GPS_GPGSV;  return parse_gpgsv(fields, &message->data.gpgsv);  }
  else
  {
    debug_printf("gps_protocol unknown type '%s'[%u]\n", fields[0], field_count);
    return false;
  }
}}}
