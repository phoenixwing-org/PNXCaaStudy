/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author
 * @file        KtString.cpp
 * @version		V1.0
 * @brief       KtString in Kt Core
 * @details  	string base on lib
 * cpp file fit for C++ 17
 */
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <string>

// Kt Include file
#include "KtString.h"
#include "KtCoreDefine.h"
#include "KtStringStruct.h"

// Instead of always comparing the text pointer if NULL we set to some static data.
// This relives us from allocate memory with empty text.
static unsigned int    g_KtString_Array[]     = {0, 0, 0};
static KtStringStruct* g_KtString_DummyStruct = (KtStringStruct*)g_KtString_Array;
static char*           g_KtString_DummyText   = g_KtString_DummyStruct->data();

/** @brief 设置空字符串 */
#define KTSTRING_SET_EMPTY()       \
    _pText = g_KtString_DummyText; \
    _pData = g_KtString_DummyStruct

//--------------------------------------------------------------------
bool KtIsWhiteChar(const char iChar) {
    switch (iChar) {
    case ' ':
        return true;
    case '\t':
        return true;
    case '\n':
        return true;
    case '\r':
        return true;
    default:
        return false;
    }
}
//--------------------------------------------------------------------
KtString::KtString(unsigned int space) {
    KTSTRING_SET_EMPTY(); // empty
    this->reserve(space);
}
//--------------------------------------------------------------------
KtString::KtString(int space) {
    KTSTRING_SET_EMPTY(); // empty
    this->reserve(space);
}
//--------------------------------------------------------------------
KtString::KtString(const char* str, unsigned int count) {
    // if no text and no length
    if ((str == NULL) || (0 == count)) {
        // set to our dummy text ( don't need to compare for _pText == NULL because of that)
        KTSTRING_SET_EMPTY();
        return;
    }

    unsigned int uintTextLength = (unsigned int)strlen(str);

    // if length i zero and text has been set the make a buffer to the length of text
    if (count > uintTextLength) count = uintTextLength;

    allocate_buffer(count); // allocate buffer for text

    // copy text
    copy(str, count);
}
//--------------------------------------------------------------------
KtString::~KtString() {
    if (_pText != g_KtString_DummyText) {
        delete[] (char*)_pData;
    }
}
//--------------------------------------------------------------------
KtString::KtString(const KtString& iOriginal) {
    KTSTRING_SET_EMPTY();
    copy(iOriginal);
}
//--------------------------------------------------------------------
bool KtString::operator!() const {
    return _pData->size == 0;
}
//--------------------------------------------------------------------
KtString& KtString::operator=(const KtString& iOriginal) {
    if (&iOriginal == this) return *this;

    copy(iOriginal);

    return *this;
}
//--------------------------------------------------------------------
KtString& KtString::operator=(const char* str) {
    this->clear();
    return append(str, -1);
}
//--------------------------------------------------------------------
KtString KtString::operator+(const KtString& str) const {
    KtString st = *this; // copy
    st << str;
    return st;
}
//--------------------------------------------------------------------
KtString KtString::operator+(const char* str) const {
    KtString st = *this; // copy
    st << str;
    return st;
}
//--------------------------------------------------------------------
KtString& KtString::operator<<(char iChar) {
    return append(&iChar, 1);
}
//--------------------------------------------------------------------
KtString& KtString::operator<<(int v) {
    // Int32 -2,147,483,648 to +2,147,483,647
    char str1[ 15 ];

    snprintf(str1, 14, "%d", v); // convert to string
    return append(str1, -1);
}
//--------------------------------------------------------------------
KtString& KtString::operator<<(float v) {
    KtString str;
    str.set_num(v);
    return append(str._pText, str._pData->size); // append
}
//--------------------------------------------------------------------
KtString& KtString::operator<<(unsigned int v) {
    // vmax : 4294967295U
    char str1[ 15 ];             // initial space
    snprintf(str1, 14, "%u", v); // convert to string
    return append(str1, -1);
}
//--------------------------------------------------------------------
KtString& KtString::operator<<(const char* str) { // ok for end char 00
    // char use operator<<(char iChar)
    return append(str, -1);
}
//--------------------------------------------------------------------
KtString& KtString::operator<<(const KtString& str) {
    return append(str._pText, str._pData->size); // append
}
//--------------------------------------------------------------------
KtString& KtString::operator<<(void* pointer) {
    char str1[ 24 ];                     // initial space
    snprintf(str1, 24, "0x%p", pointer); // convert to string
    return append(str1, -1);
}
//--------------------------------------------------------------------
bool KtString::allocate_buffer(const unsigned int count) {
    // calculate space length
    unsigned int uintTotalLength = sizeof(KtStringStruct) + count + 1;
    if (uintTotalLength < count) // this means out of range
        return false;

    // Allocate memory for the data for text and the requested length
    try {
        KtStringStruct* p1 = (KtStringStruct*)new char[ uintTotalLength ];
        _pData             = p1;
    }
    catch (...) {
        // out of memory：
        return false;
    }

    _pText = (char*)_pData->data(); // set pointer to text

    _pData->space = count; // set max length
    _pData->size  = 0;     // set current length

    _pText[ 0 ]     = '\0'; // no characters yet so set first to 0
    _pText[ count ] = '\0'; // set last character in buffer to 0
    return true;
}
//--------------------------------------------------------------------
KtString& KtString::append(const char* str, unsigned int len) {
    if (0 == len || NULL == str) return *this;

    unsigned int pos = 0; //\0 position
    if (len == KtUint_MAX) {
        pos = len = (unsigned int)strlen(str);
        if (0 == len) return *this;
    }
    else {
        // check pos small then len?

        for (; pos < len; pos++) {
            if (0 == str[ pos ]) break;
        }
        // then use pos value
    }

    // Come here, len>0
    if ((KtUint_MAX - _pData->size) < len) // range check
    {
        return *this; // out range:
    }

    const unsigned int total = len + _pData->size; // target length

    if (reserve(total) < total) return *this; // Not enough space was requested

    // get position after last character in string
    try {
        char*        pDst      = _pText + _pData->size;
        unsigned int copyCount = std::min(len, pos); // how many to copy
        memcpy((void*)pDst, (void*)str, copyCount * sizeof(char));

        if (len > pos) // if length larger than length ,append ' '
        {
            memset(pDst + pos, ' ', len - pos);
        }

        _pText[ total ] = '\0'; // set string end
        _pData->size    = total;
    }
    catch (...) {
    }

    return *this;
}
//--------------------------------------------------------------------
KtString& KtString::append_filename(const KtString& iFileName) {
    if (_pData->size != 0 && (this->back() != '\\' && this->back() != '/')) {
        (*this) << "/";
    }

    return append(iFileName._pText, iFileName._pData->size);
}
//--------------------------------------------------------------------
KtString& KtString::clear() {
    if (_pText == g_KtString_DummyText) return *this; // already empty
    _pText[ 0 ]  = '\0';
    _pData->size = 0;
    return *this;
}
//--------------------------------------------------------------------
int KtString::compare(const char* str) const {
    return strcmp(_pText, str);
}
//---INSIDE FUNCTION----------------------------------------
bool KtString::copy(const KtString& iOriginal) {
    if (iOriginal._pText == g_KtString_DummyText) {
        KTSTRING_SET_EMPTY(); // empty
        return true;
    }
    KtStringStruct* pData = iOriginal._pData;

    if (!allocate_buffer(pData->space)) return false;
    return copy(iOriginal._pText, pData->size);
}
//---INSIDE FUNCTION----------------------------------------------
bool KtString::copy(const char* str, unsigned int count) {
    if (0 == count || count >= INT_MAX) // some lager then INT_Max
        count = (unsigned int)strlen(str);

    if (_pData->space < count) return false; // need space exists.

    memcpy(_pText, str, count * sizeof(char));
    _pText[ count ] = '\0';
    _pData->size    = count;
    return true;
}
//---INSIDE FUNCTION----------------------------------------------
bool KtString::copy(const char* str1, const char* str2, unsigned int count) {
    unsigned int uintTextLength1; // length of text 1
    unsigned int uintTextLength2; // length of text 2
    unsigned int uintTotalLength; // the length of both text 1 and text 2 or the SetLength

    KtStringStruct* bufOld; // pointer to the data object for the text

    bufOld = _pData; // Old data

    uintTextLength1 = 0;
    uintTextLength2 = 0;

    if (count != 0) {
        uintTotalLength = count;
    }
    else {
        if (str1 != NULL) uintTextLength1 = (unsigned int)strlen(str1);

        if (str2 != NULL) uintTextLength2 = (unsigned int)strlen(str2);

        uintTotalLength = uintTextLength1 + uintTextLength2;
    }

    if (uintTotalLength) {
        if (!allocate_buffer(uintTotalLength)) {
            return false;
        }
        if (str1)
            if (!copy(str1, uintTextLength1)) {
                KtString::safe_delete(bufOld);
                return false;
            }

        if (str2)
            if (!append(str2, uintTextLength2)) {
                KtString::safe_delete(bufOld);
                return false;
            }
    }

    KtString::safe_delete(bufOld);
    return true;
}
//--------------------------------------------------------------------
KtString& KtString::correct() {
    // NULL string
    if (_pData == g_KtString_DummyStruct) return *this;

    unsigned int space = _pData->space;

    // 查找第一个0就跳出 i 不用等于 space
    for (unsigned int i = 0; i < space; i++) {
        if ('\0' == _pText[ i ]) {
            _pData->size = i; // correct size
            return *this;     // 找到第一个0就跳出
        }
    }

    _pData->size    = space; // correct size
    _pText[ space ] = '\0';  // set last character in buffer to 0
    return *this;
}
//--------------------------------------------------------------------
KtString& KtString::fill(int count, const char fillChar) {
    if (0 == _pData->size || 0 == count) // count 为0，或者本身为空字符串
        return *this;

    // reach here,  count != 0, size > 0.
    // 肯定要填充字符的
    unsigned int width = abs(count); // 填充的宽度

    if (width >= _pData->size)                  // 全部填充
        memset(_pText, fillChar, _pData->size); // length size
    else if (count > 0)                         // right fill
        memset(_pText + (_pData->size - width), fillChar,
               width);                   // length width，起点从后面返回width
    else                                 // left fill
        memset(_pText, fillChar, width); // length width,从头开始

    return *this;
}
//--------------------------------------------------------------------
KtString& KtString::fill_width(unsigned int minWidth, const char fillChar) {
    int dis = minWidth - _pData->size; // dif
    if (dis > 0)                       // right fill fillChar
    {
        if (reserve(minWidth) < minWidth) return *this; // out of memory

        memset(_pText + _pData->size, fillChar, dis); // set fillChar

        _pText[ minWidth ] = 0;        // end char 0
        _pData->size       = minWidth; // set size
    }
    else if ((dis = minWidth + _pData->size) < 0) // left fill fillChar
    {
        this->shift(-dis, fillChar);
    }
    return *this;
}
//--------------------------------------------------------------------
KtStringStruct* KtString::get_string_struct() {
    return ((KtStringStruct*)_pText) - 1;
}
//--------------------------------------------------------------------
KtString& KtString::insert(unsigned int position, const char* after, unsigned int len) {
    if (NULL == after) // need not
        return *this;

    // auto get length
    if (len >= INT_MAX) len = (unsigned int)strlen(after);
    if (0 == len) // need not
        return *this;

    // reach here, means  len>0

    // check position
    if (position >= this->_pData->size) {
        return append(after, len); // append at tail
    }

    // memory allocation
    const unsigned int newSize = len + _pData->size;
    if (this->reserve(newSize) < newSize) { // out of memory
        return *this;
    }

    // memmove(void *str1, const void *str2, size_t n) 从 str2 复制 n 个字符到 str1
    // memmove() is better safe than memcpy()
    // move back
    memmove(_pText + (position + len), // position + len 位置的字符串
            this->_pText + position,   // position 位置的字符串
            _pData->size - position);  // 计算尾部字符串的length ，不考虑尾部的\0

    // memcpy(void *str1, const void *str2, size_t n) 从存储区 str2 复制 n 个字节到存储区 str1
    memcpy(_pText + position, after, len); // copy str

    _pData->size      = newSize; // set size
    _pText[ newSize ] = 0;       // end of string
    return *this;
}
//--------------------------------------------------------------------
bool KtString::is_empty() {
    return _pData->size == 0;
}
//--------------------------------------------------------------------
KtString KtString::left(unsigned int count) const {
    if (count >= _pData->size) return *this; // return this

    // reach here, _pData > 0
    KtString newValue; // for return
    if (0 == count) return newValue;

    if (newValue.reserve(count + 1) < (count + 1)) return newValue;

    newValue.copy(_pText, count); // copy
    return newValue;              // new string
}
//--------------------------------------------------------------------
KtString& KtString::replace(unsigned int position, unsigned int count, const char* after,
                            unsigned int len) {
    // case 1: is tail
    if (position >= _pData->size) return append(after, len);

    // case 2: trim at tail
    // use subtract to prevent out range of unsigned int
    if (count > (_pData->size - position)) {
        this->resize(position);    // at position resize
        return append(after, len); // append
    }

    // check length
    if (NULL == after)
        len = 0;
    else if (len >= INT_MAX) // too long
    {
        len = (unsigned int)strlen(after);
    }

    // target size
    const unsigned int newSize = _pData->size - count + len;
    // reserve newSize space
    if (newSize > _pData->space) {
        if (reserve(newSize) < newSize) return *this; // out of memory
    }

    // case 4：befor 和after数量不等时
    if (len != count) {
        // memmove(void *str1, const void *str2, size_t n) 从 str2 复制 n 个字符到 str1
        // 但是在重叠内存块这方面，memmove() 是比 memcpy() 更安全的方法
        // move back 移动的数量为
        memmove(_pText + position + len,          // position 位置 +len的字符串
                _pText + position + count,        // position 位置 +n的字符串
                _pData->size - position - count); // 计算尾部字符串的length ，不考虑尾部的\0

        _pData->size = newSize; // set size
    }

    // case 5：after count>0  ,NULL != after
    if (len > 0) {
        // memcpy(void *str1, const void *str2, size_t n) 从存储区 str2 复制 n 个字节到存储区 str1
        memcpy(_pText + position, after, len); // copy str
    }

    _pText[ newSize ] = 0; // end of string
    return *this;
}
//--------------------------------------------------------------------
unsigned int KtString::reserve(unsigned int count) {
    // -1- check count
    if (count <= _pData->space) return _pData->space; // need not

    // -2- allocate buffer
    KtStringStruct* bufOld = _pData; // remember old pointer
    if (!allocate_buffer(count))     // failed
        return _pData->space;

    // -3- copy data
    if (!copy(bufOld->data(), bufOld->size)) return _pData->space;

    // -4- release old space
    if (bufOld != NULL) KtString::safe_delete(bufOld);
    return _pData->space;
}
//--------------------------------------------------------------------
unsigned int KtString::resize(unsigned int len) {
    // len = 0
    if (0 == len) {
        // not empty
        if (_pData != g_KtString_DummyStruct) { // length 0
            _pText[ 0 ]  = '\0';
            _pData->size = 0;
        }
        return 0;
    }

    // reach here, len > 0

    // length same,
    if (len == _pData->size) return len;

    // length small
    if (len < _pData->size) {
        _pText[ len ] = '\0';
        _pData->size  = len;
        return len;
    }

    // reach here,  len > size
    if (len > _pData->space) {
        // here, len > space
        if (reserve(len) < len) return _pData->size; // out of memory
    }

    // reach here, space enough
    _pText[ len ] = '\0'; // end char 0
    _pData->size  = len;  // length

    return len;
}
//--------------------------------------------------------------------
unsigned int KtString::resize(unsigned int count, const char fillChar) {
    const unsigned int oldCount = _pData->size; // remember the old size
    if (resize(count) == count) {
        // set the vacancy with the given character.
        if (count > oldCount) memset(_pText + oldCount, fillChar, count - oldCount);
    }

    return _pData->size;
}
//--------------------------------------------------------------------
KtString KtString::right(unsigned int count) const {
    if (0 == count) return KtString();

    if (count >= _pData->size) return *this;

    unsigned int pos    = _pData->size - count;
    KtString     newStr = (const char*)(_pText + pos);
    return newStr;
}
//--------------------------------------------------------------------
void KtString::release() {
    // if not default NULL
    if (_pData != g_KtString_DummyStruct) {
        delete[] (char*)_pData;
        KTSTRING_SET_EMPTY(); // set null
    }
}
//--------------------------------------------------------------------
void KtString::safe_delete(KtStringStruct* ipData) {
    // ASSERT(ipData);
    //  if not default NULL
    if (ipData != g_KtString_DummyStruct) {
        delete[] (char*)ipData;
    }
}
//--------------------------------------------------------------------
void KtString::safe_delete(char* str) { // only used for this string
    if (str != g_KtString_DummyText) {
        delete[] (char*)(((KtStringStruct*)str) - 1);
    }
}
//--------------------------------------------------------------------
KtString& KtString::set_num(double value, unsigned int n /* = 0*/) {
    clear();
    // check 0 for n
    if (0 == n)
        n = 6;
    else if (n > 16)
        n = 16;

    std::ostringstream os;
    bool               scientific = (abs(value) > 1e15);

    if (scientific) {
        // reference to https://www.cnblogs.com/llxblogs/p/7768669.html
        os.setf(std::ios::scientific, std::ios::fixed | std::ios::showpos);
    }

    os.precision(n);
    os << value; // change to string

    return this->append(os.str().c_str(), -1); // append
}
//--------------------------------------------------------------------
KtString& KtString::set_num(int value) {
    clear();              // clear only
    if (reserve(20) < 20) // memory allocation
        return *this;

    snprintf(_pText, 20, "%d", value); // convert to string
    correct();                         // correct size
    return *this;
}
//--------------------------------------------------------------------
KtString& KtString::set_num(unsigned int value) {
    clear();
    if (reserve(20) < 20) // memory allocation
        return *this;

    snprintf(_pText, 20, "%u", value); // convert to string
    correct();                         // correct size
    return *this;
}
//--------------------------------------------------------------------
KtString& KtString::set_num(float value, unsigned int n /* = 0*/) {
    clear();

    // check 0 for n
    if (0 == n)
        n = 6;
    else if (n > 8)
        n = 8;

    std::ostringstream os;
    bool               scientific = (abs(value) > 1e8);

    if (scientific) {
        // reference to https://www.cnblogs.com/llxblogs/p/7768669.html
        os.setf(std::ios::scientific, std::ios::fixed | std::ios::showpos);
    }

    os.precision(n);
    os << value; // change to string

    return this->append(os.str().c_str(), -1); // append
}
//--------------------------------------------------------------------
KtString& KtString::set_num_width(double value, unsigned int minWidth, const char fillChar) {
    return set_num(value).fill_width(minWidth, fillChar);
}
//--------------------------------------------------------------------
KtString& KtString::set_num_width(int value, unsigned int minWidth, const char fillChar) {
    return set_num(value).fill_width(minWidth, fillChar);
}
//--------------------------------------------------------------------
KtString& KtString::shift(int dis, const char fillChar) {
    // dis can be negative, means shift left
    if (0 == dis) return *this;

    const unsigned int newSize = _pData->size + dis;
    if (dis < 0) {
        // shift left
        dis = -dis;
        if ((unsigned int)dis >= _pData->size) return clear();

        // memmove(void *str1, const void *str2, size_t n) from str2 copy n chars to str1
        memmove(_pText,              // position  string
                _pText + dis,        // position + dis string
                _pData->size - dis); // calculate tail chars length ，not include \0
    }
    else // dis > 0
    {
        // shift right
        if (this->reserve(newSize) < newSize) // memory allocation failed
            return *this;

        // memmove(void *str1, const void *str2, size_t n) from str2 copy n chars to str1
        memmove(_pText + dis,  // position + dis string
                _pText,        // head string
                _pData->size); // move size

        memset(_pText, fillChar, dis);
    }

    _pData->size      = newSize;
    _pText[ newSize ] = 0; // end of string
    return *this;
}

