#ifndef _FDTDCONSTANTS_H
#define _FDTDCONSTANTS_H

#include <limits>
#include <cmath>
#include <array>
#include <memory>
#include <iostream>

namespace fdtd{


namespace Detail
{
    double constexpr sqrtNewtonRaphson(double x, double curr, double prev)
    {
        return curr == prev
            ? curr
            : sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
    }
}

/*
* Constexpr version of the square root
* Return value:
*   - For a finite and non-negative value of "x", returns an approximation for the square root of "x"
*   - Otherwise, returns NaN
*/
double constexpr sqrt(double x)
{
    return x >= 0 && x < std::numeric_limits<double>::infinity()
        ? Detail::sqrtNewtonRaphson(x, x, 0)
        : std::numeric_limits<double>::quiet_NaN();
}


static constexpr double pi = 3.14159265358979323846264338327950288; 
static constexpr double eps0 = 8.854e-12; /**< permittivity of free space */
static constexpr double mu0 = pi*4.0e-7; /**< permeability of free space */
static constexpr double c0 = 2.99792458e+8;	/**< speed of light in a vacuum */
static constexpr double imp0 = sqrt(mu0/eps0); /**< free space impedance */




struct EMMode{};
struct TE : public EMMode{static const std::size_t dim=2;
                          static const std::size_t numE=2;
                          static const std::size_t numH=1;};
struct TM : public EMMode{static const std::size_t dim=2;
                          static const std::size_t numE=1;
                          static const std::size_t numH=2;};
struct TEM : public EMMode{static const std::size_t dim=1;
                           static const std::size_t numE=1;
                           static const std::size_t numH=1;};
struct ThreeD : public EMMode{static const std::size_t dim=3;
                              static const std::size_t numE=3;
                              static const std::size_t numH=3;};



struct Field{};
struct Ex : public Field{};
struct Ey : public Field{};
struct Ez : public Field{};
struct Dx : public Field{};
struct Dy : public Field{};
struct Dz : public Field{};
struct Hx : public Field{};
struct Hy : public Field{};
struct Hz : public Field{};
struct Bx : public Field{};
struct By : public Field{};
struct Bz : public Field{};



enum class Dir : char{
	X = 1,
	Y,
	Z
};



}// end namespace fdtd

#endif