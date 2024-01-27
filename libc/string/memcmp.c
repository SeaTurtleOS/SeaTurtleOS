#include <string.h>
 
int memcmp(const void* aptr, const void* bptr, size_t size) {
	const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for (size_t i = 0; i < size; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
		// Returns 1 or -1 depending on which string is bigger.
		// Both give 1 when converted to binary and back to int, though
	}
	return 0;
	// Only returns 0 if both strings are "equal"
	// This is why !memcmp is used so often.
}