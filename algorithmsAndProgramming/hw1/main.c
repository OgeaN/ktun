#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>


int main(){
    FILE *fp ;
    FILE *fp2;
    int sayi;
    
    srand ( time(NULL) );
    
    int dizi[100];
    for (int i=0; i<100; i++) {
       dizi[i]=rand()%1000;

  }

  fp=fopen("sayilar.txt","w");
  if(fp == NULL){
        printf("dosya okunamadi!\n");
        fclose(fp);
    }
  for (size_t i = 0; i < 100; i++)
  {
    fprintf(fp,"%d \n",dizi[i]);
  }
  fclose(fp);

    fp = fopen("sayilar.txt","r");
    fp2= fopen("sayilar2.txt","w");
    if(fp == NULL){
        printf("dosya okunamadi!\n");
        fclose(fp);
    }
    if(fp2 == NULL){
        printf("dosya okunamadi!\n");
        fclose(fp2);
    }


    while(!feof(fp)){
        fscanf(fp,"%d\n",&sayi);
        int a=0;
        for (int i = 1; i < sayi; i++)
        {
            
            if (sayi%i==0)
            {
                a++;
            }
        }
        if (a==1)
        {
            fprintf(fp2,"%d \n",sayi);
            
        }
        
    }

    fclose(fp);
    fclose(fp2);


    return 0;
}