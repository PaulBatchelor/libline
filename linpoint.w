@** Linear Points. Linear points create a straight line from point A to point B. 

@<Top@> += 
@<Linear Point@>

@* Linear Point Data.
@ The main data structure for a linear point contains an incrementor value 
|inc| and an accumulator value |acc|. 

@<Linear Point@> +=
typedef struct {
    ll_flt inc;
    ll_flt acc;
} linpoint;

@* Linear Point Setup.
@ The setup function for linpoint allocates the memory needed for the 
|linpoint| struct, then binds it and the step callback to the point.

@<Linear Point@>+=
@<Private Functions for Linear Point@>@/
void ll_linpoint(ll_point *pt)
{
    linpoint *lp;
    lp = ll_point_malloc(pt, sizeof(linpoint));
    ll_point_cb_step(pt, linpoint_step);
    ll_point_data(pt, lp);
    ll_point_cb_destroy(pt, ll_linpoint_destroy);
}

@* The Linear Step Function.
@ The linear step function is reasonably straightforward. When the line 
position is zero, the incrementor and acculumaltor values are implemented. 
Next, the current value of the acculumator is returned and then incremented.

@<Private Functions for Linear Point@>+=

static ll_flt linpoint_step(ll_point *pt, void *ud, UINT pos, UINT dur)
{
    linpoint *lp;
    ll_flt val;

    lp = ud;

    if(pos == 0) {
        lp->acc = ll_point_A(pt);
        lp->inc = (ll_point_B(pt) - ll_point_A(pt)) / dur;
    }

    val = lp->acc;
    lp->acc += lp->inc;
    return val;
}

@* Freeing Linear Point Memory.
@ The destroy function for linpoint destroys the memory previously allocated.
@<Private Functions for Lin...@>+=
static void ll_linpoint_destroy(void *ud, void *ptr)
{
    ll_point *pt;
    pt = ud;
    ll_point_free(pt, ptr);
}

