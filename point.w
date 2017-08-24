@* The Point. The point is the atomic value used inside of libline. 

@<Top@>+= @<The Point@>

@ A libline point can be best thought of as a line chunk going from
point A to point B over a given duration in seconds.

@<The Point@>+=
struct ll_point {@/
    ll_flt A;
    ll_flt dur;
    ll_flt *B;

@ The line is built around a linked list data structure, so the struct has
a reference to the next entry in the list. 

@<The Point@>+=
    ll_point *next;@/
};

@ The size of the point struct is implemented as a function.

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
void ll_point_set_next_value(ll_point *pt, ll_flt *val)
{
    pt->B = val;
}

@ Set the point duration. 
@<The Point@>+=
void ll_point_dur(ll_point *pt, ll_flt dur)
{
    pt->dur = dur;
}

@ The following function is used to set the next entry in the linked list.
@<The Point@>+=
void ll_point_set_next_point(ll_point *pt, ll_point *next)
{
    pt->next = next;
}

@ The following function is used to retrive the next entry in the linked list.
@<The Point@>+=
ll_point * ll_point_get_next_point(ll_point *pt)
{
    return pt->next;
}

@ In order to set a B value, there needs to be a way to get the memory address
of another points A value. This function returns the memory address of a points
A value.
@<The Point@>+=
ll_flt * ll_point_get_value(ll_point *pt)
{
    return &pt->A;
}
