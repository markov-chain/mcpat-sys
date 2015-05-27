#ifndef __XML_PARSE_H__
#define __XML_PARSE_H__

extern "C" {
	typedef struct ParseXML_t;
	ParseXML_t *new_ParseXML();
	void delete_ParseXML(ParseXML_t *);
	void ParseXML_parse(ParseXML_t *, char *);
}

#endif
