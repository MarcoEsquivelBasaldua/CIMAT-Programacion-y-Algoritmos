#include <stdlib.h>
#include <stdio.h>

int main(void){
    int n=100;
    int i=1, s=1;

    while(s<=n){
        printf("%d ",(i+1)*(i+2)/2);
        i++;
        s += i;
        printf("%d ",s);
    }
    return 0;
}
