#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include <wrapper/XML_Parse.h>

extern "C" {
	typedef struct Processor_t;
	Processor_t *new_Processor(ParseXML_t *XML_interface);
	void delete_Processor(Processor_t *);
}

#endif
