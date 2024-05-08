import sys
import sqlite3
import re
from PyQt5.QtWidgets import QApplication,QDialog, QWidget, QVBoxLayout, QLabel, QPushButton, QMessageBox, QFileDialog, QComboBox, QLineEdit, QInputDialog , QHBoxLayout


class LoginWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Kullanıcı Girişi")
        self.setGeometry(100, 100, 300, 150)

        layout = QVBoxLayout()

        self.kullanici_adi_label = QLabel("Kullanıcı Adı:")
        self.kullanici_adi_entry = QLineEdit()
        layout.addWidget(self.kullanici_adi_label)
        layout.addWidget(self.kullanici_adi_entry)

        self.sifre_label = QLabel("Şifre:")
        self.sifre_entry = QLineEdit()
        self.sifre_entry.setEchoMode(QLineEdit.Password)
        layout.addWidget(self.sifre_label)
        layout.addWidget(self.sifre_entry)

        self.giris_button = QPushButton("Giriş Yap")
        self.giris_button.clicked.connect(self.giris)
        layout.addWidget(self.giris_button)

        self.kayit_button = QPushButton("Kayıt Ol")
        self.kayit_button.clicked.connect(self.kayit_ol)
        layout.addWidget(self.kayit_button)

        self.setLayout(layout)

    def giris(self):
        kullanici_adi = self.kullanici_adi_entry.text()
        sifre = self.sifre_entry.text()
        if self.check_credentials(kullanici_adi, sifre):
            self.ana_menu()
            self.close()
        else:
            QMessageBox.critical(self, "Hata", "Kullanıcı adı veya şifre yanlış!")

    def kayit_ol(self):
        kullanici_adi = self.kullanici_adi_entry.text()
        sifre = self.sifre_entry.text()
        self.register_user(kullanici_adi, sifre)

    def check_credentials(self, kullanici_adi, sifre):
        conn = sqlite3.connect("kullanici_bilgileri.db")
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM kullanici WHERE kullanici_adi=? AND sifre=?", (kullanici_adi, sifre))
        if cursor.fetchone():
            return True
        else:
            return False
        conn.close()

    def register_user(self, kullanici_adi, sifre):
        conn = sqlite3.connect("kullanici_bilgileri.db")
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM kullanici WHERE kullanici_adi=?", (kullanici_adi,))
        if cursor.fetchone():
            QMessageBox.critical(self, "Hata", "Bu kullanıcı adı zaten var!")
        else:
            cursor.execute("INSERT INTO kullanici (kullanici_adi, sifre) VALUES (?, ?)", (kullanici_adi, sifre))
            QMessageBox.information(self, "Başarılı", "Kullanıcı kaydedildi.")
        conn.commit()
        conn.close()

    def ana_menu(self):
        self.menu_window = MenuWindow()
        self.menu_window.show()

class MenuWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Ana Menü")
        self.setGeometry(100, 100, 300, 150)

        layout = QVBoxLayout()

        self.karsilastir_button = QPushButton("Karşılaştır")
        self.karsilastir_button.clicked.connect(self.karsilastir_menu)
        layout.addWidget(self.karsilastir_button)

        self.islemler_button = QPushButton("İşlemler")
        self.islemler_button.clicked.connect(self.islemler_menu)
        layout.addWidget(self.islemler_button)

        self.cikis_button = QPushButton("Çıkış")
        self.cikis_button.clicked.connect(self.close)
        layout.addWidget(self.cikis_button)

        self.setLayout(layout)

    def islemler_menu(self):
        self.islemler_window = IslemWindow()
        self.islemler_window.show()

    def karsilastir_menu(self):
        self.karsilastir_window = KarsilastirWindow()
        self.karsilastir_window.show()

class IslemWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("İşlemler Menüsü")
        self.setGeometry(100, 100, 300, 150)

        layout = QVBoxLayout()

        self.sifre_button = QPushButton("Şifre Değiştir")
        self.sifre_button.clicked.connect(self.sifre_degistir)
        layout.addWidget(self.sifre_button)

        self.setLayout(layout)

    def sifre_degistir(self):
        sifre = SifreWindow()
        sifre.exec_()

