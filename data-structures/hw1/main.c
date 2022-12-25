#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_LINE_LENGTH 1000



typedef struct yemekler{
    char *yemekismi;
    int gr;
    float fiyat;


    struct yemekler * sonraki;
}yemek;

yemek * Ara(yemek * r,int yemekismi)
{ yemek *gecici;
    gecici=r;
    while(gecici)
    {
        if(strcmp(gecici->yemekismi,yemekismi)==0) return gecici;
        gecici=gecici->sonraki;
        return gecici;
    }
    return NULL;
}

void bastir(yemek * r){
    yemek * gecici=r;
    printf("%s %dgr %.2fTL \n",gecici->yemekismi,gecici->gr,gecici->fiyat);
    gecici = gecici -> sonraki;
    while (gecici != r){
        printf("%s %dgr %.2fTL \n",gecici->yemekismi,gecici->gr,gecici->fiyat);
        gecici = gecici -> sonraki;
    }
    printf("\n");
}

yemek * ekle (yemek * r,char *yemekismi,int gr,float fiyat){
    if( r == NULL){
        r = (yemek *) malloc (sizeof ( yemek) );
        r -> sonraki = r;
        r -> gr = gr;
        r->yemekismi = yemekismi;
        r->fiyat=fiyat;

        return r;
    }
    if(r->fiyat > fiyat){
        yemek * temp = ( yemek * ) malloc (sizeof ( yemek ) );
        temp -> gr = gr;
        temp->yemekismi = yemekismi;
        temp->fiyat=fiyat;
        temp -> sonraki = r;
        yemek * gecici=r;
        while(gecici->sonraki != r){
            gecici=gecici->sonraki;
        }
        gecici->sonraki=temp;
        return temp;
    }
    yemek * gecici = r;
    while(gecici -> sonraki != r && gecici -> sonraki -> fiyat < fiyat ){
        gecici = gecici -> sonraki;
    }

    yemek * temp = (yemek*)malloc(sizeof(yemek));
    temp->sonraki = gecici->sonraki;
    gecici->sonraki = temp;
    temp -> gr = gr;
    temp-> yemekismi = yemekismi;
    temp->fiyat=fiyat;
    return r;
}

yemek * sil(yemek *r, char *yemekismi){
    yemek *temp;
    yemek *gecici = r;
    if(strcmp(r->yemekismi,yemekismi)==0 ){
        while(gecici->sonraki != r){
            gecici=gecici->sonraki;
        }
        gecici->sonraki=r->sonraki;
        free(r);
        return gecici->sonraki;
    }

    while (gecici->sonraki != r && strcmp(gecici->sonraki->yemekismi , yemekismi )!=0){
        gecici = gecici->sonraki;
    }
    if (gecici->sonraki == r){
        printf( "Yemek Bulunamadi!\n" );
        return r;
    }
    temp = gecici->sonraki;
    gecici->sonraki = gecici->sonraki->sonraki;
    free (temp);
    return r;
}
int main(){
    setlocale(LC_ALL, "Turkish");
    yemek * bilgi;
    bilgi = NULL;
    int secim;
    char yemekismi[30];
    char silinecekyemek[30];
    int gram;
    float ucret;
    char    line[MAX_LINE_LENGTH];


    char yemekadi[30];
    int gr;
    float tutar;

    bilgi= ekle(bilgi,"Et_Doner",100,49.5);
    bilgi= ekle(bilgi,"Tavuk_Doner",100,24.5);
    bilgi= ekle(bilgi,"Mercimek_Corbasi",150,19.9);
    bilgi= ekle(bilgi,"Kofte",200,59.9);




    while(1){
        printf("1-Ekleme \n2-Silme \n3-Listeleme \n4-Yemek Secimi \n0-Cikis\n" );
        printf("Yapmak istediginiz islemi giriniz : ");
        scanf("%d",&secim);
        if(secim==1){
            printf("Yemek ismi :");
            scanf("%s",yemekismi);
            printf("gr :");
            scanf("%d",&gram);
            printf("fiyat :");
            scanf("%f",&ucret);
            bilgi= ekle(bilgi,yemekismi,gram,ucret);
        }
        else if(secim==2){
            printf("Silmek istediginiz yemek ismi :");
            scanf("%s",silinecekyemek);
            bilgi= sil(bilgi,silinecekyemek);
        }
        else if(secim==3){
            bastir(bilgi);
        }
        else if(secim==4){
            char a[30];
            bastir(bilgi);
            printf("istediginiz yemegin ismini giriniz : ");
            scanf("%s",a);
            printf("%s Yemegini sectiniz afiyet olsun\n",a);

        }
        else if(secim==0){
            exit(0);
        }
    }





}