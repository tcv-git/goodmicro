// Coloured terminal output with timestamps
// Based on part of dqrs: PUBLIC DOMAIN 2016 <http:///www.purposeful.co.uk/software/dqrs>
// Further modifications: Copyright Green Energy Options Limited

#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED

#include <stdint.h>

#define BOLD       0x08u
#define RED        0x04u
#define GREEN      0x02u
#define BLUE       0x01u
#define BLACK      0x00u
#define CYAN       (      GREEN | BLUE)
#define MAGENTA    (RED         | BLUE)
#define YELLOW     (RED | GREEN       )
#define WHITE      (RED | GREEN | BLUE)

#define INVERSE    0x80u
#define ON_RED     0x40u
#define ON_GREEN   0x20u
#define ON_BLUE    0x10u
#define ON_BLACK   0x00u
#define ON_CYAN    (         ON_GREEN | ON_BLUE)
#define ON_MAGENTA (ON_RED |            ON_BLUE)
#define ON_YELLOW  (ON_RED | ON_GREEN          )
#define ON_WHITE   (ON_RED | ON_GREEN | ON_BLUE)

#ifdef __cplusplus
extern "C" {
#endif

void terminal_set_color(uint8_t color);
void terminal_write(const uint8_t *data, uint32_t count);
void terminal_restore(void);

#ifdef __cplusplus
}
#endif

#endif // TERMINAL_H_INCLUDED
