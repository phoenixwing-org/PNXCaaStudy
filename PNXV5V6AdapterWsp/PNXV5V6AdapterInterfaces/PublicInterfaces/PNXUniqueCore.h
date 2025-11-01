/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @brief
 * @details
 * @date		2021-9-1
 */

#ifndef PNXUniqueCore_H
#define PNXUniqueCore_H

#include "CATISpecObject.h"
#include "CATMathAxis.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATUnicodeString.h"

// ObjectSpecModeler Framework
#include "CATLISTV_CATISpecObject.h"

#include "PNXV5V6AdapterItf.h"

/** @brief PNX UniqueClass   */
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

public: // functions
    /**
     * @brief checkout
     * @return HRESULT
     */
    HRESULT CheckoutAxis();

    // dump
    void dump();
};

#endif
