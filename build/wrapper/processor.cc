#include <source/XML_Parse.h>
#include <source/processor.h>
#include <wrapper/cacti/cacti_interface.h>
#include <wrapper/common.h>
#include <wrapper/processor.h>

Processor_t *new_Processor(ParseXML_t *XML_interface) {
	return TO(Processor_t, new Processor(TO(ParseXML, XML_interface)));
}

void delete_Processor(Processor_t *self) {
	delete TO(Processor, self);
}

powerDef_t *Processor_power(Processor_t *self) {
	return TO(powerDef_t, &TO(Processor, self)->power);
}

powerDef_t *Processor_rt_power(Processor_t *self) {
	return TO(powerDef_t, &TO(Processor, self)->rt_power);
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
