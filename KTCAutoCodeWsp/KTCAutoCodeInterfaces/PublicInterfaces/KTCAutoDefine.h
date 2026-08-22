/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @file        KTCAutoDefine.h
 * @date		2021-9-16
 * @brief       Core defines
 */
#ifndef KTCAutoDefine_H_
#define KTCAutoDefine_H_

#include <KtCore/KtCoreDefine.h>

/** @brief CAA min pixel value, 0.000001m = 0.001mm */
#define KTC_MIN_LENGTH_VALUE_M 1e-6

/** @brief CAA min pixel value, 0.001mm */
#define KTC_MIN_LENGTH_VALUE_MM 0.001

/** MAX LENGTH in CAA */
#define KTC_FLT_MAX_LENGTH 1e38F

#pragma region functions

/**
 * @brief CAA pointer Release
 * @param[in] pCAA CAA feature pointer
 */
#define KTCRelease(pCAA) \
    if (NULL != pCAA) {  \
        pCAA->Release(); \
        pCAA = NULL;     \
    }

/**
 * @brief empty the CAA ISO or HSO
 * @param[in] OBJECT ISO or HSO pointer
 */
#define KTCEmpty(OBJECT)  \
    if (NULL != OBJECT) { \
        OBJECT->Empty();  \
        OBJECT = NULL;    \
    }

/**
 * @brief CAA pointer RequestDelayedDestruction
 * @param[in] pCAA CAA feature pointer
 */
#define KTCRequestDelayedDestruction(pCAA) \
    if (NULL != pCAA) {                    \
        pCAA->RequestDelayedDestruction(); \
        pCAA = NULL;                       \
    }

/** @brief No Doc. */
#define KTCRequestDelayedDestructionIf KTCRequestDelayedDestruction

/** @brief No Selection String. */
#define KTC_NO_SELECTION "(No Selection)"

/**
 * @brief Kevin system set version for CAA feature.
 * @param[in] id target version id
 * @return if failed, return hr. if ok, do not break.
 */
#define KTC_FEATURE_SETVERSION(id) \
    {                              \
        hr = this->SetVersion(id); \
        if (FAILED(hr)) return hr; \
    }

/** @brief give the icon of direction sign. */
#define KTC_DIRECTION_SIGN_ICON(sign) (sign) < 0 ? "I_KTCDirectionDown" : "I_KTCDirectionUp"

/** @brief invert the direction sign. */
#define KTC_DIRECTION_SIGN_INVERT(sign) sign = (sign) < 0 ? 1 : -1

/** @brief direction down,  sign < 0. */
#define KTC_DIRECTION_SIGN_DOWN(sign) (sign) < 0

#pragma endregion functions

// enum
namespace KTC {
/** @brief Feature Mode */
enum FeatureMode {
    FeatureModeEdit     = 0,
    FeatureModeCreation = 1,
};

/** @brief value action mode */
enum ValueActionMode {
    ValueNormal   = 0, // if exist , remove, otherwise append
    ValueAdd      = 1, // append only
    ValueSubtract = 2, // remove only
};

typedef int Key_Item;

#ifndef CATULONG64
typedef unsigned long long CtxMenuDef;
#else
typedef CATULONG64 CtxMenuDef;
#endif

} // namespace KTC

/**
 * @brief set message
 * @param MESSAGE append message
 */
#define KTC_MESSAGE_LINE(MESSAGE) (msg = MESSAGE)

/**
 * @brief set new message with prifix Funcion
 * @param MESSAGE append message
 * like:KT_MESSAGE_FUN_HR("Query CATICkeParmFactory error.",hr);
 */
#define KTC_MESSAGE_FUN(MESSAGE) (msg = __FUNCTION__) << " : " << MESSAGE

/**
 * @brief set new message with prifix Funcion and hr
 * @param MESSAGE append message
 * @param HR append hr
 * like:KT_MESSAGE_FUN_HR("Query CATICkeParmFactory error.",hr);
 */
#define KTC_MESSAGE_FUN_HR(MESSAGE, HR) \
    (msg = __FUNCTION__) << " : " << MESSAGE << " hr = " << (int)HR

#define KTC_MESSAGE_CODE_RETURN_HR(MESSAGE, HR, CODE)  \
    {                                                  \
        msg.clear() << MESSAGE << " hr = " << (int)HR; \
        parameter->set_message(CODE, msg);             \
        return hr;                                     \
    }

#define KTC_MESSAGE_RETURN_CODE(MESSAGE, CODE) \
    {                                          \
        msg.clear() << MESSAGE;                \
        parameter->set_message(CODE, msg);     \
        return CODE;                           \
    }

#define KTC_MESSAGE_FUN_CODE_RETURN_HR(MESSAGE, HR, CODE)                       \
    {                                                                           \
        msg.clear() << __FUNCTION__ << " : " << MESSAGE << " hr = " << (int)HR; \
        parameter->set_message(CODE, msg);                                      \
        return hr;                                                              \
    }

#endif // KTCAutoDefine_H_
