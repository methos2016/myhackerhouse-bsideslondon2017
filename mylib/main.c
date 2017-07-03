#include <stdio.h>
#include "foo.h"
 
int main(void)
{
    puts("This is a shared library test...");
    runme();
    return 0;
}
