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

#ifndef PNXETemplateFeatureFactory_H
#define PNXETemplateFeatureFactory_H

// Local Framework
#include "PNXITemplateFeature.h"
#include "PNXTemplateFeatureItf.h"
#include "PNXTemplateFeatureParam.h"

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CATISpecObject;

/**
 * @brief PNXTemplateFeature Factory
 * @note Class extending the CATPrtCont object: The container of specifications
 * in the Part document.It implements the interfaces :
 * PNXTemplateFeatureInterfaces.PNXITemplateFeatureFactory
 */
class PNXETemplateFeatureFactory : public CATBaseUnknown {
    CATDeclareClass;

public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    PNXETemplateFeatureFactory();
    virtual ~PNXETemplateFeatureFactory();

public:
    /**
     * @brief Create PNXITemplateFeature Instance
     * @param[in] ioParam Param value
     * @param[out] ospObjectOnTemplateFeature Out Instance pointer
     * @return HRESULT
     */
    HRESULT CreateTemplateFeature(PNXTemplateFeatureParam& ioParam,
                                  CATISpecObject_var&      ospObjectOnTemplateFeature);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXETemplateFeatureFactory(PNXETemplateFeatureFactory&);
    PNXETemplateFeatureFactory& operator=(PNXETemplateFeatureFactory&);
};

#endif
