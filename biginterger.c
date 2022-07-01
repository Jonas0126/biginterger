#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"
#include <ctype.h>



int main(){

    bigint str1, str2, str3;
    bigint_init(&str1);
    bigint_init(&str2);
    bigint_init(&str3);
    while(1)
    {
        printf("input num1 :");
        bigint_input(&str1);

        printf("input num2 :");
        bigint_input(&str2);

        bigint_dif(&str3, &str1, &str2);
        //bigint_add(&str3, &str1, &str2);
        //printf("str3len = \n" , strlen(str3.num));
        printf("plus num1 and num2 -> %s , %s\n", str1.num, str2.num);
        printf("str3 = str1 - str2 -> %s = %s + %s\n" , str3.num, str1.num, str2.num);
        /*free(str1.num);    
        free(str2.num);
        free(str3.num);
        str1.num = NULL;
        str3.num = NULL;
        str2.num = NULL;*/


    }
    
    free(str1.num);    
    free(str2.num);
    free(str3.num);
    return 0;
}