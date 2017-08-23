@* The header file. This library has a single header file, containing all
the necessary struct and function definitions for the API. This file should be
installed alongside the generated library file in order to be used with other
programs.
@(line.h@>=
#ifndef LINE_H
#define LINE_H
@<Header Data@>@/
#endif

@ The core unit is a point, which has two fundamental properties: a value, and
a duration. 
@<Header Data@>+=
typedef struct ll_point ll_point;

@ Points are tacked on sequentially, and then they interpolated with some
specified behavior. This collection of points forms a line. 
@<Header Data@>+=
typedef struct ll_line ll_line;

@ Compilers are unable to tell what size opaque pointers are, so functions
need to be written which return the size. This also shifts the burden of 
allocation onto the user. 
@<Header Data@>+=
size_t ll_line_size(void);
size_t ll_point_size(void);

@ Once memory is allocated, data types need to be initialized. These functions
are safe to call multiple times. 
@<Header Data@>+=
void ll_point_init(ll_point *pt);
void ll_line_init(ll_point *pt);
