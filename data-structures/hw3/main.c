#include <stdio.h>
#include <string.h>

const char alfabe[10][5]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

void yazdirma(char sayi[],int n,int indis,char sonuc[]){
    if (indis==n)
    {
        printf("%s ",sonuc);
        return;
    }
    for (int i = 0; i <strlen(alfabe[sayi[indis]-48]) ; i++)
    {
        sonuc[indis]=alfabe[sayi[indis]-48][i];
        yazdirma(sayi,n,indis+1,sonuc);
    }
}


int main (){
    int n;
    char sayi[10];
    printf("Sayiyi giriniz :");
    scanf("%s",&sayi);
    n=strlen(sayi);
    char sonuc[n];
    sonuc[n]='\0';
    yazdirma(sayi,n,0,sonuc);

}