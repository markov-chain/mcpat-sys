#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis/hiredis.h>
#include <wrapper/cache/interface.h>

struct {
	pthread_mutex_t mutex;
	bool initialized;
	bool available;
	char host[1024];
	int port;
} cache_state = {
	.mutex = PTHREAD_MUTEX_INITIALIZER,
	.initialized = false,
	.available = false,
	.host = {0},
	.port = 0
};

static void cache_initialize();

bool cache_get(InputParameter *, uca_org_t *, void **) {
	if (!cache_state.initialized) {
		pthread_mutex_lock(&cache_state.mutex);
		if (!cache_state.initialized) cache_initialize();
		pthread_mutex_unlock(&cache_state.mutex);
	}

	if (!cache_state.available) return false;

	return false;
}

void cache_set(InputParameter *, uca_org_t *, void **) {
}

static void cache_initialize() {
	char *result;

	result = getenv(CACHE_HOST_ENV);
	if (result && strlen(result) > 0) {
		strncpy(cache_state.host, result, sizeof(cache_state.host) - 1);
	} else {
		strncpy(cache_state.host, CACHE_HOST_DEF, sizeof(cache_state.host) - 1);
	}

	result = getenv(CACHE_PORT_ENV);
	if (result && strlen(result) > 0) {
		cache_state.port = atoi(result);
	} else {
		cache_state.port = CACHE_PORT_DEF;
	}

	cache_state.initialized = true;
}
