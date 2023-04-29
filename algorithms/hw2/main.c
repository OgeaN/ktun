#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_DUGUM 9

int color[MAX_DUGUM]; // 0 white 1 gray 2 black
int pred[MAX_DUGUM];
int d[MAX_DUGUM];
int f[MAX_DUGUM];
int time;

typedef struct dugum
{ 
int dugum_no;
struct dugum *pNext;
}DUGUMLER;

typedef struct liste
{
DUGUMLER satir[MAX_DUGUM];
}LISTELER;

LISTELER * grafEkle(LISTELER *root,int indeks,int no){
    if (root->satir[indeks].dugum_no==-1)
    {
        DUGUMLER * r=((DUGUMLER *) malloc(sizeof(DUGUMLER)));
        r->dugum_no=no;
        r->pNext=NULL;
        root->satir[indeks]=*r;
        return root;
    }
    DUGUMLER * iter=root->satir;
   iter=iter+indeks;
    while (iter->pNext!=NULL)
    {
       iter=iter->pNext;
    }
    DUGUMLER * temp=(DUGUMLER *) malloc(sizeof (DUGUMLER));
    temp->dugum_no=no;
    temp->pNext=NULL;
    iter->pNext=temp;
    return root;
}

void listele(LISTELER *graf){
    printf("Komsuluk Listesi Gosterimi: \n");
    for (int i = 0; i < sizeof(graf->satir)/sizeof(graf->satir[0]); i++)
    {
        DUGUMLER *iter=graf->satir;
        iter=iter+i;
        while (iter->pNext!=NULL)
        {
            printf("%d :",iter->dugum_no);
            
            iter=iter->pNext;
        }
        printf("%d",iter->dugum_no);
        printf("\n");
        
    }
    printf("\n");
    

}

void txtEkle(LISTELER *graf){

    FILE * veri = fopen("graf.txt","r");
    if(veri == NULL){
        printf("dosya okunamadi!\n");
        fclose(veri);
        return;
    }
    char line[17];
    char * noPtr;
    int no;
    int i=0;
    printf("Matrix: \n");
while (fgets(line, 50, veri) != NULL) {
        int j = 0;
        noPtr = strtok(line," ");
        //int noIndex = 0;
        no=atoi(noPtr);
        graf=grafEkle(graf,i,i);
        if (no==1)
        {
            grafEkle(graf,i,j);
        }
        printf(" %d ",no);
        
        for (j=1; j < MAX_DUGUM; j++)
        {
            noPtr = strtok(NULL, " ");
            no = atoi(noPtr);
            printf(" %d ",no);
            if (no==1)
            {
                graf=grafEkle(graf,i,j);  
            }
        }
    printf("\n");
    i++;
}
printf("\n");
fclose(veri);
}

void DFSVisit(LISTELER * graf,int node) {
    color[node] = 1;
    d[node]=++time; 
    printf("%d ", node); 
    DUGUMLER *iter=&graf->satir[node];
    while (iter!=NULL)
    {
        int gecici=iter->dugum_no;
        if (color[gecici]==0)
        {
            pred[gecici]=node;
            DFSVisit(graf,gecici);
        }
        iter=iter->pNext;
    }
    color[node]=2;
    f[node]=++time;
}

void DFS(LISTELER * graf,int num_nodes) {
    for(int i=0; i<num_nodes; i++) {
        color[i] = 0; 
        pred[i]=-1;
    }
    time=0;
    for(int i=0; i<num_nodes; i++) {
        if(color[i] == 0) { 
            DFSVisit(graf,i);
        }
    }
}




int main(){
    LISTELER *graf=(LISTELER *)malloc(sizeof(LISTELER));
    for(int i =0; i<MAX_DUGUM;i++){
        graf->satir[i].dugum_no = -1;
    } 
    txtEkle(graf);
    listele(graf);
    printf("DFS ile gezilme sirasi: \n");
    DFS(graf,9);
    for (int i = 0; i < MAX_DUGUM; i++)
    {
        printf("\n %d.elamanin son durumdaki \n"
       "Rengi:%d ,"
       "Parenti:%d "
       "ilk bulunma zamani:%d "
       "islenme zamani:%d \n ", i, color[i], pred[i], d[i], f[i]);
    }
    
}