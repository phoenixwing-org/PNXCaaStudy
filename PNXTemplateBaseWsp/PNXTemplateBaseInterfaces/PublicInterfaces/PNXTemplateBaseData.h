/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @file  		PNXTemplateBaseData.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef PNXTemplateBaseData_H
#define PNXTemplateBaseData_H

// System  Framework
#include "CATBaseUnknown.h"
#include "CATISO.h"
#include "CATISpecObject.h"
#include "CATMathTransformation.h"

// CAT pre-declare class
class PNXITemplateBase;
class CATIGSMTool;
class CATIPrtPart;
class CATFrmEditor;
class CAT3DRep;

// Kt
#include "KtListV.h"

// Local Framework
#include "PNXTemplateBaseItf.h"
#include "PNXTemplateBaseParam.h"

/** @brief Core of Line create */
class ExportedByPNXTemplateBaseItf PNXTemplateBaseData {

public:
    /** @brief Standard constructors and destructors */
    PNXTemplateBaseData();
    virtual ~PNXTemplateBaseData();

private:
    /** @brief  Copy constructor and equal operator prevent to copy */
    PNXTemplateBaseData(PNXTemplateBaseData&);
    PNXTemplateBaseData& operator=(PNXTemplateBaseData&);

public:
    /**
     * @brief sample fuction
     */
    int sample_function() const;

public:
    // START KEVIN CAA WIZARD SECTION PNXTemplateBaseDataPublic PARAM DECLARATION

    // clang-format off

    // @app Kt Auto Code
    // @version 5.0.0, (2024)

    /**
     * @brief Current Element
     * @author Phoenix
     * @date 2025/12/17
     * @id 100
     */
    CATISpecObject_var featureCurrent_;

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
    PNXTemplateBaseParam* parameter;

    /**
     * @brief CAA Frame Editor
     * @author Phoenix
     * @date 2025/12/17
     * @id 103
     */
    CATFrmEditor* catFrmEditor_;

    /**
     * @brief CATISO pointer
     * @author Phoenix
     * @date 2025/12/17
     * @id 104
     */
    CATISO* catISO_;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBaseDataPublic PARAM DECLARATION

protected:
    // START KEVIN CAA WIZARD SECTION PNXTemplateBaseDataProtected PARAM DECLARATION

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
    // END KEVIN CAA WIZARD SECTION PNXTemplateBaseDataProtected PARAM DECLARATION

    int code_;
};

#endif
