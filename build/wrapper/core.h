#ifndef ____CORE_H____
#define ____CORE_H____

extern "C" {
	typedef struct Core_t;
	powerDef_t *Core_power(Core_t *);
	powerDef_t *Core_rt_power(Core_t *);
	double Core_clockRate(Core_t *);
	double Core_executionTime(Core_t *);
}

#endif
