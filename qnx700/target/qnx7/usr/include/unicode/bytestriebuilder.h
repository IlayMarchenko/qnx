// Copyright (C) 2016 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html
/*
*******************************************************************************
*   Copyright (C) 2010-2016, International Business Machines
*   Corporation and others.  All Rights Reserved.
*******************************************************************************
*   file name:  bytestriebuilder.h
*   encoding:   US-ASCII
*   tab size:   8 (not used)
*   indentation:4
*
*   created on: 2010sep25
*   created by: Markus W. Scherer
*/

/**
 * \file
 * \brief C++ API: Builder for icu::BytesTrie
 */

#ifndef __BYTESTRIEBUILDER_H__
#define __BYTESTRIEBUILDER_H__

#include "unicode/utypes.h"
#include "unicode/bytestrie.h"
#include "unicode/stringpiece.h"
#include "unicode/stringtriebuilder.h"

U_NAMESPACE_BEGIN

class BytesTrieElement;
class CharString;
/**
 * Builder class for BytesTrie.
 *
 * This class is not intended for public subclassing.
 * @stable ICU 4.8
 */
class U_COMMON_API BytesTrieBuilder : public StringTrieBuilder {
public:
    /**
     * Constructs an empty builder.
     * @param errorCode Standard ICU error code.
     * @stable ICU 4.8
     */
    BytesTrieBuilder(UErrorCode &errorCode);

    /**
     * Destructor.
     * @stable ICU 4.8
     */
    virtual ~BytesTrieBuilder();

    /**
     * Adds a (byte sequence, value) pair.
     * The byte sequence must be unique.
     * The bytes will be copied; the builder does not keep
     * a reference to the input StringPiece or its data().
     * @param s The input byte sequence.
     * @param value The value associated with this byte sequence.
     * @param errorCode Standard ICU error code. Its input value must
     *                  pass the U_SUCCESS() test, or else the function returns
     *                  immediately. Check for U_FAILURE() on output or use with
     *                  function chaining. (See User Guide for details.)
     * @return *this
     * @stable ICU 4.8
     */
    BytesTrieBuilder &add(StringPiece s, int32_t value, UErrorCode &errorCode);

    /**
     * Builds a BytesTrie for the add()ed data.
     * Once built, no further data can be add()ed until clear() is called.
     *
     * A BytesTrie cannot be empty. At least one (byte sequence, value) pair
     * must have been add()ed.
     *
     * This method passes ownership of the builder's internal result array to the new trie object.
     * Another call to any build() variant will re-serialize the trie.
     * After clear() has been called, a new array will be used as well.
     * @param buildOption Build option, see UStringTrieBuildOption.
     * @param errorCode Standard ICU error code. Its input value must
     *                  pass the U_SUCCESS() test, or else the function returns
     *                  immediately. Check for U_FAILURE() on output or use with
     *                  function chaining. (See User Guide for details.)
     * @return A new BytesTrie for the add()ed data.
     * @stable ICU 4.8
     */
    BytesTrie *build(UStringTrieBuildOption buildOption, UErrorCode &errorCode);

    /**
     * Builds a BytesTrie for the add()ed data and byte-serializes it.
     * Once built, no further data can be add()ed until clear() is called.
     *
     * A BytesTrie cannot be empty. At least one (byte sequence, value) pair
     * must have been add()ed.
     *
     * Multiple calls to buildStringPiece() return StringPieces referring to the
     * builder's same byte array, without rebuilding.
     * If buildStringPiece() is called after build(), the trie will be
     * re-serialized into a new array.
     * If build() is called after buildStringPiece(), the trie object will become
     * the owner of the previously returned array.
     * After clear() has been called, a new array will be used as well.
     * @param buildOption Build option, see UStringTrieBuildOption.
     * @param errorCode Standard ICU error code. Its input value must
     *                  pass the U_SUCCESS() test, or else the function returns
     *                  immediately. Check for U_FAILURE() on output or use with
     *                  function chaining. (See User Guide for details.)
     * @return A StringPiece which refers to the byte-serialized BytesTrie for the add()ed data.
     * @stable ICU 4.8
     */
    StringPiece buildStringPiece(UStringTrieBuildOption buildOption, UErrorCode &errorCode);

    /**
     * Removes all (byte sequence, value) pairs.
     * New data can then be add()ed and a new trie can be built.
     * @return *this
     * @stable ICU 4.8
     */
    BytesTrieBuilder &clear();

private:
    BytesTrieBuilder(const BytesTrieBuilder &other);  // no copy constructor
    BytesTrieBuilder &operator=(const BytesTrieBuilder &other);  // no assignment operator

    void buildBytes(UStringTrieBuildOption buildOption, UErrorCode &errorCode);

    virtual int32_t getElementStringLength(int32_t i) const;
    virtual UChar getElementUnit(int32_t i, int32_t byteIndex) const;
    virtual int32_t getElementValue(int32_t i) const;

    virtual int32_t getLimitOfLinearMatch(int32_t first, int32_t last, int32_t byteIndex) const;

    virtual int32_t countElementUnits(int32_t start, int32_t limit, int32_t byteIndex) const;
    virtual int32_t skipElementsBySomeUnits(int32_t i, int32_t byteIndex, int32_t count) const;
    virtual int32_t indexOfElementWithNextUnit(int32_t i, int32_t byteIndex, UChar byte) const;

    virtual UBool matchNodesCanHaveValues() const { return FALSE; }

    virtual int32_t getMaxBranchLinearSubNodeLength() const { return BytesTrie::kMaxBranchLinearSubNodeLength; }
    virtual int32_t getMinLinearMatch() const { return BytesTrie::kMinLinearMatch; }
    virtual int32_t getMaxLinearMatchLength() const { return BytesTrie::kMaxLinearMatchLength; }

    /**
     * @internal
     */
    class BTLinearMatchNode : public LinearMatchNode {
    public:
        BTLinearMatchNode(const char *units, int32_t len, Node *nextNode);
        virtual UBool operator==(const Node &other) const;
        virtual void write(StringTrieBuilder &builder);
    private:
        const char *s;
    };
    
    // don't use #ifndef U_HIDE_INTERNAL_API with private class members or virtual methods.
    virtual Node *createLinearMatchNode(int32_t i, int32_t byteIndex, int32_t length,
                                        Node *nextNode) const;

    UBool ensureCapacity(int32_t length);
    virtual int32_t write(int32_t byte);
    int32_t write(const char *b, int32_t length);
    virtual int32_t writeElementUnits(int32_t i, int32_t byteIndex, int32_t length);
    virtual int32_t writeValueAndFinal(int32_t i, UBool isFinal);
    virtual int32_t writeValueAndType(UBool hasValue, int32_t value, int32_t node);
    virtual int32_t writeDeltaTo(int32_t jumpTarget);

    CharString *strings;  // Pointer not object so we need not #include internal charstr.h.
    BytesTrieElement *elements;
    int32_t elementsCapacity;
    int32_t elementsLength;

    // Byte serialization of the trie.
    // Grows from the back: bytesLength measures from the end of the buffer!
    char *bytes;
    int32_t bytesCapacity;
    int32_t bytesLength;
};

U_NAMESPACE_END

#endif  // __BYTESTRIEBUILDER_H__

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/icu/icu-58.1/source/common/unicode/bytestriebuilder.h $ $Rev: 817488 $")
#endif
