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
