#include <stdio.h>
#include <string.h>

#define MAXL 30

typedef struct{ int anno; int mese; int giorno;} date;
typedef struct{ int ora; int minuti; int secondi;} timestamp;
typedef struct {
    char cod_tratta[MAXL];
    char partenza[MAXL];
    char destinazione[MAXL];
    date giorno;
    timestamp orario_partenza;
    timestamp orario_arrivo;
    int ritardo;
} tratta;

typedef enum{r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_err} comando;


void leggi_tratte(FILE *fin, tratta contenitore[], int n);
void esegui_comando(comando cmd, tratta contenitore[], int n);
int core(tratta contenitore[], int n);

int main(){
    FILE *fp_read;
    int n;
    
    if((fp_read = fopen("log.txt", "r")) == NULL){
        printf("Errore durante l'apertura del file");
        return 1;
    }
    
    fscanf(fp_read, "%d", &n);
    tratta tratte[n];

    leggi_tratte(fp_read, tratte, n);

    if(core(tratte, n) < 0) printf("Errore");
    
    return 0;
}


void leggi_tratte(FILE *fin, tratta contenitore[], int n){
    int rit;
    char cod_tr[MAXL], part[MAXL], dest[MAXL];
    date data;
    timestamp ora_part;
    timestamp ora_arr;

    
    for(int i = 0; i<n; i++){
        fscanf(fin, "%s %s %s", cod_tr, part, dest);
        fscanf(fin, "%d/%d/%d", &data.anno, &data.mese, &data.giorno );
        fscanf(fin, "%d:%d:%d %d:%d:%d", &ora_part.ora, &ora_part.minuti, &ora_part.secondi, &ora_arr.ora, &ora_arr.minuti, &ora_arr.secondi);
        fscanf(fin, "%d", &rit);


        strcpy(contenitore[i].cod_tratta, cod_tr);
        strcpy(contenitore[i].partenza, part);
        strcpy(contenitore[i].destinazione, dest),
        contenitore[i].giorno = data;
        contenitore[i].orario_partenza = ora_part;
        contenitore[i].orario_arrivo = ora_arr;
        contenitore[i].ritardo = rit;
    }

    return;
}

void esegui_comando(comando cmd, tratta cnt[], int n){
    int c=0;
    char fermata[20];
    date data1;
    date data2;
    switch(cmd){
        case r_date:
            printf("Intervallo di date (prima la partenza) con il seguente formato e separate da spz <yyyy/mm/dd>\n");
            scanf("%d/%d/%d", &data1.anno, &data1.mese, &data1.giorno);
            scanf(" %d/%d/%d", &data2.anno, &data2.mese, &data2.giorno);
            for(int i=0; i<n; i++){
                if(cnt[i].giorno.anno > data2.anno || cnt[i].giorno.anno < data1.anno ){
                    continue;
                }else if((cnt[i].giorno.anno == data1.anno && cnt[i].giorno.mese < data1.mese) || (cnt[i].giorno.anno == data2.anno && cnt[i].giorno.mese > data2.mese)){
                    continue;
                }else if((cnt[i].giorno.anno == data1.anno && cnt[i].giorno.mese == data1.mese && cnt[i].giorno.giorno < data1.giorno) || (cnt[i].giorno.anno == data2.anno && cnt[i].giorno.mese == data2.mese && cnt[i].giorno.giorno > data2.giorno) ){
                    continue;
                }else{
                    printf("%s\n", cnt[i].cod_tratta);
                    c=1;
                }
            }
            if(c==0) printf("Non ci sono corse in queste date\n");
            break;
        case r_partenza:
            printf("Di quale fermata vuoi ottenere le relative partenze? ");
            scanf("%s", fermata);
            for(int i=0; i<n; i++){
                if(strcmp(cnt[i].partenza, fermata) == 0){
                    printf("%s\n", cnt[i].cod_tratta);
                    c=1;
                }
            }
            if(c==0) printf("Non ci sono partenze da questa feramta\n");
            break; 
        case r_capolinea:
            printf("Di quale capolinea cerchi le tratte? ");
            scanf("%s", fermata);
            for(int i=0; i<n; i++){
                if(strcmp(cnt[i].destinazione, fermata)==0){
                    printf("%s\n", cnt[i].cod_tratta);
                    c=1;
                }
            }
            if(c==0) printf("Questa fermata non è un capolinea\n");
            break; 
        case r_ritardo:
            printf("Intervallo di date (prima la partenza) con il seguente formato e separate da spz <yyyy/mm/dd>\n");
            scanf("%d/%d/%d", &data1.anno, &data1.mese, &data1.giorno);
            scanf(" %d/%d/%d", &data2.anno, &data2.mese, &data2.giorno);
            for(int i=0; i<n; i++){
                if(cnt[i].giorno.anno > data2.anno || cnt[i].giorno.anno < data1.anno ){
                    continue;
                }else if((cnt[i].giorno.anno == data1.anno && cnt[i].giorno.mese < data1.mese) || (cnt[i].giorno.anno == data2.anno && cnt[i].giorno.mese > data2.mese)){
                    continue;
                }else if((cnt[i].giorno.anno == data1.anno && cnt[i].giorno.mese == data1.mese && cnt[i].giorno.giorno < data1.giorno) || (cnt[i].giorno.anno == data2.anno && cnt[i].giorno.mese == data2.mese && cnt[i].giorno.giorno > data2.giorno) ){
                    continue;
                }else{
                    if(cnt[i].ritardo != 0){
                        printf("%s\n", cnt[i].cod_tratta);
                        c=1;
                    }
                }
            }
            if(c==0) printf("In questo intervallo di date non sono stati effettuati ritardi\n");
            break;
        case r_ritardo_tot:
            int rit_tot=0;
            char tratta[10];
            printf("Codice tratta: ");
            scanf("%s", tratta);
            for(int i=0; i<n;i++){
                if(strcmp(cnt[i].cod_tratta, tratta) == 0) rit_tot += cnt[i].ritardo;
            }
            if(rit_tot) printf("La tratta ha accumulato: %d minuti\n", rit_tot);
            else printf("La tratta non ha effettuato ritardi o non esiste\n");
            break; 

    }
}
int core(tratta contenitore[], int n){
    int flag = 0;
    char scelta[12];
    char tab_comandi[6][12] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    comando cmd;
    

    while(!flag){
        printf("Scegli un opzione tramite il suo rispettivo comando:\n");
        printf("\t[date] tutte le corse partite in un certo intervallo di date\n");
        printf("\t[partenza] tutte le corse partite da una certa fermata\n");
        printf("\t[capolinea] tutte le corse aventi una specifica destinazione\n");
        printf("\t[ritardo] tutte le corse che hanno raggiunto la destinazione in ritardo, in un certo intervallo di date\n");
        printf("\t[ritardo_tot] ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta\n");
        printf("\t[fine] terminare il programma\n");

        scanf("%s", scelta);
        if(strcmp(scelta, "fine")==0){
            flag = 1;
            continue;
        }
        cmd = r_date;
        while(cmd<r_err && strcmp(scelta, tab_comandi[cmd])!=0){
            cmd++;
        }

        if (cmd==r_err) return -1;
        
        esegui_comando(cmd, contenitore, n);
    }

    return 0;
}
