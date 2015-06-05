#ifndef __WRAPPER_SHAREDCACHE_H__
#define __WRAPPER_SHAREDCACHE_H__

#include <wrapper/basic_components.h>

extern "C" {
	typedef struct SharedCache_t;
	powerDef_t *SharedCache_power(SharedCache_t *);
	powerDef_t *SharedCache_rt_power(SharedCache_t *);
	CacheDynParam_t *SharedCache_cachep(SharedCache_t *);
}

#endif
