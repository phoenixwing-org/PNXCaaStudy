/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd.
 * @license     MIT
 * @file        KtListV.h
 * @brief       Simple generic container with vector-like behavior.
 *
 * This header defines a small template class `KtListV<T>` that behaves like a
 * very light-weight wrapper around `std::vector<T>`. It is designed for simple
 * use cases where you need:
 *   - to append elements at the end (similar to `push_back`)
 *   - to get the current number of stored elements
 *   - to access elements by index
 *
 * Only a minimal API is provided on purpose.
 */

#ifndef KtListV_H
#define KtListV_H

// Standard Library
#include <vector>

// core
#include <KtCore/KtListP.h>

// TODO replace vector to KtListP

/**
 * @class KtListV
 * @brief Simple value list container.
 *
 * This template class implements a small container storing elements of type `T`.
 * Internally it uses `std::vector<T>` and exposes only a sub‑set of its
 * functionality:
 *
 * - `Append(const T&)`  : add an element at the end (same idea as `push_back`)
 * - `Size() const`      : get the number of stored elements
 * - `operator[]`        : access element by index (no bounds check)
 * - iterators           : basic forward iteration support
 *
 * Example usage:
 * @code
 *   KtListV<CATUnicodeString> names;
 *   names.Append(CATUnicodeString("Hello"));
 *   names.Append(CATUnicodeString("World"));
 *   int count = names.Size();  // count == 2
 * @endcode
 */
template <typename T> class KtListV {
public:
    /// Type aliases for convenience.
    typedef T                                       value_type;
    typedef typename std::vector<T>::size_type      size_type;
    typedef typename std::vector<T>::iterator       iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

public:
    /**
     * @brief Default constructor.
     *
     * Creates an empty list.
     */
    KtListV() {
    }

    /**
     * @brief Returns the number of elements stored in the list.
     *
     * @return The current size of the list.
     */
    size_type size() const {
        return _data.size();
    }

    /**
     * @brief Removes all elements from the list.
     *
     * After this call, size() will return 0.
     */
    void clear() {
        _data.clear();
    }

    /**
     * @brief Appends an element at the end of the list.
     *
     * This method is conceptually equivalent to `std::vector::push_back`.
     *
     * @param iValue Element to be appended (copied into the container).
     */
    void Append(const T& iValue) {
        _data.push_back(iValue);
    }

    /**
     * @brief Provides read/write access to the element at given index.
     *
     * No bounds checking is performed; the behavior is undefined if
     * `iIndex` is out of range.
     *
     * @param iIndex Index of the element (0-based).
     * @return Reference to the element at position `iIndex`.
     */
    T& operator[](size_type iIndex) {
        return _data[ iIndex ];
    }

    /**
     * @brief Provides read-only access to the element at given index.
     *
     * No bounds checking is performed; the behavior is undefined if
     * `iIndex` is out of range.
     *
     * @param iIndex Index of the element (0-based).
     * @return Const reference to the element at position `iIndex`.
     */
    const T& operator[](size_type iIndex) const {
        return _data[ iIndex ];
    }

    /**
     * @brief Returns an iterator to the first element.
     *
     * @return Iterator to the beginning of the container.
     */
    iterator begin() {
        return _data.begin();
    }

    /**
     * @brief Returns a const iterator to the first element.
     *
     * @return Const iterator to the beginning of the container.
     */
    const_iterator begin() const {
        return _data.begin();
    }

    /**
     * @brief Returns an iterator to the element following the last element.
     *
     * @return Iterator to one past the last element.
     */
    iterator end() {
        return _data.end();
    }

    /**
     * @brief Returns a const iterator to the element following the last element.
     *
     * @return Const iterator to one past the last element.
     */
    const_iterator end() const {
        return _data.end();
    }

private:
    /// Internal storage for elements.
    std::vector<T> _data;
};

#endif // KtListV_H
