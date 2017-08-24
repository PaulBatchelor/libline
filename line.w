@* The Line. A line is a sequence of points in time. A line smoothly steps
through the points with some sort of interpolation.

@<Top@> += @<The Line@>

@ Blah.

@<The Line@> += 
struct ll_line {
    ll_point *root;
    ll_point *last;
    int size;
};


