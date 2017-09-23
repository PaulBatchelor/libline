/* mkplt.c
 *
 * An example C program which generates XY plot data designed to be used with 
 * Runt, a stack based programming language. 
 *
 * x y pt
 *
 * where:
 *
 * x is the x coordinate
 *
 * y is the y coordinate 
 *
 * "pt" is a word that will need to be in Runt in charge of drawing the
 * point data.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include "line.h"

#define PIXELS_PER_SECOND 100 
#define WIDTH 400
#define SCALE 200

void line_1()
{
    unsigned int i;
    ll_flt val;
    FILE *fp;

    ll_line *line; 
    ll_point *pt;

    fp = fopen("line_1.rnt", "w");
    line = malloc(ll_line_size());
    ll_line_init(line, PIXELS_PER_SECOND);
    pt = ll_line_append(line, 0.f, 4.f);
    ll_linpoint(pt);
    ll_line_append(line, 1.f, 1.f);
    ll_line_done(line);

    for(i =0; i <= WIDTH; i++) {
        val = ll_line_step(line);
        /* flip the Y value to make origin bottom left */
        val = 1 - val;
        if(i == 0) {
            fprintf(fp, "%d %g mv\n", i, val*SCALE);
        } else {
            fprintf(fp, "%d %g pt\n", i, val*SCALE);
        }
    }

    fclose(fp);
    ll_line_free(line);
    free(line);
}

int main()
{
    line_1();
    return 0;
}
