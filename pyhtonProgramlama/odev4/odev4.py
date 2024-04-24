import sqlite3
import re
from collections import Counter


def yukle_metin(veritabani_adi, metin1, metin2):
    conn = sqlite3.connect(veritabani_adi)
    cursor = conn.cursor()

    cursor.execute('''CREATE TABLE IF NOT EXISTS metinler
                      (id INTEGER PRIMARY KEY,
                      metin TEXT)''')

    cursor.execute("INSERT INTO metinler (metin) VALUES (?)", (metin1,))
    cursor.execute("INSERT INTO metinler (metin) VALUES (?)", (metin2,))

    conn.commit()
    conn.close()


def jaccard_benzerlik(metin1, metin2):
    kume1 = set(re.findall(r'\w+', metin1.lower()))
    kume2 = set(re.findall(r'\w+', metin2.lower()))
    benzerlik = len(kume1.intersection(kume2)) / len(kume1.union(kume2))
    return benzerlik

def karsilastir(metin1, metin2):
    score=0
    if len(metin1)>=len(metin2):
        for i in range(len(metin2)):
            if metin1[i]==metin2[i]:
              score+=1
        return score/len(metin2)
    else:
        for i in range(len(metin1)):
            if metin1[i]==metin2[i]:
              score+=1
        return score/len(metin1)
def jaccard_kendi (metin1, metin2):
    fcount = 0 
    scount = 0
    for f in metin1:
        if f in metin2:
            scount += 1
    fcount = len(metin1)+len(metin2)
    score = float(scount) / float(fcount)
    return score

def benzerlik_sonuclari_kaydet(veritabani_adi, dosya_adi):
    conn = sqlite3.connect(veritabani_adi)
    cursor = conn.cursor()

    cursor.execute("SELECT metin FROM metinler")
    metinler = cursor.fetchall()
    print(metinler)
    metin1 = metinler[0][0]
    metin2 = metinler[1][0]

    jaccard_sonuc = jaccard_benzerlik(metin1, metin2)
    ikinci_sonuc=jaccard_kendi(metin1,metin2)
    benim_sonuc=karsilastir(metin1,metin2)
    with open(dosya_adi, 'w') as dosya:
        dosya.write("Jaccard Benzerlik Katsayisi: {:.2f}\n".format(jaccard_sonuc))
        dosya.write("Hazır fonksiyon olmayan Jaccard Benzerlik Katsayısı: {:.2f}\n".format(ikinci_sonuc))
        dosya.write("Sırayla Benzerlik Katsayısı: {:.2f}\n".format(benim_sonuc))
        dosya.write("Benzerlik Durumu:\n")
        if jaccard_sonuc >= 0.5:
            dosya.write("Metinler benzer.\n")
        else:
            dosya.write("Metinler benzer degil.\n")

    print("Jaccard Benzerlik Katsayısı: {:.2f}".format(jaccard_sonuc))
    print("Hazır fonksiyon olmayan Jaccard Benzerlik Katsayısı: {:.2f}".format(ikinci_sonuc))
    print("Sırayla Benzerlik Katsayısı: {:.2f}".format(benim_sonuc))
    if jaccard_sonuc >= 0.5:
        print("Metinler benzer.")
    else:
        print("Metinler benzer değil.")


    cursor.execute("DELETE FROM metinler WHERE id=?",(1,))
    cursor.execute("DELETE FROM metinler WHERE id=?",(2,))
    conn.commit()
    conn.close()


metin1 = input("İlk metni giriniz: ")
metin2 = input("İkinci metni giriniz: ")


veritabani_adi = "metinler.db"
yukle_metin(veritabani_adi, metin1, metin2)


dosya_adi = "benzerlik_durumu.txt"
benzerlik_sonuclari_kaydet(veritabani_adi, dosya_adi)

