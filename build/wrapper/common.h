#ifndef __COMMON_H__
#define __COMMON_H__

#define TO(type, some) (reinterpret_cast<type *>(some))

extern "C" {
	void set_opt_for_clk(int);
}

#endif
