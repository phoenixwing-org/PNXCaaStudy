/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @date  		  2025-12-17
 * @file  		  PNXTemplateFeatureAdn.h
 * @brief 	    Provide implementation to interface CATIPrtWksAddin
 */

#ifndef PNXTemplateFeatureAdn_H
#define PNXTemplateFeatureAdn_H

// System Framework
#include "CATBaseUnknown.h" // Needed to derive from CATBaseUnknown

class CATCmdContainer; // Needed by Create Toolbars

/** Class representing an addin of the Part Document Workbench.
 *  It implements the CATIPrtWksAddin interface which
 *  is specified by the workbench as the interface to implement in its addins.
 */
class PNXTemplateFeatureAdn : public CATBaseUnknown {
    // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

public:
    PNXTemplateFeatureAdn();
    virtual ~PNXTemplateFeatureAdn();

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
