// Toggle button and LED driver
// Copyright Green Energy Options Ltd.

#ifndef TOGGLE_H_INCLUDED
#define TOGGLE_H_INCLUDED

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void toggle_init(void);
void toggle_poll(void);
bool toggle_get(void);

#ifdef __cplusplus
}
#endif

#endif // TOGGLE_H_INCLUDED
