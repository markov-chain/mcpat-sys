#include <stdlib.h>
#include <string.h>

#include <hiredis/hiredis.h>
#include <wrapper/cache/interface.h>

static bool cache_initialized = false;
static char cache_host[1024];
static int cache_port;

static void cache_initialize();

bool cache_get(InputParameter *, uca_org_t *, void **) {
	if (!cache_initialized) {
		cache_initialize();
		cache_initialized = true;
	}
	return false;
}

void cache_set(InputParameter *, uca_org_t *, void **) {
}

static void cache_initialize() {
	char *result;
	
	memset((void *)cache_host, 0, sizeof(cache_host));
	cache_port = 0;

	result = getenv(CACHE_HOST_ENV);
	if (result && strlen(result) > 0) {
		strncpy(cache_host, result, sizeof(cache_host) - 1);
	} else {
		strncpy(cache_host, CACHE_HOST_DEF, sizeof(cache_host) - 1);
	}

	result = getenv(CACHE_PORT_ENV);
	if (result && strlen(result) > 0) {
		cache_port = atoi(result);
	} else {
		cache_port = CACHE_PORT_DEF;
	}
}
