//17/01/2018


/*
 * ВАЖНО!
 * Для повышения производительности отключены проверки на превышение размера
 * битового поля!
 *
 *
 */
#ifndef SMALL_BITSET_H
#define SMALL_BITSET_H

#include "qglobal.h"
#include "string.h"

/*!
 * \struct bits_t
 * \brief Класс битового поля с compile-time размером и возможностью установки
 * и получения значений его битов.
 */
template<size_t bitsCount>
struct bits_t
{
    constexpr static size_t BYTE = 8u;
    constexpr static size_t BYTES_COUNT = (bitsCount - 1u)/BYTE + 1u;
    quint8 buf[BYTES_COUNT];

    /// Конструктор
    bits_t()
        :buf{}
    {

    }

    /*!
     * \struct bit_ref_t
     * \brief Класс "ссылки" на бит, для возможности прямого присвоения
     */
    struct bit_ref_t
    {
        bits_t<bitsCount>* bits;
        size_t index;

        bit_ref_t(bits_t<bitsCount> *_bits, size_t _index)
        {
            this->bits = _bits;
            this->index = _index;
        }

        void operator=(bool val)
        { bits->setBit(index, val); }

        void operator=(int val)
        { bits->setBit(index, val==1); }

        operator bool() const
        { return bits->getBit(index); }

        inline void set()
        { bits->setBit(index, true); }

        inline void on()
        { bits->setBit(index, true); }

        inline void unset()
        { bits->setBit(index, false); }

        inline void off()
        { bits->setBit(index, false); }
    };


    /// Вернуть размер структуры
    size_t getSize()
    {
        return (sizeof(*this)) * 8u;
    }


    ///
    inline size_t getBitsCount() const
    {
        return bitsCount;
    }


    ///
    inline size_t getBytesCount() const
    {
        return BYTES_COUNT;
    }


    ///
    inline size_t getRealBitsCount() const
    {
        return BYTES_COUNT*BYTE;
    }


    /// Вернуть логическое значение бита
    inline bool getBit(size_t index) const
    {
        return static_cast<bool>(buf[index/BYTE] >> (index % BYTE)&1);
    }


    ///
    inline void operator=(bits_t<bitsCount> other)
    {
        for (size_t i = 0; i < BYTES_COUNT; ++i)
        {
            buf[i] = other.buf[i];
        }
    }


    ///
    inline bool operator ==(bits_t<bitsCount> b)
    {
        for (size_t i = 0, n = BYTES_COUNT; i < n; ++i)
            if (this->buf[i] != b.buf[i])
                return false;
        return true;
    }


    ///
    inline void operator|=(bits_t<bitsCount> b)
    {
        for (size_t i = 0, n = BYTES_COUNT; i < n; ++i)
        {
            buf[i] |= b.buf[i];
        }
    }


    ///
    inline bits_t<bitsCount> operator~()
    {
        bits_t<bitsCount> tmp;
        for (size_t i = 0, n = BYTES_COUNT; i < n; ++i)
        {
            tmp.buf[i] = ~buf[i];
        }
        return tmp;
    }


    ///
    inline bits_t<bitsCount> operator&(bits_t<bitsCount> b)
    {
        bits_t<bitsCount> tmp;
        for (size_t i = 0, n = BYTES_COUNT; i < n; ++i)
        {
            tmp.buf[i] = buf[i] & b.buf[i];
        }
        return tmp;
    }


    /// Вернуть класс обёртки бита с возможностью присвоения
    inline bit_ref_t operator [](size_t index)
    {
        return bit_ref_t(this, index);
    }


    /// Вернуть логическое значение бита
    inline bool operator[](size_t index) const
    {
        return static_cast<bool>(buf[index/BYTE] >> (index % BYTE)&1);
    }


    /// Установить логическое значение бита
    inline void setBit(size_t ind, bool bit)
    {
//        buf[ind/BYTE] ^= ((buf[ind/BYTE] >> (ind%BYTE) & 1)^bit) << ind%BYTE;
        auto &byte = buf[ind/BYTE];
        const size_t off = ind%BYTE;
        byte ^= (((byte >> off) & 1)^bit) << off;
    }


    ///
    inline void setBits(std::initializer_list<bool> lst)
    {
        auto it = lst.begin();
        size_t ind = 0;

        while (it != lst.end())
        {
            this->setBit(ind, *it);
            ++it;
            ++ind;
        }
    }


    ///
    inline void setAll()
    {
        memset(buf, 255, BYTES_COUNT);
    }


    ///
    inline void resetAll()
    {
        memset(buf, 0, getSize());
    }


    ///
    inline void resetByte(size_t index)
    {
        buf[index] = 0;
    }


    /// Установить биты из массива указателей
    inline void fromBoolPtrArr(const bool** src, size_t count)
    {
        if (count > getSize())
            return;

        for (size_t i = 0; i < count; ++i)
        {
            setBit(i, *src[i]);
        }
    }
};


template <typename T>
bool getBit(T src, size_t index)
{
    return static_cast<bool>((src >> index)&1);
}


template <typename T>
void setBit(T &dest, size_t index, bool bit)
{
    if (getBit(dest, index) != bit)
        dest ^= (1 << index);
}

#endif //SMALL_BITSET_H
