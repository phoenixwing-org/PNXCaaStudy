/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXETemplateFeature.cpp
 * @brief       Provide implementation to interface
 *      PNXITemplateFeature
 */

// ObjectSpecsModeler
#include "CATIDescendants.h"

// MecModInterfaces Framework
#include "CATIMfBRep.h"

// ObjectSpecsModeler Framework
#include "CATISpecAttrAccess.h" // needed to access feature attributes
#include "CATISpecAttrKey.h"    // needed to access to the feature attribute values
#include "CATISpecObject.h"     // needed to manage/query features

#include "iostream.h"

// Kt
#include "KtString.h"

// Local Framework
#include "PNXETemplateFeature.h"

CATImplementClass(PNXETemplateFeature, DataExtension, CATBaseUnknown, PNXTemplateFeature);

//-------------------------------------------------------------------------------------
// PNXETemplateFeature : constructor
//-------------------------------------------------------------------------------------
PNXETemplateFeature::PNXETemplateFeature()
    : CATBaseUnknown()
    , ktcSpecRW() {
    ktcSpecRW.initial(this); // initial
}
//-------------------------------------------------------------------------------------
PNXETemplateFeature::~PNXETemplateFeature() {
    // ktcSpecRW, No Actions
}

// Tie the implementation to its interface
// ---------------------------------------

// To declare that PNXTemplateFeature implements PNXITemplateFeature, insert
// the following line in the interface dictionary:
//
// PNXTemplateFeature  PNXITemplateFeature  libPNXTemplateFeatureItf

#include "TIE_PNXITemplateFeature.h" // needed to tie the implementation to its interface
TIE_PNXITemplateFeature(PNXETemplateFeature);

#pragma region KEVIN_SYSTEM_CODE_FUNCTIONS

//-----------------------------------------------------------------------------
CATUnicodeString PNXETemplateFeature::GetErrMsg() const // 0
{
    CATUnicodeString value("");
    ktcSpecRW.GetValue("ErrMsg", value);
    return value;
}
//-----------------------------------------------------------------------------
HRESULT PNXETemplateFeature::SetErrMsg(const CATUnicodeString& value) // 0
{
    return ktcSpecRW.SetValue("ErrMsg", value);
}
//-----------------------------------------------------------------------------
HRESULT PNXETemplateFeature::GetParams(PNXTemplateFeatureParam& value) const {
    if (!ktcSpecRW.IsAvailable()) return E_INVALIDARG;

    // KEVIN_SYSTEM_CODE START
    value.FeatureVersion = this->GetVersion(); // 0A
    // KEVIN_SYSTEM_CODE END

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature IMPLEMENTS PARAM GET

    // clang-format off

    value.MyCurve = GetMyCurve(); // 2
    GetMyFaces(value.MyFaces); // 3
    value.MyStep = GetMyStep(); // 4
    value.FinishCalc = GetFinishCalc(); // 5

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature IMPLEMENTS PARAM GET

    return S_OK; // ok
}
//-----------------------------------------------------------------------------
HRESULT PNXETemplateFeature::SetParams(const PNXTemplateFeatureParam& value) {
    if (!ktcSpecRW.IsAvailable()) return E_INVALIDARG;

    HRESULT hr = S_OK; // default ok

    // KEVIN_SYSTEM_CODE START
    //  do not use SetVersion() here

    CATUnicodeString msg;               // for error message
    CATBoolean       findError = FALSE; // for find error
    // KEVIN_SYSTEM_CODE END

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature IMPLEMENTS PARAM SET

    // clang-format off

    hr = SetMyCurve(value.MyCurve); // 2
    if (FAILED(hr)) {
        msg.Append("\nSet Parameter of MyCurve Error!");
        findError = TRUE;
    }
    hr = SetMyFaces(value.MyFaces); // 3
    if (FAILED(hr)) {
        msg.Append("\nSet Parameter of MyFaces Error!");
        findError = TRUE;
    }
    hr = SetMyStep(value.MyStep); // 4
    if (FAILED(hr)) {
        msg.Append("\nSet Parameter of MyStep Error!");
        findError = TRUE;
    }
    hr = SetFinishCalc(value.FinishCalc); // 5
    if (FAILED(hr)) {
        msg.Append("\nSet Parameter of FinishCalc Error!");
        findError = TRUE;
    }
    if (findError) {
        SetErrMsg(msg);
        return E_FAIL;
    }

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature IMPLEMENTS PARAM SET
    return S_OK; // ok
}
//-----------------------------------------------------------------------------
int PNXETemplateFeature::GetVersion() const // 0A
{
    int value(0);
    ktcSpecRW.GetValue("FeatureVersion", value);
    return value;
}
//-----------------------------------------------------------------------------
HRESULT PNXETemplateFeature::SetVersion(const int& value) // 0A
{
    const int featureVersion = this->GetVersion(); // get current feature version
    if (GetVersion() > value) {
        KtString msg(100);
        msg = "Error! Unexpected input version %1 which is smaller than the feature version %2. ";
        msg.arg(value).arg(featureVersion);
        this->SetErrMsg(msg.str());
        return E_UNEXPECTED;
    }
    else if (value > PNXTemplateFeatureParam::GetSoftwareVersion()) {
        KtString msg(100);
        msg = "Error! Unexpected input version %1 which is larger than the software version %2. ";
        msg.arg(value).arg(PNXTemplateFeatureParam::GetSoftwareVersion());
        this->SetErrMsg(msg.str());
        return E_UNEXPECTED;
    }

    return ktcSpecRW.SetValue("FeatureVersion", value);
}
//-----------------------------------------------------------------------------
HRESULT PNXETemplateFeature::UpdateVersion() // 0X
{
    // cout <<"### " << __FUNCTION__ << endl;

    const int softVersion    = PNXTemplateFeatureParam::GetSoftwareVersion(); // get soft version
    const int featureVersion = this->GetVersion(); // get current feature version

    //
    // 1, check version
    //

    if (featureVersion < 0) {         // start from 0. Need not upate.
        *((int*)&featureVersion) = 0; // set 0, if small than 0
    }

    if (featureVersion == softVersion) { // start from 0. Need not upate.
        return S_OK;
    }

    KtString msg(100); // msg
    msg << "TemplateFeature version to update from " << featureVersion << " to " << softVersion;
    if (featureVersion > softVersion) { // unexpected version
        msg << " : Unexpected Error!";
        cout << msg.str() << endl;
        this->SetErrMsg(msg.str());
        return E_INVALIDARG;
    }

    HRESULT hr;

    //
    // 2, update.
    // for each case end :run KTC_FEATURE_SETVERSION()
    //     (a),set version to (case value + 1), (b)do not break
    // when enter a case, it will run until default.
    // each time you update software, add a case befaule case default.
    //

    cout << msg.str() << endl;

    // start from feature version
    switch (featureVersion) {
    case 0: {
        //
        // your code to update version from 0 to 1
        //

        cout << "\tyour code for update from 0 to 1" << endl;
    }
        KTC_FEATURE_SETVERSION(1); // set to case value + 1
    default:
        if (softVersion == this->GetVersion()) // ok for update
            return S_OK;

        // if get here, means wrong!!!
    } // switch
    msg << " : Unexpected Error!";
    this->SetErrMsg(msg.str());
    return E_UNEXPECTED; // unexpected
}

