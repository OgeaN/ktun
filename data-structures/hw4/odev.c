#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_SIZE 10

typedef struct{

    int musteri_no;
    char ad[20],soyad[20];
}Musteri;

Musteri veri_liste[MAX_SIZE];
int hash_tablo[MAX_SIZE];

void tabloyuBaslat(){
    for(int i =0; i<MAX_SIZE;i++){

        hash_tablo[i] = -1;
        veri_liste[i].musteri_no = -1;

    } 
}
int tablo_dolumu(){
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if(hash_tablo[i]==-1){
            return -1;
        }
    }
    return 1;
}

int Hash(int musteri_no){

    return ((musteri_no*3)+2) % MAX_SIZE;
}
int Hash_2(int musteri_no){
    if(((musteri_no*7)+2) % MAX_SIZE==0){
        return 1;
    }
    return ((musteri_no*7)+2) % MAX_SIZE;
}


void musteri_ekle(int musteri_no,char * ad,char * soyad ){
    for (int i = 0; i <10; i++){
        int hash_index=(Hash(musteri_no) + i * Hash_2(musteri_no)) % MAX_SIZE;
        if( hash_tablo[hash_index] == -1 ){ 

        hash_tablo[hash_index] = musteri_no;
        
        veri_liste[hash_index].musteri_no = musteri_no;
        strcpy( veri_liste[hash_index].ad , ad);
        strcpy( veri_liste[hash_index].soyad , soyad);
        printf("%s %s isimli musteri eklendi!\n",ad,soyad);
        break;
        } 
    }
}

void musteriBilgileriListele(){

    for(int i =0;i<MAX_SIZE;i++){
        
        printf("\t%d\t- ",i);
        if(veri_liste[i].musteri_no != -1){
            printf("   %d  %s  %s\n",veri_liste[i].musteri_no,veri_liste[i].ad,veri_liste[i].soyad);
        }else printf("\n");
            
    }

}
void tabloyuYazdir(){

    for(int i =0;i<MAX_SIZE;i++){
        printf("\t%d\t %d \n ",i,hash_tablo[i]);
    }
}
void txtEkle(){

    FILE * veri = fopen("veri.txt","r");
    if(veri == NULL){
        printf("dosya okunamadi!\n");
        fclose(veri);
        return;
    }
    int musteri_no;
    char isim[20];
    int soyisim[20];

    while(!feof(veri)){
        fscanf(veri,"%d %s %s \n",&musteri_no,isim,soyisim);
        musteri_ekle(musteri_no,isim,soyisim);
    }

    fclose(veri);
}

int tablodaAra(int musteri_no){
    for (int i = 0; i <10; i++){
        int hash_index=(Hash(musteri_no) + i * Hash_2(musteri_no)) % MAX_SIZE;
        if( hash_tablo[hash_index] == musteri_no ){ 
            return i+1;
        } 
        else if(i==9){
            return -1;
        }
    }

}
float ortalamaAdimSayisi(){
    int toplamAdim=0;
    int degerSayisi=0;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (hash_tablo[i]!=-1)
        {
            toplamAdim+=tablodaAra(hash_tablo[i]);
            degerSayisi++;
        }
    }
    return (float)toplamAdim/degerSayisi;
    
}


int main(){
    tabloyuBaslat();
    txtEkle();
    int musteri_no;
    int sayi;
    int ara;
    char isim[20];
    char soyisim[20];
    

    while(1==1){
		printf("\n------------------------------------------\nMusteri Ekleme(1)\nMusterileri Listele(2)\nHash Tablosunu Listele(3)\nMusteri Ara(4)\nOrtalama Adim sayisi(5)\nCikis(6)\n");
		printf("Kullanmak istediginiz islemin yanindaki sayiyi giriniz: ");
		scanf("%d",&sayi);
        printf("\n------------------------------------------\n");
        if(sayi != 6){
            switch(sayi){
			case 1:
             if(tablo_dolumu()==1){
                printf("Tablo dolu ...");
                break;
            }
				printf("\nEkleme islemine hosgeldiniz.\nMusteri no : ");
                scanf("%d",&musteri_no);
                fflush(stdin);
                printf("Isim : ");
                gets(isim);
                fflush(stdin);
                printf("Soyisim : ");
                fflush(stdin);
                gets(soyisim);
                

                musteri_ekle(musteri_no,isim,soyisim);
				break;

			case 2:
				musteriBilgileriListele();
				break;

			case 3:
				tabloyuYazdir();
				break;

			case 4:

				printf("\nAramak istediginiz musteri numarasi : ");
                scanf("%d",&ara);
                if (tablodaAra(ara)==-1)
                {
                   printf("Bulunamadi!!");
                   break;
                }
                
                printf("Aranilan deger: %d \nVeri %d adimda bulundu.",ara,tablodaAra(ara));
                    
                break;
            case 5:
                printf("Tablonun ortalama adim sayisi %f",ortalamaAdimSayisi());
                break;
		    }

        }else break;

	}
}

