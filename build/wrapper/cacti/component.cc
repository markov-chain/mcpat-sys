#include <source/cacti/component.h>
#include <wrapper/cacti/area.h>
#include <wrapper/cacti/component.h>
#include <wrapper/common.h>

Area_t *Component_area(Component_t *self) {
	return TO(Area_t, &TO(Component, self)->area);
}

powerDef_t *Component_power(Component_t *self) {
	return TO(powerDef_t, &TO(Component, self)->power);
}

powerDef_t *Component_rt_power(Component_t *self) {
	return TO(powerDef_t, &TO(Component, self)->rt_power);
}
