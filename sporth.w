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
@<The Sporth Unit Generators@>@/
void ll_sporth_ugen(ll_lines *l, plumber_data *pd, const char *ugen)
{
    plumber_ftmap_add_function(pd, ugen, sporth_ll, l);
}

@ |ll_sporth_line| registers a line as a named variable.

@<Sporth@>+=
ll_line * ll_sporth_line(ll_lines *l, plumber_data *pd, const char *name)
{
    ll_line *ln;
    SPFLOAT *val;

    ll_lines_append(l, &ln, NULL);

    plumber_create_var(pd, name, &val);
    ll_line_bind_float(ln, val);

    return ln;
}

@ The following is the Sporth unit generator 
callback used inside of Sporth. 
@<The Sporth Unit Generators@>+=
static int sporth_ll(plumber_data *pd, sporth_stack *stack, void **ud)
{
    ll_lines *l;
    l = *ud;
    if(pd->mode == PLUMBER_COMPUTE) ll_lines_step(l);
    return PLUMBER_OK;
}

@ Triggers in Sporth can be leveraged to schedule lines. After creating a 
new line for Sporth to read via |ll_sporth_line|, a ugen can be created to 
reset that line with a trigger via |ll_line_reset|.

@<The Sporth Unit Generators@>+=
static int sporth_ll_reset(plumber_data *pd, sporth_stack *stack, void **ud)
{
    ll_line *ln;
    SPFLOAT tick;
    ln = *ud;
    switch(pd->mode) {
        case PLUMBER_COMPUTE:
            tick = sporth_stack_pop_float(stack);
            if(tick) {
                ll_line_reset(ln);
            }
            break;
        case PLUMBER_CREATE:
        case PLUMBER_INIT:
            sporth_stack_pop_float(stack);
            break;
    }
    return PLUMBER_OK;
}

@ The ugen function must be bound to a named ftable in Sporth, where the user
data is the line.

@<Sporth@>+=

void ll_sporth_reset_ugen(ll_lines *l, plumber_data *pd, const char *ugen)
{
    ll_line *ln;
    ln = ll_lines_current_line(l);
    plumber_ftmap_add_function(pd, ugen, sporth_ll_reset, ln);
}

