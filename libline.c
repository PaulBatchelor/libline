/*1:*/
#line 10 "./libline.w"

#include <stdlib.h> 
#include <stdio.h> 
#include "line.h"
/*39:*/
#line 3 "./point.w"
/*41:*/
#line 9 "./point.w"

struct ll_point{
ll_flt A;
ll_flt dur;
ll_flt*B;

/*:41*//*42:*/
#line 18 "./point.w"

ll_point*next;

/*:42*//*43:*/
#line 24 "./point.w"

ll_cb_malloc malloc;
ll_cb_free free;
void*ud;

/*:43*//*44:*/
#line 32 "./point.w"

void*data;
ll_cb_free destroy;

/*:44*//*45:*/
#line 38 "./point.w"

ll_cb_step step;


};

/*:45*//*47:*/
#line 47 "./point.w"

size_t ll_point_size(void)
{
return sizeof(ll_point);
}

/*:47*//*48:*/
#line 55 "./point.w"

/*61:*/
#line 164 "./point.w"

static ll_flt step(ll_point*pt,void*ud,UINT pos,UINT dur)
{
return ll_point_A(pt);
}

/*:61*//*62:*/
#line 173 "./point.w"

void ll_point_data(ll_point*pt,void*data)
{
pt->data= data;
}

void ll_point_cb_step(ll_point*pt,ll_cb_step stp)
{
pt->step= stp;
}

void ll_point_cb_destroy(ll_point*pt,ll_cb_free destroy)
{
pt->destroy= destroy;
}

/*:62*/
#line 56 "./point.w"

void ll_point_init(ll_point*pt)
{
pt->A= 1.0;
pt->dur= 1.0;
pt->B= &pt->A;
pt->ud= NULL;
pt->free= ll_free;
pt->malloc= ll_malloc;
pt->data= NULL;
pt->destroy= ll_free_nothing;
pt->step= step;
}

/*:48*//*50:*/
#line 74 "./point.w"

void ll_point_value(ll_point*pt,ll_flt val)
{
pt->A= val;
}


/*:50*//*51:*/
#line 83 "./point.w"

void ll_point_set_next_value(ll_point*pt,ll_flt*val)
{
pt->B= val;
}

/*:51*//*52:*/
#line 90 "./point.w"

void ll_point_dur(ll_point*pt,ll_flt dur)
{
pt->dur= dur;
}

ll_flt ll_point_get_dur(ll_point*pt)
{
return pt->dur;
}

/*:52*//*53:*/
#line 102 "./point.w"

void ll_point_set_next_point(ll_point*pt,ll_point*next)
{
pt->next= next;
}

/*:53*//*54:*/
#line 109 "./point.w"

ll_point*ll_point_get_next_point(ll_point*pt)
{
return pt->next;
}

/*:54*//*55:*/
#line 118 "./point.w"

ll_flt*ll_point_get_value(ll_point*pt)
{
return&pt->A;
}

/*:55*//*56:*/
#line 126 "./point.w"

ll_flt ll_point_A(ll_point*pt)
{
return pt->A;
}

ll_flt ll_point_B(ll_point*pt)
{
return*pt->B;
}

/*:56*//*58:*/
#line 142 "./point.w"

void*ll_point_malloc(ll_point*pt,size_t size)
{
return pt->malloc(pt->ud,size);
}
void ll_point_free(ll_point*pt,void*ptr)
{
pt->free(pt->ud,ptr);
}

/*:58*//*59:*/
#line 154 "./point.w"

void ll_point_destroy(ll_point*pt)
{
pt->destroy(pt,pt->data);
}

/*:59*//*63:*/
#line 190 "./point.w"

ll_flt ll_point_step(ll_point*pt,UINT pos,UINT dur)
{
return pt->step(pt,pt->data,pos,dur);
}

/*:63*//*64:*/
#line 199 "./point.w"

void ll_point_mem_callback(ll_point*pt,ll_cb_malloc m,ll_cb_free f)
{
pt->malloc= m;
pt->free= f;
}
#line 1 "./line.w"
/*:64*/
#line 3 "./point.w"


/*:39*//*65:*/
#line 4 "./line.w"
/*67:*/
#line 10 "./line.w"

struct ll_line{
ll_point*root;
ll_point*last;
int size;
int curpos;

/*:67*//*68:*/
#line 20 "./line.w"

int sr;

/*:68*//*69:*/
#line 26 "./line.w"

unsigned int counter;

/*:69*//*70:*/
#line 32 "./line.w"

unsigned int idur;

/*:70*//*71:*/
#line 38 "./line.w"

ll_cb_malloc malloc;
ll_cb_free free;

/*:71*//*72:*/
#line 44 "./line.w"

void*ud;

/*:72*//*73:*/
#line 49 "./line.w"

int end;
};

