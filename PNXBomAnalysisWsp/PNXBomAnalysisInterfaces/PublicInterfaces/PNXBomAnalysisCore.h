/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
 * @file  		PNXBomAnalysisCore.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXBomAnalysisCore_H
#define PNXBomAnalysisCore_H

// CAT
#include "CATIProduct.h"

// Local Framework
#include "PNXBomAnalysisCoreData.h"

/** @brief Core of Line create */
class ExportedByPNXBomAnalysisItf PNXBomAnalysisCore : public PNXBomAnalysisCoreData {

public:
    /** @brief Standard constructors and destructors */
    PNXBomAnalysisCore();
    virtual ~PNXBomAnalysisCore();

private:
    /** @brief  Copy constructor and equal operator prevent to copy */
    PNXBomAnalysisCore(PNXBomAnalysisCore&);
    PNXBomAnalysisCore& operator=(PNXBomAnalysisCore&);

public:
    /** @brief calculate */
    HRESULT calculate();

    /**
     * @brief checkout properties
     * @param productObject input product
     * @param item output bom item
     * @return error code
     */
    static int checkoutProperties(CATISpecObject_var productObject, PNXBomItem& item);

    /** @brief pretreat */
    HRESULT pretreat();

private:
};

#endif
