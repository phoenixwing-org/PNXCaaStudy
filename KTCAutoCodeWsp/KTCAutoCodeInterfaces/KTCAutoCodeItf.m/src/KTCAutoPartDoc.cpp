/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    KTCAutoCode
 * @file  		KTCAutoPartDoc.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

// cat
#include "CATFrmEditor.h"
#include "CATIBuildPath.h"
#include "CATPathElement.h"

// Local
#include "KTCAutoDefine.h"
#include "KTCAutoPartDoc.h"

//-----------------------------------------------------------------------------
KTCAutoPartDoc::KTCAutoPartDoc()
    : _editor(NULL) {

    // your code here:
}
//-----------------------------------------------------------------------------
KTCAutoPartDoc::~KTCAutoPartDoc() {
    _editor = NULL;
}
//-----------------------------------------------------------------------------
KTCAutoPartDoc::KTCAutoPartDoc(const KTCAutoPartDoc& iOriginal)
    : _editor(iOriginal._editor) {
}
//-----------------------------------------------------------------------------
KTCAutoPartDoc& KTCAutoPartDoc::operator=(const KTCAutoPartDoc& iOriginal) {
    _editor = iOriginal._editor;
    return *this;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoPartDoc::checkout_pathelement(CATISpecObject_var object,
                                             CATPathElement**   pathElement) {

    // check path element
    if (!pathElement) return E_INVALIDARG;
    *pathElement = NULL; // initialize

    // check object
    if (!object) return E_INVALIDARG;

    // parameters
    CATIBuildPath* buildPath = NULL;
    HRESULT        hr;

    // check editor
    if (!_editor) {
        hr = initial_editor(NULL);
        if (FAILED(hr)) return hr;
    }

    // checkout build path
    hr = object->QueryInterface(IID_CATIBuildPath, (void**)&buildPath);
    if (FAILED(hr)) return hr;

    // check out path element
    CATPathElement context = _editor->GetUIActiveObject();
    hr                     = buildPath->ExtractPathElement(&context, pathElement);
    KTCRelease(buildPath);
    return hr;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoPartDoc::checkout_pathelement(const CATListValCATISpecObject_var& iList,
                                             CATLISTP(CATPathElement) & oList) {
    oList.RemoveAll(); // initialize

    if (0 == iList.Size()) return S_OK;

    // parameters
    CATPathElement* pathElement = NULL;
    HRESULT         hr;

    // checkout path element list from index 1
    for (int i = 1; i <= iList.Size(); i++) {
        hr = this->checkout_pathelement(iList[ i ], &pathElement);
        if (FAILED(hr)) return hr; // error
        oList.Append(pathElement);
    }

    return S_OK; // ok
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoPartDoc::initial_editor(CATFrmEditor* iEditor) {
    // 1. set to input editor
    if (iEditor) {
        _editor = iEditor;
        return S_OK;
    };

    // 2.already initialized
    if (_editor) return S_OK;

    // 3. check and get current editor
    _editor = CATFrmEditor::GetCurrentEditor();
    if (!_editor) return E_POINTER; // failed

    return S_OK; // ok
}
