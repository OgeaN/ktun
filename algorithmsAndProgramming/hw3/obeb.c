#include <stdio.h>
#include <stdlib.h>

int ebob(int sayi1,int sayi2,int sayi3){
        if (sayi1%sayi3==0 && sayi2%sayi3==0)
        {
            return sayi3;
        }
        ebob(sayi1,sayi2,sayi3-1);
        
    }


int main(){
    int sayi1,sayi2,sayi3,sonuc;
    printf("1. tamsayi degerini giriniz :");
    scanf("%d",&sayi1);
    printf("2. tamsayi degerini giriniz :");
    scanf("%d",&sayi2);
    sayi3=sayi1;

    sonuc=ebob(sayi1,sayi2,sayi3);
    printf("Girilen iki tam sayinin obebi : %d",sonuc);

}