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
#include "CATFeatureImportAgent.h"
#include "CATHSO.h"
#include "CATOtherDocumentAgent.h"
#include "CATPathElement.h"
#include "iostream.h"

// Local
#include "KTCAutoHSO.h"
#include "KTCAutoPartDoc.h"

//-----------------------------------------------------------------------------
KTCAutoHSO::KTCAutoHSO()
    : catFrmEditor_(NULL)
    , hso_(NULL)
    , partDoc_() {
}
//-----------------------------------------------------------------------------
KTCAutoHSO::~KTCAutoHSO() {
    catFrmEditor_ = NULL; // outside
    hso_          = NULL; // outside
    // partDoc_
}
//-----------------------------------------------------------------------------
KTCAutoHSO::KTCAutoHSO(const KTCAutoHSO& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
KTCAutoHSO& KTCAutoHSO::operator=(const KTCAutoHSO& iOriginal) {
    catFrmEditor_ = iOriginal.catFrmEditor_;
    hso_          = iOriginal.hso_;
    partDoc_.initial_editor(iOriginal.catFrmEditor_);

    return *this;
}
//-----------------------------------------------------------------------------
int KTCAutoHSO::AddElement(CATISpecObject_var object) {
    if (!hso_) return 0;
    if (!object) return 0;

    // initialize part doc
    KTCAutoPartDoc doc;
    doc.initial_editor(catFrmEditor_); // initial
    // checkout path element
    CATPathElement* pathElement = NULL;
    doc.checkout_pathelement(object, &pathElement);
    if (!pathElement) return 0;

    // add to hso
    hso_->AddElement(pathElement);
    KTCRelease(pathElement);
    cout << "- [Debug] OK hso AddElement = 1" << endl;
    return 1;
} //-----------------------------------------------------------------------------
//----------------------------------------
int KTCAutoHSO::AddElement(const CATListValCATISpecObject_var& list) {
    if (!hso_) return 0;
    if (list.Size() == 0) return 0;

    // initialize part doc
    KTCAutoPartDoc doc;
    doc.initial_editor(catFrmEditor_); // initial

    // checkout path element
    CATPathElement*          pathElement = NULL;
    CATListPtrCATPathElement pathElementList;
    HRESULT                  hr = doc.checkout_pathelement(list, pathElementList);
    if (FAILED(hr)) return 0;

    // add to hso by AddElements() ,最后发信号
    int count = 0;
    for (int i = 1; i <= pathElementList.Size(); i++) {
        pathElement = pathElementList[ i ];
        if (!pathElement) continue;

        // add to hso
        hso_->AddElements(pathElement);
        count++;
        KTCRelease(pathElement);
    }
    hso_->EndAddElements(); // end add elements  发信号

    cout << "- [Debug] OK hso AddElements = " << count << endl;
    return count;
}
//-----------------------------------------------------------------------------
int KTCAutoHSO::after_element_selected(CATPathElementAgent* agent, CATISpecObject_var& ioObject,
                                       KTC::ValueActionMode mode) {
    /**
     * 作用： 从agent获得选入元素，根据mode，设定ioObject
     */
    if (!agent) return 0;

    // 获得 base unknown
    CATBaseUnknown* baseUnknown = agent->GetElementValue();
    if (!baseUnknown) return 0;

    // 获得 spec object
    CATISpecObject_var specObject = NULL_var;
    HRESULT            hr = baseUnknown->QueryInterface(IID_CATISpecObject, (void**)&specObject);
    if (FAILED(hr) || !specObject) return 0;

    // 获得 path element，用於反選
    CATPathElement* pathElement = agent->GetValue();
    if (!pathElement) return 0;

    // 处理模式
    switch (mode) {
    case KTC::ValueAdd: // 不一致，设定值 or 一致不动作
    {
        if (specObject != ioObject) ioObject = specObject;
        break;
    }
    case KTC::ValueSubtract: // 存在，清空 or 不存在，不动作
    {
        RemoveElement(pathElement); // 处理hso
        if (specObject == ioObject) ioObject = NULL_var;
        break;
    }
    default: // case KTC::ValueNormal:
    {
        if (specObject == ioObject) {   // 相同清空
            RemoveElement(pathElement); // 处理hso
            ioObject = NULL_var;
        } else // or 不同赋值
            ioObject = specObject;
        break;
    }
    }

    // cout << "- [Debug] OK " << __FUNCTION__ << "(... object) = 1" << endl;
    return 1;
}
//-----------------------------------------------------------------------------
int KTCAutoHSO::after_element_selected(CATPathElementAgent*          agent,
                                       CATListValCATISpecObject_var& ioList,
                                       KTC::ValueActionMode          mode) {
    /**
     * 作用： 从agent获得选入元素，根据mode，设定ioList
     */
    if (!agent) return 0;

    // 获得 base unknown
    CATBaseUnknown* baseUnknown = agent->GetElementValue();
    if (!baseUnknown) return 0;

    // 获得 spec object
    CATISpecObject_var specObject = NULL_var;
    HRESULT            hr = baseUnknown->QueryInterface(IID_CATISpecObject, (void**)&specObject);
    if (FAILED(hr) || !specObject) return 0;

    const int location = ioList.Locate(specObject);

    // 获得 path element，用於反選
    CATPathElement* pathElement = agent->GetValue();
    if (!pathElement) return 0;

    // 处理模式
    switch (mode) {
    case KTC::ValueAdd:
        // 不在列表里面，添加
        if (location == 0) ioList.Append(specObject);
        break;
    case KTC::ValueSubtract:
        // 存在，清空 or 不存在，不动作
        RemoveElement(pathElement);                       // 处理hso
        if (location > 0) ioList.RemoveValue(specObject); // 处理列表
        break;
    default:
        // case KTC::ValueNormal:
        if (location != 0) {                // 存在清空
            RemoveElement(pathElement);     // 处理hso
            ioList.RemoveValue(specObject); // 处理列表
        } else {                            // or 不存在添加
            ioList.Append(specObject);
        }
        break;
    }

    // cout << "- [Debug] OK " << __FUNCTION__ << "(... list) = 1" << endl;
    return 1;
}
//-----------------------------------------------------------------------------
void KTCAutoHSO::initial(CATFrmEditor* editor, CATHSO* hso) {
    catFrmEditor_ = editor;
    hso_          = hso;
}
//-----------------------------------------------------------------------------
int KTCAutoHSO::RemoveElement(CATISpecObject_var object) {
    if (!catFrmEditor_ || !hso_) return 0;

    // set editor to part doc
    partDoc_.initial_editor(catFrmEditor_); // inital

    // checkout path element
    CATPathElement* pathElement = NULL;
    HRESULT         hr          = partDoc_.checkout_pathelement(object, &pathElement);
    if (!pathElement) return 0;

    // remove from hso
    cout << "- [Debug] OK hso RemoveElement(...) = 1" << pathElement << endl;
    hso_->RemoveElement(pathElement);
    KTCRelease(pathElement);

    return 1;
}
//-----------------------------------------------------------------------------
int KTCAutoHSO::RemoveElement(const CATListValCATISpecObject_var& list) {
    if (!catFrmEditor_ || !hso_) return 0;

    // set editor to part doc
    partDoc_.initial_editor(catFrmEditor_); // initial

    // parameters
    int                      count       = 0; // remove count
    CATPathElement*          pathElement = NULL;
    CATListPtrCATPathElement pathElementList;

    // checkout path element
    HRESULT hr = partDoc_.checkout_pathelement(list, pathElementList);
    if (FAILED(hr)) return 0;

    // remove from hso by RemoveElements() ,最后发信号
    for (int i = 1; i <= pathElementList.Size(); i++) {
        pathElement = pathElementList[ i ];
        if (!pathElement) continue;

        // remove from hso
        hso_->RemoveElements(pathElement);
        KTCRelease(pathElement);
        count++;
    }
    hso_->EndRemoveElements(); // end remove elements  发信号

    cout << "- [Debug] OK hso RemoveElements(...) = " << count << endl;
    return count;
}
