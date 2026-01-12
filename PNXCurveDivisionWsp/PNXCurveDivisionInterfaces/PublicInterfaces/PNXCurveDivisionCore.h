/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @file  		PNXCurveDivisionCore.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXCurveDivisionCore_H
#define PNXCurveDivisionCore_H

// Local Framework
#include "PNXCurveDivisionCoreData.h"

/** @brief Core of Line create */
class ExportedByPNXCurveDivisionItf PNXCurveDivisionCore : public PNXCurveDivisionCoreData {

public:
    /** @brief Standard constructors and destructors */
    PNXCurveDivisionCore();
    virtual ~PNXCurveDivisionCore();

private:
    /** @brief  Copy constructor and equal operator prevent to copy */
    PNXCurveDivisionCore(PNXCurveDivisionCore&);
    PNXCurveDivisionCore& operator=(PNXCurveDivisionCore&);

public:
    /** @brief calculate */
    HRESULT calculate();

    /** @brief Create the line */
    HRESULT create();

    /** @brief Pretreat */
    HRESULT pretreat();

private:
};

#endif
