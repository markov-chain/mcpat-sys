#ifndef ____CORE_H____
#define ____CORE_H____

#include <wrapper/sharedcache.h>

extern "C" {
	typedef struct Core_t;
	powerDef_t *Core_power(Core_t *);
	powerDef_t *Core_rt_power(Core_t *);
	double Core_clockRate(Core_t *);
	double Core_executionTime(Core_t *);
	SharedCache_t *Core_l2cache(Core_t *);
}

#endif
