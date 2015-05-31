#ifndef ____COMPONENT_H____
#define ____COMPONENT_H____

#include <wrapper/cacti/cacti_interface.h>

extern "C" {
	typedef struct Component_t;
	powerDef_t *Component_power(Component_t *);
	powerDef_t *Component_rt_power(Component_t *);
}

#endif
