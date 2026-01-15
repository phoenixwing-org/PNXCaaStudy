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

#ifndef PNXITemplateFeature_H
#define PNXITemplateFeature_H

// Local Framework
#include "PNXTemplateFeatureItf.h"
#include "PNXTemplateFeatureParam.h"

// System Framework
#include "CATBaseUnknown.h"
#include "CATISpecObject.h"
#include "CATListOfDouble.h"
#include "CATUnicodeString.h"

extern ExportedByPNXTemplateFeatureItf IID IID_PNXITemplateFeature;

/**
 * Interface to manage User Features.
 *
 *  Role : use this interface to get / set the input of a User Feature.
 *         A User Feature is the intersection of two extruded surfaces.
 *         Each of the two surfaces is buildt using a curve (profile) and a direction (of
 * extrusion). Consequently, a User Feature has two input curves and two input directions.
 */

class ExportedByPNXTemplateFeatureItf PNXITemplateFeature : public CATBaseUnknown {
    CATDeclareInterface;

public: // KEVIN_SYSTEM_CODE
    // KEVIN_SYSTEM_CODE START
    /** @brief GetErrMsg */
    virtual CATUnicodeString GetErrMsg() const = 0; // 0

    /** @brief SetErrMsg */
    virtual HRESULT SetErrMsg(const CATUnicodeString& value) = 0; // 0

    /** @brief GetParams */
    virtual HRESULT GetParams(PNXTemplateFeatureParam& value) const = 0;

    /** @brief SetParams */
    virtual HRESULT SetParams(const PNXTemplateFeatureParam& value) = 0;

    /**
     * @brief Kt Software saved Version
     * @return int. Version saved in the feature. Start from 0.
     */
    virtual int GetVersion() const = 0; // 0A

    /**
     * @brief Kt Software saved Version
     * @param[in] value target version. Start from 0.
     * @return HRESULT.
     * @note Only used in PNXETemplateFeature::UpdateVersion() and factory
     */
    virtual HRESULT SetVersion(const int& value) = 0; // 0A

    /**
     * @brief Update the saved version to software version
     * @return HRESULT
     */
    virtual HRESULT UpdateVersion() = 0; // 0X

    // KEVIN_SYSTEM_CODE END

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature INTERFACES HEAD GET

    // clang-format off
public: // Get
    /**
     * @brief My Curve
     * @return CATISpecObject_var
     * @author Phoenix
     * @date 2025/12/17
     * @id 2
     */
    virtual CATISpecObject_var GetMyCurve() const = 0;

    /**
     * @brief My Faces
     * @return HRESULT
     * @author Phoenix
     * @date 2025/12/17
     * @id 3
     */
    virtual HRESULT GetMyFaces(CATListValCATISpecObject_var& value) const = 0;

    /**
     * @brief My Step
     * @return double
     * @author Phoenix
     * @date 2025/12/17
     * @id 4
     */
    virtual double GetMyStep() const = 0;

    /**
     * @brief My Calc
     * @return CATBoolean
     * @author Phoenix
     * @date 2025/12/17
     * @id 5
     */
    virtual CATBoolean GetFinishCalc() const = 0;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature INTERFACES HEAD GET

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature INTERFACES HEAD SET

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
    virtual HRESULT SetMyCurve(const CATISpecObject_var& value, const CATBoolean& checkExist = CATTrue) = 0;

    /**
     * @brief My Faces
     * @param[in] value CATListValCATISpecObject_var
     * @return HRESULT
     * @author Phoenix
     * @date 2025/12/17
     * @id 3
     */
    virtual HRESULT SetMyFaces(const CATListValCATISpecObject_var& value, const CATBoolean& checkExist = CATTrue) = 0;

    /**
     * @brief My Step
     * @param[in] value double
     * @return HRESULT
     * @author Phoenix
     * @date 2025/12/17
     * @id 4
     */
    virtual HRESULT SetMyStep(const double& value, const CATBoolean& checkExist = CATTrue) = 0;

    /**
     * @brief My Calc
     * @param[in] value CATBoolean
     * @return HRESULT
     * @author Phoenix
     * @date 2025/12/17
     * @id 5
     */
    virtual HRESULT SetFinishCalc(const CATBoolean& value, const CATBoolean& checkExist = CATTrue) = 0;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature INTERFACES HEAD SET
};

/** @brief Macro for Handlers  */
CATDeclareHandler(PNXITemplateFeature, CATBaseUnknown);
#endif
