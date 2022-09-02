import bpy
import numpy as np
import pandas as pd

path = 'ここにcsvファイルの入っているフォルダのパスを入れてください'


def delete_objs():
    for item in bpy.data.objects:
        bpy.data.objects.remove(item)
    for item in bpy.data.meshes:
        bpy.data.meshes.remove(item)
    for item in bpy.data.materials:
        bpy.data.materials.remove(item)
        

def get_data(n, m):
    df_atoms = pd.read_csv(path + f'atoms_{n}_{m}.csv', index_col=0)
    df_bonds = pd.read_csv(path + f'bonds_{n}_{m}.csv', index_col=0)
    return df_atoms, df_bonds
        

def create_atom(tag, loc, radius):
    bpy.ops.mesh.primitive_uv_sphere_add(segments=32, ring_count=16, radius=radius, calc_uvs=True, enter_editmode=False, align='WORLD', location=loc, rotation=(0.0, 0.0, 0.0), scale=(1.0, 1.0, 1.0))
    obj = list(filter(lambda x: x.name[:6] == 'Sphere', bpy.data.objects))[0]
    obj.name = tag


def create_bond(tag, loc, theta, radius):
    bpy.ops.mesh.primitive_cylinder_add(vertices=32, radius=radius, depth=1.46, end_fill_type='NGON', calc_uvs=True, enter_editmode=False, align='WORLD', location=loc, rotation=theta, scale=(1.0, 1.0, 1.0))
    obj = list(filter(lambda x: x.name[:8] == 'Cylinder', bpy.data.objects))[0]
    obj.name = tag


def main():
#    delete_objs()
    
    df_atoms, df_bonds = get_data(10, 10)
    
    for tag, loc in df_atoms.iterrows():
        create_atom(tag, loc.values, 0.3)

    for tag, item in df_bonds.iterrows():
        loc = item['x':'z'].values
        theta = item['theta_x':'theta_z'].values
        create_bond(tag, loc, theta, 0.1)

#    for obj in bpy.data.objects:
#        print(obj.name)


if __name__ == '__main__':
    main()
