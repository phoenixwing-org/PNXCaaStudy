/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXEBomAnalysisEdit_H
#define PNXEBomAnalysisEdit_H

// System Framework
#include "CATExtIEdit.h" // To derive from

/**
 * Class extending the object "PNXBomAnalysis".
 * It implements the interfaces :
 *      ApplicationFrame.CATIEdit
 *         This interface is called when editing a Sound Hole.
 *         It associates a dialog panel and fill in the contextual menu of the
 * Sound Hole.
 */

class PNXEBomAnalysisEdit : public CATExtIEdit {
    CATDeclareClass;

public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    PNXEBomAnalysisEdit();
    virtual ~PNXEBomAnalysisEdit();

    /**
     * Implements the method Activate of the interface CATIEdit
     * see ApplicationFrame.CATIEdit.Activate
     */
    CATCommand* Activate(CATPathElement* ipPath);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXEBomAnalysisEdit(PNXEBomAnalysisEdit& iObjectToCopy);
    PNXEBomAnalysisEdit& operator=(PNXEBomAnalysisEdit& iObjectToCopy);
};

#endif
