import datetime
from datetime import datetime, timedelta
from time import strptime

def harf_frekans(metin):
    data={}
    ozelKarakter = """!,.?():;'"[]{}<>/\|`~-_ 0123456789*=+%$"""
    karakter=0
    harf=0
    metin=metin.lower()
    for isaretci in metin:
        karakter+=1
        if isaretci not in ozelKarakter:
            harf+=1
            if isaretci not in data:
                data[isaretci]=1
            else:
                data[isaretci]+=1
    
    print("--------------------------------------------")
    for i in data:
        print("{}: number of using: {}  using rate:{:.2f}".format(str(i),str(data.get(i)),float(data.get(i)/harf)*100))
    print("--------------------------------------------")

def bilgi_ver():
    print("Osman Gündemir")
    print("221220094")
    print("Merhaba Python Programlama İnşallah Ödev 2 Tam Puan")
        
def harf_kontrol(metin):
    if metin.isalpha():
        return True
    else:
        return False

def kucuk_harf_cevir(metin):
    return metin.lower()

def uzunluk(metin):
    uzunluk=0
    for isaretci in metin:
        uzunluk+=1
    return uzunluk

def asal_mi(sayi):
    if sayi < 2:
        return False
    for i in range(2, int(sayi ** 0.5) + 1):
        if sayi % i == 0:
            return False
    return True

def gelecek_tarih(tarih, gun_sayisi):
    tarih_obj = datetime.strptime(tarih, "%Y-%m-%d")
    gelecek = tarih_obj - timedelta(days=gun_sayisi)
    return gelecek.strftime("%Y-%m-%d")