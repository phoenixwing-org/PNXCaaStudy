/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @file  		PNXTemplateBaseCore.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef PNXTemplateBaseCore_H
#define PNXTemplateBaseCore_H

// Local Framework
#include "PNXTemplateBaseData.h"

/** @brief Core of Line create */
class ExportedByPNXTemplateBaseItf PNXTemplateBaseCore : public PNXTemplateBaseData {

public:
    /** @brief Standard constructors and destructors */
    PNXTemplateBaseCore();
    virtual ~PNXTemplateBaseCore();

private:
    /** @brief  Copy constructor and equal operator prevent to copy */
    PNXTemplateBaseCore(PNXTemplateBaseCore&);
    PNXTemplateBaseCore& operator=(PNXTemplateBaseCore&);

public:
    /** @brief calculate */
    HRESULT calculate();

    /** @brief Create the line */
    HRESULT create();

    /** @brief Pretreat */
    HRESULT pretreat();

    /** @brief show_rep */
    HRESULT show_rep();
};

#endif
