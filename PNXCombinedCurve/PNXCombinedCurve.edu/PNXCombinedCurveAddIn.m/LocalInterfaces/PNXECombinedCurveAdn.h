// COPYRIGHT DASSAULT SYSTEMES 2000
#ifndef PNXECombinedCurveAdn_H
#define PNXECombinedCurveAdn_H

// System Framework
#include "CATBaseUnknown.h" // Needed to derive from CATBaseUnknown

class CATCmdContainer; // Needed by CreateToolbars

/** Class representing an addin of the CATIShapeDesign Workbench.
 *  It implements the CATIShapeDesignWorkshopAddin interface which
 *  is specified by the workbench as the interface to implement in its addins.
 */
class PNXECombinedCurveAdn : public CATBaseUnknown {
    // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

public:
    PNXECombinedCurveAdn();
    virtual ~PNXECombinedCurveAdn();

    /**
     * Instantiates the command headers for the commands.
     */
    void CreateCommands();

    /**
     * Creates toolbars and arranges the commands inside.
     */
    CATCmdContainer* CreateToolbars();
};
#endif