//--------------------------------------------------------------------
KtString KtString::sliced(unsigned int pos, unsigned int count) const {
    if (0 == count ||        // empty
        pos >= _pData->size) // out of boundary
        return KtString();   // empty string

    // Come here, means pos< size, size>0

    if (count > _pData->size) count = _pData->size;

    // length exceed tail
    if ((_pData->size - pos) < count) return KtString(_pText + pos);

    // Come here, means not end，(pos + count) < size
    return KtString(_pText + pos, count);
}
//--------------------------------------------------------------------
double KtString::to_double() const {
    return atof(_pText);
}
//--------------------------------------------------------------------
int KtString::to_int() const {
    return atoi(_pText);
}
//--------------------------------------------------------------------
KtString& KtString::to_lower() {
    unsigned int strSize = _pData->size; // size
    char*        pChar   = _pText;       // first char
    // low 65~90,high 97-122
    for (unsigned int i = 0; i < strSize; i++, pChar++) {
        if (*pChar >= 65 && *pChar <= 90) *pChar += 32;
    } // for i
    return *this;
}
//--------------------------------------------------------------------
KtString KtString::to_lower_copy() const {
    KtString strValue = *this;
    return strValue.to_lower();
}
//--------------------------------------------------------------------
KtString& KtString::to_upper() {
    unsigned int strSize = _pData->size; // size
    char*        pChar   = _pText;       // first char

    // low 65~90,high 97-122
    for (unsigned int i = 0; i < strSize; i++, pChar++) {
        if (*pChar >= 97 && *pChar <= 122) *pChar -= 32;
    } // for i
    return *this;
}
//--------------------------------------------------------------------
KtString KtString::to_upper_copy() const {
    KtString strValue = *this;
    return strValue.to_upper();
}
//--------------------------------------------------------------------
KtString& KtString::trim() {
    unsigned int strSize = _pData->size; // current length
    if (strSize == 0) return *this;

    // 1. 找到第一个非空白字符的位置
    unsigned int start = 0;
    while (start < strSize && KtIsWhiteChar(_pText[ start ])) {
        ++start;
    }

    // 字符串全是空白
    if (start == strSize) {
        clear();
        return *this;
    }

    // 2. 找到最后一个非空白字符的位置
    unsigned int end = strSize - 1;
    while (end > start && KtIsWhiteChar(_pText[ end ])) {
        --end;
    }

    // 3. 计算新的长度，并把中间有效部分移到字符串开头
    unsigned int newsize = end - start + 1;
    if (start > 0) {
        memmove(_pText, _pText + start, newsize);
    }

    _pText[ newsize ] = '\0';
    _pData->size      = newsize;

    return *this;
}
//--------------------------------------------------------------------
KtString& KtString::trim_left(unsigned int count) {
    if (count >= _pData->size || 0 == count) return *this; // return this

    _pText[ count ] = 0;     // set 0
    _pData->size    = count; // set size
    return *this;
}
//--------------------------------------------------------------------
bool KtString::operator==(const char* str) const {
    return strcmp(_pText, str) == 0;
}
//--------------------------------------------------------------------
bool KtString::operator==(const KtString& str) const {
    return strcmp(_pText, str._pText) == 0;
}
//--------------------------------------------------------------------
bool KtString::operator<(const KtString& str) const {
    return strcmp(_pText, str._pText) < 0;
}
//--------------------------------------------------------------------
char& KtString::operator[](unsigned int position) {
    return _pText[ position ];
}
//--------------------------------------------------------------------
const char& KtString::operator[](unsigned int position) const {
    return _pText[ position ];
}
//--------------------------------------------------------------------
unsigned int KtString::capacity() const {
    return _pData->space;
}
//--------------------------------------------------------------------
const char& KtString::back() const {
    return _pText[ _pData->size - 1 ];
}
//--------------------------------------------------------------------
const char& KtString::front() const {
    return *_pText;
}
//--------------------------------------------------------------------
KtString& KtString::pop(unsigned int count) {
    if (count >= _pData->size) return clear();

    resize(_pData->size - count);
    return *this;
}
//--------------------------------------------------------------------
KtString& KtString::remove(unsigned int position, unsigned int count) {
    return replace(position, count, NULL, 0);
}
//--------------------------------------------------------------------
unsigned int KtString::size() const {
    return _pData->size;
}
//--------------------------------------------------------------------
const char* KtString::str() const {
    return _pText;
}
//--------------------------------------------------------------------
char* KtString::data() {
    return _pText;
}
