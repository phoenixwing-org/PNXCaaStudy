/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    KTCAutoCode
 * @file  		KTCAutoHSO.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

// cat
#include "iostream.h"

// Local
#include "KTCAutoHSO.h"

//-----------------------------------------------------------------------------
KTCAutoHSO::KTCAutoHSO()
    : _editor(NULL)
    , _hso(NULL) {
}
//-----------------------------------------------------------------------------
KTCAutoHSO::~KTCAutoHSO() {
    _editor = NULL; // outside
    _hso    = NULL; // outside
}
//-----------------------------------------------------------------------------
KTCAutoHSO::KTCAutoHSO(const KTCAutoHSO& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
KTCAutoHSO& KTCAutoHSO::operator=(const KTCAutoHSO& iOriginal) {
    _editor = iOriginal._editor;
    _hso    = iOriginal._hso;
    return *this;
}
//-----------------------------------------------------------------------------
int KTCAutoHSO::add_element(CATISpecObject_var object) {
    cout << "TODO KTCAutoHSO::add_element" << endl;
    if (!_hso) return 0;

    return 0;
} //-----------------------------------------------------------------------------
int KTCAutoHSO::add_element(const CATListValCATISpecObject_var& list) {
    cout << "TODO KTCAutoHSO::add_element list" << endl;
    if (!_hso) return 0;

    return 0;
}
//-----------------------------------------------------------------------------
int KTCAutoHSO::after_element_selected(CATFeatureImportAgent* agent, CATISpecObject_var object,
                                       KTC::ValueActionMode mode) {
    cout << "TODO KTCAutoHSO::after_element_selected" << endl;
    return 0;
}
//-----------------------------------------------------------------------------
int KTCAutoHSO::after_element_selected(CATFeatureImportAgent*              agent,
                                       const CATListValCATISpecObject_var& list,
                                       KTC::ValueActionMode                mode) {
    cout << "TODO KTCAutoHSO::after_element_selected list" << endl;
    return 0;
}
//-----------------------------------------------------------------------------
void KTCAutoHSO::initial(CATFrmEditor* editor, CATHSO* hso) {
    _editor = editor;
    _hso    = hso;
}
