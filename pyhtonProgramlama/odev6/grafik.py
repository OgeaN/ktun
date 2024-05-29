import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
excel_path = 'C:/Users/OgeaN/Desktop/pyhtonProgramlama/odev6/coordinates.xlsx'
# Excel dosyasını okuma


coords_df = pd.read_excel(excel_path)

# Grafiği 100x100 ızgaralarla bölme
grid_size = 100
num_grids = 1000 // grid_size

# Izgara renkleri için bir renk paleti belirleme
colors = plt.cm.tab20(np.linspace(0, 1, num_grids**2))

# Her bir noktaya uygun rengi atama
colors_for_points = []
for x, y in zip(coords_df['x'], coords_df['y']):
    grid_x = x // grid_size
    grid_y = y // grid_size
    grid_index = grid_y * num_grids + grid_x
    colors_for_points.append(colors[grid_index % len(colors)])

# Grafik oluşturma
plt.figure(figsize=(10, 10))
plt.scatter(coords_df['x'], coords_df['y'], c=colors_for_points, s=10)
plt.title('100x100 Tablo')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.show()