@** Memory. Several aspects of this program require memory to be allocated. 
In order to be maximally flexible, the default system memory handling 
functions have been wrapped inside helper functions with a void pointer for
user data. This way, these functions can be swapped out for custom ones for 
situations where a different memory handling system is used, such as 
garbage collection.

@<Top@>+=
void * ll_malloc(void *ud, size_t size)
{
    return malloc(size);
}

void ll_free(void *ud, void *ptr)
{
    free(ptr);
}

void ll_free_nothing(void *ud, void *ptr)
{

}
