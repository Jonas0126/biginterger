#include "bigint.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



int bigint_input(bigint * bi)//輸入一個bigint
{
    bigint_init(bi);
    int strSize = bi->maxlen;//最大長度
    int input_pos = bi->strlen;//目前要輸入的位置
    char input = NULL;


    while((input = getc(stdin)) != '\n')//每次接收一字元 直到遇到換行符
    {
        if(isdigit(input))//如果不是數字則報錯
        {
            bi->num[input_pos++] = input;

            if(input_pos == bi->maxlen)//如果分配的空間滿了 再多分配STRLEN的空間
            {
                bi->maxlen += bi->expendlen;

                bi->num = (char*)realloc(bi,bi->maxlen);
            }
        }
        else
        {
            printf("input error! only number allow!");
            free(bi->num);
            return 0;
        }
    }
    bi->num[input_pos] = '\0';
    bi->strlen = input_pos;
    return 1;
}


void bigint_init(bigint * bi)//初始化一個bigint
{
    

    //初始n的值
    bi->num = '\0';
    bi->strlen = 0;//已經使用長度
    bi->maxlen = 1000;//最大長度
    bi->expendlen = 1000;

    int strSize = bi->maxlen;//最大長度
    
    bi->num = (char*)malloc(sizeof(char) * strSize);//給n.num分配空間
}

void bigint_append(bigint * bi, char s)
{
    int i = 0;

    while(i <= bi->strlen)//將s插入第一位其他往後
    {

        char temp = bi->num[i];
        bi->num[i++] = s;
        s = temp;

        if(i == bi->maxlen)//如果分配的空間滿了 再多分配STRLEN的空間
        {
            bi->maxlen += bi->expendlen;

            bi->num = (char*)realloc(bi,bi->maxlen);
        }
        
    }

    bi->num[i] = '\0';
    bi->strlen = i;


}




void bigint_add(bigint * n3, bigint * n1, bigint * n2)
{

    bigint_init(n3);
    


    //測試資訊
    #if 1 
    printf("n1l = %d\n" , n1->strlen);
    printf("n2l = %d\n" , n2->strlen);
    #endif

    printf("開始加法----------------------------\n");

    char carry = 0;

    int n1_pos = n1->strlen - 1;
    int n2_pos = n2->strlen - 1;

    while((n1_pos >= 0) && (n2_pos >= 0))
    {

        #if 0 //測試資訊
        printf("n1l = %d\n", n1l);
        printf("n2l = %d\n", n2l);
        printf("n1.num[n1l] = %c\n", n1.num[n1l]);
        printf("n2.num[n2l] = %c\n", n2.num[n2l]);
        printf("(int)n1.num[n1l] = %d\n", (int)n1.num[n1l]);
        printf("(int)n2.num[n2l] = %d\n", (int)n2.num[n2l]);
        #endif

        char asii = (int)n1->num[n1_pos] + (int)n2->num[n2_pos];

        #if 1 //測試資訊
        printf("asii = %d\n", asii);
        #endif

        //是否有低位進位
        if(carry == 1)
            asii += 1;

        //是否產生進位
        if(asii >= 106)
        {
            asii -= 58;
            carry = 1;
        }
        else
        {
            asii -= 48;
            carry = 0;
        }

        bigint_append(n3, asii);



        n1_pos--;
        n2_pos--;
    }

    #if 1 //測試資訊
    printf("n1l = %d\n", n1_pos);
    printf("n2l = %d\n", n2_pos);
    #endif

    //n1是否已經結束
    while(n1_pos >= 0)
    {
        #if 1 //測試資訊
        printf("n1l = %d\n", n1_pos);
        #endif

        //是否有低位進位
        if(carry == 1)
        {
            char asii = (int)n1->num[n1_pos] + 1;
            
            #if 1 //測試資訊
            printf("asii = %d\n", asii);
            printf("n1.num[n1l] = %c\n", n1->num[n1_pos]);
            #endif

            //是否產生進位
            if(asii >= 58)
            {
                asii -= 10;
                carry = 1;
            }
            else
                carry = 0;



            #if 1 //測試資訊
            printf("asii = %d\n", asii);
            #endif

            bigint_append(n3, asii);

        }
        else
        {
            bigint_append(n3, n1->num[n1_pos]);

            #if 1//測試資訊
            printf("n1.num[n1l] = %c\n", n1->num[n1_pos]);
            #endif
        }
        n1_pos--;
    }


    //n2是否已經結束
    while(n2_pos >= 0)
    {

        //是否有低位進位
        if(carry == 1)
        {
            char asii = (int)n2->num[n2_pos] + 1;

            //是否產生進位
            if(asii >= 58)
            {
                asii -= 10;
                carry = 1;
            }
            else
                carry = 0;


           bigint_append(n3, asii);
        }
        else
        {
            bigint_append(n3, n2->num[n2_pos]);

            #if 1//測試資訊
            printf("n2.num[n2_pos] = %c\n", n2->num[n2_pos]);
            #endif
        }
        n2_pos--;
    }

    #if 1 //測試資訊
    printf("carry = %d\n", carry);
    #endif


    //是否有進位
    if((carry == 1))
    {
        bigint_append(n3, '1');
    }

}
