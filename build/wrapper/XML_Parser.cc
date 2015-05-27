#include "source/XML_Parse.h"
#include "XML_Parse.h"

#define TO(type, pointer) (reinterpret_cast<type *>(pointer))

extern "C" {

struct ParseXML_t *new_ParseXML() {
	return TO(struct ParseXML_t, new ParseXML());
}

void delete_ParseXML(struct ParseXML_t *parsexml) {
	delete TO(ParseXML, parsexml);
}

}
