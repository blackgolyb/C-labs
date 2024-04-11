#include <stdio.h>

// Визначення константи
// #define DEBUG_MODE
// #define VERBOSE_DEBUG
#define VERSION "1.0.0"
#define AUTHOR "Омельніцький А.М."
#define GROUP "КН-1023б"

#ifdef DEBUG_MODE
#define DEBUG_PRINTF(fmt,...) printf(fmt, ##__VA_ARGS__)

#ifdef VERBOSE_DEBUG
#define DEBUG_PRINTF(fmt,...) printf("Version: %s, Author: %s, Group: %s\n", VERSION, AUTHOR, GROUP); printf(fmt, ##__VA_ARGS__);
#endif

#else

#define RELEASE_MODE
#define DEBUG_PRINTF(fmt,...)

#endif

int task2() {
    DEBUG_PRINTF("Debug mode enabled.\n");

#if defined(DEBUG_MODE) && defined(VERBOSE_DEBUG)
    printf("Verbose debug mode enabled.\n");
#elif defined(DEBUG_MODE)
    printf("Verbose debug mode disabled.\n");
#endif

#ifdef RELEASE_MODE
    printf("Release mode enabled.\n");
#endif

    return 0;
}