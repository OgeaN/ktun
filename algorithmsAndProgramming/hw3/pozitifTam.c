#include <stdio.h>
#include <stdlib.h>

int tamSayiBulucu(int sayi,int basla){
    if (basla>sayi)
    {
        return 0;
    }
    
    
    return basla + tamSayiBulucu(sayi,basla+1);
    
}


int main(){

    int sonuc,sayi;
    printf("Sayiyi giriniz : ");
    scanf("%d",&sayi);
    sonuc=tamSayiBulucu(sayi,1);
    printf("%d",sonuc);
}