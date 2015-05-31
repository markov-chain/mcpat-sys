#include <source/basic_components.h>
#include <wrapper/basic_components.h>
#include <wrapper/common.h>

double CacheDynParam_clockRate(CacheDynParam_t *self) {
	return TO(CacheDynParam, self)->clockRate;
}

double CacheDynParam_executionTime(CacheDynParam_t *self) {
	return TO(CacheDynParam, self)->executionTime;
}
