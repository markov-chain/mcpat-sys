#ifndef __WRAPPER_PROCESSOR_H__
#define __WRAPPER_PROCESSOR_H__

#include <wrapper/XML_Parse.h>
#include <wrapper/cacti/component.h>
#include <wrapper/sharedcache.h>

extern "C" {
	typedef struct Processor_t;
	Processor_t *new_Processor(ParseXML_t *XML_interface);
	void delete_Processor(Processor_t *);
	Core_t *Processor_cores(Processor_t *, int);
	SharedCache_t *Processor_l3array(Processor_t *, int);
	Component_t *Processor_l3(Processor_t *);
	int Processor_numCore(Processor_t *);
	int Processor_numL2(Processor_t *);
	int Processor_numL3(Processor_t *);
	int Processor_numNOC(Processor_t *);
	int Processor_numL1Dir(Processor_t *);
	int Processor_numL2Dir(Processor_t *);
}

#endif
