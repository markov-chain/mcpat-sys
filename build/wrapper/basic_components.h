#ifndef ____BASIC_COMPONENTS_H____
#define ____BASIC_COMPONENTS_H____

extern "C" {
	typedef struct CacheDynParam_t;
	double CacheDynParam_clockRate(CacheDynParam_t *);
	double CacheDynParam_executionTime(CacheDynParam_t *);
}

#endif
