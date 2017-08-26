@** Lines in Sporth. An optional feature of this line library is to have hooks
into the Sporth programming language via the Sporth API. 

@<Top@>+=
#ifdef LL_SPORTH
@<Sporth@>
#endif

@ In order to use Lines in Sporth, it needs to
be registered as a Sporth unit generator. This unit generator will handle 
initialization and tear-down of |ll_lines|, as well as step through all 
the lines at every sample. This unit generator should be instantiated exactly
once at the top of the Sporth patch.

@<Sporth@>+=
@<The Sporth Unit Generator@>@/
void ll_sporth_ugen(ll_lines *l, plumber_data *pd, const char *ugen)
{
    plumber_ftmap_add_function(pd, ugen, sporth_ll, l);
}

@ |ll_sporth_line| registers a line as a named variable.

@<Sporth@>+=
ll_line * ll_sporth_line(ll_lines *l, plumber_data *pd, const char *name)
{
    ll_line *ln;
    ll_flt *val;

    ll_lines_append(l, &ln, &val);

    plumber_ftmap_delete(pd, 0);
    plumber_ftmap_add_userdata(pd, name, val);
    plumber_ftmap_delete(pd, 1);
    return ln;
}

@ The following is the Sporth unit generator 
callback used inside of Sporth. 
@<The Sporth Unit Generator @>+=
static int sporth_ll(plumber_data *pd, sporth_stack *stack, void **ud)
{
    ll_lines *l;
    l = *ud;
    if(pd->mode == PLUMBER_COMPUTE) ll_lines_step(l);
    return PLUMBER_OK;
}

