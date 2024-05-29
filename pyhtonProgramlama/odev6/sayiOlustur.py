import numpy as np
import pandas as pd

num_points = 1000
x_coords = np.random.randint(0, 1001, num_points)
y_coords = np.random.randint(0, 1001, num_points)

coords_df = pd.DataFrame({
    'x': x_coords,
    'y': y_coords
})

# DataFrame'i bir Excel dosyasına kaydetme
excel_path = 'C:/Users/OgeaN/Desktop/pyhtonProgramlama/odev6/coordinates.xlsx'
coords_df.to_excel(excel_path, index=False)

excel_path
