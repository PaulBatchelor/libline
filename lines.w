@* The Lines. When more than one line is required, you need {\it lines}. 
|ll_lines| is the next abstraction up from |ll_line|. 

@<Top@>+= @<Lines@>

@ The |ll_line_entry| data struct wraps |ll_line| into a linked list entry.

@<Lines@>+=
typedef struct ll_line_entry {
    ll_line *entry; /* main ll\_line entry */
    ll_flt val; /* store output step value */
    struct ll_line_entry *next; /* next ll\_line\_entry value */
} ll_line_entry;

@ The |ll_lines| data struct is linked list of |ll_line_entry|. 

@<Lines@>+=
struct ll_lines {
    ll_line_entry *root;
    ll_line_entry *last;
    unsigned int size;
    ll_cb_malloc malloc;
    ll_cb_free free;
};

@ |ll_lines_size| returns the size of the ll\_lines data struct.

@<Lines@>+=

size_t ll_lines_size()
{
    return sizeof(ll_lines);
}

@ |ll_lines_init| initializes all the data of an allocated |ll_lines| struct.

@<Lines@>+=
void ll_lines_init(ll_lines *l)
{
    l->root = NULL;
    l->last = NULL;
    l->size = 0;
    l->malloc = ll_malloc;
    l->free = ll_free;
}

@ Alternative memory allocation functions can be set for |ll_lines| via
|ll_lines_mem_callback|.

@<Lines@>+=
void ll_lines_mem_callback(ll_lines *l, ll_cb_malloc m, ll_cb_free f)
{
    l->malloc = m;
    l->free = f;
}

@ Write some words here.
@<Lines@>+=
void ll_lines_append(ll_lines *l, ll_line **line, ll_flt **val)
{
    /* TODO: implement me */
}

@ Write some words here.

@<Lines@>+=
void ll_lines_step(ll_lines *l)
{
    /* TODO: implement me */
}

@ Lines free. 
@<Lines@>+=
void ll_lines_free(ll_lines *l)
{
    /* TODO: implement me */
}
