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
          CATMechanicalModeler         \
          CATProductStructure1         \
          JS0GROUP                      \
          KnowledgeItf                  \       
          CATBasicTopologicalOpe        \
          CATObjectSpecsModeler 


#Link with with external libraries

#Link with include file

#Name of the libraries
