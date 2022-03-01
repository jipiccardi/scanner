# -*- coding: utf-8 -*-
"""
Created on Mon Nov  1 00:25:22 2021

@author: Grupo 3
"""
import open3d as o3d
import pandas as pd
import numpy as np

scan_name=["caja2_clean","caja_desfasada_clean",
    "cilindro_clean","cilindro_desf_clean",
    "piramide_clean","piramide_desfasada_clean"]
dist_centro=252.77 #Medida con el scanner


# scan_name=[
#      "piramide_clean"]

for name in scan_name :
    aux="./dataset/"+name+".csv"
    aux2="./Blender/"+name+".ply"
    df=pd.read_csv(aux,sep=';')  #Leo los datos del csv
    df.set_index(['thetha','altura'],drop=False,inplace=True) #Nombre de las columnas
    df = df.rename(columns={'thetha':'angulo','altura':'z'})

    df = df.groupby(['altura','thetha']).mean() #Promedio de las muestras para un mismo angulo y altura
    df['radio'] = -0.0341 * (df.voltage*3300/4095) + 268.73 #Se aplica la curva que convierte tension a distancia
    df.radio=dist_centro - df.radio #Se calcula la distancia del centro de la pieza al punto de medicion
    df=df[df.radio>0] #Se eliminan las muestras mayores a la distancia al centro 

    df.angulo = df.angulo * (8*2*np.pi/2048)
    df['x']=df.radio * np.cos(df.angulo)
    df['y']=df.radio * np.sin(df.angulo)

    point_cloud = np.zeros((df.x.size,3))
    point_cloud[:,0]= df.x 
    point_cloud[:,1]= df.y
    point_cloud[:,2]= df.z*3

    #Representacion nube de puntos
    pcd = o3d.geometry.PointCloud()
    pcd.points = o3d.utility.Vector3dVector(point_cloud)
    pcd.colors = o3d.utility.Vector3dVector(point_cloud/255)
    pcd.normals = o3d.utility.Vector3dVector(point_cloud)
    #o3d.visualization.draw_geometries([pcd])

    #Metodo Poisson
    poisson_mesh = o3d.geometry.TriangleMesh.create_from_point_cloud_poisson(pcd, depth=8, width=0, scale=1.1, linear_fit=False)[0]
    bbox = pcd.get_axis_aligned_bounding_box()
    p_mesh_crop = poisson_mesh.crop(bbox)
    o3d.io.write_triangle_mesh(aux2, p_mesh_crop)