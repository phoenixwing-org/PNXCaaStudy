
/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXETemplateFeatureIcon.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef PNXETemplateFeatureIcon_H
#define PNXETemplateFeatureIcon_H

#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

class PNXETemplateFeatureIcon : public CATBaseUnknown {
    CATDeclareClass;

public:
    PNXETemplateFeatureIcon();

    virtual ~PNXETemplateFeatureIcon();

public:
    /**
     * @brief Get Icon Name
     * @param[out] oName Icon filename without extension
     * @return HRESULT
     */
    HRESULT GetIconName(CATUnicodeString& oName);
    /**
     * @brief Set Icon Name
     * @param[in] iName Icon filename without extension
     * @return HRESULT
     */
    HRESULT SetIconName(const CATUnicodeString& iName);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXETemplateFeatureIcon(PNXETemplateFeatureIcon&);
    PNXETemplateFeatureIcon& operator=(PNXETemplateFeatureIcon&);

private:
    // CATUnicodeString _name;
};

#endif
