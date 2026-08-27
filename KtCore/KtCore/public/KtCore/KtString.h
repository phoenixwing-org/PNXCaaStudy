/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @file        KtString.h
 * @version		V1.0
 * @brief       KtString in Kt Core
 * @details  	string base on lib
 * header file fit for C++ 98
 */
#ifndef _KtString_H_
#define _KtString_H_

#include <KtCore/KtCore.h>

// std
#include <cstring> // for strcmp
#include <iostream>
#include <limits.h>
#include <string>

class KtStringStruct;

/** @brief KtString in Kt */
class ExportedByKtCore KtString {
public: // structure
    /** @brief constructor */
    KtString(unsigned int iSpace = 0);

    /** @brief constructor */
    KtString(int space);

    /** destructor */
    ~KtString();

    /**
     * @brief constructor
     * @param[in] str char pointer
     * @param[in] count default -1
     */
    KtString(const char* str, unsigned int count = UINT_MAX);

    /**
     * @brief constructor
     * @param[in] iOriginal string pass by reference
     */
    KtString(const KtString& iOriginal);

    // Assignment Operators
    /**
     * @brief Copy assignment operator
     * @param[in] other String to copy from
     * @return Reference to this string
     */
    KtString& operator=(const KtString& other);

    /**
     * @brief Assignment operator from C-string
     * @param[in] str C-string to assign
     * @return Reference to this string
     */
    KtString& operator=(const char* str);

    // Comparison Operators
    /**
     * @brief Equality operator
     * @param[in] other String to compare with
     * @return True if strings are equal
     */
    bool operator==(const KtString& other) const;

    /**
     * @brief Equality operator with C-string
     * @param[in] str C-string to compare with
     * @return True if strings are equal
     */
    bool operator==(const char* str) const;

    /**
     * @brief Less-than comparison operator
     * @param[in] other String to compare with
     * @return True if this string is lexicographically less than other
     */
    bool operator<(const KtString& other) const;

    // Concatenation Operators
    /**
     * @brief Concatenation operator with C-string
     * @param[in] str C-string to append
     * @return New string containing the concatenated result
     */
    KtString operator+(const char* str) const;

    /**
     * @brief Concatenation operator with KtString
     * @param[in] other String to append
     * @return New string containing the concatenated result
     */
    KtString operator+(const KtString& other) const;

    // Stream-like Append Operators
    /**
     * @brief Append a single character
     * @param[in] ch Character to append
     * @return Reference to this string
     */
    KtString& operator<<(char ch);

    /**
     * @brief Append an integer value
     * @param[in] value Integer value to append
     * @return Reference to this string
     */
    KtString& operator<<(int value);

    /**
     * @brief Append a float value
     * @param[in] value Float value to append
     * @return Reference to this string
     */
    KtString& operator<<(float value);

    /**
     * @brief Append an unsigned integer value
     * @param[in] value Unsigned integer value to append
     * @return Reference to this string
     */
    KtString& operator<<(unsigned int value);

    /**
     * @brief Append a C-string
     * @param[in] str C-string to append
     * @return Reference to this string
     */
    KtString& operator<<(const char* str);

    /**
     * @brief Append another KtString
     * @param[in] other String to append
     * @return Reference to this string
     */
    KtString& operator<<(const KtString& other);

    /**
     * @brief Append a pointer address
     * @param[in] ptr Pointer to append
     * @return Reference to this string
     */
    KtString& operator<<(void* ptr);

    /**
     * @brief Stream output operator
     * @param[in] os Output stream
     * @param[in] str String to output
     * @return Reference to the output stream
     */
    friend inline std::ostream& operator<<(std::ostream& os, const KtString& str) {
        return os << str._pText;
    }

    /**
     * @brief Logical NOT operator - checks if string is empty
     * @return True if string is empty
     */
    bool operator!() const;

    /**
     * @brief Subscript operator (non-const)
     * @param[in] index Character index
     * @return Reference to the character at the specified index
     * @warning No bounds checking is performed
     */
    char& operator[](unsigned int index);

    /**
     * @brief Subscript operator (const)
     * @param[in] index Character index
     * @return Const reference to the character at the specified index
     * @warning No bounds checking is performed
     */
    const char& operator[](unsigned int index) const;

    // String Modification Functions
    /**
     * @brief Append a C-string to this string
     * @param[in] str C-string to append
     * @param[in] len Length to append (UINT_MAX for auto, 0 to skip)
     * @note If len is larger than the actual string length, spaces will be filled
     * @return Reference to this string
     */
    KtString& append(const char* str, unsigned int len = UINT_MAX);

    /**
     * @brief Append a file name with path separator
     * @param[in] fileName File name to append
     * @return Reference to this string
     * @note Automatically adds '/' separator if needed
     */
    KtString& append_filename(const KtString& fileName);

    /**
     * @brief Get the last character of the string
     * @return Const reference to the last character
     * @warning No bounds checking - undefined if string is empty
     */
    const char& back() const;

