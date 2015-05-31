#include <source/core.h>
#include <wrapper/cacti/cacti_interface.h>
#include <wrapper/common.h>
#include <wrapper/core.h>
#include <wrapper/sharedcache.h>

powerDef_t *Core_power(Core_t *self) {
	return TO(powerDef_t, &TO(Core, self)->power);
}

powerDef_t *Core_rt_power(Core_t *self) {
	return TO(powerDef_t, &TO(Core, self)->rt_power);
}

double Core_clockRate(Core_t *self) {
	return TO(Core, self)->clockRate;
}

double Core_executionTime(Core_t *self) {
	return TO(Core, self)->executionTime;
}

SharedCache_t *Core_l2cache(Core_t *self) {
	return TO(SharedCache_t, TO(Core, self)->l2cache);
}
