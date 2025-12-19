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

#ifndef KTCAutoHSO_H
#define KTCAutoHSO_H

#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCAutoHSO.h"

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
     * @return add count
     */
    int add_element(CATISpecObject_var object);

    int add_element(const CATListValCATISpecObject_var& list);

    /**
     * @return count
     */
    int after_element_selected(CATFeatureImportAgent* agent, CATISpecObject_var object,
                               KTC::ValueActionMode mode);

    /**
     * @return count
     */
    int after_element_selected(CATFeatureImportAgent*              agent,
                               const CATListValCATISpecObject_var& list, KTC::ValueActionMode mode);

    /**
     * @return initial
     */
    void initial(CATFrmEditor* editor, CATHSO* hso);

public:
    CATFrmEditor* _editor; // catia frame editor
    CATHSO*       _hso;    // catia hso
};

#endif
