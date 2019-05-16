
def dependency_type():
    return 'binary_only'

#def default_lib_dir():
#    return ''

def default_libs(env):
    return 'graflib grafX11 packlib mathlib kernlib X11'.split()

def gsim_libs(env):
    return 'geant321 pawlib graflib grafX11 packlib lapack mathlib kernlib blas X11'.split()


#def load_flags(env):
#    return False
