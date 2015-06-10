#include <source/core.h>
#include <wrapper/common.h>
#include <wrapper/core.h>
#include <wrapper/sharedcache.h>

double Core_clockRate(Core_t *self) {
	return TO(Core, self)->clockRate;
}

double Core_executionTime(Core_t *self) {
	return TO(Core, self)->executionTime;
}

SharedCache_t *Core_l2cache(Core_t *self) {
	return TO(SharedCache_t, TO(Core, self)->l2cache);
}
