#======================================================================
# @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
# @license     MIT
# @author      Phoenix Wing
# @checkout    PNXCurveDivision.git
# @brief    Imakefile for module PNXCurveDivisionAdn.m
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
          DI0PANV2                  \
          JS0FM                     \
          JS0GROUP \
          PNXCurveDivisionItf

#Link with with external libraries

#Link with include file

#Name of the libraries
				
