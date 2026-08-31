#======================================================================
# @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
# @license     MIT
# @author      Phoenix Wing
# @checkout    PNXTemplateFeature
# @brief    Imakefile for module PNXTemplateFeatureAdn.m
# SHARED LIBRARY 
#======================================================================

BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH=CATApplicationFrame         \
          CATDialogEngine             \
          CATMathematics			\
          CATMechanicalCommands       \
          CATMechanicalModeler        \
          CATMechanicalModelerUI      \
          CATMecModInterfaces         \
          CATObjectModelerBase        \
          CATObjectSpecsModeler       \
          CATVisualization CATViz     \
          CATInteractiveInterfaces    \
          CATProductStructure1		\
          CATConstraintModelerItf	\
          DI0PANV2                  \
          JS0FM                     \
          JS0GROUP					\
          PNXTemplateFeatureItf     \
          KTCAutoCodeItf		    \
          KTCAutoCodeUI

#Link with with external libraries
LOCAL_LDFLAGS =/LIBPATH:"$(ROOT_DIR_CORE)\bin"

#Link with include file
LOCAL_CCFLAGS = /I"$(ROOT_DIR_CORE)\include" 

#Name of the libraries
SYS_LIBS = KtCore.lib
				