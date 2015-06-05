#ifndef __WRAPPER_CACHE_INTERFACE_H__
#define __WRAPPER_CACHE_INTERFACE_H__

#include <source/cacti/Ucache.h>
#include <source/cacti/cacti_interface.h>

typedef struct __InputParameter {
	InputParameter base;
} __InputParameter;

typedef struct __uca_org_t {
	uca_org_t base;
	mem_array tag_array2;
	mem_array data_array2;
	bool tag_array2_present;
	bool data_array2_present;
} __uca_org_t;

typedef __InputParameter cache_key_t;
typedef __uca_org_t cache_value_t;

extern "C" {
	int cache_activate(const char *, int);
	void cache_deactivate();
}

void cache_key(cache_key_t *, InputParameter *);
bool cache_get(cache_key_t *, uca_org_t *);
void cache_set(cache_key_t *, uca_org_t *);

#endif
