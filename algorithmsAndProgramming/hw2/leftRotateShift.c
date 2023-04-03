#include <stdio.h>


unsigned short rotate_left(unsigned short sayi, unsigned short shift_sayisi) {
    unsigned short sonuc = (sayi << shift_sayisi) | (sayi >> (16 - shift_sayisi));
    return sonuc;
}

int main() {
    unsigned short sayi, shift_sayisi;
    printf("Sayiyi giriniz: ");
    scanf("%hu", &sayi);
    printf("Kac kere otelenecegini giriniz: ");
    scanf("%hu", &shift_sayisi);
    unsigned short sonuc = rotate_left(sayi, shift_sayisi);
    printf("Sonuc: %hu\n", sonuc);
    return 0;
}
