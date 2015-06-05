#ifndef __WRAPPER_CACTI_INTERFACE_H__
#define __WRAPPER_CACTI_INTERFACE_H__

#include <source/cacti/cacti_interface.h>

extern "C" {
	typedef struct powerComponents_t;
	double powerComponents_dynamic(powerComponents_t *);
    double powerComponents_leakage(powerComponents_t *);
    double powerComponents_gate_leakage(powerComponents_t *);
    double powerComponents_short_circuit(powerComponents_t *);
    double powerComponents_longer_channel_leakage(powerComponents_t *);
    double powerComponents_power_gated_leakage(powerComponents_t *);
    double powerComponents_power_gated_with_long_channel_leakage(powerComponents_t *);

	typedef struct powerDef_t;
    powerComponents_t *powerDef_readOp(powerDef_t *);
    powerComponents_t *powerDef_writeOp(powerDef_t *);
    powerComponents_t *powerDef_searchOp(powerDef_t *);
}

#endif
