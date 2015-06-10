#ifndef __WRAPPER_CACTI_COMPONENT_H__
#define __WRAPPER_CACTI_COMPONENT_H__

#include <wrapper/cacti/cacti_interface.h>
#include <wrapper/cacti/area.h>

extern "C" {
	typedef struct Component_t;
	Area_t *Component_area(Component_t *);
	powerDef_t *Component_power(Component_t *);
	powerDef_t *Component_rt_power(Component_t *);
}

#endif
