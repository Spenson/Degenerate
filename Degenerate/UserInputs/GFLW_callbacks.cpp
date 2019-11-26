#include "GFLW_callbacks.h"

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}



