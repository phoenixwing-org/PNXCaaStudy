/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
 * @file  		PNXV5V6AdapterCore.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXV5V6AdapterCore_H
#define PNXV5V6AdapterCore_H

// Local Framework
#include "PNXV5V6AdapterCoreData.h"

/** @brief Core of Line create */
class ExportedByPNXV5V6AdapterItf PNXV5V6AdapterCore : public PNXV5V6AdapterCoreData {

public:
    /** @brief Standard constructors and destructors */
    PNXV5V6AdapterCore();
    virtual ~PNXV5V6AdapterCore();

private:
    /** @brief  Copy constructor and equal operator prevent to copy */
    PNXV5V6AdapterCore(PNXV5V6AdapterCore&);
    PNXV5V6AdapterCore& operator=(PNXV5V6AdapterCore&);

public:
    /** @brief Calculate */
    HRESULT Calculate();

    /** @brief Create the line */
    HRESULT Create();

    /** @brief Pretreat */
    HRESULT Pretreat();

private:
};

#endif
