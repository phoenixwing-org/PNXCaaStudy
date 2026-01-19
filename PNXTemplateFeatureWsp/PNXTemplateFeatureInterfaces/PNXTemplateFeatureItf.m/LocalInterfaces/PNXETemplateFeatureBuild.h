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

#ifndef PNXETemplateFeatureBuild_H
#define PNXETemplateFeatureBuild_H

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

// local
#include "PNXITemplateFeature.h"

/**
 * Class extending the object "PNXTemplateFeature".
 *
 * It implements the interfaces :
 *       ObjectSpecsModeler.CATIBuild
 */

class PNXETemplateFeatureBuild : public CATBaseUnknown {
    CATDeclareClass;

public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    PNXETemplateFeatureBuild();
    virtual ~PNXETemplateFeatureBuild();

    /**
     * Implements the method build of the interface CATIBuild.
     * see ObjectSpecsModeler.CATIBuild.Build
     */
    HRESULT Build();

protected:
    /**
     * @brief build feature
     * @param[in] feature target version. Start from 0.
     * @return HRESULT.
     */
    HRESULT build_feature(PNXITemplateFeature_var feature);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXETemplateFeatureBuild(PNXETemplateFeatureBuild&);
    PNXETemplateFeatureBuild& operator=(PNXETemplateFeatureBuild&);
};

#endif
