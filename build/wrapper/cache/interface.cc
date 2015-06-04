// The code below is not thread safe. There is no point in pursuing thread
// safeness here as McPAT internally is not thread safe anyway.

#include <stdlib.h>
#include <string.h>

#include <hiredis/hiredis.h>
#include <wrapper/cache/interface.h>

#define CACHE_HOST_ENV "MCPAT_CACHE_HOST"
#define CACHE_PORT_ENV "MCPAT_CACHE_PORT"

#define CACHE_HOST_DEF "127.0.0.1"
#define CACHE_PORT_DEF 6379

#define ZERO_FIELD(field) (memset((void *)&(field), 0, sizeof(field)))

struct {
	bool initialized;
	bool available;
	char host[1024];
	int port;
	redisContext *redis;
} cache_state = {
	.initialized = false,
	.available = false
};

static void cache_initialize(void);
static void cache_deinitialize(void);
static void cache_serialize(cache_value_t *, uca_org_t *);
static void cache_deserialize(cache_value_t *, uca_org_t *);

void cache_key(cache_key_t *key, InputParameter *input) {
	if (!cache_state.initialized) {
		cache_initialize();
		cache_state.initialized = true;
	}

	if (!cache_state.available) return;

	key->base = *input;
	ZERO_FIELD(key->base.dvs_voltage);
}

bool cache_get(cache_key_t *key, uca_org_t *output) {
	if (!cache_state.available) return false;

	const int argc = 2;
	const char *argv[argc] = {"GET", (char *)key};
	size_t argvlen[argc] = {3, sizeof(cache_key_t)};

	redisReply *reply = (redisReply *)redisCommandArgv(
		cache_state.redis, argc, argv, argvlen);

	if (!reply) {
		printf("Cache: failed to get (%s).\n", cache_state.redis->errstr);
		cache_deinitialize();
		return false;
	}

	if (reply->type == REDIS_REPLY_ERROR) {
		printf("Cache: failed to get (%s).\n", reply->str);
		freeReplyObject((void *)reply);
		cache_deinitialize();
		return false;
	}

	if (reply->len != sizeof(cache_value_t)) {
		printf("Cache: received corrupted data.\n");
		freeReplyObject((void *)reply);
		cache_deinitialize();
		return false;
	}

	cache_deserialize((cache_value_t *)reply->str, output);
	freeReplyObject((void *)reply);

	return true;
}

void cache_set(cache_key_t *key, uca_org_t *output) {
	if (!cache_state.available) return;

	cache_value_t value;
	cache_serialize(&value, output);

	const int argc = 3;
	const char *argv[argc] = {"SET", (char *)key, (char *)&value};
	size_t argvlen[argc] = {3, sizeof(cache_key_t), sizeof(cache_value_t)};

	redisReply *reply = (redisReply *)redisCommandArgv(
		cache_state.redis, argc, argv, argvlen);

	if (!reply) {
		printf("Cache: failed to set (%s).\n", cache_state.redis->errstr);
		cache_deinitialize();
		return;
	}

	if (reply->type == REDIS_REPLY_ERROR) {
		printf("Cache: failed to set (%s).\n", reply->str);
		cache_deinitialize();
	}

	freeReplyObject((void *)reply);
}

static void cache_initialize() {
	char *result;

	ZERO_FIELD(cache_state);

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
	cache_state.available = true;
}

static void cache_deinitialize() {
	if (cache_state.redis) {
		redisFree(cache_state.redis);
	}
	ZERO_FIELD(cache_state);
}

static void cache_serialize(cache_value_t *value, uca_org_t *output) {
	ZERO_FIELD(*value);

	value->base = *output;
	value->base.tag_array2 = NULL;
	value->base.data_array2 = NULL;
	ZERO_FIELD(value->base.uca_q);
	value->base.uca_pg_reference = NULL;

	if (output->tag_array2) {
		value->tag_array2 = *output->tag_array2;
		value->tag_array2.arr_min = NULL;
	}

	if (output->data_array2) {
		value->data_array2 = *output->data_array2;
		value->data_array2.arr_min = NULL;
	}
}

static void cache_deserialize(cache_value_t *value, uca_org_t *output) {
	mem_array *tag_array2 = output->tag_array2;
	if (tag_array2) {
		*tag_array2 = value->tag_array2;
	}

	mem_array *data_array2 = output->data_array2;
	if (data_array2) {
		*data_array2 = value->data_array2;
	}

	*output = value->base;
	output->tag_array2 = tag_array2;
	output->data_array2 = data_array2;
}
