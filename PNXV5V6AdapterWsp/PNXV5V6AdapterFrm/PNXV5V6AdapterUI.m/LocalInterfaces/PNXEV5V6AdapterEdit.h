/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXEV5V6AdapterEdit_H
#define PNXEV5V6AdapterEdit_H

// System Framework
#include "CATExtIEdit.h" // To derive from

/**
 * Class extending the object "PNXV5V6Adapter".
 * It implements the interfaces :
 *      ApplicationFrame.CATIEdit
 *         This interface is called when editing a Sound Hole.
 *         It associates a dialog panel and fill in the contextual menu of the
 * Sound Hole.
 */

class PNXEV5V6AdapterEdit : public CATExtIEdit {
    CATDeclareClass;

public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    PNXEV5V6AdapterEdit();
    virtual ~PNXEV5V6AdapterEdit();

    /**
     * Implements the method Activate of the interface CATIEdit
     * see ApplicationFrame.CATIEdit.Activate
     */
    CATCommand* Activate(CATPathElement* ipPath);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXEV5V6AdapterEdit(PNXEV5V6AdapterEdit& iObjectToCopy);
    PNXEV5V6AdapterEdit& operator=(PNXEV5V6AdapterEdit& iObjectToCopy);
};

#endif
