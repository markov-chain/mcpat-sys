#include <source/processor.h>
#include <source/XML_Parse.h>
#include <wrapper/processor.h>
#include <wrapper/common.h>

Processor_t *new_Processor(ParseXML_t *XML_interface) {
	return TO(Processor_t, new Processor(TO(ParseXML, XML_interface)));
}

void delete_Processor(Processor_t *processor) {
	delete TO(Processor, processor);
}