class SifreWindow(QDialog):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Şifre Değiştir")

        layout = QVBoxLayout()

        self.kullanici_adi_entry = QLineEdit()
        self.kullanici_adi_entry.setPlaceholderText("Kullanıcı Adı")
        layout.addWidget(self.kullanici_adi_entry)

        self.eski_sifre_entry = QLineEdit()
        self.eski_sifre_entry.setPlaceholderText("Eski Şifre")
        self.eski_sifre_entry.setEchoMode(QLineEdit.Password)
        layout.addWidget(self.eski_sifre_entry)

        self.yeni_sifre_entry = QLineEdit()
        self.yeni_sifre_entry.setPlaceholderText("Yeni Şifre")
        self.yeni_sifre_entry.setEchoMode(QLineEdit.Password)
        layout.addWidget(self.yeni_sifre_entry)

        self.sifre_guncelle_button = QPushButton("Şifreyi Güncelle")
        self.sifre_guncelle_button.clicked.connect(self.sifre_guncelle)
        layout.addWidget(self.sifre_guncelle_button)

        self.setLayout(layout)

    def sifre_guncelle(self):
        kullanici_adi = self.kullanici_adi_entry.text()
        eski_sifre = self.eski_sifre_entry.text()
        yeni_sifre = self.yeni_sifre_entry.text()

        if self.check_credentials(kullanici_adi, eski_sifre):
            conn = sqlite3.connect("kullanici_bilgileri.db")
            cursor = conn.cursor()
            cursor.execute("UPDATE kullanici SET sifre=? WHERE kullanici_adi=?", (yeni_sifre, kullanici_adi))
            QMessageBox.information(self, "Başarılı", "Şifre güncellendi.")
            conn.commit()
            conn.close()
        else:
            QMessageBox.critical(self, "Hata", "Eski şifre yanlış!")

    def check_credentials(self, kullanici_adi, eski_sifre):
        conn = sqlite3.connect("kullanici_bilgileri.db")
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM kullanici WHERE kullanici_adi=? AND sifre=?", (kullanici_adi, eski_sifre))
        row = cursor.fetchone()
        conn.close()
        if row:
            return True
        else:
            return False

class KarsilastirWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Metin Karşılaştırma")
        self.setGeometry(100, 100, 400, 100)

        layout = QVBoxLayout()
        
        self.algoritma_combo = QComboBox()
        self.algoritma_combo.addItems(["Jaccard Benzerlik", "Hazır Fonksiyon Olmayan Jaccard", "Sırayla Benzerlik"])
        layout.addWidget(self.algoritma_combo)
        
       
        h1 = QHBoxLayout()
        self.metin1_label = QLabel("Metin 1:")
        h1.addWidget(self.metin1_label)
        self.metin1_entry = QLineEdit()
        h1.addWidget(self.metin1_entry)
        
        self.dosya_sec_button1 = QPushButton("Dosya Seç")
        self.dosya_sec_button1.clicked.connect(self.dosya_sec1)
        h1.addWidget(self.dosya_sec_button1)
        
        layout.addLayout(h1)
        
        
        h2 = QHBoxLayout()
        self.metin2_label = QLabel("Metin 2:")
        h2.addWidget(self.metin2_label)
        self.metin2_entry = QLineEdit()
        h2.addWidget(self.metin2_entry)
        
        self.dosya_sec_button2 = QPushButton("Dosya Seç")
        self.dosya_sec_button2.clicked.connect(self.dosya_sec2)
        h2.addWidget(self.dosya_sec_button2)
        
        layout.addLayout(h2)

       
        self.karsilastir_button = QPushButton("Karşılaştır")
        self.karsilastir_button.clicked.connect(self.karsilastir)
        layout.addWidget(self.karsilastir_button)

        
        self.sonuc_label = QLabel()
        layout.addWidget(self.sonuc_label)

        self.setLayout(layout)

    def dosya_sec1(self):
        dosya, _ = QFileDialog.getOpenFileName(self, "Metin Dosyası Seç", "", "Text Files (*.txt)")
        if dosya:
            self.metin1_entry.setText(dosya)
            self.metin1 = self.read_text_file(dosya)

    def dosya_sec2(self):
        dosya, _ = QFileDialog.getOpenFileName(self, "Metin Dosyası Seç", "", "Text Files (*.txt)")
        if dosya:
            self.metin2_entry.setText(dosya)
            self.metin2 = self.read_text_file(dosya)

    def read_text_file(self, dosya):
        with open(dosya, 'r', encoding='utf-8') as file:
            return file.read()

    def karsilastir(self):
        algoritma_index = self.algoritma_combo.currentIndex()

        if hasattr(self, 'metin1') and hasattr(self, 'metin2'):
            metin1 = self.metin1
            metin2 = self.metin2

            if algoritma_index == 0:
                result = jaccard_benzerlik(metin1, metin2)
            elif algoritma_index == 1:
                result = jaccard_kendi(metin1, metin2)
            elif algoritma_index == 2:
                result = karsilastir(metin1, metin2)

            self.sonuc_label.setText(f"Karşılaştırma Sonucu: {result}")
        else:
            QMessageBox.critical(self, "Hata", "Lütfen iki metin dosyası seçin.")

def jaccard_benzerlik(metin1, metin2):
    kume1 = set(re.findall(r'\w+', metin1.lower()))
    kume2 = set(re.findall(r'\w+', metin2.lower()))
    benzerlik = len(kume1.intersection(kume2)) / len(kume1.union(kume2))
    return benzerlik

def karsilastir(metin1, metin2):
    score = 0
    if len(metin1) >= len(metin2):
        for i in range(len(metin2)):
            if metin1[i] == metin2[i]:
                score += 1
        return score / len(metin2)
    else:
        for i in range(len(metin1)):
            if metin1[i] == metin2[i]:
                score += 1
        return score / len(metin1)

def jaccard_kendi(metin1, metin2):
    fcount = 0
    scount = 0
    for f in metin1:
        if f in metin2:
            scount += 1
    fcount = len(metin1) + len(metin2)
    score = float(scount) / float(fcount)
    return score

if __name__ == '__main__':
    app = QApplication(sys.argv)
    login = LoginWindow()
    login.show()
    sys.exit(app.exec_())
