#ifndef ___COMMON_H___
#define ___COMMON_H___

#define TO(type, some) (reinterpret_cast<type *>(some))

extern "C" {
	void set_opt_for_clk(int);
}

#endif
