// cplusplus.h PUBLIC DOMAIN 2020

#ifndef CPLUSPLUS_H_INCLUDED
#define CPLUSPLUS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

int get_member_of_static(void);
int get_member_of_stack(void);

void call_virt(void);

#ifdef __cplusplus
}
#endif

#endif // CPLUSPLUS_H_INCLUDED