#pragma endregion KEVIN_SYSTEM_CODE_FUNCTIONS

// DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
// START KEVIN CAA WIZARD SECTION PNXTemplateFeature IMPLEMENTS CPP GET

// clang-format off

//-----------------------------------------------
CATISpecObject_var PNXETemplateFeature::GetMyCurve() const // 2
{
    CATISpecObject_var value(NULL_var);
    ktcSpecRW.GetSpecValue("MyCurve", value);
    return value;
}
//-----------------------------------------------
HRESULT PNXETemplateFeature::GetMyFaces(CATListValCATISpecObject_var& value) const // 3
{
    return ktcSpecRW.GetListValue("MyFaces", value);
}
//-----------------------------------------------
double PNXETemplateFeature::GetMyStep() const // 4
{
    double value(5);
    ktcSpecRW.GetSpecValue("MyStep", value);
    return value;
}
//-----------------------------------------------
CATBoolean PNXETemplateFeature::GetFinishCalc() const // 5
{
    CATBoolean value(0);
    ktcSpecRW.GetValue("FinishCalc", value);
    return value;
}

// clang-format on
// END KEVIN CAA WIZARD SECTION PNXTemplateFeature IMPLEMENTS CPP GET

// DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
// START KEVIN CAA WIZARD SECTION PNXTemplateFeature IMPLEMENTS CPP SET

// clang-format off

//-----------------------------------------------
HRESULT PNXETemplateFeature::SetMyCurve(const CATISpecObject_var& value, const CATBoolean& checkExist) // 2
{
    return ktcSpecRW.SetSpecValue("MyCurve", value, checkExist);
}
//-----------------------------------------------
HRESULT PNXETemplateFeature::SetMyFaces(const CATListValCATISpecObject_var& value, const CATBoolean& checkExist) // 3
{
    return ktcSpecRW.SetListValue("MyFaces", value, checkExist);
}
//-----------------------------------------------
HRESULT PNXETemplateFeature::SetMyStep(const double& value, const CATBoolean& checkExist) // 4
{
    return ktcSpecRW.SetSpecValue("MyStep", value, checkExist);
}
//-----------------------------------------------
HRESULT PNXETemplateFeature::SetFinishCalc(const CATBoolean& value, const CATBoolean& checkExist) // 5
{
    return ktcSpecRW.SetValue("FinishCalc", value, checkExist);
}

// clang-format on
// END KEVIN CAA WIZARD SECTION PNXTemplateFeature IMPLEMENTS CPP SET
