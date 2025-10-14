#ifndef PNXECombinedCurveInputDescription_H
#define PNXECombinedCurveInputDescription_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATIniInputDescriptionAdaptor.h" // needed to derive from

class PNXECombinedCurveInputDescription : public CATIniInputDescriptionAdaptor {
    CATDeclareClass;

public:
    PNXECombinedCurveInputDescription();
    virtual ~PNXECombinedCurveInputDescription();

    virtual HRESULT
        GetListOfModifiedFeatures(CATListValCATBaseUnknown_var& oListOfModifiedFeatures);

    virtual HRESULT GetMainInput(CATBaseUnknown_var& oMainInput);

    virtual HRESULT GetFeatureType(CATIInputDescription::FeatureType& oFeature_type);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXECombinedCurveInputDescription(PNXECombinedCurveInputDescription&);
    PNXECombinedCurveInputDescription& operator=(PNXECombinedCurveInputDescription&);
};

#endif
