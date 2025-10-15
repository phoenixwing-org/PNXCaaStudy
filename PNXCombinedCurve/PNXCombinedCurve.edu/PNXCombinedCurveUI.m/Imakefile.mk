# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module PNXCombinedCurveUI.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
     
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = DI0PANV2 JS0FM JS0GROUP CATDialogEngine CATApplicationFrame
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES) \
    CATMechanicalCommands       \
    CATMechanicalModeler        \
    CATMechanicalModelerUI      \
    CATMecModInterfaces         \
    CATObjectModelerBase        \
    CATObjectSpecsModeler       \
    CATVisualization CATViz     \
    CATInteractiveInterfaces    \
    CATProductStructure1        \
    CATConstraintModelerItf     \
    PNXCombinedCurve

