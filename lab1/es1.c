#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *cercaRegexp(char *src, char *regexp);

int main(){
    int lenst, lenexp;
    // char *stringa, *expreg;

    // printf("Lunghezza stringa e lunghezza espressione regolare: ");
    // scanf("%d %d", &lenst, &lenexp);
    // getchar();
    // stringa = (char *)malloc(lenst+1);
    // expreg = (char*)malloc(lenexp+1);
    // printf("Stringa: ");
    // fgets(stringa, lenst+1, stdin);

    // printf("Espressione regolare da cercare: ");
    // scanf("%s", expreg);

    char stringa[]="foto porto", expreg[]=".oto";

    printf("%p", cercaRegexp(stringa, expreg));
    
    // free(stringa);
    // free(expreg);
    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    switch(*regexp){
        case '.':
            int c=0, flag=0;
            regexp++;
            while(*src != '\0'){
                if(*src==' ') src++;
                else if(*src == *regexp){
                    c++,regexp++, src++;
                    if(*regexp=='\0'){
                        return src-c-1;
                    }
                }else{
                    if(c==0 && !flag){
                        src++;
                        flag=1;
                    }else{
                        flag = 0;
                        regexp-=c;
                        c=0;
                        while(*src!=' '){
                            src++;
                        }
                    }
                }
            }
            break;
        case '[':
            regexp++;
            int c=0;
            while(*regexp!=']'){
                c++;
                regexp++;
            }
            for(int i=0; i<c; i++){
                while(*src!='\0'){
                     
                }
            }
            break;
        case '\\':
            break;
        default:
            return NULL;
    }
    return NULL;
}

