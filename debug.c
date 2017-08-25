#include <stdio.h>
#include <stdlib.h>
#include <soundpipe.h>
#include "line.h"

typedef struct {
    sp_ftbl *ft;
    sp_osc *osc;
    ll_line *line;
} user_data;

static void process(sp_data *sp, void *udata)
{
    SPFLOAT s_osc;
    user_data *ud;
    ud = udata;

    ud->osc->freq = ll_line_step(ud->line);
    sp_osc_compute(sp, ud->osc, NULL, &s_osc);
    sp_out(sp, 0, s_osc);
}

int main(int argc, char *argv[])
{
    sp_data *sp;
    user_data ud;
    ll_line *line;
    sp_create(&sp);
    sp->sr = 44100;

    sp_ftbl_create(sp, &ud.ft, 8192);
    sp_gen_sine(sp, ud.ft);
    sp_osc_create(&ud.osc);
    sp_osc_init(sp, ud.osc, ud.ft, 0.f);

    ud.line = malloc(ll_line_size());
    line = ud.line;
    ll_line_init(line, sp->sr);
    ll_line_append(line, 440.0, 2.0);
    ll_line_append(line, 880.0, 4.0);
    ll_line_done(line);
    ll_line_print(line);

    sp_process(sp, &ud, process);

    ll_line_free(line);
    free(line);

    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_destroy(&sp);
    return 0;
}
