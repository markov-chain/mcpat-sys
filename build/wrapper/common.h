#ifndef __WRAPPER_COMMON_H__
#define __WRAPPER_COMMON_H__

#define TO(type, some) (reinterpret_cast<type *>(some))

extern "C" {
	void opt_for_clk_set(int);
}

#endif
