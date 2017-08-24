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
#include <stdlib.h>
#ifdef BUILD_MAIN
#include <stdio.h>
#include "line.h"
int main()
{
    ll_line *line;
    line = malloc(ll_line_size());
    ll_line_init(line, 44100);
    ll_line_append(line, 1.0, 2.0);
    ll_line_append(line, 3.0, 4.0);
    ll_line_print(line);
    ll_line_free(line);
    free(line);
    return 0;
}
#endif
@<Top@>@/

@i header
@i point
@i line
@i mem
