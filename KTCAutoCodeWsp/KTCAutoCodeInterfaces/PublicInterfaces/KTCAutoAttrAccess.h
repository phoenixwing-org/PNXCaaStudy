/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXAutoCode
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef KTCAutoAttrAccess_H
#define KTCAutoAttrAccess_H

// CAT
#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// Auto Code
#include "KTCAutoAttrAccess.h"
#include "KTCAutoCodeItf.h"
#include "KtString.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoAttrAccess {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoAttrAccess();
    virtual ~KTCAutoAttrAccess();

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoAttrAccess(const KTCAutoAttrAccess&);
    KTCAutoAttrAccess& operator=(const KTCAutoAttrAccess&);

public:
    /**
     * @brief initial
     * @param name attribute name
     * @return bool
     */
    HRESULT initial(CATISpecObject_var value);

    /**
     * @brief Is Available
     * @return bool
     */
    bool IsAvailable() const;

public:
    /**
     * @brief Get List Value of specobject
     * @param name attribute name
     * @param value output value
     * @return HRESULT
     */
    HRESULT GetListValue(const CATUnicodeString& name, CATListValCATISpecObject_var& value) const;

    /**
     * @brief Get Value of specobject
     * @param name attribute name
     * @param value output value
     * @return HRESULT
     */
    HRESULT GetSpecValue(const CATUnicodeString& name, CATISpecObject_var& value) const;

    /**
     * @brief Get Value of CATBoolean
     * @param name attribute name
     * @param value output value
     * @return HRESULT
     */
    HRESULT GetSpecValue(const CATUnicodeString& name, CATBoolean& value) const;

    /**
     * @brief Get Value of int
     * @param name attribute name
     * @param value output value
     * @return HRESULT
     */
    HRESULT GetSpecValue(const CATUnicodeString& name, int& value) const;

    /**
     * @brief Get Value of double
     * @param name attribute name
     * @param value output value
     * @return HRESULT
     */
    HRESULT GetSpecValue(const CATUnicodeString& name, double& value) const;

    /**
     * @brief Get Value of CATBoolean
     * @param name attribute name
     * @param value output value
     * @return HRESULT
     */
    HRESULT GetValue(const CATUnicodeString& name, CATBoolean& value) const;

    /**
     * @brief Get Value of int
     * @param name attribute name
     * @param value output value
     * @return HRESULT
     */
    HRESULT GetValue(const CATUnicodeString& name, int& value) const;
    /**
     * @brief Get Value of double
     * @param name attribute name
     * @param value output value
     * @return HRESULT
     */
    HRESULT GetValue(const CATUnicodeString& name, double& value) const;

    /**
     * @brief Get Value of CATUnicodeString
     * @param name attribute name
     * @param value output value
     * @return HRESULT
     */
    HRESULT GetValue(const CATUnicodeString& name, CATUnicodeString& value) const;

    /**
     * @brief Get Value of KtString
     * @param name attribute name
     * @param value output value
     * @return HRESULT
     */
    HRESULT GetValue(const CATUnicodeString& name, KtString& value) const;

public: // Set
    /**
     * @brief Set Spec Value
     * @param name attribute name
     * @param[in] value CATListValCATISpecObject_var
     * @param[in] checkExist whether check exist
     * @return HRESULT
     * @author Phoenix
     */
    HRESULT SetListValue(const CATUnicodeString& name, const CATListValCATISpecObject_var& value,
                         CATBoolean checkExist = CATTrue);

    /**
     * @brief Set Spec Value
     * @param name attribute name
     * @param[in] value CATISpecObject_var
     * @param[in] checkExist whether check exist
     * @return HRESULT
     * @author Phoenix
     */
    HRESULT SetSpecValue(const CATUnicodeString& name, const CATISpecObject_var& value,
                         CATBoolean checkExist = CATTrue);

    /**
     * @brief Set Spec Value
     * @param name attribute name
     * @param[in] value CATISpecObject_var
     * @param[in] checkExist whether check exist
     * @return HRESULT
     * @author Phoenix
     */
    HRESULT SetSpecValue(const CATUnicodeString& name, CATBoolean value,
                         CATBoolean checkExist = CATTrue);

    /**
     * @brief Set Spec Value
     * @param name attribute name
     * @param[in] value int
     * @param[in] checkExist whether check exist
     * @return HRESULT
     * @author Phoenix
     */
    HRESULT SetSpecValue(const CATUnicodeString& name, int value, CATBoolean checkExist = CATTrue);

    /**
     * @brief Set Spec Value
     * @param name attribute name
     * @param[in] value double
     * @param[in] checkExist whether check exist
     * @return HRESULT
     * @author Phoenix
     */
    HRESULT SetSpecValue(const CATUnicodeString& name, double value,
                         CATBoolean checkExist = CATTrue);

    /**
     * @brief Set Value
     * @param name attribute name
     * @param[in] value double
     * @return HRESULT
     * @author Phoenix
     */
    HRESULT SetValue(const CATUnicodeString& name, double value, CATBoolean checkExist = CATTrue);

    /**
     * @brief Set Value
     * @param name attribute name
     * @param[in] value int
     * @return HRESULT
     * @author Phoenix
     */
    HRESULT SetValue(const CATUnicodeString& name, int value, CATBoolean checkExist = CATTrue);

    /**
     * @brief Set Value
     * @param name attribute name
     * @param[in] value CATBoolean
     * @return HRESULT
     * @author Phoenix
     */
    HRESULT SetValue(const CATUnicodeString& name, CATBoolean value,
                     CATBoolean checkExist = CATTrue);

    /**
     * @brief Set Value
     * @param name attribute name
     * @param[in] value CATUnicodeString
     * @return HRESULT
     * @author Phoenix
     */
    HRESULT SetValue(const CATUnicodeString& name, const CATUnicodeString& value,
                     CATBoolean checkExist = CATTrue);

    /**
     * @brief Set Value
     * @param name attribute name
     * @param[in] value KtString
     * @return HRESULT
     * @author Phoenix
     */
    HRESULT SetValue(const CATUnicodeString& name, const KtString& value,
                     CATBoolean checkExist = CATTrue);

private:
    bool available_; // is available
};

#endif
