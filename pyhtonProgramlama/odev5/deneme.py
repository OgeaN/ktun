import sys
from PyQt5.QtWidgets import QApplication, QWidget, QHBoxLayout, QLabel, QPushButton

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Yan Yana Widgetlar")
        self.setGeometry(100, 100, 400, 200)

        layout = QHBoxLayout()

        label1 = QLabel("Label 1")
        layout.addWidget(label1)

        button1 = QPushButton("Button 1")
        layout.addWidget(button1)

        self.setLayout(layout)

app = QApplication(sys.argv)
window = MainWindow()
window.show()
sys.exit(app.exec_())