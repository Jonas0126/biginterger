#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"
#include <ctype.h>



int main(){

    bigint str1;
    int s;
    s = bigint_new(&str1);
    
    if(s != 0)
    {
        printf("hi\n");
        printf("%d,%s\n",str1.digit,str1.num);
        printf("bye");
        free(str1.num);
    }

    
    
    return 0;
}