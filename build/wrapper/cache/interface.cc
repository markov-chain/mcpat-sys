#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis/hiredis.h>
#include <wrapper/cache/interface.h>

struct {
	pthread_mutex_t mutex;
	bool initialized;
	char host[1024];
	int port;
	redisContext *redis;
} cache_state = {
	.mutex = PTHREAD_MUTEX_INITIALIZER,
	.initialized = false,
	.host = {0},
	.port = 0,
	.redis = NULL
};

static void cache_initialize();

bool cache_get(InputParameter *, uca_org_t *, void **) {
	if (!cache_state.initialized) {
		pthread_mutex_lock(&cache_state.mutex);
		if (!cache_state.initialized) {
			cache_initialize();
			cache_state.initialized = true;
		}
		pthread_mutex_unlock(&cache_state.mutex);
	}

	if (!cache_state.redis) return false;

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

	redisContext *redis = redisConnect(cache_state.host, cache_state.port);
	if (!redis) {
		printf("Cache: failed to initialize.\n");
		return;
	}

	if (redis->err) {
		printf("Cache: failed to connect to %s:%d (%s).\n",
			cache_state.host, cache_state.port, redis->errstr);
		redisFree(redis);
		return;
	}

	cache_state.redis = redis;
}
