#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    FILE *fp1, *fp2;
    fp1 = fopen("sayilar0.txt", "w");
    fp2 = fopen("sayilar1.txt", "w");

    srand(time(NULL)); 

    for (int i = 0; i < 100; i++)
    {
        int sayi = rand() % 101;

        if ((sayi & (1 << 4)) == 0) 
        {
            sayi |= (1 << 3);
            fprintf(fp1, "%d\n", sayi); 
        }
        else if ((sayi & (1 << 4)) != 0) 
        {
            sayi &= ~(1 << 2); 
            fprintf(fp2, "%d\n", sayi); 
        }
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}
