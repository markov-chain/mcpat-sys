#ifndef __XML_PARSE__
#define __XML_PARSE__

#define INTO(some, type) (reinterpret_cast<type>(some))

extern "C" {
	typedef struct ParseXML_t;
	ParseXML_t *ParseXML_new();
	void ParseXML_free(ParseXML_t *);
	void ParseXML_parse(ParseXML_t *, char *);
}

#endif
