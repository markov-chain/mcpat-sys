#ifndef ___CACHE_INTERFACE_H___
#define ___CACHE_INTERFACE_H___

#include <source/cacti/Ucache.h>
#include <source/cacti/cacti_interface.h>

#define CACHE_HOST_ENV "MCPAT_CACHE_HOST"
#define CACHE_PORT_ENV "MCPAT_CACHE_PORT"

#define CACHE_HOST_DEF "127.0.0.1"
#define CACHE_PORT_DEF 6379

bool cache_get(InputParameter *, uca_org_t *, void **);
void cache_set(InputParameter *, uca_org_t *, void **);

#endif
