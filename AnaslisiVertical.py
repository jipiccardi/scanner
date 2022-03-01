# -*- coding: utf-8 -*-
"""
Created on Mon Feb 28 23:11:13 2022

@author: santi
"""

import open3d as o3d
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


dist_centro=252.77 #Medida con el scanner

df=pd.read_csv('./dataset/linea3_clean.csv',sep=';')  #Leo los datos del csv

df.set_index(['thetha','altura'],drop=False,inplace=True) #Nombre de las columnas

df = df.rename(columns={'thetha':'angulo','altura':'z'})

df = df.groupby(['altura','thetha']).mean() #Promedio de las muestras para un mismo angulo y altura

df['radio'] = -0.0341 * (df.voltage*3300/4095) + 268.73 #Se aplica la curva que convierte tension a distancia
df.radio=dist_centro - df.radio #Se calcula la distancia del centro de la pieza al punto de medicion
df=df[df.radio>0] #Se eliminan las muestras mayores a la distancia al centro 


df['x']=df.radio * np.cos(df.angulo)
df['y']=df.radio * np.sin(df.angulo)


plt.scatter(df.x, df.z,s=1)
#plt.show()
