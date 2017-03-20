import numpy as np
from PyNuLib import *

# This is a helper module meant to import the necessary PyNuLib code
# and wrap functionality up into simply python functions and classes.
# If you would like to expose additional NuLib internals (from the
# f90 runtime), you can do so in src/pyinterface.F90

def InitializeNuLib():
    parameters_filename = "./parameters"
    Pynulib.standard_nulib_init()
    Pynulib.weakrate_init()

def GetNuclei():
    species = []
    for i, a in enumerate(pynulib.nuclei_a):
        species.append((a,pynulib.nuclei_z[i]))
    return species

def InitWeakRateLib():
    Pynulib.weakrate_init()