/*:73*//*74:*/
#line 54 "./line.w"

size_t ll_line_size(void)
{
return sizeof(ll_line);
}


/*:74*//*76:*/
#line 66 "./line.w"

void ll_line_init(ll_line*ln,int sr)
{
ln->root= NULL;
ln->last= NULL;
ln->size= 0;
ln->sr= sr;
ln->malloc= ll_malloc;
ln->free= ll_free;
ln->idur= 0;
ln->counter= 0;
ln->curpos= 0;
ln->end= 0;
}

/*:76*//*78:*/
#line 94 "./line.w"

void ll_line_append_point(ll_line*ln,ll_point*p)
{
if(ln->size==0){
ln->root= p;
}else{
ll_point_set_next_point(ln->last,p);
ll_point_set_next_value(ln->last,ll_point_get_value(p));
}
ln->last= p;
ln->size++;
}


/*:78*//*79:*/
#line 117 "./line.w"

ll_point*ll_line_append(ll_line*ln,ll_flt val,ll_flt dur)
{
ll_point*pt;

pt= ln->malloc(ln->ud,ll_point_size());

ll_point_init(pt);
ll_point_value(pt,val);
ll_point_dur(pt,dur);
ll_point_mem_callback(pt,ln->malloc,ln->free);

ll_line_append_point(ln,pt);

return pt;
}

/*:79*//*80:*/
#line 137 "./line.w"

void ll_line_done(ll_line*ln)
{
ln->curpos= 0;
ln->last= ln->root;
ln->idur= ll_point_get_dur(ln->root)*ln->sr;
ln->counter= ln->idur;
ln->end= 0;
}

/*:80*//*82:*/
#line 151 "./line.w"

void ll_line_free(ll_line*ln)
{
ll_point*pt;
ll_point*next;
unsigned int i;

pt= ln->root;
for(i= 0;i<ln->size;i++){
next= ll_point_get_next_point(pt);
ll_point_destroy(pt);
ln->free(ln->ud,pt);
pt= next;
}
}

/*:82*//*84:*/
#line 172 "./line.w"

ll_flt ll_line_step(ll_line*ln)
{
UINT dur;
UINT pos;
/*:84*//*85:*/
#line 181 "./line.w"

if(ln->end){
return ll_point_A(ln->last);
}

/*:85*//*86:*/
#line 189 "./line.w"

if(ln->counter==0){

/*:86*//*87:*/
#line 197 "./line.w"

if(ln->curpos<(ln->size-1)){

/*:87*//*88:*/
#line 203 "./line.w"

ln->last= ll_point_get_next_point(ln->last);
ln->idur= ll_point_get_dur(ln->last)*ln->sr;
ln->counter= ln->idur;
ln->curpos++;
/*:88*//*89:*/
#line 210 "./line.w"

}else{
ln->end= 1;
}
}

/*:89*//*90:*/
#line 221 "./line.w"

dur= ln->idur;
pos= dur-ln->counter;
ln->counter--;
return ll_point_step(ln->last,pos,dur);
}

/*:90*//*92:*/
#line 232 "./line.w"

void ll_line_print(ll_line*ln)
{
ll_point*pt;
ll_point*next;
unsigned int i;
ll_flt*val;

pt= ln->root;
printf("there are %d points...\n",ln->size);
for(i= 0;i<ln->size;i++){
next= ll_point_get_next_point(pt);
val= ll_point_get_value(pt);
printf("point %d: dur %g, val %g\n",
i,
ll_point_get_dur(pt),
*val
);

pt= next;
}
}
#line 1 "./lines.w"
/*:92*/
#line 4 "./line.w"


/*:65*//*93:*/
#line 4 "./lines.w"
/*95:*/
#line 10 "./lines.w"

typedef struct ll_line_entry{
ll_line*ln;
ll_flt val;
struct ll_line_entry*next;
}ll_line_entry;

/*:95*//*96:*/
#line 19 "./lines.w"

struct ll_lines{
ll_line_entry*root;
ll_line_entry*last;
unsigned int size;
int sr;
ll_cb_malloc malloc;
ll_cb_free free;
void*ud;
ll_line*line;
ll_point*pt;
};

/*:96*//*98:*/
#line 36 "./lines.w"


size_t ll_lines_size()
{
return sizeof(ll_lines);
}

/*:98*//*99:*/
#line 45 "./lines.w"

void ll_lines_init(ll_lines*l,int sr)
{
l->root= NULL;
l->last= NULL;
l->size= 0;
l->malloc= ll_malloc;
l->free= ll_free;
l->sr= sr;
}

/*:99*//*101:*/
#line 60 "./lines.w"

void ll_lines_mem_callback(ll_lines*l,void*ud,ll_cb_malloc m,ll_cb_free f)
{
l->malloc= m;
l->free= f;
l->ud= ud;
}

