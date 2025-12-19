/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @date  		  2025-12-17
 * @file  		  PNXTemplateBaseAdn.h
 * @brief 	    Provide implementation to interface CATIPrtWksAddin
 */

#ifndef PNXTemplateBaseAdn_H
#define PNXTemplateBaseAdn_H

// System Framework
#include "CATBaseUnknown.h" // Needed to derive from CATBaseUnknown

class CATCmdContainer; // Needed by Create Toolbars

/** Class representing an addin of the Part Document Workbench.
 *  It implements the CATIPrtWksAddin interface which
 *  is specified by the workbench as the interface to implement in its addins.
 */
class PNXTemplateBaseAdn : public CATBaseUnknown {
    // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

public:
    PNXTemplateBaseAdn();
    virtual ~PNXTemplateBaseAdn();

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
