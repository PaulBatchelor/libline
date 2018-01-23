#include <stdio.h>
#include <runt.h>
#include <patchwerk.h>
#include <runt_patchwerk.h>
#include "runt_ll.h"

runt_ptr runt_load_patchwerk(runt_vm *vm);

static runt_int loader(runt_vm *vm)
{
    runt_load_stdlib(vm);
    runt_load_patchwerk(vm);
    runt_load_ll(vm);
    return RUNT_OK;
}

int main(int argc, char *argv[])
{
    return irunt_begin(argc, argv, loader);
}
