/*2:*/
#line 5 "./header.w"

#ifndef LINE_H
#define LINE_H
#ifdef LL_SPORTH
#include <soundpipe.h> 
#include <sporth.h> 
#endif
/*4:*/
#line 21 "./header.w"

#ifndef LLFLOAT
typedef float ll_flt;
#else
typedef LLFLOAT ll_flt;
#endif
#define UINT unsigned int
/*:4*//*5:*/
#line 30 "./header.w"

typedef struct ll_point ll_point;

/*:5*//*6:*/
#line 35 "./header.w"

typedef struct ll_line ll_line;

/*:6*//*7:*/
#line 39 "./header.w"

typedef struct ll_lines ll_lines;


/*:7*//*8:*/
#line 47 "./header.w"

typedef void*(*ll_cb_malloc)(void*ud,size_t size);
typedef void(*ll_cb_free)(void*ud,void*ptr);

/*:8*//*9:*/
#line 53 "./header.w"

typedef ll_flt(*ll_cb_step)(ll_point*pt,void*ud,UINT pos,UINT dur);

/*:9*//*11:*/
#line 59 "./header.w"

void*ll_malloc(void*ud,size_t size);
void ll_free(void*ud,void*ptr);
void ll_free_nothing(void*ud,void*ptr);

/*:11*//*12:*/
#line 67 "./header.w"

void*ll_point_malloc(ll_point*pt,size_t size);
void ll_point_free(ll_point*pt,void*ptr);
void ll_point_destroy(ll_point*pt);

/*:12*//*14:*/
#line 76 "./header.w"

size_t ll_line_size(void);
size_t ll_point_size(void);

/*:14*//*15:*/
#line 83 "./header.w"

void ll_point_init(ll_point*pt);
void ll_line_init(ll_line*ln,int sr);

/*:15*//*17:*/
#line 90 "./header.w"

void ll_point_value(ll_point*pt,ll_flt val);
void ll_point_dur(ll_point*pt,ll_flt dur);
ll_flt ll_point_get_dur(ll_point*pt);

/*:17*//*18:*/
#line 96 "./header.w"

void ll_point_set_next_value(ll_point*pt,ll_flt*val);

/*:18*//*19:*/
#line 100 "./header.w"

ll_flt ll_point_A(ll_point*pt);
ll_flt ll_point_B(ll_point*pt);

/*:19*//*20:*/
#line 106 "./header.w"

ll_flt*ll_point_get_value(ll_point*pt);

/*:20*//*21:*/
#line 111 "./header.w"

void ll_point_set_next_point(ll_point*pt,ll_point*next);

/*:21*//*22:*/
#line 117 "./header.w"

ll_point*ll_point_get_next_point(ll_point*pt);

/*:22*//*23:*/
#line 121 "./header.w"

ll_flt ll_point_step(ll_point*pt,UINT pos,UINT dur);

/*:23*//*24:*/
#line 125 "./header.w"

void ll_point_data(ll_point*pt,void*data);
void ll_point_cb_step(ll_point*pt,ll_cb_step stp);
void ll_point_cb_destroy(ll_point*pt,ll_cb_free destroy);

/*:24*//*25:*/
#line 132 "./header.w"

void ll_point_mem_callback(ll_point*pt,ll_cb_malloc m,ll_cb_free f);

/*:25*//*27:*/
#line 139 "./header.w"

void ll_line_append_point(ll_line*ln,ll_point*p);

/*:27*//*28:*/
#line 148 "./header.w"

ll_point*ll_line_append(ll_line*ln,ll_flt val,ll_flt dur);

/*:28*//*29:*/
#line 154 "./header.w"

void ll_line_free(ll_line*ln);

/*:29*//*30:*/
#line 159 "./header.w"

void ll_line_mem_callback(ll_line*ln,ll_cb_malloc m,ll_cb_free f);


/*:30*//*31:*/
#line 167 "./header.w"

void ll_line_done(ll_line*ln);


/*:31*//*32:*/
#line 174 "./header.w"

ll_flt ll_line_step(ll_line*ln);


/*:32*//*33:*/
#line 179 "./header.w"

void ll_line_print(ll_line*ln);

/*:33*//*34:*/
#line 183 "./header.w"

void ll_linpoint(ll_point*pt);

/*:34*//*36:*/
#line 189 "./header.w"

size_t ll_lines_size();
void ll_lines_init(ll_lines*l,int sr);
void ll_lines_mem_callback(ll_lines*l,void*ud,ll_cb_malloc m,ll_cb_free f);
void ll_lines_append(ll_lines*l,ll_line**line,ll_flt**val);
void ll_lines_step(ll_lines*l);
void ll_lines_free(ll_lines*l);

/*:36*//*37:*/
#line 199 "./header.w"

void ll_add_linpoint(ll_lines*l,ll_flt val,ll_flt dur);
void ll_end(ll_lines*l);

/*:37*//*38:*/
#line 206 "./header.w"

#ifdef LL_SPORTH
void ll_sporth_ugen(ll_lines*l,plumber_data*pd,const char*ugen);
ll_line*ll_sporth_line(ll_lines*l,plumber_data*pd,const char*name);
#endif

#line 1 "./point.w"
/*:38*/
#line 12 "./header.w"

#endif

/*:2*/
