#include "bigint.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define STRLEN 1000 //每次最大分配長度


int bigint_new(bigint * bi)//新建一個bigint
{
    int strSize = STRLEN;//最大長度
    int strLength = 0;//目前已用長度

    char input = NULL;

    bi->num= (char*)malloc(sizeof(char) * strSize);

    while((input = getc(stdin)) != '\n')//每次接收一字元 直到遇到換行符
    {
        if(isdigit(input))//如果不是數字則報錯
        {
            bi->num[strLength++] = input;
            if(strLength == strSize)//如果分配的空間滿了 再多分配STRLEN的空間
            {
                strSize += STRLEN;
                bi->num = (char*)realloc(bi,strSize);
            }
        }
        else
        {
            printf("input error! only number allow!");
            free(bi->num);
            return 0;
        }
    }
    bi->digit = strLength;//設定bi的位數有幾位
    bi->num[strLength] = '\0';
    return 1;
}