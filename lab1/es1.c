#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXS 50
#define MAXE 25

char *cercaRegexp(char *src, char *regexp);

int main(){
    char stringa[]= "cane marino", expreg[] = "\\aane";
    char *p= cercaRegexp(stringa, expreg);
    if(p) printf("La prima occorrenza di '%s' inizia da %p", expreg, p);
    else printf("Non esistono occorrenze di '%s' in '%s'", expreg, stringa);
    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    char *start=src, *rep=regexp;
    while(*src != '\0'){
        if(*src==*regexp) {
            while(*src==*regexp){
                src++, regexp++;
                if(*regexp == '\0' && (*src == ' ' || *src == '\0')){
                    return start;
                }
            }
        }else{
            switch(*regexp){
                case '.':
                    src++, regexp++;
                    if(*regexp == '\0' && (*src == ' ' || *src == '\0')){
                        return start;
                    }
                    break;
                case '[':
                    regexp++;
                    while(*regexp != ']'){
                        if(*regexp == '^'){
                            regexp++;
                            if(*src==*regexp){
                               while(*src!= ' ' && *src!= '\0'){
                                    src++;
                               }
                               while(*regexp!=']') regexp++;
                            }else{
                                while(*regexp!=']'){
                                    regexp++;
                                    if(*src==*regexp){
                                        while(*src!= ' ' && *src!= '\0'){
                                                src++;
                                        }
                                        while(*regexp!=']') regexp++;
                                    }
                                }
                                src++;
                            }
                            if(*regexp == '\0' && (*src == ' ' || *src == '\0')){
                                return start;
                            }
                        }else if(*src!=*regexp && *regexp != ']'){
                            regexp++;
                        }else{
                            src++;
                            while(*regexp != ']') regexp++;
                            if(*regexp == '\0' && (*src == ' ' || *src == '\0')){
                                return start;
                            }
                        }
                    }
                    // regexp deve finire su ]
                    regexp++;
                    if(*regexp == '\0' && (*src == ' ' || *src == '\0')){
                        return start;
                    }
                    break;
                case '\\':
                    regexp++;
                    if(isalpha(*regexp)){
                        if(*regexp == 'a'){
                            if(islower(*src)) regexp++, src++;
                        }else if(*regexp == 'A'){
                            if(isupper(*src)) regexp++, src++;
                        }
                    }
                    if(*regexp == '\0' && (*src == ' ' || *src == '\0')){
                        return start;
                    }
                    break;
                default:
                    regexp=rep;
                    while(*src != ' ' && *src != '\0'){
                        src++;
                    }
                    src++;
                    start=src;
                    break;
                }
            }
        }
    return NULL;
}