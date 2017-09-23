@** Bezier Points. Bezier points are used to create quadratic bezier curves.

@<Top@> +=
@<Bezier Point@>

@* Bezier Point Data. More to write here.

@<Bezier Point@>+=
typedef struct {
    ll_flt cx;
    ll_flt cy;
} bezierpt;

@* Bezier Setup. The setup function for producing a bezier curve is
|ll_bezier|. It takes in two arguments for a control point. The X value is
normalized between 0 and 1. 


@<Bezier Point@>+=
@<Static Functions for Bezier Point@>@/
void ll_bezier(ll_point *pt, ll_flt cx, ll_flt cy)
{
    bezierpt *b;
    b = ll_point_malloc(pt, sizeof(bezierpt));
    b->cx = cx;
    b->cy = cy;
    ll_point_cb_step(pt, bezier_step);
    ll_point_data(pt, b);
    ll_point_cb_destroy(pt, bezier_destroy);
}

@ This is the linear step function. 
@<Static Functions for Bezier Point@>+=
@<Quadratic Equation Solver@>@/
static ll_flt bezier_step(ll_point *pt, void *ud, UINT pos, UINT dur)
{
    bezierpt *bez;
    ll_flt x[3];
    ll_flt y[3];
    ll_flt t;
    ll_flt val;

    bez = ud;
    x[0] = 0.f; /* always zero */
    x[1] = bez->cx * dur;
    x[2] = dur;

    y[0] = ll_point_A(pt);
    y[1] = bez->cy;
    y[2] = ll_point_B(pt);

    t = find_t(x[0], x[1], x[2], pos);
    val = 
        (1.0 - t)*(1.0 - t)*y[0] + 
        2.0*(1.0 - t)*t*y[1] +
        t*t*y[2];

    return val;
}

@
@<Quadratic Equation Solver@>+=
static ll_flt quadratic_equation(ll_flt a, ll_flt b, ll_flt c)
{
    ll_flt det; /* determinant */

    det = b*b - 4*a*c;
    if(det >= 0) {
        return ((-b + sqrt(det)) / (2.0 * a));
    } else {
        return 0;
    }
}

@
@<Quadratic Equation Solver@>+=
static ll_flt find_t(ll_flt x1, ll_flt x2, ll_flt x3, int x)
{
    ll_flt a;
    ll_flt b;
    ll_flt c;

    a = (x1 - 2.0*x2 + x3);
    b = 2.0*(-x1 + x2);
    c = x1 - x;

    if(a) {
        return quadratic_equation(a, b, c);
    } else {
        return (x - x1) / b;
    }

}



@ The bezier destroy function frees the data allocated by the bezier.
@<Static Functions for Bezier Point@>+=
static void bezier_destroy(void *ud, void *ptr)
{
    ll_point *pt;
    pt = ud;
    ll_point_free(pt, ptr);
}
