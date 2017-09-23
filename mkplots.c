/* mkplots.c
 *
 * An example C program which generates XY plot data designed to be used with 
 * Runt, a stack based programming language. 
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include "line.h"

#define PIXELS_PER_SECOND 100 
#define WIDTH 400
#define SCALE 200

void draw_line(FILE *fp, ll_line *line)
{
    unsigned int i;
    ll_flt val;

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

    fprintf(fp, "done\n");
}

void draw_dots(FILE *fp, ll_line *line)
{
    unsigned int i;
    ll_flt val;
    ll_point *pt;
    ll_point *next;
    ll_flt t;

    pt = ll_line_top_point(line);
    t = 0;
    for(i = 0; i < ll_line_npoints(line); i++) {
        next = ll_point_get_next_point(pt);
        /* flip the Y value to make origin bottom left */
        val = 1 - val;
        fprintf(fp, "%g %g dot\n", t * PIXELS_PER_SECOND, val * SCALE);
        t += ll_point_A(pt);
        pt = next;
    }
}

void line_1()
{
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

    draw_line(fp, line);
    draw_dots(fp, line);

    fclose(fp);
    ll_line_free(line);
    free(line);
}

void line_2()
{
    FILE *fp;

    ll_line *line; 
    ll_point *pt;

    fp = fopen("line_2.rnt", "w");
    line = malloc(ll_line_size());
    ll_line_init(line, PIXELS_PER_SECOND);
    pt = ll_line_append(line, 0.f, 4.f);
    ll_exppoint(pt, 2.f);
    ll_line_append(line, 1.f, 1.f);
    ll_line_done(line);

    draw_line(fp, line);
    draw_dots(fp, line);

    fclose(fp);
    ll_line_free(line);
    free(line);
}

void line_3()
{
    FILE *fp;

    ll_line *line; 
    ll_point *pt;

    fp = fopen("line_3.rnt", "w");
    line = malloc(ll_line_size());
    ll_line_init(line, PIXELS_PER_SECOND);
    pt = ll_line_append(line, 0.f, 4.f);
    ll_exppoint(pt, -4.f);
    ll_line_append(line, 1.f, 1.f);
    ll_line_done(line);

    draw_line(fp, line);
    draw_dots(fp, line);

    fclose(fp);
    ll_line_free(line);
    free(line);
}

int main()
{
    line_1();
    line_2();
    line_3();
    return 0;
}
