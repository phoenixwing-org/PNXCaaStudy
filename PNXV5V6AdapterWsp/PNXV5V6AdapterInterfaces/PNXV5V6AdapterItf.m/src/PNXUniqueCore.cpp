/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @date		2025-11-11
 * @brief
 */

// CAT
#include "CATDocument.h"
#include "CATMathTransformation.h"
#include "CATPoint.h"
#include "iostream.h"

// Local
#include "PNXUniqueCore.h"
//-----------------------------------------------------------------------------
PNXUniqueCore::PNXUniqueCore() 
{
 
}
//-----------------------------------------------------------------------------
PNXUniqueCore::~PNXUniqueCore() {

}
//-----------------------------------------------------------------------------
HRESULT PNXUniqueCore::CheckoutAxis() {
    CATMathAxis MyAxis = CATMathOIJK; // set abs axis

    // if (NULL_var == CurrentAxis) // abs axis
    //     return S_OK;

    return S_OK;
}
//-----------------------------------------------------------------------------
void PNXUniqueCore::dump() {
}
