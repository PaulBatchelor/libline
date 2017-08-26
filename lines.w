@** The Lines. When more than one line is required, you need {\it lines}. 
|ll_lines| is the next abstraction up from |ll_line|. 

@<Top@>+= @<Lines@>

@ The |ll_line_entry| data struct wraps |ll_line| into a linked list entry.

@<Lines@>+=
typedef struct ll_line_entry {
    ll_line *ln ; /* main ll\_line entry */
    ll_flt val; /* store output step value */
    struct ll_line_entry *next; /* next ll\_line\_entry value */
} ll_line_entry;

@ The |ll_lines| data struct is linked list of |ll_line_entry|. 

@<Lines@>+=
struct ll_lines {
    ll_line_entry *root;
    ll_line_entry *last;
    unsigned int size;
    int sr; /* samplerate */
    ll_cb_malloc malloc;
    ll_cb_free free;
    void *ud;
};

@ |ll_lines_size| returns the size of the ll\_lines data struct.

@<Lines@>+=

size_t ll_lines_size()
{
    return sizeof(ll_lines);
}

@ |ll_lines_init| initializes all the data of an allocated |ll_lines| struct.

@<Lines@>+=
void ll_lines_init(ll_lines *l, int sr)
{
    l->root = NULL;
    l->last = NULL;
    l->size = 0;
    l->malloc = ll_malloc;
    l->free = ll_free;
    l->sr = sr;
}

@ Alternative memory allocation functions can be set for |ll_lines| via
|ll_lines_mem_callback|.

@<Lines@>+=
void ll_lines_mem_callback(ll_lines *l, void *ud, ll_cb_malloc m, ll_cb_free f)
{
    l->malloc = m;
    l->free = f;
    l->ud = ud;
}

@ This creates and appends a new |ll_line| to the |ll_lines| linked list.
The address of this new |ll_line| is saved to the variable |line|. The output
memory address of the |ll_line| is saved to the variable |val|. 

@<Lines@>+=
void ll_lines_append(ll_lines *l, ll_line **line, ll_flt **val)
{
    ll_line_entry *entry;
   
    entry = l->malloc(l->ud, sizeof(ll_line_entry));
    entry->val = 0.f;
    entry->ln = l->malloc(l->ud, ll_line_size());
    ll_line_init(entry->ln, l->sr);
  
    if(line != NULL) *line = entry->ln;
    if(val != NULL) *val = &entry->val;

    if(l->size == 0) {
        l->root = entry; 
    } else {
        l->last->next = entry;
    }

    l->size++;
    l->last = entry;
}

@ The step function for |ll_lines| will walk through the linked list and call
the step function for each |ll_line| inside each |ll_line_entry|. 

@<Lines@>+=
void ll_lines_step(ll_lines *l)
{
    unsigned int i;
    ll_line_entry *entry;

    entry = l->root;

    for(i = 0; i < l->size; i++) {
        entry->val = ll_line_step(entry->ln);
        entry = entry->next;
    }
}

@ Write some words here.
@<Lines@>+=
void ll_lines_free(ll_lines *l)
{
    unsigned int i;
    ll_line_entry *entry;
    ll_line_entry *next;

    entry = l->root;

    for(i = 0; i < l->size; i++) {
        next = entry->next;
        ll_line_free(entry->ln);
        l->free(l->ud, entry->ln);
        l->free(l->ud, entry);
        entry = next;
    }
}
