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

#ifndef PNXITemplateFeatureFactory_H
#define PNXITemplateFeatureFactory_H

// Local Framework
#include "PNXITemplateFeature.h"
#include "PNXTemplateFeatureItf.h"
#include "PNXTemplateFeatureParam.h"

// System Framework
#include "CATBaseUnknown.h"
#include "CATISpecObject.h"

extern ExportedByPNXTemplateFeatureItf IID IID_PNXITemplateFeatureFactory;

/**
 * @brief PNXTemplateFeature Factory
 * @note Class extending the CATPrtCont object: The container of specifications
 * in the Part document.It is an interface for:
 * PNXTemplateFeatureInterfaces.PNXITemplateFeatureFactory
 */
class ExportedByPNXTemplateFeatureItf PNXITemplateFeatureFactory : public CATBaseUnknown {
    CATDeclareInterface;

public:
    /**
     * @brief Create PNXITemplateFeature Instance
     * @param[in] parameter parameter pointer
     * @param[out] ospFeature Out Instance smart pointer
     * @return HRESULT
     * @note Implements the method create of the interface PNXITemplateFeatureFactory
     */
    virtual HRESULT create(PNXTemplateFeatureParam* parameter, CATISpecObject_var& ospFeature) = 0;
};

/** @brief Macro for Handlers  */
CATDeclareHandler(PNXITemplateFeatureFactory, CATBaseUnknown);
#endif
