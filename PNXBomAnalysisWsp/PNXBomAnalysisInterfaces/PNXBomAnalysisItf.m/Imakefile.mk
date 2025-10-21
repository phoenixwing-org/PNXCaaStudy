#======================================================================
# @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
# @license     MIT
# @author      Phoenix Wing
# @checkout    PNXBomAnalysis.git
# @brief    Imakefile for module PNXBomAnalysis.m
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
          KTCCoreToolkit                \
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
          KTCCoreToolkit
#endif

#Link with with external libraries
LOCAL_LDFLAGS =/LIBPATH:"$(KT_ROOT)\kt\core\lib"

#Link with include file
LOCAL_CCFLAGS = /I"$(KT_ROOT)\kt\core\include" 

#Name of the libraries
SYS_LIBS = KtCore.lib
