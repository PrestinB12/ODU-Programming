#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <cassert>
#include <iostream>

template <typename T>
class Matrix
//
// Provides a "2-dimensional" rectangular
// array-like structure for indexing using
// a pair of indices.
{
public:
  Matrix();

  Matrix(unsigned theLength1, unsigned theLength2);

  template <typename Iterator>
  Matrix(unsigned theLength1, unsigned theLength2, Iterator start, Iterator stop)
      : _length1(theLength1), _length2(theLength2)
  {
    data = new T[theLength1 * theLength2];
    for (unsigned i = 0; i < theLength1; ++i)
      for (unsigned j = 0; j < theLength2; ++j)
      {
        data[i + _length1 * j] = *start;
        ++start;
      }
  }

  Matrix(const Matrix<T> &);

  ~Matrix();

  const Matrix<T> &operator=(const Matrix<T> &);

  // Indexing into the matrix: What we would like to do is allow
  // myMatrix[i,j]. But C++ allows operator[] only to take a single
  // parameter. But operator() can take whatever parameters we like.
  // So we can write myMatrix(i,j).
  T &operator()(int i1, int i2);
  const T &operator()(int i1, int i2) const;

  unsigned length1() const;
  unsigned length2() const;

  bool operator==(const Matrix<T> &) const;

private:
  T *data;
  unsigned _length1;
  unsigned _length2;
};

template <typename T>
Matrix<T>::Matrix()
    : data(0), _length1(0), _length2(0)
{
}

template <typename T>
Matrix<T>::Matrix(unsigned theLength1, unsigned theLength2)
    : _length1(theLength1), _length2(theLength2)
{
  data = new T[theLength1 * theLength2];
}


template <typename T>
Matrix<T>::Matrix(const Matrix<T> &m)
    : _length1(m._length1), _length2(m._length2)
{
  data = new T[_length1 * _length2];
  std::copy(m.data, m.data + _length1 * _length2, data);
}

template <typename T>
Matrix<T>::~Matrix()
{
  delete[] data;
}

template <typename T>
const Matrix<T> &Matrix<T>::operator=(const Matrix<T> &m)
{
  if (this != &m)
  {
    if (_length1 * _length2 < m._length1 * m._length2)
    {
      delete[] data;
      data = new T[m._length1 * m._length2];
    }
    _length1 = m._length1;
    _length2 = m._length2;
    copy(m.data, m.data + _length1 * _length2, data);
  }
  return *this;
}

// Indexing into the matrix: What we would like to do is allow
// myMatrix[i,j]. But C++ allows operator[] only to take a single
// parameter. But operator() can take whatever parameters we like.
// So we can write myMatrix(i,j).
template <typename T>
T &Matrix<T>::operator()(int i1, int i2)
{
  assert((i1 >= 0) && ((unsigned)i1 < _length1));
  assert((i2 >= 0) && ((unsigned)i2 < _length2));
  return data[i1 + _length1 * i2];
}

template <typename T>
const T &Matrix<T>::operator()(int i1, int i2) const
{
  assert((i1 >= 0) && (i1 < (int)_length1));
  assert((i2 >= 0) && (i2 < (int)_length2));
  return data[i1 + _length1 * i2];
}

template <typename T>
inline unsigned Matrix<T>::length1() const
{
  return _length1;
}

template <typename T>
inline unsigned Matrix<T>::length2() const
{
  return _length2;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> &m) const
{
  return (_length1 == m._length1) && (_length2 == m._length2) && std::equal(data, data + _length1 * _length2, m.data);
}


template <typename T>
std::ostream& operator<< (std::ostream& out, const Matrix<T>& m)
{
  for (int i = 0; i < (int)m.length1(); ++i)
  {
    for (int j = 0; j < (int)m.length2(); ++j)
    {
      if (j > 0)
          out << "\t";
      out << m(i,j);
    }
    out << "\n";
  }
  return out;
}

#endif
