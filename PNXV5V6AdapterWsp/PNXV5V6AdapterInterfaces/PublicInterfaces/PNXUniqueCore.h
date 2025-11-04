/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @date		2021-9-1
 * @brief
 */

#ifndef PNXUniqueCore_H
#define PNXUniqueCore_H

// CAT
#include "CATISpecObject.h"

// PNX
#include "PNXUniqueDefine.h"
#include "PNXV5V6AdapterItf.h"

/** @brief PNX UniqueCore */
class ExportedByPNXV5V6AdapterItf PNXUniqueCore {
public:
    /** @brief Standard constructors and destructors */
    PNXUniqueCore();
    virtual ~PNXUniqueCore();

private:
    /** @brief Copy constructor and equal operator */
    PNXUniqueCore(const PNXUniqueCore&);
    PNXUniqueCore& operator=(const PNXUniqueCore&);

public:
    /**
     * @brief calculate by input PNXIMechanicalFeature_var
     *
     * @param spFeature PNXIMechanicalFeature_var for V5 or V6
     * @return int Error codes
     */
    int calculate(PNXIMechanicalFeature_var spFeature);

    /**
     * @brief checkout Unique Class for V5 or V6
     * @return PNXIMechanicalFeature_var
     */
    PNXIMechanicalFeature_var checkoutUniqueClass();

public:
    CATISpecObject_var feature; // main feature
};

#endif
