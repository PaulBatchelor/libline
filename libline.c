/*1:*/
#line 10 "./libline.w"

#include <stdlib.h> 
#include <stdio.h> 
#include "line.h"
/*38:*/
#line 3 "./point.w"
/*40:*/
#line 9 "./point.w"

struct ll_point{
ll_flt A;
ll_flt dur;
ll_flt*B;

/*:40*//*41:*/
#line 18 "./point.w"

ll_point*next;

/*:41*//*42:*/
#line 24 "./point.w"

ll_cb_malloc malloc;
ll_cb_free free;
void*ud;

/*:42*//*43:*/
#line 32 "./point.w"

void*data;
ll_cb_free destroy;

/*:43*//*44:*/
#line 38 "./point.w"

ll_cb_step step;


};

/*:44*//*46:*/
#line 47 "./point.w"

size_t ll_point_size(void)
{
return sizeof(ll_point);
}

/*:46*//*47:*/
#line 55 "./point.w"

/*60:*/
#line 164 "./point.w"

static ll_flt step(ll_point*pt,void*ud,UINT pos,UINT dur)
{
return ll_point_A(pt);
}

/*:60*//*61:*/
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

/*:61*/
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

/*:47*//*49:*/
#line 74 "./point.w"

void ll_point_value(ll_point*pt,ll_flt val)
{
pt->A= val;
}


/*:49*//*50:*/
#line 83 "./point.w"

void ll_point_set_next_value(ll_point*pt,ll_flt*val)
{
pt->B= val;
}

/*:50*//*51:*/
#line 90 "./point.w"

void ll_point_dur(ll_point*pt,ll_flt dur)
{
pt->dur= dur;
}

ll_flt ll_point_get_dur(ll_point*pt)
{
return pt->dur;
}

/*:51*//*52:*/
#line 102 "./point.w"

void ll_point_set_next_point(ll_point*pt,ll_point*next)
{
pt->next= next;
}

/*:52*//*53:*/
#line 109 "./point.w"

ll_point*ll_point_get_next_point(ll_point*pt)
{
return pt->next;
}

/*:53*//*54:*/
#line 118 "./point.w"

ll_flt*ll_point_get_value(ll_point*pt)
{
return&pt->A;
}

/*:54*//*55:*/
#line 126 "./point.w"

ll_flt ll_point_A(ll_point*pt)
{
return pt->A;
}

ll_flt ll_point_B(ll_point*pt)
{
return*pt->B;
}

/*:55*//*57:*/
#line 142 "./point.w"

void*ll_point_malloc(ll_point*pt,size_t size)
{
return pt->malloc(pt->ud,size);
}
void ll_point_free(ll_point*pt,void*ptr)
{
pt->free(pt->ud,ptr);
}

/*:57*//*58:*/
#line 154 "./point.w"

void ll_point_destroy(ll_point*pt)
{
pt->destroy(pt,pt->data);
}

/*:58*//*62:*/
#line 190 "./point.w"

ll_flt ll_point_step(ll_point*pt,UINT pos,UINT dur)
{
return pt->step(pt,pt->data,pos,dur);
}

/*:62*//*63:*/
#line 199 "./point.w"

void ll_point_mem_callback(ll_point*pt,ll_cb_malloc m,ll_cb_free f)
{
pt->malloc= m;
pt->free= f;
}
#line 1 "./line.w"
/*:63*/
#line 3 "./point.w"


/*:38*//*64:*/
#line 4 "./line.w"
/*66:*/
#line 10 "./line.w"

struct ll_line{
ll_point*root;
ll_point*last;
int size;
int curpos;

/*:66*//*67:*/
#line 20 "./line.w"

int sr;

/*:67*//*68:*/
#line 26 "./line.w"

unsigned int counter;

/*:68*//*69:*/
#line 32 "./line.w"

unsigned int idur;

/*:69*//*70:*/
#line 38 "./line.w"

ll_cb_malloc malloc;
ll_cb_free free;

/*:70*//*71:*/
#line 44 "./line.w"

void*ud;

/*:71*//*72:*/
#line 49 "./line.w"

int end;
};

/*:72*//*73:*/
#line 54 "./line.w"

size_t ll_line_size(void)
{
return sizeof(ll_line);
}


/*:73*//*75:*/
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

/*:75*//*77:*/
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


/*:77*//*78:*/
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

/*:78*//*79:*/
#line 137 "./line.w"

void ll_line_done(ll_line*ln)
{
ln->curpos= 0;
ln->last= ln->root;
ln->idur= ll_point_get_dur(ln->root)*ln->sr;
ln->counter= ln->idur;
ln->end= 0;
}

