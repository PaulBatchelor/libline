@ This document describes libline, a library for producing lines and automation
curves for audio-related purposes. Line segments produced are audio-rate and
sample accurate. Libline will is designed
to pair well with sound tools like Soundpipe and Sporth, where such gesture
facilities do not exist.

@c 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#ifdef LL_SPORTH_UGEN
#include "plumber.h"
#endif
#include "line.h"@/
@<Top@>@/

@i header
@i point
@i line
@i lines
@i linpoint
@i exppoint
@i bezier
@i tick 
@i mem
@i sporth
