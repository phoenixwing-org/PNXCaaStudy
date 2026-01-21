# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module PNXCombinedCurve.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH=CATGeometricObjects          \
          CATCGMGeoMath                   \
          CATMathematics  CATMathStream             \
          CATMecModInterfaces          \
          CATMechanicalModeler         \
          CATConstraintModelerItf         \
          CATNewTopologicalObjects     \
          CATObjectModelerBase         \
          CATObjectSpecsModeler        \
          CATTopologicalOperators      \
          CATInteractiveInterfaces      \
          CATVisualization      \
          JS0GROUP KnowledgeItf

#Link with with external libraries
LOCAL_LDFLAGS =/LIBPATH:"$(ROOT_DIR_CORE)\bin"

#Link with include file
LOCAL_CCFLAGS = /I"$(ROOT_DIR_CORE)\include" 

#Name of the libraries
SYS_LIBS = KtCore.lib