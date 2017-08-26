#include <stdio.h>
#include <stdlib.h>
#include <soundpipe.h>
#include "line.h"

typedef struct {
    sp_ftbl *ft;
    sp_osc *osc;
    ll_line *l;
    ll_lines *lines;
    ll_flt *val;
} user_data;

static void process(sp_data *sp, void *udata)
{
    SPFLOAT s_osc;
    user_data *ud;
    ud = udata;

    ll_lines_step(ud->lines);
    ud->osc->freq = *ud->val;
    sp_osc_compute(sp, ud->osc, NULL, &s_osc);
    sp_out(sp, 0, s_osc);
}

int main(int argc, char *argv[])
{
    sp_data *sp;
    user_data ud;
    ll_line *line;
    ll_lines *lines;
    ll_point *pt;

    sp_create(&sp);
    sp->sr = 44100;

    sp_ftbl_create(sp, &ud.ft, 8192);
    sp_gen_sine(sp, ud.ft);
    sp_osc_create(&ud.osc);
    sp_osc_init(sp, ud.osc, ud.ft, 0.f);

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
    ll_line_print(line);

    sp_process(sp, &ud, process);

    ll_lines_free(lines);
    free(lines);

    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_destroy(&sp);
    return 0;
}
