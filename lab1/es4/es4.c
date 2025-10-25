#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXC 7
#define MAXP 12
#define MAXA 15

typedef struct {int yyyy, mm, dd;} data;
typedef struct {int ora, min, sec;} orario;

typedef struct {
    char cod_tratta[MAXC], staz_part[MAXP], staz_arr[MAXA];
    data data_part;
    orario orario_part, orario_arr;
    int ritardo;
} corsa;

int core(FILE *fin, int n, corsa cnt[]);
int switch_func(int scelta, int n, corsa cnt[]);
void leggi_tratta(FILE *fin, int n, corsa contenitore[]);
void stampa_tratta_p(corsa *c);
int stampa_tratte(corsa cnt[], int n, int tipo);
void bubble_sort_opt_data(corsa **vpp, int n);
int ric_dic_ricorsiva_stz_p(corsa **p, int l, int r, char key[]);
void copy_ad(corsa srcp[], corsa **p, int n);
void stampa_tratte_p(corsa **vpp, int n);
int ric_dic_ricorsiva_cod_tr_p(corsa **p, int l, int r, char key[]);

int main(){
    FILE *fp_read;
    int n=0;

    if((fp_read = fopen("corse.txt", "r")) == NULL){
        printf("Errore di apertura del file");
        return 1;
    }

    fscanf(fp_read, "%d", &n);
    corsa cnt[n];

    if(core(fp_read, n, cnt) < 0) printf("Errore");

    fclose(fp_read);
    return 0;
}

void leggi_tratta(FILE *fin, int n, corsa contenitore[]){
    char cod_tr[MAXC], part[MAXP], dest[MAXA];
    data data_tratta;
    orario ora_part;
    orario ora_arr;

    for(int i = 0; i<n; i++){
        fscanf(fin, "%s %s %s", cod_tr, part, dest);
        fscanf(fin, "%d/%d/%d", &data_tratta.yyyy, &data_tratta.mm, &data_tratta.dd );
        fscanf(fin, "%d:%d:%d %d:%d:%d", &ora_part.ora, &ora_part.min, &ora_part.sec, &ora_arr.ora, &ora_arr.min, &ora_arr.sec);
        fscanf(fin, "%d", &contenitore[i].ritardo);

        strcpy(contenitore[i].cod_tratta, cod_tr);
        strcpy(contenitore[i].staz_part, part);
        strcpy(contenitore[i].staz_arr, dest),
        contenitore[i].data_part = data_tratta;
        contenitore[i].orario_part = ora_part;
        contenitore[i].orario_arr = ora_arr;
    }
}

void stampa_tratta_p(corsa *c){
    printf("%s %s %s ", c -> cod_tratta, c -> staz_part, c -> staz_arr);
    printf("%d/%.2d/%.2d ", c -> data_part.yyyy, c -> data_part.mm, c -> data_part.dd);
    printf("%.2d:%.2d:%.2d ", c -> orario_part.ora, c -> orario_part.min, c -> orario_part.sec);
    printf("%.2d:%.2d:%.2d ", c -> orario_arr.ora, c -> orario_arr.min, c -> orario_arr.sec);
    printf("%d\n", c -> ritardo);
}

int stampa_tratte(corsa cnt[], int n, int tipo){
    if(tipo==0)
        for(int i=0; i<n; i++) stampa_tratta_p(cnt+i);
    else if(tipo == 1){
        FILE *fout;
        if((fout  = fopen("output.txt", "w")) == NULL){
            return -1;
        }
        for(int i=0; i<n; i++){
            fprintf(fout, "%s %s %s ", cnt[i].cod_tratta, cnt[i].staz_part, cnt[i].staz_arr);
            fprintf(fout, "%d/%.2d/%.2d ", cnt[i].data_part.yyyy, cnt[i].data_part.mm, cnt[i].data_part.dd);
            fprintf(fout, "%.2d:%.2d:%d ", cnt[i].orario_part.ora, cnt[i].orario_part.min, cnt[i].orario_part.sec);
            fprintf(fout, "%.2d:%.2d:%d ", cnt[i].orario_arr.ora, cnt[i].orario_arr.min, cnt[i].orario_arr.sec);
            fprintf(fout, "%d\n", cnt[i].ritardo);
        }
        fclose(fout);
    }
    return 0;
}

void stampa_tratte_p(corsa **vpp, int n){
    corsa c1;
        for(int i=0; i<n; i++){
            c1= **(vpp+i);
            printf("%s %s %s ", c1.cod_tratta, c1.staz_part, c1.staz_arr);
            printf("%d/%.2d/%.2d ", c1.data_part.yyyy, c1.data_part.mm, c1.data_part.dd);
            printf("%.2d:%.2d:%d ", c1.orario_part.ora, c1.orario_part.min, c1.orario_part.sec);
            printf("%.2d:%.2d:%d ", c1.orario_arr.ora, c1.orario_arr.min, c1.orario_arr.sec);
            printf("%d\n", c1.ritardo);
        }
}

