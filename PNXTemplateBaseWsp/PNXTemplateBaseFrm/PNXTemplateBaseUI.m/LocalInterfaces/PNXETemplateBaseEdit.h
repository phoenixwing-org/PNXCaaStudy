/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef PNXETemplateBaseEdit_H
#define PNXETemplateBaseEdit_H

// System Framework
#include "CATExtIEdit.h" // To derive from

/**
 * Class extending the object "PNXTemplateBase".
 * It implements the interfaces :
 *      ApplicationFrame.CATIEdit
 *         This interface is called when editing a User Feature.
 *         It associates a dialog panel and fill in the contextual menu of the User Feature.
 */

class PNXETemplateBaseEdit : public CATExtIEdit {
    CATDeclareClass;

public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    PNXETemplateBaseEdit();
    virtual ~PNXETemplateBaseEdit();

    /**
     * Implements the method Activate of the interface CATIEdit
     * see ApplicationFrame.CATIEdit.Activate
     */
    CATCommand* Activate(CATPathElement* ipPath);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXETemplateBaseEdit(PNXETemplateBaseEdit& iObjectToCopy);
    PNXETemplateBaseEdit& operator=(PNXETemplateBaseEdit& iObjectToCopy);
};

#endif
