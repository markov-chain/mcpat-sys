#include <source/cacti/component.h>
#include <wrapper/cacti/component.h>
#include <wrapper/common.h>

powerDef_t *Component_power(Component_t *self) {
	return TO(powerDef_t, &TO(Component, self)->power);
}

powerDef_t *Component_rt_power(Component_t *self) {
	return TO(powerDef_t, &TO(Component, self)->rt_power);
}
