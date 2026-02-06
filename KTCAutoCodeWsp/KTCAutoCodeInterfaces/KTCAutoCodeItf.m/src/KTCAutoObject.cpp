/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    KTCAutoCode
 * @file  		KTCAutoObject.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

#include "CATError.h"
#include "CATMfErrUpdate.h"
#include "iostream.h"

// Local
#include "KTCAutoObject.h"

//-----------------------------------------------------------------------------
KTCAutoObject::KTCAutoObject() {

    // your code here:
}
//-----------------------------------------------------------------------------
KTCAutoObject::~KTCAutoObject() {
}
//-----------------------------------------------------------------------------
void KTCAutoObject::print_info(CATISpecObject_var object, const char* title, int type) {
    if (!object) {
        cout << "    - input object is NULL_var." << endl;
        return;
    }

    // with object
    switch (type) {
    case 0:
        cout << "    - " << title << " Object : { Name = `" << object->GetName()
             << "`, DisplayName = `" << object->GetDisplayName() << "`, Type = `"
             << object->GetType() << "`, SupperType = `" << object->GetSuperType() << "`}" << endl;
        break;
    default:
        cout << "    - input Type Error: `" << type << "`" << endl;
    }
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoObject::update(CATISpecObject_var object, bool isCout) {
    if (!object) return E_INVALIDARG;

    // ¸üÐÂ
    CATTry {
        int result = object->Update();
        if (0 == result)
            return S_OK;
        else {
            if (isCout) cout << "Error update `" << object->GetName() << "`" << endl;
            return E_FAIL;
        }
    }
    CATCatch(CATMfErrUpdate, pUpdateError) { // ´íÎó
        if (isCout) {
            cout << "Error update `" << object->GetName() << "`" << pUpdateError->GetDiagnostic()
                 << endl;
        }
    }
    CATCatch(CATError, pError) { // ´íÎó
        if (isCout) {
            cout << "Error update `" << object->GetName() << "`" << pError->GetMessageText()
                 << endl;
        }
    }
    CATEndTry;

    return E_UNEXPECTED;
}
