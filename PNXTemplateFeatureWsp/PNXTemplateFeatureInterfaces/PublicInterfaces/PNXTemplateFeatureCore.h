/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXTemplateFeatureCore.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef PNXTemplateFeatureCore_H
#define PNXTemplateFeatureCore_H

// Local Framework
#include "PNXTemplateFeatureData.h"

/** @brief Core of Line create */
class ExportedByPNXTemplateFeatureItf PNXTemplateFeatureCore : public PNXTemplateFeatureData {

public:
    /** @brief Standard constructors and destructors */
    PNXTemplateFeatureCore();
    virtual ~PNXTemplateFeatureCore();

private:
    /** @brief  Copy constructor and equal operator prevent to copy */
    PNXTemplateFeatureCore(PNXTemplateFeatureCore&);
    PNXTemplateFeatureCore& operator=(PNXTemplateFeatureCore&);

public:
    /** @brief calculate */
    int calculate();

    /** @brief Create the line */
    int create();

    /** @brief Pretreat */
    int pretreat();

    /** @brief show_rep */
    int show_rep();
};

#endif
