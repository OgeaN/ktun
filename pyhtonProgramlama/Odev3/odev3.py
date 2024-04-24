class Personel:
    def __init__(self, adi, departmani, calisma_yili, maas):
        self.adi = adi
        self.departmani = departmani
        self.calisma_yili = calisma_yili
        self.maas = maas

class Firma:
    def __init__(self):
        self.personel_listesi = []

    def personel_ekle(self, personel):
        self.personel_listesi.append(personel)

    def personel_listele(self):
        for personel in self.personel_listesi:
            print("Adı:", personel.adi)
            print("Departmanı:", personel.departmani)
            print("Çalışma Yılı:", personel.calisma_yili)
            print("Maaşı:", personel.maas)
            print("----------------------")

    def maas_zammi(self, personel, zam_orani):
        personel.maas += personel.maas * (zam_orani / 100)

    def personel_cikart(self, personel):
        self.personel_listesi.remove(personel)
if __name__ == "__main__":
    personel1 = Personel("Ahmet", "dsda", 5, 5000)
    personel2 = Personel("Ayşe", "gdfg", 3, 4500)
    
    firma = Firma()
    firma.personel_ekle(personel1)
    firma.personel_ekle(personel2)
    firma.personel_listele()

    
    firma.maas_zammi(personel1, 10)
    firma.maas_zammi(personel2, 8) 

    
    firma.personel_listele()

    
    firma.personel_cikart(personel1)

   
    firma.personel_listele()
