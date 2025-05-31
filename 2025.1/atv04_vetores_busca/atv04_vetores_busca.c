#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    srand(time(NULL));
    printf("RAND_MAX = %d\n", RAND_MAX);
    for(int i = 1; i <=50; i +=1){
    
    printf ("aleatorio = %d\n", rand()% 1000+1);
    }
    return 0;
} 