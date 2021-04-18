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

#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include "gps_protocol.h"


#define BUFFER_SIZE  256u
#define VECTOR_SIZE   32u


static char  buffer[BUFFER_SIZE];
static char *vector[VECTOR_SIZE];
static unsigned int buffer_len = 0;

static void gps_protocol_parse(char *line, unsigned int length);

static void gps_parse_gpgll(char ** fields);
static void gps_parse_gprmc(char ** fields);
static void gps_parse_gpvtg(char ** fields);
static void gps_parse_gpgga(char ** fields);
static void gps_parse_gpgsa(char ** fields);
static void gps_parse_gpgsv(char ** fields);


void gps_protocol_flush(void)
{{{
  buffer_len = 0;
}}}

void gps_protocol_rx(char c)
{{{
  if (buffer_len < BUFFER_SIZE)
  {
    if (c == '\n')
    {
      buffer[buffer_len] = '\0';

      gps_protocol_parse(buffer, buffer_len);

      buffer_len = 0;
    }
    else
    {
      buffer[buffer_len] = c;

      buffer_len++;
    }
  }
  else
  {
    if (c == '\n')
    {
      buffer_len = 0;
    }
  }
}}}

static void gps_protocol_parse(char *line, unsigned int length)
{{{
  while ((length > 0) && isspace(line[length - 1]))
  {
    length--;
  }

  if ((length < 4) || (line[0] != '$') || (line[length - 3] != '*'))
  {
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
    return;
  }

  line[length - 3] = '\0';

  unsigned int count;

  char *next = &line[1];

  for (count = 0; count < (VECTOR_SIZE - 1); count++)
  {
    vector[count] = next;

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

  if (count == (VECTOR_SIZE - 1))
  {
    return;
  }

  count++;

  vector[count] = NULL;

  if      (!strcasecmp(vector[0], "GPGLL") && (count ==  7)){  gps_parse_gpgll(vector);  }
  else if (!strcasecmp(vector[0], "GPRMC") && (count == 12)){  gps_parse_gprmc(vector);  }
  else if (!strcasecmp(vector[0], "GPVTG") && (count ==  9)){  gps_parse_gpvtg(vector);  }
  else if (!strcasecmp(vector[0], "GPGGA") && (count == 15)){  gps_parse_gpgga(vector);  }
  else if (!strcasecmp(vector[0], "GPGSA") && (count == 18)){  gps_parse_gpgsa(vector);  }
  else if (!strcasecmp(vector[0], "GPGSV") && (count == 20)){  gps_parse_gpgsv(vector);  }
  else
  {
    return;
  }
}}}

static void gps_parse_gpgll(char ** fields)
{{{
  char *string_latitude      = fields[1];
  char *string_latitude_dir  = fields[2];
  char *string_longitude     = fields[3];
  char *string_longitude_dir = fields[4];
  char *string_time          = fields[5];
  char *string_valid         = fields[6];

  (void)string_latitude;
  (void)string_latitude_dir;
  (void)string_longitude;
  (void)string_longitude_dir;
  (void)string_time;
  (void)string_valid;
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

  (void)string_time;
  (void)string_valid;
  (void)string_latitude;
  (void)string_latitude_dir;
  (void)string_longitude;
  (void)string_longitude_dir;
  (void)string_ground_speed;
  (void)string_bearing;
  (void)string_date;
  (void)string_variation;
  (void)string_variation_dir;
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

  (void)string_bearing_true;
  (void)string_bearing_true_true;
  (void)string_bearing_mag;
  (void)string_bearing_mag_mag;
  (void)string_ground_speed_knots;
  (void)string_ground_speed_knots_unit;
  (void)string_ground_speed_kph;
  (void)string_ground_speed_kph_unit;
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
