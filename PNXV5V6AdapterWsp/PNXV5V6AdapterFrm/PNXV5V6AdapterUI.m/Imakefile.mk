#======================================================================
# @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
# @license     MIT
# @author      Phoenix Wing
# @checkout    PNXV5V6Adapter.git
# @brief    Imakefile for module PNXV5V6AdapterAdn.m
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
          PNXV5V6AdapterItf \
          KTCAutoCodeUI   \
          KTCAutoCodeItf
				
