/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXECurveDivisionEdit_H
#define PNXECurveDivisionEdit_H

// System Framework
#include "CATExtIEdit.h" // To derive from

/**
 * Class extending the object "PNXCurveDivision".
 * It implements the interfaces :
 *      ApplicationFrame.CATIEdit
 *         This interface is called when editing a User Feature.
 *         It associates a dialog panel and fill in the contextual menu of the
 * User Feature.
 */

class PNXECurveDivisionEdit : public CATExtIEdit {
    CATDeclareClass;

public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    PNXECurveDivisionEdit();
    virtual ~PNXECurveDivisionEdit();

    /**
     * Implements the method Activate of the interface CATIEdit
     * see ApplicationFrame.CATIEdit.Activate
     */
    CATCommand* Activate(CATPathElement* ipPath);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXECurveDivisionEdit(PNXECurveDivisionEdit& iObjectToCopy);
    PNXECurveDivisionEdit& operator=(PNXECurveDivisionEdit& iObjectToCopy);
};

#endif
