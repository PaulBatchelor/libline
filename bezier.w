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

@ This is the bezier curve step function which computes a quadratic
bezier line. The quadratic equation for a Bezier curve is the following:

$$B(t) = (1 - t)^2 P_0 + 2(1 - t)tP_1 + t^2 P_2$$

Where $t$ is a normalized time value between 0 and 1, and $P_n$ refers to a 
2-dimensional point with a $(x,y)$ coordinate. 

The issue with the classic equation above is that the value is derived from
$t$, allowing $x$ to be fractional. This is problematic because the system 
implemented here is discrete, restricted to whole-integer values of $x$.

The solution to this problem is to rework the equation above to solve for $t$
in terms of the current sample position $x_n$. Once $t$ is found, it 
can be used to compute the result, which is the y component of the bezier 
curve in terms of t. The reworked bezier equation is touched upon in greater
detail in the |@<Quadratic Equation Solver@>| section.

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

@ The function below implements a quadratic equation solver for all 
real values. Imaginary values return a value of 0.
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

@ The Bezier x component $B_x$ can be rearranged to be a quadratic equation for 
$t$, given the x bezier control points $x_0$, $x_1$, and $x_2$, as well as 
the current sample position $x_n$. 

$$\eqalign{
    x_n &= (1 - t)^2 x_0 + 2(1 - t)tx_1 + t^2 x_2 \cr
        &= (1 - 2t + t^2)x_0 + (2t - 2t^2)x_1 + t^2x_2 \cr
        &= x_0 - 2tx_0 + t^2x_0 + 2tx_1 - 2t^2x_1 + t^2x_2 \cr
        &= (x_0 - 2x_1 + x_2)t^2 + 2(-x_0 + x_1)t + x_0 \cr
      0 &= (x_0 - 2x_1 + x_2)t^2 + 2(-x_0 + x_1)t + x_0 - x_n\cr
}$$

This yields the following $a$, $b$, and $c$ quadratic equation 
coefficients:
$$\eqalign{
    a &= x_0 - 2x_1 + x2, \cr
    b &= 2(-x_0 + x_1) \cr
    c &= x_0 - x_n \cr
}$$

Using those variables, the value of $t$ can be found if it is a real value.
@<Quadratic Equation Solver@>+=
static ll_flt find_t(ll_flt x0, ll_flt x1, ll_flt x2, int x)
{
    ll_flt a;
    ll_flt b;
    ll_flt c;

    a = (x0 - 2.0*x1 + x2);
    b = 2.0*(-x0 + x1);
    c = x0 - x;

    if(a) {
        return quadratic_equation(a, b, c);
    } else {
        return (x - x0) / b;
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
