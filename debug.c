#include <stdio.h>
#include <stdlib.h>
#include <soundpipe.h>
#include "line.h"

typedef struct {
    sp_ftbl *ft;
    sp_fosc *fm;
    ll_line *l;
    ll_lines *lines;
    ll_flt *val;
    ll_flt *indx;
} user_data;

static void process(sp_data *sp, void *udata)
{
    SPFLOAT s_osc;
    user_data *ud;
    ud = udata;

    ll_lines_step(ud->lines);
    ud->fm->freq = *ud->val;
    ud->fm->indx = *ud->indx;
    sp_fosc_compute(sp, ud->fm, NULL, &s_osc);
    sp_out(sp, 0, s_osc);
}

static void process_sporth(sp_data *sp, void *ud)
{
    plumber_data *pd;

    pd = ud;

    plumber_compute(pd, PLUMBER_COMPUTE);

    sp_out(sp, 0, sporth_stack_pop_float(&pd->sporth.stack));

}

int test_1(int argc, char **argv[])
{
    sp_data *sp;
    user_data ud;
    ll_line *line;
    ll_lines *lines;
    ll_point *pt;
    ll_line *l_index;

    sp_create(&sp);
    sp->sr = 44100;

    sp_ftbl_create(sp, &ud.ft, 8192);
    sp_gen_sine(sp, ud.ft);
    sp_fosc_create(&ud.fm);
    sp_fosc_init(sp, ud.fm, ud.ft);

    ud.lines = malloc(ll_lines_size());
    lines = ud.lines;
    ll_lines_init(ud.lines, sp->sr);
    ll_lines_append(lines, &ud.l, &ud.val);

    line = ud.l;
    pt = ll_line_append(line, 440.0, 1.0);
    ll_linpoint(pt);
    pt = ll_line_append(line, 880.0, 0.5);
    ll_linpoint(pt);
    pt = ll_line_append(line, 300.0, 0.9);
    ll_linpoint(pt);

    ll_line_done(line);

    ll_lines_append(lines, &l_index, &ud.indx);
    pt = ll_line_append(l_index, 0, 3.0);
    ll_linpoint(pt);
    pt = ll_line_append(l_index, 6.7, 1.0);
    ll_linpoint(pt);
    ll_line_done(l_index);

    sp_process(sp, &ud, process);

    ll_lines_free(lines);
    free(lines);

    sp_ftbl_destroy(&ud.ft);
    sp_fosc_destroy(&ud.fm);
    sp_destroy(&sp);
    return 0;
}

int test_sporth(int argc , char *argv[])
{
    sp_data *sp;
    ll_lines *lines;
    plumber_data pd;

    sp_create(&sp);
    sp->sr = 44100;
    pd.sp = sp;

    lines = malloc(ll_lines_size());
    ll_lines_init(lines, sp->sr);


    /* register plumber */

    plumber_register(&pd);
    plumber_init(&pd);
    ll_sporth_ugen(lines, &pd, "ll");

    ll_sporth_line(lines, &pd, "freq");
    ll_add_linpoint(lines, 440, 1.0);
    ll_add_linpoint(lines, 880, 0.5);
    ll_add_linpoint(lines, 300.0, 0.9);
    ll_end(lines);

    ll_sporth_line(lines, &pd, "index");
    ll_add_linpoint(lines, 0, 3.0);
    ll_add_linpoint(lines, 6.7, 1.0);
    ll_end(lines);


    /* parse sporth string */

    plumber_parse_string(&pd, "_ll fe _freq get 0.3 1 1 _index get fm ");
    plumber_compute(&pd, PLUMBER_INIT);

    sp_process(sp, &pd, process_sporth);

    ll_lines_free(lines);
    free(lines);
    

    plumber_clean(&pd);
    sp_destroy(&sp);
    return 0;
}

int main(int argc, char *argv[])
{
    return test_sporth(argc, argv);
}
