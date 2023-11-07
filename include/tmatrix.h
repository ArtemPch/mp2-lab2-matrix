// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        if (v.pMem == nullptr) {
            sz = 0;
            pMem = nullptr;
        }
        else {
            sz = v.sz;
            pMem = new T[sz];
            std::copy(v.pMem, v.pMem + sz, pMem);
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = nullptr;
        std::swap(pMem, v.pMem);
    }
    ~TDynamicVector()
    {
        if (pMem != nullptr)
            delete[] pMem;

        pMem = nullptr;
        sz = 0;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return *this;
        if (sz != v.sz)
        {
            if (pMem != nullptr)
                delete[] pMem;
            sz = v.sz;
            pMem = new T[sz];
        }
        std::copy(v.pMem, v.pMem + v.sz, pMem);
        return *this;

    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this == &v)
            return *this;
        if (pMem != nullptr) {
            delete[] pMem;
            pMem = nullptr;
        }

        sz = v.sz;
        std::swap(pMem, v.pMem);

        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind > sz || ind < 0) throw "Error index";
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind > sz || ind < 0) throw "Error index";
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) return false;
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector end(sz);
        for (int i = 0; i < sz; i++) {
            end.pMem[i] = pMem[i] + val;
        }
        return end;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector end(sz);
        for (int i = 0; i < sz; i++) {
            end.pMem[i] = pMem[i] - val;
        }
        return end;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector end(sz);
        for (int i = 0; i < sz; i++) {
            end.pMem[i] = pMem[i] * val;
        }
        return end;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "Error sz";
        TDynamicVector end(sz);
        for (int i = 0; i < sz; i++) {
            end.pMem[i] = pMem[i] + v.pMem[i];
        }
        return end;

    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "Error sz";
        TDynamicVector end(sz);
        for (int i = 0; i < sz; i++) {
            end.pMem[i] = pMem[i] - v.pMem[i];
        }
        return end;
    }
    T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))S
    {
        if (sz != v.sz) throw "Error sz";
        T end = T();
        for (int i = 0; i < sz; i++) {
            end += pMem[i] * v.pMem[i];
        }
        return end;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != m.pMem[i]) return false;
        }
        return true;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix end(sz);
        for (int i = 0; i < n; i++) {
            end.pMem[i] = pMem[i] * val;
        }
        return end;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.sz) throw "Error len";
        TDynamicVector<T> end(sz);
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                end[i] += pMem[i][j] * v[j];
            }
        }
        return end;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw "Error len";
        TDynamicMatrix end(sz);
        for (int i = 0; i < sz; i++) {
            end.pMem[i] = pMem[i] + m.pMem[i];
        }
        return end;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw "Error len";
        TDynamicMatrix end(sz);
        for (int i = 0; i < sz; i++) {
            end.pMem[i] = pMem[i] - m.pMem[i];
        }
        return end;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw "Error len";
        TDynamicMatrix end(sz);
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                for (int k = 0; k < sz; k++) {
                    end[i][j] += pMem[i][k] * m.pMem[k][j];
                }
            }
        }

        return end;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (int i = 0; i < v.sz; i++) {
            istr >> v.pMem[i];
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (int i = 0; i < v.sz; i++) {
            ostr << v.pMem[i] << endl;
        }
        return ostr;
    }
};

#endif