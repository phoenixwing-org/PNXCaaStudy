# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module PNXCombinedCurveUI.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH=PNXCombinedCurve         \
          CATApplicationFrame         \
          CATDialogEngine             \
          CATMechanicalCommands       \
          CATMechanicalModeler        \
          CATMechanicalModelerUI      \
          CATMecModInterfaces         \
          CATObjectModelerBase        \
          CATObjectSpecsModeler       \
          CATVisualization CATViz     \
          CATInteractiveInterfaces    \
          CATProductStructure1    \
          CATConstraintModelerItf \
          DI0PANV2                    \
          JS0FM                       \
          JS0GROUP
