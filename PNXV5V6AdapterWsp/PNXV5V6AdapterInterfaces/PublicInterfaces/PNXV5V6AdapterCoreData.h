/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
 * @file  		PNXV5V6AdapterCoreData.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-11-08
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXV5V6AdapterCoreData_H
#define PNXV5V6AdapterCoreData_H

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
#include "PNXV5V6AdapterItf.h"
#include "PNXV5V6AdapterParam.h"

/** @brief Core of Line create */
class ExportedByPNXV5V6AdapterItf PNXV5V6AdapterCoreData {

public:
    /** @brief Standard constructors and destructors */
    PNXV5V6AdapterCoreData();
    virtual ~PNXV5V6AdapterCoreData();

private:
    /** @brief  Copy constructor and equal operator prevent to copy */
    PNXV5V6AdapterCoreData(PNXV5V6AdapterCoreData&);
    PNXV5V6AdapterCoreData& operator=(PNXV5V6AdapterCoreData&);

public:
public:
    // START KEVIN CAA WIZARD SECTION PNXV5V6AdapterCoreDataPublic PARAM
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
    PNXV5V6AdapterParam* parameter;

    /**
     * @brief CAA Frame Editor
     * @author Phoenix
     * @date 2021/10/28
     * @id 103
     */
    CATFrmEditor* _catFrmEditor;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6AdapterCoreDataPublic PARAM
    // DECLARATION

protected:

    int _code; // CODE
};

#endif
