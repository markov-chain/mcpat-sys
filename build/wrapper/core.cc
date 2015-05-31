#include <source/core.h>
#include <wrapper/cacti/cacti_interface.h>
#include <wrapper/common.h>
#include <wrapper/core.h>

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
