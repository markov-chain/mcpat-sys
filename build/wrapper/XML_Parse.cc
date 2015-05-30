#include <wrapper/XML_Parse.h>
#include <wrapper/common.h>

ParseXML_t *new_ParseXML() {
	return TO(ParseXML_t, new ParseXML());
}

void delete_ParseXML(ParseXML_t *self) {
	delete TO(ParseXML, self);
}

void ParseXML_parse(ParseXML_t *self, char *filename) {
	TO(ParseXML, self)->parse(filename);
}

root_system *ParseXML_sys(ParseXML_t *self) {
	return &TO(ParseXML, self)->sys;
}