    /**
     * @brief Get the capacity of the string buffer
     * @return Number of characters that can be stored without reallocation
     */
    unsigned int capacity() const;

    /**
     * @brief Clear the string content without releasing memory
     * @return Reference to this string
     * @see release() to free memory
     */
    KtString& clear();

    /**
     * @brief compare if two texts is equal
     * @param[in] other compared KtString
     * @return integer, compare result:0:same,-：smaller,+:greater
     */
    int compare(const char* other) const;

    /**
     * @brief correct the size of the string by find the char '\0'.
     * @return a reference to this string.
     */
    KtString& correct();

    /**
     * @brief cout class members for debug
     * @return void
     */
    inline void dump() const {
        std::cout << _pText << std::endl;
    }

    /**
     * @brief Set string with the lowest numbered.
     * @param[in] width specifies the amount of space that argument fillChar shall occupy.
     *  If a requires less space than minWidth, it is padded to minWidth with character fillChar.
     *  A positive(+) width produces right-fill text.
     *  A negative(-) minWidth produces left-fill text.
     * 	0:do not fill;
     * @param[in] fillChar the given character.
     * @return a reference to this string. this function do not change the size.
     */
    KtString& fill(int width, const char fillChar = ' ');

    /**
     * @brief Set string with the lowest numbered.
     * @param[in] minWidth specifies the minimum amount of space that argument fillChar shall
     * occupy. If a requires less space than minWidth, it is padded to minWidth with character
     * fillChar. A positive(+) minWidth produces right-aligned text. A negative(-) minWidth produces
     * left-aligned text. 0:auto width;
     * @param[in] fillChar the given character..
     * @return a reference to this string
     */
    KtString& fill_width(unsigned int minWidth, const char fillChar = ' ');

    /**
     * @brief get first one of string
     * @return the first one character
     */
    const char& front() const;

    /**
     * @brief inserts the C string after at the given index position
     * @param[in] position insert position. start from 0
     * @param[in] after string
     * @param[in] len [0,~): after string length, (~,0): auto get length of after;
     * @return a reference to this string
     */
    KtString& insert(unsigned int position, const char* after, unsigned int len = -1);

    /**
     * @brief check the string if is empty
     * @return bool true:empty false:not empty
     */
    bool is_empty() const;

    /**
     * @brief get left string by specified length
     * @param[in] count length
     * @return left string
     */
    KtString left(unsigned int count) const;

    /**
     * @brief pop count from the tail
     * @param[in] count pop count
     * @return a reference to this string
     * @note resize(size - count)
     */
    KtString& pop(unsigned int count);

    /**
     * @brief release the memory
     */
    void release();

    /**
     * @brief remove count characters beginning at index position.
     * @param[in] position insert position.
     * @param[in] count characters count to remove.
     * @return a reference to this string
     */
    KtString& remove(unsigned int position, unsigned int count);

    /**
     * @brief Replaces n characters beginning at index position with the string after.
     * @param[in] position insert position.
     * @param[in] n characters count to being replaced.
     * @param[in] after target string
     * @param[in] len [0,~):target string length, (~,0): auto get length of after;
     * @return a reference to this string
     * @see insert() when n = 0.
     */
    KtString& replace(unsigned int position, unsigned int n, const char* after,
                      unsigned int len = -1);

    /**
     * @brief change space
     * @param[in] count length
     * @return capacity obtained. Maybe less or larger than you want.
     */
    unsigned int reserve(unsigned int count);

    /**
     * @brief resize a new size.
     * If count larger than size, you have to handle the middle/
     * empty characters (end tags).
     * @param count target string size
     * @return size obtained. Maybe less than you want.
     * @see resize(count,fillChar) for fill vacancy.
     */
    unsigned int resize(unsigned int count);

    /**
     * @brief resize and fill with given fillChar.
     * @param count target string size, Negative representation 0.
     * @param[in] fillChar the given character.
     * @return size obtained. Maybe less than you want.
     * @see resize(count)
     */
    unsigned int resize(unsigned int count, const char fillChar);

    /**
     * @brief get right string by specified length
     * @param[in] count length
     * @return right string
     */
    KtString right(unsigned int count) const;

    /**
     * @brief convert double to string
     * @param[in] value double value
     * @param[in] n digit count, 0 means default 6. max 16.
     * @return bool: execution result
     */
    KtString& set_num(double value, unsigned int n = 6);

    /**
     * @brief float	convert to string
     * @param[in] value float value
     * @param[in] n digit count, 0 means default 6, max 8.
     * @return bool: execution result
     */
    KtString& set_num(float value, unsigned int n = 6);

    /**
     * @brief unsigned int convert to string
     * @param[in] value unsigned int value
     * @return bool: execution result
     */
    KtString& set_num(unsigned int value);

    /**
     * @brief integer convert to string
     * @param[in] value integer value
     * @return a reference to this string
     */
    KtString& set_num(int value);

