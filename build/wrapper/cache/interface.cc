#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis/hiredis.h>
#include <wrapper/cache/interface.h>

#define ZERO_FIELD(field) (memset((void *)&(field), 0, sizeof(field)))
#define PRINT_ERROR(format, args...) (fprintf(stderr, "Cache: " format ".\n" , ##args))

typedef struct cache_state_t {
	bool active;
	redisContext *redis;
} cache_state_t;

// The code below is not thread safe. There is no point in pursuing thread
// safeness here as McPAT internally is not thread safe anyway.
static cache_state_t cache_state = {false, NULL};

static void cache_serialize(cache_value_t *, uca_org_t *);
static void cache_deserialize(cache_value_t *, uca_org_t *);

int cache_activate(const char *host, int port) {
	cache_deactivate();

	redisContext *redis = redisConnect(host, port);
	if (!redis) return -ENOMEM;

	int error = redis->err;
	if (error) {
		redisFree(redis);
		return error;
	}

	cache_state.redis = redis;
	cache_state.active = true;

	return 0;
}

void cache_deactivate() {
	if (cache_state.redis) {
		redisFree(cache_state.redis);
		cache_state.redis = NULL;
	}
	cache_state.active = false;
}

void cache_key(cache_key_t *key, InputParameter *input) {
	if (!cache_state.active) return;

	key->base = *input;
	ZERO_FIELD(key->base.dvs_voltage);
}

bool cache_get(cache_key_t *key, uca_org_t *output) {
	if (!cache_state.active) return false;

	const int argc = 2;
	const char *argv[argc] = {"GET", (char *)key};
	size_t argvlen[argc] = {3, sizeof(cache_key_t)};

	redisReply *reply = (redisReply *)redisCommandArgv(
		cache_state.redis, argc, argv, argvlen);

	if (!reply) {
		PRINT_ERROR("failed to get (%s)", cache_state.redis->errstr);
		cache_deactivate();
		return false;
	}

	bool found = false;

	switch (reply->type) {
	case REDIS_REPLY_STRING:
		if (reply->len != sizeof(cache_value_t)) {
			PRINT_ERROR("received data with a wrong size");
			cache_deactivate();
			break;
		}
		cache_deserialize((cache_value_t *)reply->str, output);
		found = true;
		break;

	case REDIS_REPLY_NIL:
		break;

	case REDIS_REPLY_ERROR:
		PRINT_ERROR("failed to get (%s)", reply->str);
		cache_deactivate();
		break;

	default:
		PRINT_ERROR("received data with a wrong type");
		cache_deactivate();
		break;
	}

	freeReplyObject((void *)reply);
	return found;
}

void cache_set(cache_key_t *key, uca_org_t *output) {
	if (!cache_state.active) return;

	cache_value_t value;
	cache_serialize(&value, output);

	const int argc = 3;
	const char *argv[argc] = {"SET", (char *)key, (char *)&value};
	size_t argvlen[argc] = {3, sizeof(cache_key_t), sizeof(cache_value_t)};

	redisReply *reply = (redisReply *)redisCommandArgv(
		cache_state.redis, argc, argv, argvlen);

	if (!reply) {
		PRINT_ERROR("failed to set (%s)", cache_state.redis->errstr);
		cache_deactivate();
		return;
	}

	switch (reply->type) {
	case REDIS_REPLY_STATUS:
		break;

	case REDIS_REPLY_ERROR:
		PRINT_ERROR("failed to set (%s)", reply->str);
		cache_deactivate();
		break;

	default:
		PRINT_ERROR("failed to set");
		cache_deactivate();
		break;
	}

	freeReplyObject((void *)reply);
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
		value->tag_array2_present = true;
	}

	if (output->data_array2) {
		value->data_array2 = *output->data_array2;
		value->data_array2.arr_min = NULL;
		value->data_array2_present = true;
	}
}

static void cache_deserialize(cache_value_t *value, uca_org_t *output) {
	mem_array *tag_array2 = output->tag_array2;
	if (value->tag_array2_present && !tag_array2) {
		tag_array2 = new mem_array();
	}
	if (tag_array2) {
		*tag_array2 = value->tag_array2;
	}

	mem_array *data_array2 = output->data_array2;
	if (value->data_array2_present && !data_array2) {
		data_array2 = new mem_array();
	}
	if (data_array2) {
		*data_array2 = value->data_array2;
	}

	*output = value->base;
	output->tag_array2 = tag_array2;
	output->data_array2 = data_array2;
}
