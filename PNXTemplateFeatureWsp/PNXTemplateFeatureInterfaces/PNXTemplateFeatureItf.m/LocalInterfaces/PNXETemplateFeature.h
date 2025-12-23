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

#ifndef PNXETemplateFeature_H
#define PNXETemplateFeature_H

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown
#include "KTCAutoAttrAccess.h"
#include "PNXTemplateFeatureParam.h"

/**
 * Class extending the object "PNXTemplateFeature".
 *
 * It implements the interface :
 *      PNXTemplateFeatureInterfaces.PNXITemplateFeature
 */

class PNXETemplateFeature : public CATBaseUnknown {
    CATDeclareClass;

public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    PNXETemplateFeature();
    virtual ~PNXETemplateFeature();

public: // KEVIN_SYSTEM_CODE
    // KEVIN_SYSTEM_CODE START

    /** @brief GetErrMsg */
    CATUnicodeString GetErrMsg() const; // 0

    /** @brief SetErrMsg */
    HRESULT SetErrMsg(const CATUnicodeString& value); // 0

    /** @brief GetParams */
    HRESULT GetParams(PNXTemplateFeatureParam& value) const;

    /** @brief SetParams */
    HRESULT SetParams(const PNXTemplateFeatureParam& value);

    /**
     * @brief Kt Software saved Version
     * @return int. Version saved in the feature. Start from 0.
     */
    int GetVersion() const; // 0A

    /**
     * @brief Kt Software saved Version
     * @param[in] value target version. Start from 0.
     * @return HRESULT.
     * @note Only used in PNXETemplateFeature::UpdateVersion()
     */
    HRESULT SetVersion(const int& value); // 0A

    /**
     * @brief Update the saved version to software version
     * @return HRESULT
     */
    HRESULT UpdateVersion(); // 0B

    // KEVIN_SYSTEM_CODE END

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature IMPLEMENTS HEAD GET

    // clang-format off
public: // Get
    /**
     * @brief My Curve
     * @return CATISpecObject_var
     * @author Phoenix
     * @date 2025/12/17
     * @id 2
     */
    CATISpecObject_var GetMyCurve() const;

    /**
     * @brief My Faces
     * @return HRESULT
     * @author Phoenix
     * @date 2025/12/17
     * @id 3
     */
    HRESULT GetMyFaces(CATListValCATISpecObject_var& value) const;

    /**
     * @brief My Step
     * @return double
     * @author Phoenix
     * @date 2025/12/17
     * @id 4
     */
    double GetMyStep() const;

    /**
     * @brief My Calc
     * @return CATBoolean
     * @author Phoenix
     * @date 2025/12/17
     * @id 5
     */
    CATBoolean GetFinishCalc() const;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature IMPLEMENTS HEAD GET

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature IMPLEMENTS HEAD SET

    // clang-format off
public: // Set
    /**
     * @brief My Curve
     * @param[in] value CATISpecObject_var
     * @return HRESULT
     * @author Phoenix
     * @date 2025/12/17
     * @id 2
     */
    HRESULT SetMyCurve(const CATISpecObject_var& value, const CATBoolean& checkExist = CATTrue);

    /**
     * @brief My Faces
     * @param[in] value CATListValCATISpecObject_var
     * @return HRESULT
     * @author Phoenix
     * @date 2025/12/17
     * @id 3
     */
    HRESULT SetMyFaces(const CATListValCATISpecObject_var& value, const CATBoolean& checkExist = CATTrue);

    /**
     * @brief My Step
     * @param[in] value double
     * @return HRESULT
     * @author Phoenix
     * @date 2025/12/17
     * @id 4
     */
    HRESULT SetMyStep(const double& value, const CATBoolean& checkExist = CATTrue);

    /**
     * @brief My Calc
     * @param[in] value CATBoolean
     * @return HRESULT
     * @author Phoenix
     * @date 2025/12/17
     * @id 5
     */
    HRESULT SetFinishCalc(const CATBoolean& value, const CATBoolean& checkExist = CATTrue);

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature IMPLEMENTS HEAD SET

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXETemplateFeature(PNXETemplateFeature&);
    PNXETemplateFeature& operator=(PNXETemplateFeature&);
    KTCAutoAttrAccess    ktcSpecRW; // for 	KTCAutoAttrAccess
};

#endif
