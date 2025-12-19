#======================================================================
# @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
# @license     MIT
# @author      Phoenix Wing
# @checkout    PNXBomAnalysis.git
# @brief    Imakefile for module PNXBomAnalysisAdn.m
# SHARED LIBRARY 
#======================================================================

BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH=CATApplicationFrame         \
          CATDialogEngine             \
          CATMathematics			\
          CATMechanicalCommands       \
          CATMecModInterfaces         \
          CATObjectModelerBase        \
          CATObjectSpecsModeler \
          CATMechanicalModelerUI \
          CATProductStructure1 \
          DI0PANV2                  \
          JS0FM                     \
          JS0GROUP \
          PNXBomAnalysisItf \
          KTCAutoCodeUI   \
          KTCAutoCodeItf

#Link with with external libraries
LOCAL_LDFLAGS =/LIBPATH:"$(ROOT_DIR_CORE)\bin"

#Link with include file
LOCAL_CCFLAGS = /I"$(ROOT_DIR_CORE)\include" 

#Name of the libraries
SYS_LIBS = KtCore.lib

