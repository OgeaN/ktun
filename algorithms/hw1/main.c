#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DUGUM 7

typedef struct dugum
{ 
int dugum_no;
char *sehir;
struct dugum *pNext;
}DUGUMLER;

typedef struct liste
{
DUGUMLER satir[MAX_DUGUM];
}LISTELER;

LISTELER * graf_ekle(LISTELER *root,int indeks,int no,char *sehir){
    if (root->satir[indeks].dugum_no==-1)
    {
        DUGUMLER * r=((DUGUMLER *) malloc(sizeof(DUGUMLER)));
        r->sehir= (char *)malloc(sizeof(char)* strlen(sehir)+1 );
        strcpy(r->sehir, sehir);
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
    temp->sehir= (char *)malloc(sizeof(char)* strlen(sehir)+1 );
    strcpy(temp->sehir, sehir);
    temp->dugum_no=no;
    temp->pNext=NULL;
    iter->pNext=temp;
    return root;
}

int toplam_kenar(LISTELER *graf){
    int toplam=0;
    for (int i = 0; i < sizeof(graf->satir)/sizeof(graf->satir[0]); i++)
    {
        DUGUMLER *iter=graf->satir;
        iter=iter+i;
        while (iter->pNext!=NULL)
        {   
            toplam++;
            iter=iter->pNext;
        }      
    }
    return toplam;
}

void txtEkle(LISTELER *graf){

    FILE * veri = fopen("graf.txt","r");
    if(veri == NULL){
        printf("dosya okunamadi!\n");
        fclose(veri);
        return;
    }
    char *plakaPtr;
    char line[250];
    char *sehir;
    char *komsuPlakaPtr;
    char *komsuAd;
    int i=0;
    int plaka;
    int komsuPlaka;
while (fgets(line, 50, veri) != NULL) {
       
        sehir = strtok(line, "/");
        plakaPtr = strtok(NULL, " -> ");
        strtok(NULL, " ");
        komsuAd = strtok(NULL, "/");
        komsuPlakaPtr = strtok(NULL, " -> ");
        plaka=atoi(plakaPtr);
        graf=graf_ekle(graf,i,plaka,sehir);
        while (komsuAd != NULL) {
            komsuPlaka=atoi(komsuPlakaPtr);
            graf=graf_ekle(graf,i,komsuPlaka,komsuAd);
            strtok(NULL, " ");
            komsuAd = strtok(NULL, "/");
            komsuPlakaPtr = strtok(NULL, " -> ");
            
        }
        i++;
        
    }

    fclose(veri);
}

void giris_cikis(LISTELER *graf,int plaka){
    char g[]="";
    int giris=0,cikis=0;
    for (int i = 0; i < sizeof(graf->satir)/sizeof(graf->satir[0]); i++)
    {
       DUGUMLER *iter=graf->satir;
       iter=iter+i;
        if (iter->dugum_no==plaka)
        {       
            while (iter->pNext!=NULL)
        {   
            cikis++;
            iter=iter->pNext;
        }    
        }
        while (iter->pNext!=NULL)
        {
            if (iter->pNext->dugum_no==plaka)
            {
                giris++;
            }
            iter=iter->pNext;
        }
    }
printf("Giris derecesi :%d,Cikis Derecesi:%d\n",giris,cikis);
}

void listele(LISTELER *graf){
    for (int i = 0; i < sizeof(graf->satir)/sizeof(graf->satir[0]); i++)
    {
        DUGUMLER *iter=graf->satir;
        iter=iter+i;
        while (iter->pNext!=NULL)
        {
            printf("%s/%d->",iter->sehir,iter->dugum_no);
            
            iter=iter->pNext;
        }
        printf("%s/%d",iter->sehir,iter->dugum_no);
        printf("\n");
        
    }
    printf("\n");
    

}

void gidilir(LISTELER *graf,int plaka){
for (int i = 0; i < sizeof(graf->satir)/sizeof(graf->satir[0]); i++)
    {
       DUGUMLER *iter=graf->satir;
       iter=iter+i;
        if (iter->dugum_no==plaka)
        {
            printf("%d plakali %s sehrinden su sehir dugumlerine gidilir: ",iter->dugum_no,iter->sehir);
        
        while (iter->pNext!=NULL)
        {    
            iter=iter->pNext;
            if (iter->pNext==NULL)
        {
            printf("%s/%d",iter->sehir,iter->dugum_no);
        }
        else{
            printf("%s/%d,",iter->sehir,iter->dugum_no);
        }
            
        }    
        
        
        break;
        }
    }
}

void gelinir(LISTELER *graf,int plaka){
    printf("\n%d plakali sehrine su sehir dugumlerinden gelinir: ",plaka);
    
    for (int i = 0; i < sizeof(graf->satir)/sizeof(graf->satir[0]); i++)
    {
       DUGUMLER *iter=graf->satir;
       iter=iter+i;
            while (iter->pNext!=NULL){   
                if (iter->pNext->dugum_no==plaka){
                    printf("%s/%d,",graf->satir[i].sehir,graf->satir[i].dugum_no);     
        }    
            iter=iter->pNext;
        }
    }
}

int main(){
    int plaka;
    LISTELER *graf=(LISTELER *)malloc(sizeof(LISTELER));
    for(int i =0; i<MAX_DUGUM;i++){
        graf->satir[i].dugum_no = -1;
    } 

    txtEkle(graf);
    printf("\n-------------------------------------------\n");
    listele(graf);
    printf("Toplam Kenar Sayisi=%d \n",toplam_kenar(graf));
    printf("\nBilgilerini ogrenmek istedigin sehrin plaksisi girin : ");
    scanf("%d",&plaka);
    printf("\n");
    for (int i = 0; i < MAX_DUGUM; i++)
    {
        if (graf->satir[i].dugum_no==plaka)
        {
            giris_cikis(graf,plaka);
            gidilir(graf,plaka);
            gelinir(graf,plaka);
            exit(0);
        }
    }
    printf("Girdiginiz plaka bulunamadi...");
}   