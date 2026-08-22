#======================================================================
# @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
# @license     MIT
# @author      Phoenix Wing
# @checkout    PNXTemplateFeature
# @brief    Imakefile for module PNXTemplateFeatureCatalog.m
# SHARED LIBRARY 
#======================================================================
BUILT_OBJECT_TYPE=LOAD MODULE

LINK_WITH=CATLiteralFeatures         \
		  KnowledgeItf               \
          CATMecModInterfaces        \
          CATMechanicalModeler       \
          CATNewTopologicalObjects   \
          CATConstraintModelerItf    \
          CATObjectModelerBase       \
          CATObjectSpecsModeler      \
          AC0SPCAA                   \
          JS0FM                      \
          JS0GROUP                   \
          KTCAutoCodeItf

#Link with with external libraries
LOCAL_LDFLAGS =/LIBPATH:"$(ROOT_DIR_CORE)\lib\bin"

#Link with include file
LOCAL_CCFLAGS = /I"$(ROOT_DIR_CORE)\include" 

#Name of the libraries
SYS_LIBS = KtCore.lib