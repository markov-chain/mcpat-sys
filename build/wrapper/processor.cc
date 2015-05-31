#include <source/XML_Parse.h>
#include <source/processor.h>
#include <wrapper/cacti/cacti_interface.h>
#include <wrapper/cacti/component.h>
#include <wrapper/common.h>
#include <wrapper/core.h>
#include <wrapper/processor.h>

Processor_t *new_Processor(ParseXML_t *XML_interface) {
	return TO(Processor_t, new Processor(TO(ParseXML, XML_interface)));
}

void delete_Processor(Processor_t *self) {
	delete TO(Processor, self);
}

Core_t *Processor_cores(Processor_t *self, int i) {
	return TO(Core_t, TO(Processor, self)->cores[i]);
}

powerDef_t *Processor_power(Processor_t *self) {
	return TO(powerDef_t, &TO(Processor, self)->power);
}

powerDef_t *Processor_rt_power(Processor_t *self) {
	return TO(powerDef_t, &TO(Processor, self)->rt_power);
}

Component_t *Processor_l3(Processor_t *self) {
	return TO(Component_t, &TO(Processor, self)->l3);
}

int Processor_numCore(Processor_t *self) {
	return TO(Processor, self)->numCore;
}

int Processor_numL2(Processor_t *self) {
	return TO(Processor, self)->numL2;
}

int Processor_numL3(Processor_t *self) {
	return TO(Processor, self)->numL3;
}

int Processor_numNOC(Processor_t *self) {
	return TO(Processor, self)->numNOC;
}

int Processor_numL1Dir(Processor_t *self) {
	return TO(Processor, self)->numL1Dir;
}

int Processor_numL2Dir(Processor_t *self) {
	return TO(Processor, self)->numL2Dir;
}
