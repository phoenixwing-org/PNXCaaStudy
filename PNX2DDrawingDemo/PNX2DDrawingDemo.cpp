/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @file        PNX2DDrawingDemo.cpp
 * @version     V1.0
 * @brief       2D图纸元素属性设置演示类实现
 * @details     演示如何在2D图纸中设置箭头、直线等元素的thickness（粗细）等属性
 * @date        2025-01-XX
 */

// Local Framework
#include "PNX2DDrawingDemo.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// DrawingInterfaces Framework
#include "CATI2DAnnotation.h"
#include "CATI2DLine.h"
#include "CATI2DArrow.h"

// Visualization Framework
#include "CATIVisProperties.h"
#include "CATVisPropertiesValues.h"

// System Framework
#include "CATBoolean.h"
#include "iostream.h"

//-----------------------------------------------------------------------------
// PNX2DDrawingDemo::SetLineThickness
//-----------------------------------------------------------------------------
HRESULT PNX2DDrawingDemo::SetLineThickness(CATI2DLine* ip2DLine, int iThickness) {
    if (NULL == ip2DLine) {
        cout << "[ERROR] PNX2DDrawingDemo::SetLineThickness: ip2DLine is NULL" << endl;
        return E_FAIL;
    }

    // 方法1: 通过CATI2DAnnotation接口设置（推荐）
    CATI2DAnnotation* pi2DAnnotation = NULL;
    HRESULT rc = ip2DLine->QueryInterface(IID_CATI2DAnnotation, (void**)&pi2DAnnotation);
    if (SUCCEEDED(rc) && pi2DAnnotation != NULL) {
        rc = SetAnnotationThickness(pi2DAnnotation, iThickness);
        pi2DAnnotation->Release();
        pi2DAnnotation = NULL;
        return rc;
    }

    // 方法2: 通过CATISpecObject接口设置
    CATISpecObject* piSpecObject = NULL;
    rc = ip2DLine->QueryInterface(IID_CATISpecObject, (void**)&piSpecObject);
    if (SUCCEEDED(rc) && piSpecObject != NULL) {
        rc = Set2DElementThicknessFromSpec(piSpecObject, iThickness);
        piSpecObject->Release();
        piSpecObject = NULL;
        return rc;
    }

    cout << "[ERROR] PNX2DDrawingDemo::SetLineThickness: Failed to get interface" << endl;
    return E_FAIL;
}

//-----------------------------------------------------------------------------
// PNX2DDrawingDemo::SetArrowThickness
//-----------------------------------------------------------------------------
HRESULT PNX2DDrawingDemo::SetArrowThickness(CATI2DArrow* ip2DArrow, int iThickness) {
    if (NULL == ip2DArrow) {
        cout << "[ERROR] PNX2DDrawingDemo::SetArrowThickness: ip2DArrow is NULL" << endl;
        return E_FAIL;
    }

    // 方法1: 通过CATI2DAnnotation接口设置（推荐）
    CATI2DAnnotation* pi2DAnnotation = NULL;
    HRESULT rc = ip2DArrow->QueryInterface(IID_CATI2DAnnotation, (void**)&pi2DAnnotation);
    if (SUCCEEDED(rc) && pi2DAnnotation != NULL) {
        rc = SetAnnotationThickness(pi2DAnnotation, iThickness);
        pi2DAnnotation->Release();
        pi2DAnnotation = NULL;
        return rc;
    }

    // 方法2: 通过CATISpecObject接口设置
    CATISpecObject* piSpecObject = NULL;
    rc = ip2DArrow->QueryInterface(IID_CATISpecObject, (void**)&piSpecObject);
    if (SUCCEEDED(rc) && piSpecObject != NULL) {
        rc = Set2DElementThicknessFromSpec(piSpecObject, iThickness);
        piSpecObject->Release();
        piSpecObject = NULL;
        return rc;
    }

    cout << "[ERROR] PNX2DDrawingDemo::SetArrowThickness: Failed to get interface" << endl;
    return E_FAIL;
}

//-----------------------------------------------------------------------------
// PNX2DDrawingDemo::SetAnnotationThickness
//-----------------------------------------------------------------------------
HRESULT PNX2DDrawingDemo::SetAnnotationThickness(CATI2DAnnotation* ip2DAnnotation, int iThickness) {
    if (NULL == ip2DAnnotation) {
        cout << "[ERROR] PNX2DDrawingDemo::SetAnnotationThickness: ip2DAnnotation is NULL" << endl;
        return E_FAIL;
    }

    // 获取CATISpecObject接口
    CATISpecObject* piSpecObject = NULL;
    HRESULT rc = ip2DAnnotation->QueryInterface(IID_CATISpecObject, (void**)&piSpecObject);
    if (FAILED(rc) || piSpecObject == NULL) {
        cout << "[ERROR] PNX2DDrawingDemo::SetAnnotationThickness: Failed to get CATISpecObject" << endl;
        return E_FAIL;
    }

    // 调用通用方法设置属性
    rc = Set2DElementThicknessFromSpec(piSpecObject, iThickness);

    piSpecObject->Release();
    piSpecObject = NULL;

    return rc;
}

