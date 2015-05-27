#include <wrapper/XML_Parse.h>
#include <wrapper/common.h>

ParseXML_t *new_ParseXML() {
	return TO(ParseXML_t, new ParseXML());
}

void delete_ParseXML(ParseXML_t *parsexml) {
	delete TO(ParseXML, parsexml);
}

void ParseXML_parse(ParseXML_t *parsexml, char *filename) {
	TO(ParseXML, parsexml)->parse(filename);
}

root_system *ParseXML_sys(ParseXML_t *parsexml) {
	return &TO(ParseXML, parsexml)->sys;
}