void bubble_sort_opt_data(corsa **vpp, int n){ 
    int i, j, l=0, r=n-1, flag = 1;
    corsa *temp, c1, c2;
    
    for(i=l; i<r && flag==1; i++){
        flag=0;
        for(j=l; j<r-i+l; j++){
            c1 = **(vpp+j);
            c2 = **(vpp+j+1);
            if(c1.data_part.yyyy < c2.data_part.yyyy) continue;
            else if(c1.data_part.yyyy == c2.data_part.yyyy && c1.data_part.mm < c2.data_part.mm) continue;
            else if(c1.data_part.yyyy == c2.data_part.yyyy && c1.data_part.mm == c2.data_part.mm && c1.data_part.dd > c2.data_part.dd){
                flag=1;
                temp= vpp[j];
                vpp[j]=vpp[j+1];
                vpp[j+1]=temp;
            }else if (c1.data_part.yyyy == c2.data_part.yyyy && c1.data_part.mm == c2.data_part.mm && c1.data_part.dd == c2.data_part.dd){
                if(c1.orario_part.ora < c2.orario_part.ora) continue;
                else if(c1.orario_part.ora == c2.orario_part.ora && c1.orario_part.min < c2.orario_part.min) continue;
                else if(c1.orario_part.ora == c2.orario_part.ora && c1.orario_part.min == c2.orario_part.min && c1.orario_part.sec > c2.orario_part.sec){
                flag=1;
                temp= vpp[j];
                vpp[j]=vpp[j+1];
                vpp[j+1]=temp;
                }
            } 
            else{
                flag=1;
                temp= vpp[j];
                vpp[j]=vpp[j+1];
                vpp[j+1]=temp;
            }
        }
    }
}

int ric_dic_ricorsiva_cod_tr_p(corsa **p, int l, int r, char key[]){
    int m;
    if(l>r) return -1;
    m=(l+r)/2;

    if(strcmp(key, p[m] -> cod_tratta) == 0) return m;
    if(strcmp(key, p[m] -> cod_tratta) == -1) return ric_dic_ricorsiva_cod_tr_p(p, l, m-1, key);

    return ric_dic_ricorsiva_cod_tr_p(p, m+1, r, key);
}

int ric_dic_ricorsiva_stz_p(corsa **p, int l, int r, char key[]){
    int m;
    if(l>r) return -1;
    m=(l+r)/2;

    if(strncmp(key, p[m] -> staz_part, strlen(key)) == 0) return m;
    if(strncmp(key, p[m] -> staz_part, strlen(key)) < 0) return ric_dic_ricorsiva_stz_p(p, l, m-1, key);

    return ric_dic_ricorsiva_stz_p(p, m+1, r, key);
}

void copy_ad(corsa srcp[], corsa **p, int n){
    for(int i=0; i<n; i++){
        *(p+i) = srcp+i;
    }
    return;
}

