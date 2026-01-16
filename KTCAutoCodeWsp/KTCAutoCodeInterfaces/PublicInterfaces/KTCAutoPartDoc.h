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

#ifndef KTCAutoPartDoc_H
#define KTCAutoPartDoc_H

#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATListOfCATPathElement.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// auto code
#include "KTCAutoCodeItf.h"
#include "KTCAutoPartDoc.h"

class CATFrmEditor;

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoPartDoc {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoPartDoc();
    virtual ~KTCAutoPartDoc();

public:
    /**
     * @brief checkout path element
     * @param object CATISpecObject_var
     * @param pathElement CATPathElement**
     * @return HRESULT
     */
    HRESULT checkout_pathelement(CATISpecObject_var object, CATPathElement** pathElement);

    HRESULT checkout_pathelement(const CATListValCATISpecObject_var& list,
                                 CATPathElement**                    pathElement);
    /**
     * @brief checkout path element
     * @param iList CATListValCATISpecObject_var
     * @param oList CATListOfCATPathElement&
     * @return HRESULT
     */
    HRESULT checkout_pathelement(const CATListValCATISpecObject_var& iList,
                                 CATLISTP(CATPathElement) & oList);

    /**
     * @brief initial editor
     * @param editor CATFrmEditor*
     * @return HRESULT
     */
    HRESULT initial_editor(CATFrmEditor* editor);

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoPartDoc(const KTCAutoPartDoc&);
    KTCAutoPartDoc& operator=(const KTCAutoPartDoc&);

public:
    CATFrmEditor* catFrmEditor_; // catia frame editor
};

#endif
