@ This document describes libline, a library for producing lines and automation
curves for audio-related purposes. Line segments produced are audio-rate and
sample accurate. In the visual domain, lines can be used to very concisely 
describe change over time. In the sound domain, line segments can be mapped to
sonic parameters that *do* change over time. The line, in this regard, can be
thought of as a high-level gesture for computer music. Libline will be designed
to pair well with sound tools like Soundpipe and Sporth, where such a gesture
facility does not exist. 

@c 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "line.h"@/
@<Top@>@/

@i header
@i point
@i line
@i lines
@i linpoint
@i exppoint
@i mem
@i sporth
