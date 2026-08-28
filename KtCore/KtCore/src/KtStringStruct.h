/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @file        KtStringStruct.h
 * @version		V1.0
 */
#ifndef _KtStringStruct_H_
#define _KtStringStruct_H_

/**
 * @brief Internal structure for string metadata
 * @details The string data follows immediately after this structure in memory
 */
struct KtStringStruct {
    /** @brief Capacity of the string buffer */
    unsigned int space;

    /** @brief Current length of the string */
    unsigned int size;

    /**
     * @brief Get pointer to the string data
     * @return Pointer to the character array following this structure
     */
    char* data() {
        return reinterpret_cast<char*>(this + 1);
    }

    /**
     * @brief Get const pointer to the string data
     * @return Const pointer to the character array following this structure
     */
    const char* data() const {
        return reinterpret_cast<const char*>(this + 1);
    }
};
#endif