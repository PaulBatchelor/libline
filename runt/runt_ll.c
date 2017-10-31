#include <stdio.h>
#include <runt.h>
#include <patchwerk.h>
#include <stdlib.h>
#include <soundpipe.h>
#include "line.h"
#include "runt_patchwerk.h"
#include "runt_ll.h"
typedef struct {
    pw_patch *patch;
    ll_lines *lines;
} runt_ll_d;

static void ll_define(
    runt_vm *vm,
    runt_ptr p,
    const char *str,
    runt_uint size,
    runt_proc proc
) 
{
    runt_cell *cell;
    runt_keyword_define(vm, str, size, proc, &cell);
    runt_cell_data(vm, cell, p);
}

static runt_int line_begin(runt_vm *vm, runt_ptr p)
{
    runt_ll_d *rll;

    rll = runt_to_cptr(p);

    ll_lines_append(rll->lines, NULL, NULL);

    return RUNT_OK;
}

static runt_int add_linpoint(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    ll_flt val;
    ll_flt dur;
    runt_ll_d *rll;
   
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    dur = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    val = s->f;
  
    rll = runt_to_cptr(p);

    ll_add_linpoint(rll->lines, val, dur);

    return RUNT_OK;
}

static runt_int add_exppoint(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    ll_flt val;
    ll_flt dur;
    ll_flt curve;
    runt_ll_d *rll;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    curve = s->f;
   
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    dur = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    val = s->f;
  
    rll = runt_to_cptr(p);

    ll_add_exppoint(rll->lines, val, dur, curve);

    return RUNT_OK;
}

static runt_int add_step(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    ll_flt val;
    ll_flt dur;
    runt_ll_d *rll;
   
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    dur = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    val = s->f;
  
    rll = runt_to_cptr(p);

    ll_add_step(rll->lines, val, dur);
    return RUNT_OK;
}

typedef struct {
   pw_cable *out;
   ll_line *line;
} rpw_node_ll;

static void compute(pw_node *node)
{
    int i;
    int blksize;
    SPFLOAT out;
    rpw_node_ll *ll;

    ll = pw_node_get_data(node);
    blksize = pw_node_blksize(node); 
    for(i = 0; i < blksize; i++) {
        out = ll_line_step(ll->line);
        pw_cable_set(ll->out, i, out);
    }
}

static void destroy(pw_node *node)
{
    rpw_node_ll *ll;

    ll=  (rpw_node_ll *) pw_node_get_data(node);

    pw_node_cables_free(node);

    free(ll);
}

static runt_int node_ll(runt_vm *vm, runt_ptr p)
{
    runt_ll_d *rll;
    pw_patch *patch;
    pw_node *node;
    rpw_node_ll *ll;
    runt_stacklet *out;
    runt_int rc;
    

    rll = runt_to_cptr(p);
    patch = rll->patch;
    ll_end(rll->lines);
    rc = runt_ppush(vm, &out);
    RUNT_ERROR_CHECK(rc);

    rc = pw_patch_new_node(patch, &node);
    PW_RUNT_ERROR_CHECK(rc);
  
    ll = malloc(sizeof(rpw_node_ll));
    ll->line = ll_lines_current_line(rll->lines);

    pw_node_cables_alloc(node, 1);
    pw_node_get_cable(node, 0, &ll->out);

    pw_node_set_compute(node, compute);
    pw_node_set_destroy(node, destroy);
    pw_node_set_data(node, ll);

    rpw_push_output(vm, node, out, 0);
    return RUNT_OK;
}

static runt_int destroy_lines(runt_vm *vm, runt_ptr p)
{
    runt_ll_d *ll;
    ll = runt_to_cptr(p);
    ll_lines_free(ll->lines);
    free(ll->lines);
    free(ll);
    return RUNT_OK;
}

static runt_int libline(runt_vm *vm, runt_ptr p)
{
    ll_define(vm, p, "line_begin", 10, line_begin);
    ll_define(vm, p, "add_linpoint", 12, add_linpoint);
    ll_define(vm, p, "add_exppoint", 12, add_exppoint);
    ll_define(vm, p, "add_step", 8, add_step);
    ll_define(vm, p, "node_ll", 7, node_ll);
    runt_mark_set(vm);
    return runt_is_alive(vm);
}

runt_int runt_load_ll(runt_vm *vm, runt_ptr patchwerk)
{
    runt_ptr p;
    runt_ll_d *ll;
    sp_data *sp;
   
    ll = malloc(sizeof(runt_ll_d));
    ll->patch = runt_to_cptr(patchwerk);
    sp = pw_patch_ugens_get_data(ll->patch);
    
    ll->lines = malloc(ll_lines_size());
    ll_lines_init(ll->lines, sp->sr);

    p = runt_mk_cptr(vm, ll);
    ll_define(vm, p, "libline", 7, libline);
    runt_add_destructor(vm, destroy_lines, p);
    return runt_is_alive(vm);
}
