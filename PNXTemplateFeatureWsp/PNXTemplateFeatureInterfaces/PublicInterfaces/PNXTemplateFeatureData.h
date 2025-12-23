/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXTemplateFeatureData.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef PNXTemplateFeatureData_H
#define PNXTemplateFeatureData_H

// System  Framework
#include "CATBaseUnknown.h"
#include "CATISO.h"
#include "CATISpecObject.h"
#include "CATMathTransformation.h"

// CAT pre-declare class
class PNXITemplateFeature;
class CATIGSMTool;
class CATIPrtPart;
class CATFrmEditor;
class CAT3DRep;

// Kt
#include "KtListV.h"

// Local Framework
#include "PNXTemplateFeatureItf.h"
#include "PNXTemplateFeatureParam.h"

/** @brief Core of Line create */
class ExportedByPNXTemplateFeatureItf PNXTemplateFeatureData {

public:
    /** @brief Standard constructors and destructors */
    PNXTemplateFeatureData();
    virtual ~PNXTemplateFeatureData();

private:
    /** @brief  Copy constructor and equal operator prevent to copy */
    PNXTemplateFeatureData(PNXTemplateFeatureData&);
    PNXTemplateFeatureData& operator=(PNXTemplateFeatureData&);

public:
    /**
     * @brief sample fuction
     */
    int sample_function() const;

public:
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataPublic PARAM DECLARATION

    // clang-format off

    // @app Kt Auto Code
    // @version 5.0.0, (2024)

    /**
     * @brief Current Element
     * @author Phoenix
     * @date 2025/12/17
     * @id 100
     */
    CATISpecObject_var _featureCurrent;

    /**
     * @brief My Feature
     * @author Phoenix
     * @date 2025/12/17
     * @id 101
     */
    CATISpecObject_var feature;

    /**
     * @brief Param pointer
     * @author Phoenix
     * @date 2025/12/17
     * @id 102
     */
    PNXTemplateFeatureParam* parameter;

    /**
     * @brief CAA Frame Editor
     * @author Phoenix
     * @date 2025/12/17
     * @id 103
     */
    CATFrmEditor* _catFrmEditor;

    /**
     * @brief CATISO pointer
     * @author Phoenix
     * @date 2025/12/17
     * @id 104
     */
    CATISO* _catISO;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataPublic PARAM DECLARATION

protected:
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataProtected PARAM DECLARATION

    // clang-format off

    // @app Kt Auto Code
    // @version 5.0.0, (2024)

    /**
     * @brief My data
     * @author Kevin
     * @date 2025/12/17
     * @id 200
     */
    double _myData;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataProtected PARAM DECLARATION

    int _code;
};

#endif
