/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @date  		  2021-9-1
 * @file  		  PNXCurveDivisionAdn.h
 * @brief 	    Provide implementation to interface CATIPrtWksAddin
 */

#ifndef PNXCurveDivisionAdn_H
#define PNXCurveDivisionAdn_H

// System Framework
#include "CATBaseUnknown.h" // Needed to derive from CATBaseUnknown

class CATCmdContainer; // Needed by Create Toolbars

/** Class representing an addin of the Part Document Workbench.
 *  It implements the CATIPrtWksAddin interface which
 *  is specified by the workbench as the interface to implement in its addins.
 */
class PNXCurveDivisionAdn : public CATBaseUnknown {
    // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

public:
    PNXCurveDivisionAdn();
    virtual ~PNXCurveDivisionAdn();

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