    /**
     * @brief Returns a copy of this string with the lowest numbered
     * @param[in] value number
     * @param[in] minWidth specifies the minimum amount of space that argument fillChar shall
     * occupy. If a requires less space than minWidth, it is padded to minWidth with character
     * fillChar. A positive(+) minWidth produces right-aligned text. A negative(-) minWidth produces
     * left-aligned text. 0:auto width;
     * @param[in] fillChar the given character.
     * @return a reference to this string
     */
    KtString& set_num_width(int value, unsigned int minWidth, const char fillChar = ' ');

    /**
     * @brief Returns a copy of this string with the lowest numbered
     * @param[in] value number
     * @param[in] minWidth specifies the minimum amount of space that argument fillChar shall
     * occupy. If a requires less space than minWidth, it is padded to minWidth with character
     * fillChar. A positive(+) minWidth produces right-aligned text. A negative(-) minWidth produces
     * left-aligned text. 0:auto width;
     * @param[in] fillChar the given character.
     * @return a reference to this string
     */
    KtString& set_num_width(double value, unsigned int minWidth, const char fillChar = ' ');

    /**
     * @brief (<<)operator:This << dis, shift characters to left
     * @param[in] dis shift distance . 0: no shift; (~,0): shift left; (0,~) shift right
     * @param[in] fillChar if shift right,set the vacancy with the char fillChar.
     * @return this
     */
    KtString& shift(int dis, const char fillChar = ' ');

    /**
     * @brief Get the length of current text
     * @return unsigned int
     */
    unsigned int size() const;

    /**
     * @brief get sub string
     * @param[in] pos shift distance . 0: no shift; (~,0]: start from 0; (0,~) start position
     * @param[in] count sub string count.  (~,0): auto to tail; 0: return ""; (0,~) size
     * @return this
     */
    KtString sliced(unsigned int pos, unsigned int count = -1) const;

    /**
     * @brief string convert to string char *
     * @return char*
     */
    const char* str() const;

    /**
     * @brief string convert to double,
     * such as  "123.456" to 123.456
     * @return double
     */
    double to_double() const;

    /**
     * @brief string convert to integer,
     * such as  "123" to 123
     * @return integer
     */
    int to_int() const;

    /**
     * @brief convert to lower string
     * such as  "ABCd" to "abcd"
     * @return lower string
     */
    KtString& to_lower();

    /**
     * @brief convert to lower string copy
     * such as  "ABCd" to "abcd"
     * @return lower string
     */
    KtString to_lower_copy() const;

    /**
     * @brief convert to upper string
     * such as  "Abcd" to "ABCD"
     * @return upper string
     */
    KtString& to_upper();

    /**
     * @brief convert to upper string copy
     * such as  "Abcd" to "ABCD"
     * @return upper string
     */
    KtString to_upper_copy() const;

    /**
     * @brief trim string, remove spaces in the string
     * such as  "ab cd ef " to "abcdef"
     * @return string without spaces
     */
    KtString& trim();

    /**
     * @brief trim left string, remove spaces in the left string
     * @param[in] count length
     * @return left string without spaces
     */
    KtString& trim_left(unsigned int count);

    /**
     * @brief string pointer
     */
    char* data();

protected: // inside
    /**
     * @brief allocate buffer
     * @param[in] count buffer length
     * @return result true:allocate success false:allocate failed
     */
    bool allocate_buffer(const unsigned int count);

    /**
     * @brief copy string
     * @param[in] iOriginal original string
     * @return result true:copy success false:copy failed
     */
    bool copy(const KtString& iOriginal);

    /**
     * @brief copy string
     * @param[in] iOriginal original string
     * @param[in] count target string length
     * @return result true:copy success false:copy failed
     */
    bool copy(const char* str, unsigned int count);

    /**
     * @brief copy string
     * @param[in] str1 string1
     * @param[in] str2 string2
     * @param[i] count target string length,default 0,0:auto. +:length
     * @return result true:copy success false:copy failed
     */
    bool copy(const char* str1, const char* str2, unsigned int count = 0);

    /**  @brief Get pointer to the data for the text */
    KtStringStruct* get_string_struct();

    /**
     * @brief safe delete space
     * @param[in] ipData  data pointer
     */
    static void safe_delete(KtStringStruct* ipData);

    /**
     * @brief safe delete space
     * @param[in] str  KtString pointer
     */
    static void safe_delete(char* str);

protected: // property
    /** @brief string */
    char* _pText;

    /** @brief struct */
    KtStringStruct* _pData;
};

/**
 * @brief KtSetSample declare for string
 * param for KtSetSample:
 * @param[out] ks string to set.
 * @param[in] start start value.
 * @param[in] count wanted size
 * @return size of the list. 0 means error.
 */
inline unsigned int KtSetSample(KtString& ks, char start = 'A', unsigned int count = 8) {
    if (ks.resize(count) != count) return 0;

    // loop
    for (unsigned int i = 0; i < count; i++) {
        ks[ i ] = start % 128;
        start++;
    }

    return count;
}

#endif
