@** Exponential Points.

@<Top@> += 
@<Exponential Point@>

@* Exponential Point Data. 

@<Exponential Point@>+=

typedef struct {
    SPFLOAT curve;
} exppoint;

@ This function sets up the exponential point data struct |exppoint|.
@<Exponential Point@>+=
@<Private Functions For Exponential Points@>
void ll_exppoint(ll_point *pt, ll_flt curve)
{
    exppoint *ep;
    ep = ll_point_malloc(pt, sizeof(exppoint));
    ep->curve = curve;
    ll_point_cb_step(pt, exppoint_step);
    ll_point_data(pt, ep);
    ll_point_cb_destroy(pt, exppoint_destroy);
}


@ The exponential step function uses the following equation:

$$ y = A + (B - A) \cdot (1 - e^{tc/(N - 1)}) / (1 - e^{c}) $$

Where:

$y$ is the output value.

$A$ is the start value.

$B$ is the end value.

$t$ is the current sample position.

$N$ is the duration of the line segment, in samples.

$c$ determines the slope of the curve. When $c = 0$, a linear line is produced. 
When $c > 0$, the curve slowly rises (concave) and decays (convex). 
When $c < 0$, the curve quickly rises (convex) and decays (concave).

@<Private Functions For Exponential Points@>+=
static ll_flt exppoint_step(ll_point *pt, void *ud, UINT pos, UINT dur)
{
    exppoint *ep;
    ll_flt val;

    ep = ud;

    val = ll_point_A(pt) + 
        (ll_point_B(pt) - ll_point_A(pt)) *
        (1 - exp(pos * ep->curve / (dur - 1))) / (1 - exp(ep->curve));
    return val;
}

@ 

@<Private Functions For Exponential Points@>+=
static void exppoint_destroy(void *ud, void *ptr)
{
    ll_point *pt;
    pt = ud;
    ll_point_free(pt, ptr);
}

