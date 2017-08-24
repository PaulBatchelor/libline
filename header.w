@* The header file. This library has a single header file, containing all
the necessary struct and function definitions for the API. This file should be
installed alongside the generated library file in order to be used with other
programs.
@(line.h@>=
#ifndef LINE_H
#define LINE_H
@<Header Data@>@/
#endif

@ Line values use floating point precision. This precision is set using the 
macro definition |ll_flt| rather than a type declaration. By default, it is a 
floating point value. However, this value can be overridden at compile time. 
@<Header Data@>+=
#ifndef LLFLOAT
typedef float ll_flt;
#else 
typedef LLFLOAT ll_flt;
#endif
@ The core unit is a point, which has two fundamental properties: a value, and
a duration. 
@<Header Data@>+=
typedef struct ll_point ll_point;

@ Points are tacked on sequentially, and then they are interpolated with some
specified behavior. This collection of points forms a line. 
@<Header Data@>+=
typedef struct ll_line ll_line;

@ Memory allocation functions are needed in some situations. By default, these
are just wrappers around malloc free. However, this is designed so that
they be overridden use custom memory handling functions.

@<Header Data@>+=
typedef void * (* ll_cb_malloc)(void *ud, size_t size);
typedef void (* ll_cb_free)(void *ud, void *ptr);

@ Compilers are unable to tell what size opaque pointers are, so functions
need to be written which return the size. This also shifts the burden of 
allocation onto the user. 
@<Header Data@>+=
size_t ll_line_size(void);
size_t ll_point_size(void);

@ Once memory is allocated, data types need to be initialized. These functions
are safe to call multiple times, since no memory allocation happens here. After
this, things can be done to the structs.
@<Header Data@>+=
void ll_point_init(ll_point *pt);
void ll_line_init(ll_line *ln, int sr);

@ Points have two fundamental properties: a value, and a duration for that 
value. 
@<Header Data@>+=
void ll_point_value(ll_point *pt, ll_flt val);
void ll_point_dur(ll_point *pt, ll_flt dur);
ll_flt ll_point_get_dur(ll_point *pt);

@ Points have a {\it next} value, referencing the next point value.
@<Header Data@>+=
void ll_point_set_next_value(ll_point *pt, ll_flt *val);

@ In order to set the next value, there must be a function which is able
to return the memory address of the previous point value (not the next value).
@<Header Data@>+=
ll_flt * ll_point_get_value(ll_point *pt);

@ Points also act as a linked list, so they also contain a pointer to the next
entry.
@<Header Data@>+=
void ll_point_set_next_point(ll_point *pt, ll_point *next);

@ The linked list must be read as well written to, so a function is needed to
retrieve the next point in the linked list.

@<Header Data@>+=
ll_point * ll_point_get_next_point(ll_point *pt);

@ A point, once it is set, can be tacked on to the end of a line. The value 
of this point becomes the end value of the previous point. 
@<Header Data@>+=
void ll_line_append_point(ll_line *ln, ll_point *p);

@ The function |ll_line_append_point| assumes that points will be allocated and
freed by the user. However, this is often not an ideal situation. The line
has the ability to handle memory internally. This function will return a 
pointer to the value, for cases when further manipulations need to happen
to the point.

@<Header Data@>+=
ll_point * ll_line_append(ll_line *ln, ll_flt val, ll_flt dur);

@ All things that must be allocated must be freed as well. This function
frees all data allocated from functions like |ll_line_append|. 

@<Header Data@>+=
void ll_line_free(ll_line *ln);

@ For situations where custom memory allocation is desired, the default 
callbacks for memory can be overridden.
@<Header Data@>+=
void ll_line_mem_callback(ll_line *ln, ll_cb_malloc m, ll_cb_free f);


@ Once all points have been added, the line is finalized and rewound to the
beginning, where it can be ready to be computed as an audio-rate signal 
in time.

@<Header Data@>+=
void ll_line_rewind(ll_line *ln);
void ll_line_done(ll_line *ln);


@ The top-level function used is the step function. This function gets every
sample inside of the audio loop, generating a single sample and moving forward
in time by a single sample.
@<Header Data@>+=
ll_flt ll_line_step(ll_line *ln);


@ This function will print all the points in a given line.
@<Header Data@>+=
void ll_line_print(ll_line *ln);
