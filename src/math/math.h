#pragma once 

#include <cmath>
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>

#include "qsqrt.h"

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <typename T>
T clip(const T& n, const T& lower, const T& upper);

template<class T>
struct Vec2 {
    T x, y;

    Vec2() : x(T()), y(T()) {}

    Vec2(T _x, T _y) : x(_x), y(_y) {}

    Vec2(const Vec2<T>& v) : x(v.x), y(v.y) {}

    Vec2<T>& operator=(const Vec2<T>& v) {
        x = v.x;
        y = v.y;
        return *this;
    }

    T& operator[](std::size_t i) {
        assert(i < 2);
        if (x == 0) return x; else return y;
    }

    Vec2<T> operator+(const Vec2<T>& V) const { return Vec2<T>{x + V.x, y + V.y}; }

    Vec2<T> operator-(const Vec2<T>& V) const { return Vec2<T>{x - V.x, y - V.y}; }

    Vec2<T> operator*(float f) const { return Vec2<T>{static_cast<T>(x * f), static_cast<T>(y * f)}; }

    friend std::ostream& operator<<(std::ostream& s, Vec2<T>& v) {
        s << "(" << v.x << ", " << v.y << ")\n";
        return s;
    }

    [[nodiscard]] float norm() const { return std::sqrt(x * x + y * y); }

    [[nodiscard]] Vec2<T>& normalize(T l = 1) {
        *this = (*this) * l * Q_rsqrt(x * x + y * y);
        return *this;
    }
};

template<typename T>
Vec2<T> operator*(float f, Vec2<T> vec) { return Vec2<T>{static_cast<T>(vec.x * f), static_cast<T>(vec.y * f)}; }

template<class T>
struct Vec3 {
    T x, y, z;

    Vec3() : x(T()), y(T()), z(T()) {}

    Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

    template<class U>
    Vec3(const Vec3<U>& v);

    Vec3(const Vec3<T>& v) : x(v.x), y(v.y), z(v.z) {}

    Vec3<T>& operator=(const Vec3<T>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    T& operator[](std::size_t i) {
        assert(i < 3);
        if (i == 0) return x; else if (i == 1) return y; else return z;
    }

    Vec3<T> operator^(const Vec3<T>& v) const {
        return Vec3<T>{y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    Vec3<T> operator+(const Vec3<T>& v) const { return Vec3<T>{x + v.x, y + v.y, z + v.z}; }

    Vec3<T> operator-(const Vec3<T>& v) const { return Vec3<T>{x - v.x, y - v.y, z - v.z}; }

    Vec3<T> operator*(float f) const {
        return Vec3<T>{static_cast<T>(x * f), static_cast<T>(y * f), static_cast<T>(z * f)};
    }

    Vec3<T> operator/(float f) const {
        return Vec3<T>{static_cast<T>(x / f), static_cast<T>(y / f), static_cast<T>(z / f)};
    }

    T operator*(const Vec3<T>& v) const { return x * v.x + y * v.y + z * v.z; }

    [[nodiscard]] float norm() const { return std::sqrt(x * x + y * y + z * z); }

    [[nodiscard]] Vec3<T>& normalize(T l = 1) {
        *this = (*this) * l * Q_rsqrt(x * x + y * y + z * z);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& s, Vec3<T>& v) {
        s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
        return s;
    }
};

template<typename T>
Vec3<T> operator*(float f, Vec3<T> vec) {
    return Vec3<T>{static_cast<T>(vec.x * f), static_cast<T>(vec.y * f), static_cast<T>(vec.z * f)};
}

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;
using Vec3f = Vec3<float>;
using Vec3i = Vec3<int>;

template<>
template<>
Vec3<int>::Vec3(const Vec3<float>& v);

template<>
template<>
Vec3<float>::Vec3(const Vec3<int>& v);


///////////////////

const int DEFAULT_SIZE = 4;

class Matrix {

public:
    [[nodiscard]] inline std::size_t nrows() const { return mMatrix.size(); }

    [[nodiscard]] inline std::size_t ncols() const { return mMatrix[0].size(); }

    Matrix operator*(const Matrix& m) const;

    static Matrix eye(std::size_t size);

    Matrix transpose();

    friend std::ostream& operator<<(std::ostream& s, const Matrix& m);

    std::vector<float>& operator[](std::size_t i);

    explicit Matrix(std::size_t row = DEFAULT_SIZE, std::size_t col = DEFAULT_SIZE);

    ~Matrix() = default;

private:
    std::size_t mCols;
    std::size_t mRows;
    std::vector<std::vector<float>> mMatrix;
};

inline Vec2f mat2vec(Matrix m) {
    return Vec2f{ m[0][0]/m[2][0], m[1][0]/m[2][0] };
}

inline Matrix vec2mat(const Vec2f& v) {
    Matrix res{ 3, 1 };
    res[0][0] = v.x;
    res[1][0] = v.y;
    res[2][0] = 1.0f;
    return res;
}

inline Matrix translation(const Vec2f& v) {
    auto res = Matrix::eye(3);
    res[0][2] = v.x;
    res[1][2] = v.y;
    return res; 
}

inline Matrix rotateAround(const Vec2f& p, float angle) {
    auto rot = Matrix::eye(3);
    rot[0][0] = cosf(angle);
    rot[0][1] = -sinf(angle);
    rot[1][0] = sinf(angle);
    rot[1][1] = cosf(angle);

    auto translation0 = Matrix::eye(3);
    translation0[0][2] = -p.x;
    translation0[1][2] = -p.y;

    auto translation1 = Matrix::eye(3);
    translation1[0][2] = p.x;
    translation1[1][2] = p.y;

    return translation1 * rot * translation0; 
}
