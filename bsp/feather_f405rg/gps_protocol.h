// gps_protocol.h
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

#ifndef GPS_PROTOCOL_H_INCLUDED
#define GPS_PROTOCOL_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

enum gps_fix
{
  GPS_FIX_NONE,
  GPS_FIX_GPS,
  GPS_FIX_DGPS,
};

enum gps_dims
{
  GPS_DIMS_NONE,
  GPS_DIMS_2D,
  GPS_DIMS_3D,
};

enum gps_mode
{
  GPS_MODE_AUTO,
  GPS_MODE_DIFF,
  GPS_MODE_EST,
};

struct gps_gpgll
{
  bool          data_valid;
  uint32_t      millisecond_of_day;
  int32_t       latitude_decimilliminutes;
  int32_t       longitude_decimilliminutes;
};

struct gps_gprmc
{
  bool          data_valid;
  uint32_t      millisecond_of_day;
  int32_t       latitude_decimilliminutes;
  int32_t       longitude_decimilliminutes;
  uint32_t      groundspeed_milliknots;
  uint16_t      date_days;
  int32_t       magnetic_variation_millidegrees;
  enum gps_mode mode;
};

struct gps_gpvtg
{
  int32_t       course_millidegrees_true;
  int32_t       course_millidegrees_magnetic;
  uint32_t      groundspeed_milliknots;
  uint32_t      groundspeed_metres_per_hour;
  enum gps_mode mode;
};

struct gps_gpgga
{
  uint32_t      millisecond_of_day;
  int32_t       latitude_decimilliminutes;
  int32_t       longitude_decimilliminutes;
  enum gps_fix  fix;
  uint8_t       satellite_count;
  uint16_t      horizontal_dilution_milli;
  int32_t       altitude_mm;
  int32_t       geoid_separation_mm;
  uint32_t      diff_update_age_ms;
  uint32_t      diff_station_id;
};

struct gps_gpgsa
{
  bool          manual_mode;
  enum gps_dims dimensions;
  uint8_t       satellite_id[12];
  uint16_t      position_dilution_milli;
  uint16_t      horizontal_dilution_milli;
  uint16_t      vertical_dilution_milli;
};

struct gps_gpgsv
{
  uint8_t       message_count;
  uint8_t       message_number;
  uint8_t       satellite_count;
  uint8_t       satellite_id[4];
  uint8_t       elevation_degrees[4];
  uint16_t      azimuth_degrees[4];
  uint8_t       snr_dbhz[4];
};

enum gps_message_type
{
  GPS_GPGLL,
  GPS_GPRMC,
  GPS_GPVTG,
  GPS_GPGGA,
  GPS_GPGSA,
  GPS_GPGSV,
};

union gps_message_data
{
  struct gps_gpgll gpgll;
  struct gps_gprmc gprmc;
  struct gps_gpvtg gpvtg;
  struct gps_gpgga gpgga;
  struct gps_gpgsa gpgsa;
  struct gps_gpgsv gpgsv;
};

struct gps_message
{
  enum  gps_message_type type;
  union gps_message_data data;
};

bool gps_protocol_parse(char *line, struct gps_message *message);

#ifdef __cplusplus
}
#endif

#endif // GPS_PROTOCOL_H_INCLUDED
