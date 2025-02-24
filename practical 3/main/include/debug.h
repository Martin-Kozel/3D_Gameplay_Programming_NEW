#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

// Undefine DEBUG if already defined
#ifdef DEBUG
#undef DEBUG
#endif

// Define DEBUG level (set to 1 or 2 for more detailed messages)
#define DEBUG 1

// Macro for streaming DEBUG messages
#if defined(DEBUG) && (DEBUG >= 1)
    // For messages with format strings and arguments
    #define DEBUG_MSG(...) printf(__VA_ARGS__)
#else
    // Empty macro when debug is disabled
    #define DEBUG_MSG(...) ((void)0)
#endif

#endif // DEBUG_H