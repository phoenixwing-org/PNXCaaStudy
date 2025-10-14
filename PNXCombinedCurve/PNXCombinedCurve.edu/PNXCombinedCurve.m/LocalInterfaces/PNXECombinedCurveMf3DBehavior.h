#ifndef PNXECombinedCurveMf3DBehavior_H
#define PNXECombinedCurveMf3DBehavior_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h" // needed to derive from

class PNXECombinedCurveMf3DBehavior : public CATBaseUnknown {
    CATDeclareClass;

public:
    PNXECombinedCurveMf3DBehavior();
    virtual ~PNXECombinedCurveMf3DBehavior();

    virtual HRESULT IsASolid() const;
    virtual HRESULT IsAShape() const;
    virtual HRESULT IsADatum() const;

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXECombinedCurveMf3DBehavior(PNXECombinedCurveMf3DBehavior& iObjectToCopy);
    PNXECombinedCurveMf3DBehavior& operator=(PNXECombinedCurveMf3DBehavior& iObjectToCopy);
};

#endif
