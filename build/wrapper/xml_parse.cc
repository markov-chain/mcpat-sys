#include "source/XML_Parse.h"
#include "XML_Parse.h"

#define TO(type, pointer) (reinterpret_cast<type *>(pointer))

ParseXML_t *new_ParseXML() {
	return TO(ParseXML_t, new ParseXML());
}

void delete_ParseXML(ParseXML_t *parsexml) {
	delete TO(ParseXML, parsexml);
}
