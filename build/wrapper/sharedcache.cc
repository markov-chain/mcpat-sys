#include <source/sharedcache.h>
#include <wrapper/basic_components.h>
#include <wrapper/cacti/cacti_interface.h>
#include <wrapper/common.h>
#include <wrapper/sharedcache.h>

powerDef_t *SharedCache_power(SharedCache_t *self) {
	return TO(powerDef_t, &TO(SharedCache, self)->power);
}

powerDef_t *SharedCache_rt_power(SharedCache_t *self) {
	return TO(powerDef_t, &TO(SharedCache, self)->rt_power);
}

CacheDynParam_t *SharedCache_cachep(SharedCache_t *self) {
	return TO(CacheDynParam_t, &TO(SharedCache, self)->cachep);
}
