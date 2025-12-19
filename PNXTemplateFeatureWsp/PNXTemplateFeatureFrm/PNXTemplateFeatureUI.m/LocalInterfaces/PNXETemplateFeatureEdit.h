/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef PNXETemplateFeatureEdit_H
#define PNXETemplateFeatureEdit_H

// System Framework
#include "CATExtIEdit.h" // To derive from

/**
 * Class extending the object "PNXTemplateFeature".
 * It implements the interfaces :
 *      ApplicationFrame.CATIEdit
 *         This interface is called when editing a Sound Hole.
 *         It associates a dialog panel and fill in the contextual menu of the Sound Hole.
 */

class PNXETemplateFeatureEdit : public CATExtIEdit {
    CATDeclareClass;

public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    PNXETemplateFeatureEdit();
    virtual ~PNXETemplateFeatureEdit();

    /**
     * Implements the method Activate of the interface CATIEdit
     * see ApplicationFrame.CATIEdit.Activate
     */
    CATCommand* Activate(CATPathElement* ipPath);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXETemplateFeatureEdit(PNXETemplateFeatureEdit& iObjectToCopy);
    PNXETemplateFeatureEdit& operator=(PNXETemplateFeatureEdit& iObjectToCopy);
};

#endif
