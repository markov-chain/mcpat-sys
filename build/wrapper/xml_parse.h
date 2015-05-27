#ifndef __XML_PARSE__
#define __XML_PARSE__

#ifdef __cplusplus
extern "C" {
#endif
	typedef struct ParseXML_t;
	extern ParseXML_t *new_ParseXML();
	extern void delete_ParseXML(ParseXML_t *);
#ifdef __cplusplus
}
#endif

#endif
