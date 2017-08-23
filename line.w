@ This document describes libline, a library for producing lines and automation
curves for audio-related purposes. Line segments produced are audio-rate and
sample accurate. In the visual domain, lines can be used to very concisely 
describe change over time. In the sound domain, line segments can be mapped to
sonic parameters that *do* change over time. The line, in this regard, can be
thought of as a high-level gesture for computer music. Libline will be designed
to pair well with sound tools like Soundpipe and Sporth, where such a gesture
facility does not exist. 

Things have to start somewhere, so here is program that says hello. The
|BUILD_MAIN| macro is set via a compiler flag. As this is intended to be a
library, it is favorable to turn on presence of the main function only when
it is used for debugging purposes. 
@c 
#ifdef BUILD_MAIN
#include <stdio.h>
#include "line.h"
int main()
{
    printf("Hello libline.\n");
    return 0;
}
#endif

@i header
