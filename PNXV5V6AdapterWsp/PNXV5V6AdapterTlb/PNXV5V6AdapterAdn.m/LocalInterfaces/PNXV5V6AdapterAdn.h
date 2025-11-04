/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
 * @date  		  2021-9-1
 * @file  		  PNXV5V6AdapterAdn.h
 * @brief 	    Provide implementation to interface CATIPrtWksAddin
 */

#ifndef PNXV5V6AdapterAdn_H
#define PNXV5V6AdapterAdn_H

// System Framework
#include "CATBaseUnknown.h" // Needed to derive from CATBaseUnknown

class CATCmdContainer; // Needed by Create Toolbars

/** Class representing an addin of the Part Document Workbench.
 *  It implements the CATIPrtWksAddin interface which
 *  is specified by the workbench as the interface to implement in its addins.
 */
class PNXV5V6AdapterAdn : public CATBaseUnknown {
    // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

public:
    PNXV5V6AdapterAdn();
    virtual ~PNXV5V6AdapterAdn();

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
