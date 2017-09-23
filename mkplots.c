/* mkplt.c
 *
 * An example C program which generates XY plot data designed to be used with 
 * Runt, a stack based programming language. 
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "line.h"

#define PIXELS_PER_SECOND 100 
#define WIDTH 400
#define SCALE 200

void render_dots(FILE *fp, ll_line *line)
{
    unsigned int i;
    ll_point *pt;
    ll_point *next;
    ll_flt val;
    ll_flt t;
    /* render dots */
    t = 0;
    pt = ll_line_top_point(line);
    for(i = 0; i < ll_line_npoints(line); i++) {
        next = ll_point_get_next_point(pt);
        val = 1 - ll_point_A(pt);
        fprintf(fp, "%g %g dot\n", floor(t * PIXELS_PER_SECOND), val*SCALE);
        t += ll_point_get_dur(pt);
        pt = next;
    }
}

void render_line(FILE *fp, ll_line *line)
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

    /* done plotting line */

    fprintf(fp, "done\n");
}

/* straight line */

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

    render_line(fp, line);
    render_dots(fp, line);

    fclose(fp);
    ll_line_free(line);
    free(line);
}

/* curved exponential: concave */

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

    render_line(fp, line);
    render_dots(fp, line);

    fclose(fp);
    ll_line_free(line);
    free(line);
}

/* curved exponential: convex */

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

    render_line(fp, line);
    render_dots(fp, line);
    
    fclose(fp);
    ll_line_free(line);
    free(line);
}

/* steps */
void line_4()
{
    FILE *fp;

    ll_line *line; 

    fp = fopen("line_4.rnt", "w");
    line = malloc(ll_line_size());
    ll_line_init(line, PIXELS_PER_SECOND);

    ll_line_append(line, 0.f, 1.f);
    ll_line_append(line, 0.2f, 1.5f);
    ll_line_append(line, 1.0f, 0.5f);
    ll_line_append(line, 0.5f, 1.f);

    ll_line_done(line);

    render_line(fp, line);
    render_dots(fp, line);
    
    fclose(fp);
    ll_line_free(line);
    free(line);
}

/* linear lines: many points */
void line_5()
{
    FILE *fp;

    ll_line *line; 
    ll_point *pt;

    fp = fopen("line_5.rnt", "w");
    line = malloc(ll_line_size());
    ll_line_init(line, PIXELS_PER_SECOND);

    pt = ll_line_append(line, 0.f, 0.5f);
    ll_linpoint(pt);
    pt = ll_line_append(line, 1.0f, 0.5f);
    ll_linpoint(pt);
    pt = ll_line_append(line, 0.3f, 1.5f);
    ll_linpoint(pt);
    pt = ll_line_append(line, 0.9f, 1.5f);
    ll_linpoint(pt);
    pt = ll_line_append(line, 0.1f, 1.5f);

    ll_line_done(line);

    render_line(fp, line);
    render_dots(fp, line);
    
    fclose(fp);
    ll_line_free(line);
    free(line);
}

/* exponential lines: many points */
void line_6()
{
    FILE *fp;

    ll_line *line; 
    ll_point *pt;

    fp = fopen("line_6.rnt", "w");
    line = malloc(ll_line_size());
    ll_line_init(line, PIXELS_PER_SECOND);

    pt = ll_line_append(line, 0.f, 0.5f);
    ll_exppoint(pt, -3.f);
    pt = ll_line_append(line, 1.0f, 0.5f);
    ll_exppoint(pt, 2.f);
    pt = ll_line_append(line, 0.3f, 1.5f);
    ll_exppoint(pt, 10.f);
    pt = ll_line_append(line, 0.9f, 1.5f);
    ll_exppoint(pt, -4.f);
    pt = ll_line_append(line, 0.1f, 1.5f);

    ll_line_done(line);

    render_line(fp, line);
    render_dots(fp, line);
    
    fclose(fp);
    ll_line_free(line);
    free(line);
}

/* mixed lines: many points */
void line_7()
{
    FILE *fp;

    ll_line *line; 
    ll_point *pt;

    fp = fopen("line_7.rnt", "w");
    line = malloc(ll_line_size());
    ll_line_init(line, PIXELS_PER_SECOND);

    ll_line_append(line, 0.f, 0.1f);
    ll_line_append(line, 0.1f, 0.1f);
    ll_line_append(line, 0.2f, 0.1f);
    pt = ll_line_append(line, 0.1f, 0.1f);
    ll_exppoint(pt, 10.f);
    ll_line_append(line, 0.5f, 0.1f);
    pt = ll_line_append(line, 1.0f, 0.5f);
    ll_exppoint(pt, 2.f);
    pt = ll_line_append(line, 0.7f, 1.2f);
    ll_linpoint(pt);
    pt = ll_line_append(line, 0.6f, 1.7f);
    ll_exppoint(pt, -3.f);
    pt = ll_line_append(line, 0.8f, 1.5f);
    ll_linpoint(pt);

    ll_line_done(line);

    render_line(fp, line);
    render_dots(fp, line);
    
    fclose(fp);
    ll_line_free(line);
    free(line);
}


int main()
{
    line_1();
    line_2();
    line_3();
    line_4();
    line_5();
    line_6();
    line_7();
    return 0;
}
