# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================

# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 

LINK_WITH=  JS0GROUP \
            CATObjectModelerBase \
            CATObjectSpecsModeler  \
            CATMecModInterfaces \
            CATMechanicalModeler \
            CATCGMGeoMath CATGeometricObjects \
            CATConstraintModelerItf \
            CATGitInterfaces \
            CATVisualization CATViz \
            CATInteractiveInterfaces
            
#Link with with external libraries
LOCAL_LDFLAGS =/LIBPATH:"$(ROOT_DIR_CORE)\bin"

#Link with include file
LOCAL_CCFLAGS = /I"$(ROOT_DIR_CORE)\include" 

#Name of the libraries
SYS_LIBS = KtCore.lib

