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

#ifndef PNXTemplateFeatureParam_H
#define PNXTemplateFeatureParam_H

#include "CATISpecObject.h"
#include "CATListOfDouble.h"
#include "CATMathAxis.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATUnicodeString.h"

// ObjectSpecModeler Framework
#include "CATLISTV_CATISpecObject.h"

// KTC
#include "KTCAutoCode.h"
#include "KTCAutoDefine.h"
#include "KTCAutoParam.h"
#include "PNXTemplateFeatureItf.h"

// Kt
#include "KtString.h"

/** @brief Field Type */
enum PNXTemplateFeatureField {
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature DLG DEFINE FIELD TYPE

    // clang-format off
    //.............................................................................
    // @key    DlgDefineFieldType
    //.............................................................................
    Field_PNXTemplateFeature_None = 0, // None
    Field_PNXTemplateFeature_MyCurve = 1, // MyCurve
    Field_PNXTemplateFeature_MyFaces = 2, // MyFaces

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature DLG DEFINE FIELD TYPE
};

/** @brief KTC TemplateFeature Param */
class ExportedByPNXTemplateFeatureItf PNXTemplateFeatureParam : public KTCAutoParam {
public:
    /** @brief Standard constructors and destructors */
    PNXTemplateFeatureParam();
    virtual ~PNXTemplateFeatureParam();

    /** @brief Copy constructor and equal operator */
    PNXTemplateFeatureParam(const PNXTemplateFeatureParam&);
    PNXTemplateFeatureParam& operator=(const PNXTemplateFeatureParam&);

public:
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature PARAM DECLARATION

    // clang-format off

    // @app Kt Auto Code
    // @version 5.0.0, (2024)

    /**
     * @brief My Curve
     * @author Phoenix
     * @date 2025/12/17
     * @id 2
     */
    CATISpecObject_var MyCurve;

    /**
     * @brief My Faces
     * @author Phoenix
     * @date 2025/12/17
     * @id 3
     */
    CATListValCATISpecObject_var MyFaces;

    /**
     * @brief My Step
     * @author Phoenix
     * @date 2025/12/17
     * @id 4
     */
    double MyStep;

    /**
     * @brief My Calc
     * @author Phoenix
     * @date 2025/12/17
     * @id 5
     */
    CATBoolean FinishCalc;

    /**
     * @brief My Axis
     * @author Phoenix
     * @date 2025/12/17
     * @id 100
     */
    CATMathAxis MyAxis;

    /**
     * @brief My time string
     * @author Phoenix
     * @date 2025/12/17
     * @id 101
     */
    KtString MyTime;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature PARAM DECLARATION

public: // KEVIN_SYSTEM_CODE
    // KEVIN_SYSTEM_CODE START
    /**
     * @brief get the software version
     * @return software version
     * @note KEVIN_SYSTEM_CODE
     */
    static int GetSoftwareVersion();

    // KEVIN_SYSTEM_CODE END

public: // functions
    /**
     * @brief checkout
     * @return HRESULT
     */
    HRESULT CheckoutAxis();
};

#endif
