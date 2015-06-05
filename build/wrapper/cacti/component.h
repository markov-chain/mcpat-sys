#ifndef __WRAPPER_COMPONENT_H__
#define __WRAPPER_COMPONENT_H__

#include <wrapper/cacti/cacti_interface.h>

extern "C" {
	typedef struct Component_t;
	powerDef_t *Component_power(Component_t *);
	powerDef_t *Component_rt_power(Component_t *);
}

#endif
