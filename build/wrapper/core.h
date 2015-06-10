#ifndef __WRAPPER_CORE_H__
#define __WRAPPER_CORE_H__

#include <wrapper/sharedcache.h>

extern "C" {
	typedef struct Core_t;
	double Core_clockRate(Core_t *);
	double Core_executionTime(Core_t *);
	SharedCache_t *Core_l2cache(Core_t *);
}

#endif
