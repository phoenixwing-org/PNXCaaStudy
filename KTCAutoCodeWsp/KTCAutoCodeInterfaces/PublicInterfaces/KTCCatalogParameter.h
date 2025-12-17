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

#ifndef KTCCatalogParameter_H
#define KTCCatalogParameter_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCCatalogParameter.h"

// std
#include <vector>

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCCatalogParameter {
public:
    /** @brief Standard constructors and destructors */
    KTCCatalogParameter();
    virtual ~KTCCatalogParameter();

    /** @brief Copy constructor and equal operator */
    KTCCatalogParameter(const KTCCatalogParameter&);
    KTCCatalogParameter& operator=(const KTCCatalogParameter&);

public:
    void SetValue(const CATUnicodeString& name, TCKind kind, CATAttrInOut in);

    void SetTKListValue(const CATUnicodeString& name, TCKind kind, CATAttrInOut in);

    static HRESULT CatalogAddAttribute(CATISpecObject*                   startUp,
                                       std::vector<KTCCatalogParameter>& itemList);

public:
    CATUnicodeString name;
    TCKind           kind;
    CATAttrInOut     inOut;
    int              isList;
};

#endif