int switch_func(int scelta, int n, corsa cnt[]){
    int l, r, flag;
    corsa *temp;
    corsa **vet = (corsa **)malloc(n*(sizeof(corsa*)));
    corsa c,b;
    corsa tmp;

    switch(scelta){
        case 1:
            char chr;
            printf("File (f) o video (v): ");
            getchar();
            scanf("%c", &chr);

            if(tolower(chr)=='v') {if(stampa_tratte(cnt, n, 0) < 0) return -1;}
            else {if(stampa_tratte(cnt, n, 1) < 0) return -1;}
            break;
        case 2:
            copy_ad(cnt, vet, n);

            bubble_sort_opt_data(vet, n);

            stampa_tratte_p(vet, n);
            free(vet);
            break;
        case 3:
            l=0, r=n-1, flag = 1;
            copy_ad(cnt, vet, n);
            
            for(int i=l; i<r && flag==1; i++){
                flag=0;
                for(int j=l; j<r-i+l; j++){
                    c=**(vet+j);
                    b=**(vet+j+1);
                    if(atoi(c.cod_tratta+3) > atoi(b.cod_tratta+3)){
                        flag=1;
                        temp= vet[j];
                        vet[j]=vet[j+1];
                        vet[j+1]=temp;
                    }
                }
            }
            stampa_tratte_p(vet,n);
            break;
        case 4:
            l=0, r=n-1, flag = 1;
            copy_ad(cnt, vet, n);

            for(int i=l; i<r && flag==1; i++){
                flag=0;
                for(int j=l; j<r-i+l; j++){
                    c=**(vet+j);
                    b=**(vet+j+1);
                    if(strcmp(c.staz_part, b.staz_part) > 0){
                        flag=1;
                        temp=vet[j];
                        vet[j]=vet[j+1];
                        vet[j+1]=temp;
                    }
                }
            }
            stampa_tratte_p(vet,n);
            break;
        case 5:
            l=0, r=n-1, flag = 1;
            copy_ad(cnt, vet, n);
            for(int i=l; i<r && flag==1; i++){
                flag=0;
                for(int j=l; j<r-i+l; j++){
                    c=**(vet+j);
                    b=**(vet+j+1);
                    if(strcmp(c.staz_arr, b.staz_arr) > 0){
                        flag=1;
                        temp=vet[j];
                        vet[j]=vet[j+1];
                        vet[j+1]=temp;
                    }
                }
            }
            stampa_tratte_p(vet,n);
            break;
        case 6:
            char cod[MAXC];
            char ch;
            int in;
            printf("Codice: ");
            scanf("%s", cod);

            printf("Ricerca dicotomica (d) o lineare (l)? ");
            getchar();
            scanf("%c", &ch);

            copy_ad(cnt, vet, n);
            if(tolower(ch) != 'd' && tolower(ch) != 'l') return -1;
            else if(tolower(ch) == 'd'){
                // Ordino il vettore per poter effettuare la ricerca dicotomica
                l=0, r=n-1, flag = 1;
                for(int i=l; i<r && flag==1; i++){
                    flag=0;
                    for(int j=l; j<r-i+l; j++){
                        c=**(vet+j);
                        b=**(vet+j+1);
                        if(atoi(c.cod_tratta+3) > atoi(b.cod_tratta+3)){
                            flag=1;
                            temp=vet[j];
                            vet[j]=vet[j+1];
                            vet[j+1]=temp;
                        }
                    }
                }
                in = ric_dic_ricorsiva_cod_tr_p(vet, 0, n, cod);
                corsa co = *vet[in-1];
                while(strcmp(co.cod_tratta, cod) == 0 && in>0) in--;
                stampa_tratta_p(*(vet+in));
                free(vet);
            }else{
                for(int i=0; i<n; i++){
                    if(strcmp(cnt[i].cod_tratta, cod) == 0){
                        stampa_tratta_p(cnt+i);
                        break;
                    }
                }
            }
            break;
        case 7:
            char stz[MAXP];
            char scl;
            int index;
            printf("Stazione: ");
            scanf("%s", stz);
            
            printf("Ricerca dicotomica (d) o lineare (l)? ");
            getchar();
            scanf("%c", &scl);
            copy_ad(cnt, vet, n);
            if(tolower(scl) != 'd' && tolower(scl) != 'l') return -1;
            else if(tolower(scl) == 'd'){
                l=0, r=n-1, flag = 1;                
                for(int i=l; i<r && flag==1; i++){
                    flag=0;
                    for(int j=l; j<r-i+l; j++){
                        c=**(vet+j);
                        b=**(vet+j+1);
                        if(strcmp(c.staz_part, b.staz_part) > 0){
                            flag=1;
                            temp=vet[j];
                            vet[j]=vet[j+1];
                            vet[j+1]=temp;
                        }
                    }
                }
                
                if((index = ric_dic_ricorsiva_stz_p(vet, 0, n, stz)) <0) return -1;

                while(index>0 && strncmp(stz, vet[index-1] -> staz_part, strlen(stz)) == 0)  { 
                    index--;  
                }
                while(index<n && strncmp(vet[index]->staz_part, stz, strlen(stz)) == 0) {
                    stampa_tratta_p(vet[index]);
                    index++;
                }
                
                free(vet);
            }else{
                flag=0;
                for(int m=0; m<n; m++){
                    if(strncmp(stz, cnt[m].staz_part, strlen(stz)) == 0) stampa_tratta_p(cnt+m), flag=1;
                }
                if(!flag) return -1;
            }
            break;
    }
    return 0;
}


int core(FILE *fin, int n, corsa contenitore[]){
    int scelta;
    leggi_tratta(fin, n, contenitore);

    while(1==1){
        printf("Scegli un'opzione (0 per uscire): \n");
        printf("\t1)Stampa a video o file\n");
        printf("\t2)Ordina il vettore per data\n");
        printf("\t3)Ordina il vettore per codice di tratta\n");
        printf("\t4)Ordina il vettore per stazione di partenza\n");
        printf("\t5)Ordina il vettore per stazione di arrivo\n");
        printf("\t6)Ricerca via codice tratta\n");
        printf("\t7)Ricerca via stazione di partenza\n");

        printf("Scegli: ");
        scanf("%d", &scelta);
        if(scelta < 0 || scelta > 7) return -1;
        if(scelta == 0) return 0;
        if(switch_func(scelta, n, contenitore) < 0) return -2;
    }
    return 0;
}