// -*- c-basic-offset: 4 -*-
/** @file math.h
 *
 *  @brief misc math function & classes used by other parts
 *         of the program
 *
 *  @author Pablo d'Angelo <pablo.dangelo@web.de>
 *
 *  $Id$
 *
 *  This is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this software; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef MY_MATH_H
#define MY_MATH_H

#include <iostream>
#include <vigra/basicimage.hxx>

#ifndef PI
	#define PI 3.14159265358979323846
#endif

#define DEG_TO_RAD( x )		( (x) * 2.0 * PI / 360.0 )
#define RAD_TO_DEG( x )		( (x) * 360.0 / ( 2.0 * PI ) )

/** namespace for various math utils */
namespace utils
{

inline double round(double x);
    
inline double round(double x)
{
    return floor(x+0.5);
}

inline float roundf(float x);

inline float roundf(float x)
{
    return (float) floor(x+0.5f);
}

inline int roundi(double x);

inline int roundi(double x)
{
    return (int) floor(x+0.5);
}

// a simple point class
template <class T>
struct TDiff2D
{
    TDiff2D()
        : x(0), y(0)
        { }
    TDiff2D(T x, T y)
        : x(x), y(y)
        { }
    TDiff2D(const vigra::Diff2D &d)
        : x(d.x), y(d.y)
        { }

    bool operator==(TDiff2D rhs) const
        {
            return x == rhs.x &&  y == rhs.y;
        }

    TDiff2D operator+(TDiff2D rhs) const
        {
            return TDiff2D (x+rhs.x, y+rhs.y);
        }

    TDiff2D operator-(TDiff2D rhs) const
        {
            return TDiff2D (x-rhs.x, y-rhs.y);
        }

    vigra::Diff2D toDiff2D() const
        {
			// windows fix
            return vigra::Diff2D((int)floor(x+0.5f), (int)floor(y+0.5f));
        }

    double x,y;
};



/** clip a point to fit int [min, max]
 *  does not do a mathematical clipping, just sets p.x and p.y
 *  to the borders if they are outside.
 */
template <class T>
T simpleClipPoint(const T & point, const T & min, const T & max)
{
    T p(point);
    if (p.x < min.x) p.x = min.x;
    if (p.x > max.x) p.x = max.x;
    if (p.y < min.y) p.y = min.y;
    if (p.y > max.y) p.y = max.y;
    return p;
}

/** calculate squared Euclidean distance between two vectors.
 */
template <class InputIterator1, class InputIterator2>
double euclid_dist(InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2)
{
    typename InputIterator1::value_type res = 0;
    InputIterator1 i(first1);
    while (i != last1) {
        double a = *i;
        double b = *(first2 + (i - first1));
        res = res + a*a + b*b;
        ++i;
    }
    return sqrt(res);
}

/** calculate squared Euclidean distance between two vectors.
 */
template <class InputIterator1, class InputIterator2, class T>
T sqr_dist(InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2, T res)
{
    InputIterator1 i(first1);
    while (i != last1) {
        T a = (T)(*i) - (T) (*(first2 + (i - first1)));
        res = res + a*a;
        ++i;
    }
    return res;
}

/** calculate the bounding box of a circle that goes through
 *  both points. the center of the circle is halfway between
 *  the two points
 */
template <class POINT>
vigra::Rect2D calcCircleROIFromPoints(const POINT& p1, const POINT & p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double r = sqrt(dx*dx + dy*dy) / 2.0;
    double mx = p1.x + dx/2;
    double my = p1.y + dy/2;

    vigra::Rect2D rect;
    rect.setUpperLeft(vigra::Point2D(roundi(mx-r), roundi(my -r)));
    rect.setLowerRight(vigra::Point2D(roundi(mx+r), roundi(my+r)));
    return rect;
}



} // namespace

typedef utils::TDiff2D<double> FDiff2D;

template <class T>
inline std::ostream & operator<<(std::ostream & o, const utils::TDiff2D<T> & d)
{
    return o << "( " << d.x << " " << d.y << " )";
}

#endif // MY_MATH_H