//-----------------------------------------------------------------------------
// PNX2DDrawingDemo::Set2DElementProperties
//-----------------------------------------------------------------------------
HRESULT PNX2DDrawingDemo::Set2DElementProperties(CATI2DAnnotation* ip2DAnnotation, 
                                               int iThickness,
                                               int iRed, 
                                               int iGreen, 
                                               int iBlue) {
    if (NULL == ip2DAnnotation) {
        cout << "[ERROR] PNX2DDrawingDemo::Set2DElementProperties: ip2DAnnotation is NULL" << endl;
        return E_FAIL;
    }

    // 获取CATISpecObject接口
    CATISpecObject* piSpecObject = NULL;
    HRESULT rc = ip2DAnnotation->QueryInterface(IID_CATISpecObject, (void**)&piSpecObject);
    if (FAILED(rc) || piSpecObject == NULL) {
        cout << "[ERROR] PNX2DDrawingDemo::Set2DElementProperties: Failed to get CATISpecObject" << endl;
        return E_FAIL;
    }

    // 获取CATIVisProperties接口
    CATIVisProperties* piVisProperties = NULL;
    rc = piSpecObject->QueryInterface(IID_CATIVisProperties, (void**)&piVisProperties);
    if (FAILED(rc) || piVisProperties == NULL) {
        cout << "[ERROR] PNX2DDrawingDemo::Set2DElementProperties: Failed to get CATIVisProperties" << endl;
        piSpecObject->Release();
        piSpecObject = NULL;
        return E_FAIL;
    }

    // 创建属性值对象并设置属性
    CATVisPropertiesValues attribut;
    
    // 设置线宽（thickness）
    attribut.SetWidth(iThickness);
    
    // 设置颜色（如果提供了颜色值）
    if (iRed >= 0 && iRed <= 255 && 
        iGreen >= 0 && iGreen <= 255 && 
        iBlue >= 0 && iBlue <= 255) {
        attribut.SetColor(iRed, iGreen, iBlue);
    }

    // 应用属性到2D元素
    // CATVPAllPropertyType: 应用所有属性类型
    // CATVPLine: 应用到线条类型（适用于直线、箭头等）
    rc = piVisProperties->SetPropertiesAtt(attribut, CATVPAllPropertyType, CATVPLine);

    if (SUCCEEDED(rc)) {
        cout << "[INFO] PNX2DDrawingDemo::Set2DElementProperties: Successfully set thickness=" 
             << iThickness << ", color=(" << iRed << "," << iGreen << "," << iBlue << ")" << endl;
    } else {
        cout << "[ERROR] PNX2DDrawingDemo::Set2DElementProperties: Failed to set properties" << endl;
    }

    // 释放接口
    piVisProperties->Release();
    piVisProperties = NULL;
    piSpecObject->Release();
    piSpecObject = NULL;

    return rc;
}

//-----------------------------------------------------------------------------
// PNX2DDrawingDemo::Set2DElementThicknessFromSpec
//-----------------------------------------------------------------------------
HRESULT PNX2DDrawingDemo::Set2DElementThicknessFromSpec(CATISpecObject* ipSpecObject, int iThickness) {
    if (NULL == ipSpecObject) {
        cout << "[ERROR] PNX2DDrawingDemo::Set2DElementThicknessFromSpec: ipSpecObject is NULL" << endl;
        return E_FAIL;
    }

    // 获取CATIVisProperties接口
    CATIVisProperties* piVisProperties = NULL;
    HRESULT rc = ipSpecObject->QueryInterface(IID_CATIVisProperties, (void**)&piVisProperties);
    if (FAILED(rc) || piVisProperties == NULL) {
        cout << "[ERROR] PNX2DDrawingDemo::Set2DElementThicknessFromSpec: Failed to get CATIVisProperties" << endl;
        return E_FAIL;
    }

    // 创建属性值对象
    CATVisPropertiesValues attribut;
    
    // 设置线宽（thickness）
    attribut.SetWidth(iThickness);
    
    // 应用属性
    // CATVPAllPropertyType: 应用所有属性类型
    // CATVPLine: 应用到线条类型（适用于2D图纸中的直线、箭头等元素）
    rc = piVisProperties->SetPropertiesAtt(attribut, CATVPAllPropertyType, CATVPLine);

    if (SUCCEEDED(rc)) {
        cout << "[INFO] PNX2DDrawingDemo::Set2DElementThicknessFromSpec: Successfully set thickness=" 
             << iThickness << endl;
    } else {
        cout << "[ERROR] PNX2DDrawingDemo::Set2DElementThicknessFromSpec: Failed to set thickness" << endl;
    }

    // 释放接口
    piVisProperties->Release();
    piVisProperties = NULL;

    return rc;
}

