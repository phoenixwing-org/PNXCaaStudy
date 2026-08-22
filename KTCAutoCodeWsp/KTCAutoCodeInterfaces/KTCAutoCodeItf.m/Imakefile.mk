#======================================================================
# @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
# @license     MIT
# @author      Phoenix Wing
# @checkout    KTCAutoCode
# @brief    Imakefile for module KTCAutoCode.m
# SHARED LIBRARY 
#======================================================================

BUILT_OBJECT_TYPE=SHARED LIBRARY 

#ifdef CATIAV5R25
LINK_WITH=CATGeometricObjects          \
          CATCGMGeoMath                \
          CATApplicationFrame          \
          CATGraphicProperties         \
	      CATGitInterfaces             \
          CATMathematics               \
          CATMathStream                \
          CATMecModInterfaces          \
          CATMechanicalModeler         \
          CATConstraintModelerItf      \
          CATNewTopologicalObjects     \
          CATObjectModelerBase         \
          CATObjectSpecsModeler        \
          CATTopologicalOperators      \
          CATInteractiveInterfaces     \
          CATVisualization              \
          JS0GROUP                      \
          KnowledgeItf                  \       
          CATBasicTopologicalOpe        \
          CATMeasureGeometryInterfaces  \   
          KTCAutoCodeItf                \
          FeatureModelerExt
#else

LINK_WITH=CATGeometricObjects          \
          CATCGMGeoMath                \
          CATApplicationFrame          \
          CATGraphicProperties         \
	      CATGitInterfaces             \
          CATMathematics               \
          CATMathStream                \
          CATMecModInterfaces          \
          CATMechanicalModeler         \
          CATConstraintModelerItf      \
          CATNewTopologicalObjects     \
          CATObjectModelerBase         \
          CATObjectSpecsModeler        \
          CATTopologicalOperators      \
          CATInteractiveInterfaces     \
          CATVisualization              \
          JS0GROUP                      \
          KnowledgeItf                  \       
          CATBasicTopologicalOpe        \
          CATMeasureGeometryInterfaces  \   
          KTCAutoCodeItf                \
#endif

#Link with with external libraries
LOCAL_LDFLAGS =/LIBPATH:"$(ROOT_DIR_CORE)\lib\bin"

#Link with include file
LOCAL_CCFLAGS = /I"$(ROOT_DIR_CORE)\include" 

#Name of the libraries
SYS_LIBS = KtCore.lib
