#pragma once

#define ERROR(fmt, ...) printf("\x1b[91mERROR\x1b[0m: " fmt, ##__VA_ARGS__)
#define WARN(fmt, ...) printf("\x1b[93mWARN\x1b[0m: " fmt, ##__VA_ARGS__)
#define INFO(fmt, ...) printf("\x1b[92mINFO\x1b[0m: " fmt, ##__VA_ARGS__)

#ifdef DEBUG
	#define DEBUG printf("\x1b[95mDEBUG\x1b[0m: " fmt, ##__VA_ARGS__)
#else
	#define DEBUG(...)
#endif
