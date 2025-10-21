/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
 * @file  		PNXBomAnalysisCoreData.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-11-08
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXBomAnalysisCoreData_H
#define PNXBomAnalysisCoreData_H

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
#include "PNXBomAnalysisItf.h"
#include "PNXBomAnalysisParam.h"

/** @brief Core of Line create */
class ExportedByPNXBomAnalysisItf PNXBomAnalysisCoreData {

public:
    /** @brief Standard constructors and destructors */
    PNXBomAnalysisCoreData();
    virtual ~PNXBomAnalysisCoreData();

private:
    /** @brief  Copy constructor and equal operator prevent to copy */
    PNXBomAnalysisCoreData(PNXBomAnalysisCoreData&);
    PNXBomAnalysisCoreData& operator=(PNXBomAnalysisCoreData&);

public:
public:
    // START KEVIN CAA WIZARD SECTION PNXBomAnalysisCoreDataPublic PARAM
    // DECLARATION
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
    PNXBomAnalysisParam* parameter;

    /**
     * @brief CAA Frame Editor
     * @author Phoenix
     * @date 2021/10/28
     * @id 103
     */
    CATFrmEditor* _catFrmEditor;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysisCoreDataPublic PARAM
    // DECLARATION

protected:

    int _code; // CODE
};

#endif
