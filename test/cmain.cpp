#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "../core/HEThreadPool.h"


int Add(int a,int b){
    printf("%d\n",a+b);
    return a+b;
}

using pfnTest = int (*)(int,int);

int main(void){
    pfnTest te = Add;
    HEThreadPool pool(2); 
    pool.AddTask(te,5,5); 
    return 0;
}
