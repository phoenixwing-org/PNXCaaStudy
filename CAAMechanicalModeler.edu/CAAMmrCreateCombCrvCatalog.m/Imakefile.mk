# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module CAAMmrCreateCombinedCurveCatalog.m
#======================================================================
#
BUILT_OBJECT_TYPE=LOAD MODULE

LINK_WITH=CAAMmrCombinedCurve         \
          CATLiteralFeatures \
		  KnowledgeItf \
          CATMecModInterfaces         \
          CATMechanicalModeler        \
          CATNewTopologicalObjects    \
          CATConstraintModelerItf    \
          CATObjectModelerBase        \
          CATObjectSpecsModeler       \
          AC0SPCAA       \
          JS0FM                       \
          JS0GROUP