/*:79*//*81:*/
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

/*:81*//*83:*/
#line 172 "./line.w"

ll_flt ll_line_step(ll_line*ln)
{
UINT dur;
UINT pos;
/*:83*//*84:*/
#line 181 "./line.w"

if(ln->end){
return ll_point_A(ln->last);
}

/*:84*//*85:*/
#line 189 "./line.w"

if(ln->counter==0){

/*:85*//*86:*/
#line 197 "./line.w"

if(ln->curpos<(ln->size-1)){

/*:86*//*87:*/
#line 203 "./line.w"

ln->last= ll_point_get_next_point(ln->last);
ln->idur= ll_point_get_dur(ln->last)*ln->sr;
ln->counter= ln->idur;
ln->curpos++;
/*:87*//*88:*/
#line 210 "./line.w"

}else{
ln->end= 1;
}
}

/*:88*//*89:*/
#line 221 "./line.w"

dur= ln->idur;
pos= dur-ln->counter;
ln->counter--;
return ll_point_step(ln->last,pos,dur);
}

/*:89*//*91:*/
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
/*:91*/
#line 4 "./line.w"


/*:64*//*92:*/
#line 4 "./lines.w"
/*94:*/
#line 10 "./lines.w"

typedef struct ll_line_entry{
ll_line*ln;
ll_flt val;
struct ll_line_entry*next;
}ll_line_entry;

/*:94*//*95:*/
#line 19 "./lines.w"

struct ll_lines{
ll_line_entry*root;
ll_line_entry*last;
unsigned int size;
int sr;
ll_cb_malloc malloc;
ll_cb_free free;
void*ud;
};

/*:95*//*97:*/
#line 34 "./lines.w"


size_t ll_lines_size()
{
return sizeof(ll_lines);
}

/*:97*//*98:*/
#line 43 "./lines.w"

void ll_lines_init(ll_lines*l,int sr)
{
l->root= NULL;
l->last= NULL;
l->size= 0;
l->malloc= ll_malloc;
l->free= ll_free;
l->sr= sr;
}

/*:98*//*100:*/
#line 58 "./lines.w"

void ll_lines_mem_callback(ll_lines*l,void*ud,ll_cb_malloc m,ll_cb_free f)
{
l->malloc= m;
l->free= f;
l->ud= ud;
}

/*:100*//*101:*/
#line 67 "./lines.w"

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

/*:101*//*103:*/
#line 90 "./lines.w"

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
}

/*:103*//*105:*/
#line 117 "./lines.w"

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

#line 1 "./linpoint.w"
/*:105*/
#line 4 "./lines.w"


/*:92*//*106:*/
#line 3 "./linpoint.w"

/*108:*/
#line 10 "./linpoint.w"

typedef struct{
ll_flt inc;
ll_flt acc;
}linpoint;

/*:108*//*110:*/
#line 20 "./linpoint.w"

/*112:*/
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

/*:112*//*114:*/
#line 57 "./linpoint.w"

static void ll_linpoint_destroy(void*ud,void*ptr)
{
ll_point*pt;
pt= ud;
ll_point_free(pt,ptr);
}

#line 1 "./mem.w"
/*:114*/
#line 21 "./linpoint.w"

void ll_linpoint(ll_point*pt)
{
linpoint*lp;
lp= ll_point_malloc(pt,sizeof(linpoint));
ll_point_cb_step(pt,linpoint_step);
ll_point_data(pt,lp);
ll_point_cb_destroy(pt,ll_linpoint_destroy);
}

/*:110*/
#line 4 "./linpoint.w"


/*:106*//*115:*/
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
/*:115*//*116:*/
#line 4 "./sporth.w"

#ifdef LL_SPORTH
/*117:*/
#line 15 "./sporth.w"

/*119:*/
#line 40 "./sporth.w"

static int sporth_ll(plumber_data*pd,sporth_stack*stack,void**ud)
{
ll_lines*l;
l= *ud;
if(pd->mode==PLUMBER_COMPUTE)ll_lines_step(l);
return PLUMBER_OK;
}
/*:119*/
#line 16 "./sporth.w"

void ll_sporth_ugen(ll_lines*l,plumber_data*pd,const char*ugen)
{
plumber_ftmap_add_function(pd,ugen,sporth_ll,l);
}

/*:117*//*118:*/
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

/*:118*/
#line 6 "./sporth.w"

#endif

/*:116*/
#line 14 "./libline.w"


#line 1 "./header.w"
/*:1*/
