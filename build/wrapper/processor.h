#ifndef ____PROCESSOR_H____
#define ____PROCESSOR_H____

#include <wrapper/XML_Parse.h>
#include <wrapper/cacti/cacti_interface.h>
#include <wrapper/cacti/component.h>

extern "C" {
	typedef struct Processor_t;
	Processor_t *new_Processor(ParseXML_t *XML_interface);
	void delete_Processor(Processor_t *);
	Core_t *Processor_cores(Processor_t *, int);
	powerDef_t *Processor_power(Processor_t *);
	powerDef_t *Processor_rt_power(Processor_t *);
	Component_t *Processor_l3(Processor_t *);
	int Processor_numCore(Processor_t *);
	int Processor_numL2(Processor_t *);
	int Processor_numL3(Processor_t *);
	int Processor_numNOC(Processor_t *);
	int Processor_numL1Dir(Processor_t *);
	int Processor_numL2Dir(Processor_t *);
}

#endif
