#include <source/sharedcache.h>
#include <wrapper/basic_components.h>
#include <wrapper/common.h>
#include <wrapper/sharedcache.h>

CacheDynParam_t *SharedCache_cachep(SharedCache_t *self) {
	return TO(CacheDynParam_t, &TO(SharedCache, self)->cachep);
}