/*:101*//*102:*/
#line 69 "./lines.w"

void ll_lines_free(ll_lines*l)
{
unsigned int i;
ll_line_entry*entry;
ll_line_entry*next;

entry= l->root;

for(i= 0;i<l->size;i++){
next= entry->next;
ll_line_free(entry->ln);
l->free(l->ud,entry->ln);
l->free(l->ud,entry);
entry= next;
}
}

/*:102*//*104:*/
#line 92 "./lines.w"

void ll_lines_append(ll_lines*l,ll_line**line,ll_flt**val)
{
ll_line_entry*entry;

entry= l->malloc(l->ud,sizeof(ll_line_entry));
entry->val= 0.f;
entry->ln= l->malloc(l->ud,ll_line_size());
ll_line_init(entry->ln,l->sr);

if(line!=NULL)*line= entry->ln;
if(val!=NULL)*val= &entry->val;

if(l->size==0){
l->root= entry;
}else{
l->last->next= entry;
}

l->size++;
l->last= entry;
l->line= entry->ln;
}

/*:104*//*106:*/
#line 120 "./lines.w"

void ll_lines_step(ll_lines*l)
{
unsigned int i;
ll_line_entry*entry;

entry= l->root;

for(i= 0;i<l->size;i++){
entry->val= ll_line_step(entry->ln);
entry= entry->next;
}
}

/*:106*//*107:*/
#line 138 "./lines.w"

void ll_add_linpoint(ll_lines*l,ll_flt val,ll_flt dur)
{
ll_point*pt;
pt= ll_line_append(l->line,val,dur);
ll_linpoint(pt);
}

void ll_end(ll_lines*l)
{
ll_line_done(l->line);
}
#line 1 "./linpoint.w"
/*:107*/
#line 4 "./lines.w"


/*:93*//*108:*/
#line 3 "./linpoint.w"

/*110:*/
#line 10 "./linpoint.w"

typedef struct{
ll_flt inc;
ll_flt acc;
}linpoint;

/*:110*//*112:*/
#line 20 "./linpoint.w"

/*114:*/
#line 36 "./linpoint.w"


static ll_flt linpoint_step(ll_point*pt,void*ud,UINT pos,UINT dur)
{
linpoint*lp;
ll_flt val;

lp= ud;

if(pos==0){
lp->acc= ll_point_A(pt);
lp->inc= (ll_point_B(pt)-ll_point_A(pt))/dur;
}

val= lp->acc;
lp->acc+= lp->inc;
return val;
}

/*:114*//*116:*/
#line 57 "./linpoint.w"

static void ll_linpoint_destroy(void*ud,void*ptr)
{
ll_point*pt;
pt= ud;
ll_point_free(pt,ptr);
}

#line 1 "./mem.w"
/*:116*/
#line 21 "./linpoint.w"

void ll_linpoint(ll_point*pt)
{
linpoint*lp;
lp= ll_point_malloc(pt,sizeof(linpoint));
ll_point_cb_step(pt,linpoint_step);
ll_point_data(pt,lp);
ll_point_cb_destroy(pt,ll_linpoint_destroy);
}

/*:112*/
#line 4 "./linpoint.w"


/*:108*//*117:*/
#line 8 "./mem.w"

void*ll_malloc(void*ud,size_t size)
{
return malloc(size);
}

void ll_free(void*ud,void*ptr)
{
free(ptr);
}

void ll_free_nothing(void*ud,void*ptr)
{

}
#line 1 "./sporth.w"
/*:117*//*118:*/
#line 4 "./sporth.w"

#ifdef LL_SPORTH
/*119:*/
#line 15 "./sporth.w"

/*121:*/
#line 40 "./sporth.w"

static int sporth_ll(plumber_data*pd,sporth_stack*stack,void**ud)
{
ll_lines*l;
l= *ud;
if(pd->mode==PLUMBER_COMPUTE)ll_lines_step(l);
return PLUMBER_OK;
}
/*:121*/
#line 16 "./sporth.w"

void ll_sporth_ugen(ll_lines*l,plumber_data*pd,const char*ugen)
{
plumber_ftmap_add_function(pd,ugen,sporth_ll,l);
}

/*:119*//*120:*/
#line 24 "./sporth.w"

ll_line*ll_sporth_line(ll_lines*l,plumber_data*pd,const char*name)
{
ll_line*ln;
ll_flt*val;

ll_lines_append(l,&ln,&val);

plumber_ftmap_delete(pd,0);
plumber_ftmap_add_userdata(pd,name,val);
plumber_ftmap_delete(pd,1);
return ln;
}

/*:120*/
#line 6 "./sporth.w"

#endif

/*:118*/
#line 14 "./libline.w"


#line 1 "./header.w"
/*:1*/
