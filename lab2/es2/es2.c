#include <stdio.h>
#include <stdlib.h>

void malloc2dP(int nr, int nc, int *** pmat, FILE *fin);
void stampa_mat(int **mat, int nr, int nc);
void separa(int **mat, int nr, int nc, int **pv1, int **pv2, int *n1, int *n2);
void stampa_vet(int *vet, int n);

int main(){
    FILE *fp_read;
    int nr, nc, n1, n2;
    int *v1, *v2;

    if((fp_read = fopen("mat.txt", "r")) == NULL){
        printf("Errore di apertura del file");
        return -1;
    }

    fscanf(fp_read, "%d %d", &nr, &nc);
    int **matrice;

    malloc2dP(nr, nc, &matrice, fp_read);
    stampa_mat(matrice, nr, nc);
    separa(matrice, nr, nc, &v1, &v2, &n1, &n2);

    stampa_vet(v1, n1);
    stampa_vet(v2, n2);
    
    free(matrice);
    free(v1); 
    free(v2);
    fclose(fp_read);
    return 0;
}

void stampa_vet(int *vet, int n){
    for(int i=0; i<n; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void stampa_mat(int **mat, int nr, int nc){
    for(int j=0; j<nr; j++){
        for(int i=0; i<nc; i++){
            printf("%d ", mat[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

void separa(int **mat, int nr, int nc, int **vec1, int **vec2, int *n1, int *n2){
    int sz_neri=0, *vet_neri, *vet_bianchi, cr_b=0, cr_n=0, k=0;
    int sz_bianchi= ((nr*nc)%2==0 ? (nc*nr)/2: (nr*nc)/2 +1);
    vet_bianchi = (int*) malloc (sizeof(int)*sz_bianchi);
    if(sz_bianchi*2!= nr*nc) sz_neri=nr*nc/2;
    if(sz_neri) vet_neri= (int*)malloc(sizeof(int)*sz_neri);
    else vet_neri = (int*)malloc(sizeof(int)*sz_bianchi);
    
    for(int j=0; j<nr; j++){
        for(int i=0; i<nc; i++){
            if(k%2==0){
                vet_bianchi[cr_b]= mat[j][i];
                cr_b++;
            }
            else{
                vet_neri[cr_n] = mat[j][i];
                cr_n++;
            }
            k++;
        }
    }

    *vec1 = vet_bianchi;
    *vec2 = vet_neri;

    *n1 = sz_bianchi;
    *n2 = (sz_neri)?sz_neri:sz_bianchi;
}

void malloc2dP(int nr, int nc, int *** pmat, FILE *fin){
    
    int **mat = (int**)malloc(nr*sizeof(int*));
    if(mat==NULL) exit(1);
    for(int j=0; j<nr; j++){
        mat[j] = (int *) malloc(nc*sizeof(int));
        if(mat[j]==NULL) exit(1);
        for(int i=0; i<nc; i++){
            fscanf(fin, "%d", &mat[j][i]);
        }
    }
    
    *pmat = mat;
}