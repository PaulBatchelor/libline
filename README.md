# libline

A library for drawing sample-accurate lines and automation curves for 
computer-based music composition. 

## Compilation

To compile libline and the debug program, run:

    make

## Using CWEB

Pre-generated files are included in this repo CWEB is not required to compile 
libline. However, those wishing to regenerate the C code and produce the 
TeX-generated documentation can run:

    make USE_CWEB=1
