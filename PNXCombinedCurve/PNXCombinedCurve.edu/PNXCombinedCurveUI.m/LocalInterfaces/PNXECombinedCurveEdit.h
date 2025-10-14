#ifndef PNXECombinedCurveEdit_H
#define PNXECombinedCurveEdit_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATExtIEdit.h" // To derive from

/**
 * Class extending the object "CombinedCurve".
 * It implements the interfaces :
 *      ApplicationFrame.CATIEdit
 *         This interface is called when editing a Combined Curve.
 *         It associates a dialog panel and fill in the contextual menu of the Combined Curve.
 */

class PNXECombinedCurveEdit : public CATExtIEdit {
    CATDeclareClass;

public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    PNXECombinedCurveEdit();
    virtual ~PNXECombinedCurveEdit();

    /**
     * Implements the method Activate of the interface CATIEdit
     * see ApplicationFrame.CATIEdit.Activate
     */
    CATCommand* Activate(CATPathElement* ipPath);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXECombinedCurveEdit(PNXECombinedCurveEdit& iObjectToCopy);
    PNXECombinedCurveEdit& operator=(PNXECombinedCurveEdit& iObjectToCopy);
};

#endif
