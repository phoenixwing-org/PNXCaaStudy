/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @file        PNX2DDrawingDemo.h
 * @version     V1.0
 * @brief       2D图纸元素属性设置演示类
 * @details     演示如何在2D图纸中设置箭头、直线等元素的thickness（粗细）等属性
 * @date        2025-01-XX
 */

#ifndef PNX2DDrawingDemo_H
#define PNX2DDrawingDemo_H

// System Framework
#include "CATBaseUnknown.h"

class CATISpecObject;
class CATI2DAnnotation;
class CATI2DLine;
class CATI2DArrow;

/**
 * @class PNX2DDrawingDemo
 * @brief 2D图纸元素属性设置演示类
 *
 * 本类演示如何在CAA 2D图纸中设置以下元素的属性：
 * - 直线（Line）的thickness（线宽）
 * - 箭头（Arrow）的thickness（线宽）
 * - 其他2D图形元素的属性设置
 */
class PNX2DDrawingDemo {
public:
    /**
     * @brief 设置2D直线的thickness（线宽）属性
     * @param[in] ip2DLine 2D直线对象的指针
     * @param[in] iThickness 线宽值（像素单位，通常1-10）
     * @return HRESULT S_OK表示成功，E_FAIL表示失败
     */
    static HRESULT SetLineThickness(CATI2DLine* ip2DLine, int iThickness);

    /**
     * @brief 设置2D箭头的thickness（线宽）属性
     * @param[in] ip2DArrow 2D箭头对象的指针
     * @param[in] iThickness 线宽值（像素单位，通常1-10）
     * @return HRESULT S_OK表示成功，E_FAIL表示失败
     */
    static HRESULT SetArrowThickness(CATI2DArrow* ip2DArrow, int iThickness);

    /**
     * @brief 设置2D注释元素的thickness（线宽）属性（通用方法）
     * @param[in] ip2DAnnotation 2D注释对象的指针
     * @param[in] iThickness 线宽值（像素单位，通常1-10）
     * @return HRESULT S_OK表示成功，E_FAIL表示失败
     */
    static HRESULT SetAnnotationThickness(CATI2DAnnotation* ip2DAnnotation, int iThickness);

    /**
     * @brief 设置2D图形元素的thickness和颜色属性（完整示例）
     * @param[in] ip2DAnnotation 2D注释对象的指针
     * @param[in] iThickness 线宽值（像素单位，通常1-10）
     * @param[in] iRed 红色分量（0-255）
     * @param[in] iGreen 绿色分量（0-255）
     * @param[in] iBlue 蓝色分量（0-255）
     * @return HRESULT S_OK表示成功，E_FAIL表示失败
     */
    static HRESULT Set2DElementProperties(CATI2DAnnotation* ip2DAnnotation, int iThickness,
                                          int iRed = 0, int iGreen = 0, int iBlue = 0);

    /**
     * @brief 从CATISpecObject获取2D注释并设置属性
     * @param[in] ipSpecObject 规格对象指针（可以是2D直线、箭头等）
     * @param[in] iThickness 线宽值
     * @return HRESULT S_OK表示成功，E_FAIL表示失败
     */
    static HRESULT Set2DElementThicknessFromSpec(CATISpecObject* ipSpecObject, int iThickness);
};

#endif // PNX2DDrawingDemo_H
