@** Tick. In Sporth, a tick is a single non-zero sample used as a trigger signal
for trigger-based unit generators. Ticks can be used as a kind of line to 
produce these kind of control signals. 

@<Top@> += @<Tick@>

@ The tick step function will only produce a non-zero value if the position
is zero.

@<Tick@> += 

static ll_flt tick_step(ll_point *pt, void *ud, UINT pos, UINT dur)
{
    if(pos == 0) {
        return 1.0;
    } else {
        return 0.0;
    }
}

@ The tick initialization function binds |tick_step| to the step function.

@<Tick@> += 
void ll_tick(ll_point *pt)
{
    ll_point_cb_step(pt, tick_step);
}
