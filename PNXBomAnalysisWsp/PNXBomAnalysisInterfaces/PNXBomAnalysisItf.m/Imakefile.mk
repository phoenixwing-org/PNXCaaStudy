#======================================================================
# @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
# @license     MIT
# @author      Phoenix Wing
# @checkout    PNXBomAnalysis.git
# @brief    Imakefile for module PNXBomAnalysis.m
# SHARED LIBRARY 
#======================================================================

BUILT_OBJECT_TYPE=SHARED LIBRARY 


LINK_WITH=CATGeometricObjects          \
          CATCGMGeoMath                \
          CATApplicationFrame          \
          CATGraphicProperties         \
	      CATGitInterfaces             \
          CATMathematics               \
          CATMathStream                \
          CATMecModInterfaces          \
          CATObjectModelerBase         \
          CATMechanicalModeler         \
          CATProductStructure1         \
          JS0GROUP                      \
          KnowledgeItf                  \       
          CATBasicTopologicalOpe        \
          CATObjectSpecsModeler \
          KTCAutoCodeItf

#Link with with external libraries
LOCAL_LDFLAGS =/LIBPATH:"$(ROOT_DIR_CORE)\bin"

#Link with include file
LOCAL_CCFLAGS = /I"$(ROOT_DIR_CORE)\include" 

#Name of the libraries
SYS_LIBS = KtCore.lib

