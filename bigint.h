#pragma once

typedef struct  bigint bigint;

struct bigint
{
    char *num;
    int strlen;
    int expendlen;//每次分配長度
    int maxlen;//最大長度
};

int bigint_input(bigint * bi);//輸入一個bigint

void bigint_init(bigint * bi);//初始化一個bigint

void bigint_add(bigint * n3, bigint * n1, bigint * n2);//相加bigint n1+n2=n3

void bigint_append(bigint * bi, char s);

void bigint_copy(bigint * bi1, bigint * bi2);//copy num form bi2 to bi1