#ifndef __WRAPPER_CACTI_AREA_H__
#define __WRAPPER_CACTI_AREA_H__

#include <wrapper/cacti/area.h>

extern "C" {
	typedef struct Area_t;
	double Area_get_area(Area_t *);
}

#endif
