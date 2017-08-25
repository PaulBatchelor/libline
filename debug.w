@* Debug. This is a little program used for debugging and testing. 

@(debug.c@>=
@<The Debug Program@>

@ 
@<The Debug Program@>=
#include <stdio.h>
#include <stdlib.h>
#include "line.h"
int main(int argc, char *argv[])
{@/
    ll_line *line;@/
    line = malloc(ll_line_size());@/
    ll_line_init(line, 44100);@/
    ll_line_append(line, 440.0, 2.0);@/
    ll_line_append(line, 880.0, 4.0);@/
    ll_line_done(line);@/
    ll_line_print(line);@/
    ll_line_free(line);@/
    free(line);@/
    return 0;@/
}
