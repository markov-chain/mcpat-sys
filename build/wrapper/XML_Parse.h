#ifndef __XML_PARSE_H__
#define __XML_PARSE_H__

#include <source/XML_Parse.h>

extern "C" {
	typedef struct ParseXML_t;
	ParseXML_t *new_ParseXML();
	void delete_ParseXML(ParseXML_t *);
	void ParseXML_parse(ParseXML_t *, char *);
	root_system *ParseXML_sys(ParseXML_t *);
}

#endif
