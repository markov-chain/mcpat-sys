#ifndef ____SHAREDCACHE_H____
#define ____SHAREDCACHE_H____

#include <wrapper/basic_components.h>

extern "C" {
	typedef struct SharedCache_t;
	powerDef_t *SharedCache_power(SharedCache_t *);
	powerDef_t *SharedCache_rt_power(SharedCache_t *);
	CacheDynParam_t *SharedCache_cachep(SharedCache_t *);
}

#endif
