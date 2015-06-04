#ifndef __CACHE_INTERFACE_H__
#define __CACHE_INTERFACE_H__

#include <source/cacti/cacti_interface.h>

bool cache_get(InputParameter *, uca_org_t *, void **);
void cache_set(InputParameter *, uca_org_t *, void **);

#endif
