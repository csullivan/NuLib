from PyNuLib import *
import numpy as np

def InitializeNuLib():
    parameters_filename = "./parameters"
    Pynulib.standard_nulib_init()
    Pynulib.weakrate_init()

def GetNuclei():
    species = []

    #print(Pynulib.nuclei_a)

    for i, a in enumerate(pynulib.nuclei_a):
        species.append((a,pynulib.nuclei_z[i]))
    return species

def InitWeakRateLib():
    Pynulib.weakrate_init()
