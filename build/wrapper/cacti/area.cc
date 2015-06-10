#include <source/cacti/area.h>
#include <wrapper/cacti/area.h>
#include <wrapper/common.h>

double Area_get_area(Area_t *self) {
	return TO(Area, self)->get_area();
}
