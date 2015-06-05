#ifndef __WRAPPER_BASIC_COMPONENTS_H__
#define __WRAPPER_BASIC_COMPONENTS_H__

extern "C" {
	typedef struct CacheDynParam_t;
	double CacheDynParam_clockRate(CacheDynParam_t *);
	double CacheDynParam_executionTime(CacheDynParam_t *);
}

#endif
