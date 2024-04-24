metin = input("Metin Giriniz: ")
data={}
ozelKarakter = """!,.?():;'"[]{}<>/\|`~-_ 0123456789*=+%$"""
karakter=0
harf=0
metin=metin.lower()
for isaretci in metin:
    karakter+=1
    if isaretci not in ozelKarakter and karakter not in [100,1000,10000]:
      harf+=1
      if isaretci not in data:
        data[isaretci]=1
      else:
        data[isaretci]+=1
    elif karakter==100:
        print("--------------------------------------------")
        print("100 karakter için veriler analiz ediliyor")
        print("--------------------------------------------")
        for i in data:
            print("{}: number of using: {}  using rate:{:.2f}".format(str(i),str(data.get(i)),float(data.get(i)/harf)*100))
        print("--------------------------------------------")
    elif karakter==1000:
        print("1000 karakter için veriler analiz ediliyor")
        print("--------------------------------------------")
        for i in data:
            print("{}: number of using: {}  using rate:{:.2f}".format(str(i),str(data.get(i)),float(data.get(i)/harf)*100))
        print("--------------------------------------------")
    elif karakter==10000:
        print("10000 karakter için veriler analiz ediliyor")
        print("--------------------------------------------")
        for i in data:
            print("{}: number of using: {}  using rate:{:.2f}".format(str(i),str(data.get(i)),float(data.get(i)/harf)*100))
        print("--------------------------------------------")
    else:
        pass

print(data)