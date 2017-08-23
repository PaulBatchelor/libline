@* The Point. The point is the atomic value used inside of libline. 

@<Top@>+= @<The Point@>

@ A libline point can be best thought of as a line chunk going from
point A to point B over a given duration in seconds.

@<The Point@>+=
struct ll_point {
    ll_flt A;
    ll_flt dur;
    ll_flt *B;
};

@ The size of the point struct.

@<The Point@>+=
size_t ll_point_size(void)
{
    return sizeof(ll_point);
}

@ Initialization. Add some words here.

@<The Point@>+=
void ll_point_init(ll_point *pt)
{
    pt->A = 1.0; /* A reasonable default value */
    pt->dur = 1.0; /* A one-second duration by default */
    pt->B = &pt->A; /* Point B points to point A by default */
}

@ Set the initial "A" value. 
@<The Point@>+=
void ll_point_value(ll_point *pt, ll_flt val)
{

    pt->A = val;
}

@ This sets the point of the "B" value. Note that this is a pointer value.

@<The Point@>+=
void ll_point_next_value(ll_point *pt, ll_flt *val)
{
    pt->B = val;
}

@ Set the point duration. 
@<The Point@>+=
void ll_point_dur(ll_point *pt, ll_flt dur)
{
    pt->dur = dur;
}
