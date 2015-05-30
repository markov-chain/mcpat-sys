#include <source/cacti/cacti_interface.h>
#include <wrapper/cacti/cacti_interface.h>
#include <wrapper/common.h>

double powerComponents_dynamic(powerComponents_t *self) {
	return TO(powerComponents, self)->dynamic;
}

double powerComponents_leakage(powerComponents_t *self) {
	return TO(powerComponents, self)->leakage;
}

double powerComponents_gate_leakage(powerComponents_t *self) {
	return TO(powerComponents, self)->gate_leakage;
}

double powerComponents_short_circuit(powerComponents_t *self) {
	return TO(powerComponents, self)->short_circuit;
}

double powerComponents_longer_channel_leakage(powerComponents_t *self) {
	return TO(powerComponents, self)->longer_channel_leakage;
}

double powerComponents_power_gated_leakage(powerComponents_t *self) {
	return TO(powerComponents, self)->power_gated_leakage;
}

double powerComponents_power_gated_with_long_channel_leakage(powerComponents_t *self) {
	return TO(powerComponents, self)->power_gated_with_long_channel_leakage;
}

powerComponents_t *powerDef_readOp(powerDef_t *self) {
	return TO(powerComponents_t, &TO(powerDef, self)->readOp);
}

powerComponents_t *powerDef_writeOp(powerDef_t *self) {
	return TO(powerComponents_t, &TO(powerDef, self)->writeOp);
}

powerComponents_t *powerDef_searchOp(powerDef_t *self) {
	return TO(powerComponents_t, &TO(powerDef, self)->searchOp);
}
