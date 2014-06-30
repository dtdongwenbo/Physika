/*
 * @file matrix_4x4.cpp 
 * @brief 4x4 matrix.
 * @author Sheng Yang, Fei Zhu, Liyou Xu
 * 
 * This file is part of Physika, a versatile physics simulation library.
 * Copyright (C) 2013 Physika Group.
 *
 * This Source Code Form is subject to the terms of the GNU General Public License v2.0. 
 * If a copy of the GPL was not distributed with this file, you can obtain one at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 *
 */

#include <limits>
#include <cstdlib>
#include "Physika_Core/Utilities/math_utilities.h"
#include "Physika_Core/Matrices/matrix_3x3.h"
#include "Physika_Core/Matrices/matrix_4x4.h"

namespace Physika{

template <typename Scalar>
SquareMatrix<Scalar,4>::SquareMatrix()
{
}

template <typename Scalar>
SquareMatrix<Scalar,4>::SquareMatrix(Scalar x00, Scalar x01, Scalar x02, Scalar x03, Scalar x10, Scalar x11, Scalar x12, Scalar x13, Scalar x20, Scalar x21, Scalar x22, Scalar x23, Scalar x30, Scalar x31, Scalar x32, Scalar x33)
{
#ifdef PHYSIKA_USE_EIGEN_MATRIX
    eigen_matrix_4x4_(0,0) = x00;
    eigen_matrix_4x4_(0,1) = x01;
    eigen_matrix_4x4_(0,2) = x02;
    eigen_matrix_4x4_(0,3) = x03;
    eigen_matrix_4x4_(1,0) = x10;
    eigen_matrix_4x4_(1,1) = x11;
    eigen_matrix_4x4_(1,2) = x12;
    eigen_matrix_4x4_(1,3) = x13;
    eigen_matrix_4x4_(2,0) = x20;
    eigen_matrix_4x4_(2,1) = x21;
    eigen_matrix_4x4_(2,2) = x22;
    eigen_matrix_4x4_(2,3) = x23;
    eigen_matrix_4x4_(3,0) = x30;
    eigen_matrix_4x4_(3,1) = x31;
    eigen_matrix_4x4_(3,2) = x32;
    eigen_matrix_4x4_(3,3) = x33;
#elif defined(PHYSIKA_USE_BUILT_IN_MATRIX)
    data_[0][0] = x00;
    data_[0][1] = x01;
    data_[0][2] = x02;
    data_[0][3] = x03;
    data_[1][0] = x10;
    data_[1][1] = x11;
    data_[1][2] = x12;
    data_[1][3] = x13;
    data_[2][0] = x20;
    data_[2][1] = x21;
    data_[2][2] = x22;
    data_[2][3] = x23;
    data_[3][0] = x30;
    data_[3][1] = x31;
    data_[3][2] = x32;
    data_[3][3] = x33;
#endif
}

template <typename Scalar>
SquareMatrix<Scalar,4>::SquareMatrix(const Vector<Scalar,4> &row1, const Vector<Scalar,4> &row2, const Vector<Scalar,4> &row3, const Vector<Scalar, 4> &row4)
{
#ifdef PHYSIKA_USE_EIGEN_MATRIX
    for(int col = 0; col < 4; ++col)
    {
        eigen_matrix_4x4_(0,col) = row1[col];
        eigen_matrix_4x4_(1,col) = row2[col];
        eigen_matrix_4x4_(2,col) = row3[col];
        eigen_matrix_4x4_(3,col) = row4[col];
    }
#elif defined(PHYSIKA_USE_BUILT_IN_MATRIX)
    for(int col = 0; col < 4; ++col)
    {
        data_[0][col] = row1[col];
        data_[1][col] = row2[col];
        data_[2][col] = row3[col];
        data_[3][col] = row4[col];
    }
#endif
}

template <typename Scalar>
SquareMatrix<Scalar,4>::SquareMatrix(const SquareMatrix<Scalar,4> &mat4)
{
    *this = mat4;
}

template <typename Scalar>
SquareMatrix<Scalar,4>::~SquareMatrix()
{
}

template <typename Scalar>
Scalar& SquareMatrix<Scalar,4>::operator() (int i, int j)
{
    bool index_valid = (i>=0&&i<4)&&(j>=0&&j<4);
    if(!index_valid)
    {
        std::cerr<<"Matrix index out of range!\n";
        std::exit(EXIT_FAILURE);
    }
#ifdef PHYSIKA_USE_EIGEN_MATRIX
    return eigen_matrix_4x4_(i,j);
#elif defined(PHYSIKA_USE_BUILT_IN_MATRIX)
    return data_[i][j];
#endif
}

template <typename Scalar>
const Scalar& SquareMatrix<Scalar,4>::operator() (int i, int j) const
{
    bool index_valid = (i>=0&&i<4)&&(j>=0&&j<4);
    if(!index_valid)
    {
        std::cerr<<"Matrix index out of range!\n";
        std::exit(EXIT_FAILURE);
    }
#ifdef PHYSIKA_USE_EIGEN_MATRIX
    return eigen_matrix_4x4_(i,j);
#elif defined(PHYSIKA_USE_BUILT_IN_MATRIX)
    return data_[i][j];
#endif
}

template <typename Scalar>
SquareMatrix<Scalar,4> SquareMatrix<Scalar,4>::operator+ (const SquareMatrix<Scalar,4> &mat4) const
{
    Scalar result[16];
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            result[i*4+j] = (*this)(i,j) + mat4(i,j);
    return SquareMatrix<Scalar,4>(result[0], result[1], result[2], result[3] , result[4], result[5], result[6], result[7], result[8], result[9], result[10], result[11], result[12] , result[13], result[14], result[15]);
}

template <typename Scalar>
SquareMatrix<Scalar,4>& SquareMatrix<Scalar,4>::operator+= (const SquareMatrix<Scalar,4> &mat4)
{
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            (*this)(i,j) = (*this)(i,j) + mat4(i,j);
    return *this;
}

template <typename Scalar>
SquareMatrix<Scalar,4> SquareMatrix<Scalar,4>::operator- (const SquareMatrix<Scalar,4> &mat4) const
{
    Scalar result[16];
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            result[i*4+j] = (*this)(i,j) - mat4(i,j);
    return SquareMatrix<Scalar,4>(result[0], result[1], result[2], result[3] , result[4], result[5], result[6], result[7], result[8], result[9], result[10], result[11], result[12] , result[13], result[14], result[15]);
}

template <typename Scalar>
SquareMatrix<Scalar,4>& SquareMatrix<Scalar,4>::operator-= (const SquareMatrix<Scalar,4> &mat4)
{
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            (*this)(i,j) = (*this)(i,j) - mat4(i,j);
    return *this;
}

template <typename Scalar>
SquareMatrix<Scalar,4>& SquareMatrix<Scalar,4>::operator= (const SquareMatrix<Scalar,4> &mat4)
{
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            (*this)(i,j) = mat4(i,j);
    return *this;
}

template <typename Scalar>
bool SquareMatrix<Scalar,4>::operator== (const SquareMatrix<Scalar,4> &mat4) const
{
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            if((*this)(i,j) != mat4(i,j))
                return false;
    return true;
}

template <typename Scalar>
SquareMatrix<Scalar,4> SquareMatrix<Scalar,4>::operator* (Scalar scale) const
{
    Scalar result[16];
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            result[i*4+j] = (*this)(i,j) * scale;
    return SquareMatrix<Scalar,4>(result[0], result[1], result[2], result[3] , result[4], result[5], result[6], result[7], result[8], result[9], result[10], result[11], result[12] , result[13], result[14], result[15]);
}

template <typename Scalar>
SquareMatrix<Scalar,4>& SquareMatrix<Scalar,4>::operator*= (Scalar scale)
{
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            (*this)(i,j) = (*this)(i,j) * scale;
    return *this;
}

template <typename Scalar>
Vector<Scalar,4> SquareMatrix<Scalar,4>::operator* (const Vector<Scalar,4> &vec) const
{
    Vector<Scalar,4> result(0);
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            result[i] += (*this)(i,j)*vec[j];
    return result;
}

template <typename Scalar>
SquareMatrix<Scalar,4> SquareMatrix<Scalar,4>::operator* (const SquareMatrix<Scalar,4> &mat2) const
{
    SquareMatrix<Scalar,4> result(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            for(int k = 0; k < 4; ++k)
                result(i,j) += (*this)(i,k) * mat2(k,j);
    return result;
}

template <typename Scalar>
SquareMatrix<Scalar,4> SquareMatrix<Scalar,4>::operator/ (Scalar scale) const
{
    if(abs(scale)<std::numeric_limits<Scalar>::epsilon())
    {
        std::cerr<<"Matrix Divide by zero error!\n";
        std::exit(EXIT_FAILURE);
    }
    Scalar result[16];
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            result[i*4+j] = (*this)(i,j) / scale;
    return SquareMatrix<Scalar,4>(result[0], result[1], result[2], result[3] , result[4], result[5], result[6], result[7], result[8], result[9], result[10], result[11], result[12] , result[13], result[14], result[15]);
}

template <typename Scalar>
SquareMatrix<Scalar,4>& SquareMatrix<Scalar,4>::operator/= (Scalar scale)
{
    if(abs(scale)<std::numeric_limits<Scalar>::epsilon())
    {
        std::cerr<<"Matrix Divide by zero error!\n";
        std::exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            (*this)(i,j) = (*this)(i,j) / scale;
    return *this;
}

template <typename Scalar>
SquareMatrix<Scalar,4> SquareMatrix<Scalar,4>::transpose() const
{
    Scalar result[16];
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j< 4; ++j)
            result[i*4+j] = (*this)(j,i);
    return SquareMatrix<Scalar,4>(result[0], result[1], result[2], result[3] , result[4], result[5], result[6], result[7], result[8], result[9], result[10], result[11], result[12] , result[13], result[14], result[15]);
}

template <typename Scalar>
SquareMatrix<Scalar,4> SquareMatrix<Scalar,4>::inverse() const
{
#ifdef PHYSIKA_USE_EIGEN_MATRIX
    Eigen::Matrix<Scalar,4,4> result_matrix = eigen_matrix_4x4_.inverse();
    return SquareMatrix<Scalar,4>(result_matrix(0,0), result_matrix(0,1), result_matrix(0,2), result_matrix(0,3), result_matrix(1,0), result_matrix(1,1),result_matrix(1,2), result_matrix(1,3), result_matrix(2,0),result_matrix(2,1), result_matrix(2,2), result_matrix(2,3), result_matrix(3,0), result_matrix(3,1), result_matrix(3,2), result_matrix(3,3));
#elif defined(PHYSIKA_USE_BUILT_IN_MATRIX)
    Scalar det = determinant();
    if(det==0)
    {
        std::cerr<<"Matrix not invertible!\n";
        std::exit(EXIT_FAILURE);
    }    //companion maxtrix
    Scalar x00 = (SquareMatrix<Scalar, 3>(data_[1][1], data_[1][2], data_[1][3], data_[2][1], data_[2][2], data_[2][3], data_[3][1], data_[3][2], data_[3][3])).determinant();
    Scalar x01 = - (SquareMatrix<Scalar, 3>(data_[1][0], data_[1][2], data_[1][3], data_[2][0], data_[2][2], data_[2][3], data_[3][0], data_[3][2], data_[3][3])).determinant();
    Scalar x02 = (SquareMatrix<Scalar, 3>(data_[1][0], data_[1][1], data_[1][3], data_[2][0], data_[2][1], data_[2][3], data_[3][0], data_[3][1], data_[3][3])).determinant();
    Scalar x03 = - (SquareMatrix<Scalar, 3>(data_[1][0], data_[1][1], data_[1][2], data_[2][0], data_[2][1], data_[2][2], data_[3][0], data_[3][1], data_[3][2])).determinant();
    Scalar x10 = - (SquareMatrix<Scalar, 3>(data_[0][1], data_[0][2], data_[0][3], data_[2][1], data_[2][2], data_[2][3], data_[3][1], data_[3][2], data_[3][3])).determinant();
    Scalar x11 = (SquareMatrix<Scalar, 3>(data_[0][0], data_[0][2], data_[0][3], data_[2][0], data_[2][2], data_[2][3], data_[3][0], data_[3][2], data_[3][3])).determinant();
    Scalar x12 = - (SquareMatrix<Scalar, 3>(data_[0][0], data_[0][1], data_[0][3], data_[2][0], data_[2][1], data_[2][3], data_[3][0], data_[3][1], data_[3][3])).determinant();
    Scalar x13 = (SquareMatrix<Scalar, 3>(data_[0][0], data_[0][1], data_[0][2], data_[2][0], data_[2][1], data_[2][2], data_[3][0], data_[3][1], data_[3][2])).determinant();
    Scalar x20 = (SquareMatrix<Scalar, 3>(data_[0][1], data_[0][2], data_[0][3], data_[1][1], data_[1][2], data_[1][3], data_[3][1], data_[3][2], data_[3][3])).determinant();
    Scalar x21 = - (SquareMatrix<Scalar, 3>(data_[0][0], data_[0][2], data_[0][3], data_[1][0], data_[1][2], data_[1][3], data_[3][0], data_[3][2], data_[3][3])).determinant();
    Scalar x22 = (SquareMatrix<Scalar, 3>(data_[0][0], data_[0][1], data_[0][3], data_[1][0], data_[1][1], data_[1][3], data_[3][0], data_[3][1], data_[3][3])).determinant();
    Scalar x23 = - (SquareMatrix<Scalar, 3>(data_[0][0], data_[0][1], data_[0][2], data_[1][0], data_[1][1], data_[1][2], data_[3][0], data_[3][1], data_[3][2])).determinant();
    Scalar x30 = - (SquareMatrix<Scalar, 3>(data_[0][1], data_[0][2], data_[0][3], data_[1][1], data_[1][2], data_[1][3], data_[2][1], data_[2][2], data_[2][3])).determinant();
    Scalar x31 = (SquareMatrix<Scalar, 3>(data_[0][0], data_[0][2], data_[0][3], data_[1][0], data_[1][2], data_[1][3], data_[2][0], data_[2][2], data_[2][3])).determinant();
    Scalar x32 = - (SquareMatrix<Scalar, 3>(data_[0][0], data_[0][1], data_[0][3], data_[1][0], data_[1][1], data_[1][3], data_[2][0], data_[2][1], data_[2][3])).determinant();
    Scalar x33 = (SquareMatrix<Scalar, 3>(data_[0][0], data_[0][1], data_[0][2], data_[1][0], data_[1][1], data_[1][2], data_[2][0], data_[2][1], data_[2][2])).determinant();
    return SquareMatrix<Scalar,4>(x00/det, x10/det, x20/det, x30/det, x01/det, x11/det, x21/det, x31/det, x02/det, x12/det, x22/det, x32/det, x03/det, x13/det, x23/det, x33/det);
#endif 
}

template <typename Scalar>
Scalar SquareMatrix<Scalar,4>::determinant() const
{
#ifdef PHYSIKA_USE_EIGEN_MATRIX
    return eigen_matrix_4x4_.determinant();
#elif defined(PHYSIKA_USE_BUILT_IN_MATRIX)
    /*std::cout<<"Line1:"<<data_[0][0] * (SquareMatrix<Scalar, 3>(data_[1][1], data_[1][2], data_[1][3], data_[2][1], data_[2][2], data_[2][3], data_[3][1], data_[3][2], data_[3][3])).determinant()<<std::endl;
    std::cout<<"Line2:"<<-  data_[0][1] * (SquareMatrix<Scalar, 3>(data_[1][0], data_[1][2], data_[1][3], data_[2][0], data_[2][2], data_[2][3], data_[3][0], data_[3][2], data_[3][3])).determinant()<<std::endl;
    std::cout<<"Line3:"<<data_[0][2] * (SquareMatrix<Scalar, 3>(data_[1][0], data_[1][1], data_[1][3], data_[2][0], data_[2][1], data_[2][3], data_[3][0], data_[3][1], data_[3][3])).determinant()<<std::endl;
    std::cout<<"Line4:"<<-  data_[0][3] * (SquareMatrix<Scalar, 3>(data_[1][0], data_[1][1], data_[1][2], data_[2][0], data_[2][1], data_[2][2], data_[3][0], data_[3][1], data_[3][2])).determinant()<<std::endl;
    return data_[0][0] * (SquareMatrix<Scalar, 3>(data_[1][1], data_[1][2], data_[1][3], data_[2][1], data_[2][2], data_[2][3], data_[3][1], data_[3][2], data_[3][3])).determinant()
        -  data_[0][1] * (SquareMatrix<Scalar, 3>(data_[1][0], data_[1][2], data_[1][3], data_[2][0], data_[2][2], data_[2][3], data_[3][0], data_[3][2], data_[3][3])).determinant()
        +  data_[0][2] * (SquareMatrix<Scalar, 3>(data_[1][0], data_[1][1], data_[1][3], data_[2][0], data_[2][1], data_[2][3], data_[3][0], data_[3][1], data_[3][3])).determinant()
        -  data_[0][3] * (SquareMatrix<Scalar, 3>(data_[1][0], data_[1][1], data_[1][2], data_[2][0], data_[2][1], data_[2][2], data_[3][0], data_[3][1], data_[3][2])).determinant();*/

    return data_[0][0]*data_[1][1]*data_[2][2]*data_[3][3] + data_[0][0]*data_[1][2]*data_[2][3]*data_[3][1] + data_[0][0]*data_[1][3]*data_[2][1]*data_[3][2]
        - (data_[0][0]*data_[1][1]*data_[2][3]*data_[3][2] + data_[0][0]*data_[1][2]*data_[2][1]*data_[3][3] + data_[0][0]*data_[1][3]*data_[2][2]*data_[3][1])
        + data_[0][1]*data_[1][0]*data_[2][3]*data_[3][2] + data_[0][1]*data_[1][2]*data_[2][0]*data_[3][3] + data_[0][1]*data_[1][3]*data_[2][2]*data_[3][0]
        - (data_[0][1]*data_[1][0]*data_[2][2]*data_[3][3] + data_[0][1]*data_[1][2]*data_[2][3]*data_[3][0] + data_[0][1]*data_[1][3]*data_[2][0]*data_[3][2])
        + data_[0][2]*data_[1][0]*data_[2][1]*data_[3][3] + data_[0][2]*data_[1][1]*data_[2][3]*data_[3][0] + data_[0][2]*data_[1][3]*data_[2][0]*data_[3][1]
        - (data_[0][2]*data_[1][0]*data_[2][3]*data_[3][1] + data_[0][2]*data_[1][1]*data_[2][0]*data_[3][3] + data_[0][2]*data_[1][3]*data_[2][1]*data_[3][0])
        + data_[0][3]*data_[1][0]*data_[2][2]*data_[3][1] + data_[0][3]*data_[1][1]*data_[2][0]*data_[3][2] + data_[0][3]*data_[1][2]*data_[2][1]*data_[3][0]
        - (data_[0][3]*data_[1][0]*data_[2][1]*data_[3][2] + data_[0][3]*data_[1][1]*data_[2][2]*data_[3][0] + data_[0][3]*data_[1][2]*data_[2][0]*data_[3][1]);
#endif
}

template <typename Scalar>
Scalar SquareMatrix<Scalar,4>::trace() const
{
    return (*this)(0,0) + (*this)(1,1) + (*this)(2,2) + (*this)(3,3);
}

template <typename Scalar>
SquareMatrix<Scalar,4> SquareMatrix<Scalar,4>::identityMatrix()
{
    return SquareMatrix<Scalar,4>(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

template <typename Scalar>
Scalar SquareMatrix<Scalar,4>::doubleContraction(const SquareMatrix<Scalar,4> &mat2) const
{
    Scalar result = 0;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            result += (*this)(i,j)*mat2(i,j);
    return result;
}

//explicit instantiation of template so that it could be compiled into a lib
template class SquareMatrix<unsigned char,4>;
template class SquareMatrix<unsigned short,4>;
template class SquareMatrix<unsigned int,4>;
template class SquareMatrix<unsigned long,4>;
template class SquareMatrix<unsigned long long,4>;
template class SquareMatrix<signed char,4>;
template class SquareMatrix<short,4>;
template class SquareMatrix<int,4>;
template class SquareMatrix<long,4>;
template class SquareMatrix<long long,4>;
template class SquareMatrix<float,4>;
template class SquareMatrix<double,4>;
template class SquareMatrix<long double,4>;

}  //end of namespace Physika