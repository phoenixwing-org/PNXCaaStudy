#======================================================================
# @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
# @license     MIT
# @author      Phoenix Wing
# @checkout    PNXV5V6Adapter.git
# @brief    Imakefile for module PNXV5V6Adapter.m
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
          CATMechanicalModeler         \
          JS0GROUP                      \
          KnowledgeItf                  \       
          CATBasicTopologicalOpe        \
          CATObjectSpecsModeler \
          KTCAutoCodeItf

#Link with with external libraries
LOCAL_LDFLAGS =/LIBPATH:"$(ROOT_DIR_CORE)\lib\bin"

#Link with include file
LOCAL_CCFLAGS = /I"$(ROOT_DIR_CORE)\include" 

#Name of the libraries
SYS_LIBS = KtCore.lib

