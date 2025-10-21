/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
 * @file
 * @brief       Prereq Components Declaration
 */

AddPrereqComponent("ApplicationFrame", Public);
AddPrereqComponent("CATIAApplicationFrame", Public);
AddPrereqComponent("Dialog", Public);
AddPrereqComponent("DialogEngine", Public);
AddPrereqComponent("GSMInterfaces", Public);
AddPrereqComponent("GeometricObjects", Public);
AddPrereqComponent("LiteralFeatures", Public);
AddPrereqComponent("KnowledgeInterfaces", Public); // pour la CXR9
AddPrereqComponent("Mathematics", Public);
AddPrereqComponent("MecModInterfaces", Public);
AddPrereqComponent("MechanicalCommands", Public);
AddPrereqComponent("MechanicalModeler", Public);
AddPrereqComponent("MechanicalModelerUI", Public);
AddPrereqComponent("NewTopologicalObjects", Public);
AddPrereqComponent("ObjectModelerBase", Public);
AddPrereqComponent("ObjectSpecsModeler", Public);
AddPrereqComponent("System", Public);
AddPrereqComponent("TopologicalOperators", Public);
AddPrereqComponent("Visualization", Public);
AddPrereqComponent("VisualizationBase", Public);
AddPrereqComponent("InteractiveInterfaces", Public);
AddPrereqComponent("SketcherInterfaces", Public);
// bypass link forte 6.1
AddPrereqComponent("ProductStructure", Public);
AddPrereqComponent("ProductStructureUI", Public);
AddPrereqComponent("CATGraphicProperties", Public);

// Split MechanicalModeler/ConstraintModeler/ConstraintModelerInterfaces
AddPrereqComponent("ConstraintModelerInterfaces", Public);
// PNXBomAnalysisInterfaces
AddPrereqComponent("PNXBomAnalysisInterfaces", Public);

