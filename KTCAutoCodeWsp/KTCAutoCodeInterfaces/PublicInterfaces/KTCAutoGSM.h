/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXAutoCode
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef KTCAutoGSM_H
#define KTCAutoGSM_H

#include "CATIGSMTool.h"
#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCAutoGSM.h"

class CATFrmEditor;
class CATIPrtPart;

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoGSM {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoGSM();
    virtual ~KTCAutoGSM();

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoGSM(const KTCAutoGSM&);
    KTCAutoGSM& operator=(const KTCAutoGSM&);

public:
    static HRESULT CreateTool(CATIPrtPart* pIPrtPart, CATIGSMTool** pIGsmTool);

    static bool IsInsideOrderedBody(CATISpecObject_var feature);

    static HRESULT LookingForGeomSet(CATFrmEditor* catFrmEditor, CATIGSMTool** piGsmtool);
};

#endif
