@* The Lines. When more than one line is required, you need {\it lines}. 
|ll_lines| is the next abstraction up from |ll_line|. 

@<Top@>+= @<Lines@>

@ The |ll_lines| data struct is linked list of |ll_line|. 

@<Lines@>+=
struct ll_lines {
    ll_line *root;
    ll_line *next;
    unsigned int size;
};
