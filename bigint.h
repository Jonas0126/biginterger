#pragma once

typedef struct  bigint bigint;

struct bigint
{
    char *num;
    int digit;
};

int bigint_new(bigint * bi);//新建一個bigint
