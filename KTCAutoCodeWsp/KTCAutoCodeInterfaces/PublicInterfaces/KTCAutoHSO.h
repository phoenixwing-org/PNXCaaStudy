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
class CATFeatureImportAgent;

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
     * @note call _hso->AddElement
     */
    int AddElement(CATISpecObject_var object);

    /**
     * @brief add elements to hso
     * @param object CATISpecObject_var
     * @return add count
     * @note call _hso->AddElements
     */
    int AddElement(const CATListValCATISpecObject_var& list);

    /**
     * @brief after element selected
     * @param agent CATFeatureImportAgent*
     * @param ioObject CATISpecObject_var& input/output object
     * @param mode KTC::ValueActionMode
     * @return treated count
     */
    int after_element_selected(CATFeatureImportAgent* agent, CATISpecObject_var& ioObject,
                               KTC::ValueActionMode mode);

    /**
     * @brief after element selected
     * @param agent CATFeatureImportAgent*
     * @param ioList CATListValCATISpecObject_var& input/output list
     * @param mode KTC::ValueActionMode
     * @return treated count
     */
    int after_element_selected(CATFeatureImportAgent* agent, CATListValCATISpecObject_var& ioList,
                               KTC::ValueActionMode mode);
    /**
     * @brief initial editor and hso
     * @param editor CATFrmEditor*
     * @param hso CATHSO*
     * @note set _editor and _hso
     */
    void initial(CATFrmEditor* editor, CATHSO* hso);

    /**
     * @brief remove element from hso
     * @param object CATISpecObject_var
     * @return remove count
     * @note call _hso->RemoveElement
     */
    int RemoveElement(CATISpecObject_var object);

    /**
     * @brief add elements to hso
     * @param object CATISpecObject_var
     * @return remove count
     * @note call _hso->RemoveElements
     */
    int RemoveElement(const CATListValCATISpecObject_var& list);

public:
    CATFrmEditor*  _editor;  // catia frame editor
    CATHSO*        _hso;     // catia hso
    KTCAutoPartDoc _partDoc; // catia part doc
};

#endif
