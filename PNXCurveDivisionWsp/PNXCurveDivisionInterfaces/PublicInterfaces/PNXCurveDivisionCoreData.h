/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @file  		PNXCurveDivisionCoreData.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-11-08
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXCurveDivisionCoreData_H
#define PNXCurveDivisionCoreData_H

// System  Framework
#include "CATBaseUnknown.h"
#include "CATISO.h"
#include "CATISpecObject.h"
#include "CATMathTransformation.h"

// CAT pre-declare class
class CATIGSMTool;
class CATIPrtPart;
class CATFrmEditor;
class CAT3DRep;

// Local Framework
#include "PNXCurveDivisionItf.h"
#include "PNXCurveDivisionParam.h"

/** @brief Core of Line create */
class ExportedByPNXCurveDivisionItf PNXCurveDivisionCoreData {

public:
    /** @brief Standard constructors and destructors */
    PNXCurveDivisionCoreData();
    virtual ~PNXCurveDivisionCoreData();

private:
    /** @brief  Copy constructor and equal operator prevent to copy */
    PNXCurveDivisionCoreData(PNXCurveDivisionCoreData&);
    PNXCurveDivisionCoreData& operator=(PNXCurveDivisionCoreData&);

public:
public:
    // START KEVIN CAA WIZARD SECTION PNXCurveDivisionCoreDataPublic PARAM DECLARATION
    // clang-format off

    // @app Kt Auto Code
    // @version 5.0.0, (2024)

    /**
     * @brief My Feature
     * @author Phoenix
     * @date 2021/10/28
     * @id 101
     */
    CATISpecObject_var feature;

    /**
     * @brief Param pointer
     * @author Phoenix
     * @date 2021/10/28
     * @id 102
     */
    PNXCurveDivisionParam* parameter;

    /**
     * @brief CAA Frame Editor
     * @author Phoenix
     * @date 2021/10/28
     * @id 103
     */
    CATFrmEditor* _catFrmEditor;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCurveDivisionCoreDataPublic PARAM DECLARATION

protected:
    int _code; // CODE
};

#endif
