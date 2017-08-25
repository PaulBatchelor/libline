@* The Line. A line is a sequence of points in time. A line smoothly steps
through the points with some sort of interpolation.

@<Top@> += @<The Line@>

@ The line is mostly a linked list, with a root value, a pointer to the value
last appended, and the size.

@<The Line@> += 
struct ll_line {@/
    ll_point *root;
    ll_point *last;
    int size;
    int curpos; /* the current point position */

@ Since the line generated is a digital audio signal, it must have a 
sampling rate |sr|.

@<The Line@> += 
    int sr;

@ A counter variable is used as a sample-accurate timer to navigate between 
sequential points.

@<The Line@> += 
    unsigned int counter;

@ The duration of the current point is in stored in the variable |idur|. This 
unit of this duration is in whole-{\bf i}nteger samples, which is the 
justification for the "i" in the beginning of the variable.
@<The Line@> += 
    unsigned int idur;

@ The line interface can handle memory allocation internally. It does so
using callback interfaces for allocating and freeing memory. By default, these
functions are wrappers around the standard C |malloc| and |free| functions. 
@<The Line@> += 
    ll_cb_malloc malloc;
    ll_cb_free free;

@ The struct also has an entry for custom user data, defined as a void 
pointer |ud|.
@<The Line@> += 
    void *ud;

@ The variable |end| is a boolean value that is set when the line reaches
the end. 
@<The Line@> += 
    int end;
@/};

@ The size of |ll_line| is implemented as a function.
@<The Line@> += 
size_t ll_line_size(void)
{
    return sizeof(ll_line);
}


@ After the line is allocated, it must be initialized. A line starts out
with zero points. Pointers are set to be |NULL| ({\tt NULL}). The 
memory allocation functions are set to defaults.

@<The Line@> += 
void ll_line_init(ll_line *ln, int sr)
{
    ln->root = NULL;
    ln->last = NULL;
    ln->size = 0;
    ln->sr = sr;
    ln->malloc = ll_malloc;
    ln->free = ll_free;
    ln->idur = 0;
    ln->counter = 0;
    ln->curpos = 0;
    ln->end = 0;
}

@ Points are added to a line in chronological order because they are appended
to the end of a linked list. 

A new line that zero points must set the root
of the linked list with the added point.  For the case when there are already 
items populated in the linked list, the last pointer entry is used. The "next" 
entry in this pointer is set to be the appended point. The "B" value of the
last point is set to point to the "A" value of the appended point.

After the point is appended, the last point is set to be the appended point.
The size of the line is incremented by 1.

@<The Line@> += 
void ll_line_append_point(ll_line *ln, ll_point *p)
{
    if(ln->size == 0) {
        ln->root = p;
    } else {
        ll_point_set_next_point(ln->last, p);
        ll_point_set_next_value(ln->last, ll_point_get_value(p));
    }
    ln->last = p;
    ln->size++;
}


@ The function |ll_line_append_point| assumes that memory is already allocated.
This, however, is a very inconvenient burden for the programmer to keep
track of. The function |ll_line_append| wraps around 
|ll_line_append_point| and uses the internal memory functions to allocate
memory.

@<The Line@> += 
ll_point * ll_line_append(ll_line *ln, ll_flt val, ll_flt dur)
{
    ll_point *pt;

    pt = ln->malloc(ln->ud, ll_point_size());

    ll_point_init(pt);
    ll_point_value(pt, val);
    ll_point_dur(pt, dur);

    ll_line_append_point(ln, pt);

    return pt;
}

@ All things that must be allocated internally must then be freed using 
the function |ll_line_free|. This function essentially walks through the 
linked list and frees all the points. 
@<The Line@> += 
void ll_line_free(ll_line *ln)
{
    ll_point *pt;
    ll_point *next;
    unsigned int i;
   
    pt = ln->root;
    for(i = 0; i < ln->size; i++) {
        next = ll_point_get_next_point(pt);
        ln->free(ln->ud, pt);
        pt = next;
    }
}

@ This is the top-level function called inside the audio callback. It computes
the line. This is done through both ticking down a timer and walking
through the linked list. 

First, there is a check to see if the counter has ticked to zero. 
If it has, the line goes to the next point in the next list. 

If there are no points left in the list, the line has ended, and the output 
value is the "A" value of the point.

If the line is not at the end, then it will step to the next point in the 
linked list. The timer is then reset, and the current position is incremented.

@<The Line@> += 
ll_flt ll_line_step(ll_line *ln)
{
    /* TODO: implement the rest of me please */
    UINT dur;
    UINT pos;

    if(ln->end) {
        return ll_point_A(ln->last);    
    }

    if(ln->counter == 0) {
        if(ln->curpos < ln->size) {
            ln->last = ll_point_get_next_point(ln->last);
            ln->idur = ll_point_get_dur(ln->last) * ln->sr;
            ln->counter = ln->idur;
            ln->curpos++;
        } else {
            ln->end = 1;
        }
    }

    dur = ln->idur;
    pos = dur - ln->counter;
    ln->counter--;
    return ll_point_step(ln->last, pos, dur);;
}

@ The functions described below are the default malloc and free functions
used internally by the line function. They are wrappers around the default
C libraries. 

@ Sometimes it is can be useful to print points in a line. |ll_line_print|  
does just that, walking through the list and printing the values.

@<The Line@> += 
void ll_line_print(ll_line *ln)
{
    ll_point *pt;
    ll_point *next;
    unsigned int i;
    ll_flt *val;
   
    pt = ln->root;
    printf("there are %d points...\n", ln->size);
    for(i = 0; i < ln->size; i++) {
        next = ll_point_get_next_point(pt);
        val = ll_point_get_value(pt);
        printf("point %d: dur %g, val %g\n", 
            i,
            ll_point_get_dur(pt),
            *val
            );

        pt = next;
    }
}

@ Once points are doing being added to a line, it must be rewound and reset
to the beginning.

@<The Line@>+=
void ll_line_done(ll_line *ln)
{
    ln->curpos = 0;
    ln->last = ln->root;
    ln->idur = ll_point_get_dur(ln->root) * ln->sr;
    ln->counter = ln->idur;
    ln->end = 0;
}
