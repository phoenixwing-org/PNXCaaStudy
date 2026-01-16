/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXAutoCode
 * @file        KTCAutoHSO.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef KTCAutoHSO_H
#define KTCAutoHSO_H

#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// auto code
#include "KTCAutoCodeItf.h"
#include "KTCAutoDefine.h"
#include "KTCAutoPartDoc.h"

class CATHSO;
class CATFrmEditor;
class CATPathElementAgent;

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoHSO {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoHSO();
    virtual ~KTCAutoHSO();

    /** @brief Copy constructor and equal operator */
    KTCAutoHSO(const KTCAutoHSO&);
    KTCAutoHSO& operator=(const KTCAutoHSO&);

public:
    /**
     * @brief add element to hso
     * @param object CATISpecObject_var
     * @return add count
     * @note call hso_->AddElement
     */
    int AddElement(CATISpecObject_var object);

    /**
     * @brief add elements to hso
     * @param object CATISpecObject_var
     * @return add count
     * @note call hso_->AddElements
     */
    int AddElement(const CATListValCATISpecObject_var& list);

    /**
     * @brief after element selected
     * @param agent CATPathElementAgent*
     * @param ioObject CATISpecObject_var& input/output object
     * @param mode KTC::ValueActionMode
     * @return treated count
     */
    int after_element_selected(CATPathElementAgent* agent, CATISpecObject_var& ioObject,
                               KTC::ValueActionMode mode);

    /**
     * @brief after element selected
     * @param agent CATPathElementAgent*
     * @param ioList CATListValCATISpecObject_var& input/output list
     * @param mode KTC::ValueActionMode
     * @return treated count
     */
    int after_element_selected(CATPathElementAgent* agent, CATListValCATISpecObject_var& ioList,
                               KTC::ValueActionMode mode);
    /**
     * @brief initial editor and hso
     * @param editor CATFrmEditor*
     * @param hso CATHSO*
     * @note set catFrmEditor_ and hso_
     */
    void initial(CATFrmEditor* editor, CATHSO* hso);

    /**
     * @brief remove element from hso
     * @param object CATISpecObject_var
     * @return remove count
     * @note call hso_->RemoveElement
     */
    int RemoveElement(CATISpecObject_var object);

    /**
     * @brief add elements to hso
     * @param object CATISpecObject_var
     * @return remove count
     * @note call hso_->RemoveElements
     */
    int RemoveElement(const CATListValCATISpecObject_var& list);

public:
    CATFrmEditor*  catFrmEditor_; // catia frame editor
    CATHSO*        hso_;          // catia hso
    KTCAutoPartDoc partDoc_;      // catia part doc
};

#endif
