#include <stdio.h>
#include <stdlib.h>

unsigned gdc(unsigned a, unsigned b);

int main(){
    int unsigned a, b, tmp;
    a = 10, b=4;
    if(a<b){
        tmp = a;
        a=b;
        b=tmp;
    }
    printf("%d", gdc(a,b));
    
    return 0;
}

unsigned gdc(unsigned a, unsigned b){
    unsigned msd;
    if(a==b) return a;
    
    if (a%2==0){
        if(b%2==0) return msd = 2*gdc(a/2, b/2);
        else return msd = gdc(a/2, b);
    }else if(b%2==0) return msd = gdc(a,b/2);
    else if(a!=b) msd = gdc((a-b)/2, b);

}
