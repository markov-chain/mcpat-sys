#ifndef ____PROCESSOR_H____
#define ____PROCESSOR_H____

#include <wrapper/XML_Parse.h>
#include <wrapper/cacti/cacti_interface.h>

extern "C" {
	typedef struct Processor_t;
	Processor_t *new_Processor(ParseXML_t *XML_interface);
	void delete_Processor(Processor_t *);
	powerDef_t *Processor_power(Processor_t *);
	powerDef_t *Processor_rt_power(Processor_t *);
}

#endif
