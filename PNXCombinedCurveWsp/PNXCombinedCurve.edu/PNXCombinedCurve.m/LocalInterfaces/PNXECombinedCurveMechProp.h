#ifndef PNXECombinedCurveMechProp_H
#define PNXECombinedCurveMechProp_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h" // needed to derive from

class PNXECombinedCurveMechProp : public CATBaseUnknown {
    CATDeclareClass;

public:
    PNXECombinedCurveMechProp();
    virtual ~PNXECombinedCurveMechProp();

    virtual int  IsInactive() const;
    virtual void Activate();
    virtual void InActivate();

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXECombinedCurveMechProp(PNXECombinedCurveMechProp& iObjectToCopy);
    PNXECombinedCurveMechProp& operator=(PNXECombinedCurveMechProp& iObjectToCopy);

private:
    int _status;
};

#endif
