#include <source/XML_Parse.h>
#include <wrapper/XML_Parse.h>

ParseXML_t *ParseXML_new() {
	return INTO(new ParseXML(), ParseXML_t *);
}

void ParseXML_free(ParseXML_t *parsexml) {
	delete INTO(parsexml, ParseXML *);
}
