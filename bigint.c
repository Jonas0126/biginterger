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


void bigint_copy(bigint * bi1, bigint * bi2, int pos)
{
    bigint_init(bi1);
    for(int i = bi2->strlen - 1; i >= pos; i--)
    {
        bigint_append(bi1, bi2->num[i]);
    }
}

void bigint_add(bigint * n3, bigint * n1, bigint * n2)
{
    bigint temp;
    bigint_init(&temp);
    


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

        bigint_append(&temp, asii);



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

            bigint_append(&temp, asii);

        }
        else
        {
            bigint_append(&temp, n1->num[n1_pos]);

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


           bigint_append(&temp, asii);
        }
        else
        {
            bigint_append(&temp, n2->num[n2_pos]);

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
        bigint_append(&temp, '1');
    }



    bigint_copy(n3, &temp, 0);

    free(temp.num);

}




void bigint_dif(bigint * n3, bigint * n1, bigint * n2)
{
    bigint temp;
    bigint_init(&temp);
    int n1_pos = 0;
    int n2_pos = 0;
    char *num1, *num2;


    //將較大的數存在num1較小的存在num2
    if(n1->strlen > n2->strlen)
    {
        num1 = n1->num;;
        num2 = n2->num;
        n1_pos = n1->strlen - 1;
        n2_pos = n2->strlen - 1;
        temp.sign = 0;
        
    }
    else if(n1->strlen == n2->strlen)
    {
        int i = n1->strlen - 1;
        int d = n1->num[i] - n2->num[i];
        while(d == 0)
        {
            i--;
            d = n1->num[i] - n2->num[i];
        }

        if(d > 0)
        {
            num1 = n1->num;;
            num2 = n2->num;
            n1_pos = n1->strlen - 1;
            n2_pos = n2->strlen - 1;
            temp.sign = 0;
        }
        else
        {
            num1 = n2->num;;
            num2 = n1->num;
            n1_pos = n2->strlen - 1;
            n2_pos = n1->strlen - 1;
            temp.sign = 1;
        }

    }
    else
    {
        num1 = n2->num;;
        num2 = n1->num;
        n1_pos = n2->strlen - 1;
        n2_pos = n1->strlen - 1;
        temp.sign = 1;
    }


    char borrow = 0;

    while((n1_pos >= 0) && (n2_pos >= 0))
    {

        char asii = (int)n1->num[n1_pos] - (int)n2->num[n2_pos];
        if(borrow == 1)
        {
            asii = asii - 1;
        }
        if((int)asii < 0)
        {
            borrow = 1;
            asii = (int)n1->num[n1_pos] - (int)n2->num[n2_pos] + 58;
        }
        else
        {
            borrow = 0;
            asii += 48;
        }

        bigint_append(&temp, asii);

        n1_pos--;
        n2_pos--;
    }

    //n1是否已經結束
    while(n1_pos >= 0)
    {
        #if 1 //測試資訊
        printf("n1_pos = %d\n", n1_pos);
        #endif

        //是否有低位借位
        if(borrow == 1)
        {
            char asii = (int)n1->num[n1_pos] - 1;
            printf("asii = %d\n", (int)asii);

            if((int)asii < 48)
            {
                borrow = 1;
                asii += 10;
            }
            else
                borrow = 0;

            bigint_append(&temp, asii);
            printf("asii = %d\n", (int)asii);

        }
        else
        {
            bigint_append(&temp, n1->num[n1_pos]);
            printf("asii = %d\n", n1->num[n1_pos]);
        }
        n1_pos--;
    }
    
    if(temp.num[0] == 48)
        bigint_copy(n3, &temp, 1);  
    else
        bigint_copy(n3, &temp, 0);


}