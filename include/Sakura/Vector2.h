/**
 * @file Vector2.h
 * Defines a 2 dimensional vector class.
 */

#ifndef SAKURA_VECTOR2_H_INCLUDED
#define SAKURA_VECTOR2_H_INCLUDED
#include <math.h>

/**
  * @namespace Sakura
  */
namespace Sakura
{

/**
 * @tparam T The type to hold.
 * @brief A 2d vector for math.
 * Defines a generic 2d vector class with two components.
 * Contains some math functions for it to help.
 */

template <class T>
class Vector2
{
public:
/**
 * Constructs itself from x and y components.
 * @param x1 The x component of the new vector.
 * @param y1 The y component of the new vector.
 */
    template <class R>
    Vector2(R x1=0, R y1=0);

/**
 * @fn Vector2()
 * Default constructor, sets to zero.
 */
    Vector2();

/**
 * @param in The Vector to copy.
 * @tparam R The type of the other vector
 * Constructs itself from another Vector2.
 */
    template <class R>
    Vector2(const Vector2<R>& in);

/**
 * @tparam R The type of the other vector.
 * @param in The vector to copy.
 * Copies the components from another Vector2.
 * @return A reference to the constructed vector (this)
 **/
    template <class R>
    Vector2<T>& operator=(const Vector2<R>& in);

/**
 * @tparam R the type of the other vector.
 * @param in The Vector to multiply by.
 * Multiplies the vector componentwise
 * @return The result from the multiplication.
 */
    template <class R>
    Vector2<T> operator*(const Vector2<R>& in) const;


/**
 * @tparam R The type of the other vector.
 * @param in The Vector to add by.
 * Adds two vectors together.
 * \return The result from the addition.
 */
    template <class R>
    Vector2<T> operator+(const Vector2<R>& in) const;


/**
 * @tparam R The type of the other vector.
 * @param in The Vector to divide by.
 * Divides two vectors componentwise.
 * \return The result from the division.
 */
    template <class R>
    Vector2<T> operator/(const Vector2<R>& in) const;


/**
 * @tparam The type of the other vector.
 * @param in The vector to subtract by.
 * Subtracts two vectors.
 * @return The result from the subtraction.
 */
    template <class R>
    Vector2<T> operator-(const Vector2<R>& in) const;


/**
  * @tparam R The type of the scalar.
  * @param in The scalar to multiply by.
  * Multiplies the vector by a scalar.
  * \return The result from the multiplication.
  */
    template <class R>
    Vector2<T> operator*(R in) const;

/**
 * @tparam R The type of the scalar.
 * @param in The scalar to add by.
 * Adds a scalar to each of the vectors components.
 * @return The result from the addition.
 */
    template <class R>
    Vector2<T> operator+(R in) const;


/**
  * @tparam R The type of the scalar.
  * @param in The scalar to divide by.
  * Divides the vector by a scalar.
  * @return The result from the division.
  */
    template <class R>
    Vector2<T> operator/(R in) const;

/**
  * @tparam R The type of the scalar.
  * @param in The component to subtract by.
  * Subtracts a scalar from each of the vectors component.
  * @return The result from the subtraction.
  */
    template <class R>
    Vector2<T> operator-(R in) const;

/**
  * @tparam R The type of the other vector.
  * @param in The vector to compare against
  * Compares this vector against another, checking if their equal.
  * @return Returns true if the components are equal, false otherwise.
  */
    template <class R>
    bool operator ==(const Vector2<R>& in) const;

/**
  * @tparam R The type of the other vector.
  * @param in The component to compare against
  * Compares this vector against another, checking if their not equal.
  * @return Returns true if the components are not equal, false otherwise.
  */
    template <class R>
    bool operator !=(const Vector2<R>& in) const;

/**
  * Normalizes the vector, making its magnitude 1.
  * @return The normalized vector.
  */
    Vector2<T> Normalize(void);

/**
  * Returns the magnitude of the vector.
  * @return The magnitude of the vector
  */
    float Magnitude(void) const;

/**
  * Constructs a perpendicular vector.
  * @return A vector perpendicular to this one.
  */
    Vector2<T> Perp(void) const;

/**
  * @tparam R The type of the vector to dot against.
  * @param other The vector to dot product against.
  * Gets the dot product of two vectors.
  * @return The result of the dot product
  */
    template <class R>
    float Dot(const Vector2<R>& other) const;
/**
  * @tparam R The type of the vector to cross product against.
  * @param in The vector to cross product against
  * @brief Does the cross product between two 2d vectors.
  * In 2D this has very little mathematical meaning.
  * @return The result of the cross product
  */
    template <class R>
    float CrossProduct( const Vector2<R>& in) const;


/**
  * @tparam R The type of the scalar.
  * @param in The scalar to cross by
  * @brief the cross product by the scalar.
  * Used in some 2d calculations.
  * @return The result from the cross.
  */
    template <class R>
    Vector2<T> CrossScalar(R in);

/**
  * @tparam R The type of the vector to compare against.
  * @param in The vector to compare.
  * @brief Checks if the components are less than the others.
  * Used to allow for this class to be used as a key in a map.
  */
    template <class R>
    bool operator<(const Vector2<R>& in) const
    {
        return (x < in.x || (x==in.x && y<in.y));
    }

public:
    T x;/**< component of the vector on the x axis */
    T y;/**< component of the vector on the y axis */
};

template <class T>
Vector2<T>::Vector2()
{
    x=0;
    y=0;
}

template <class T>
template <class R>
Vector2<T>::Vector2(R x1, R y1)
{
    x=x1;
    y=y1;
}

template <class T>
template <class R>
Vector2<T>::Vector2(const Vector2<R>& in)
{
    x=in.x;
    y=in.y;
}

template <class T>
template <class R>
Vector2<T>& Vector2<T>::operator=(const Vector2<R>& in)
{
    x=in.x;
    y=in.y;
    return *this;
}

template <class T>
template <class R>
Vector2<T> Vector2<T>::operator*(const Vector2<R>& in) const
{
    return Vector2<T>(x * in.x, y * in.y);
}

template <class T>
template <class R>
Vector2<T> Vector2<T>::operator+(const Vector2<R>& in) const
{
    return Vector2<T>(x + in.x, y + in.y);
}

template <class T>
template <class R>
Vector2<T> Vector2<T>::operator/(const Vector2<R>& in) const
{
    return Vector2<T>(x/in.x, y/in.y);
}

template <class T>
template <class R>
Vector2<T> Vector2<T>::operator-(const Vector2<R>& in) const
{
    return Vector2<T>(x-in.x, y-in.y);
}

template <class T>
template <class R>
Vector2<T> Vector2<T>::operator*(R in) const
{
    return Vector2<T>(x*in, y*in);
}

template <class T>
template <class R>
Vector2<T> Vector2<T>::operator+(R in) const
{
    return Vector2<T>(x+in, y+in);
}

template <class T>
template <class R>
Vector2<T> Vector2<T>::operator/(R in) const
{
    return Vector2<T>(x/in, y/in);
}

template <class T>
template <class R>
bool Vector2<T>::operator==(const Vector2<R>& in) const
{
    return x==in.x && y == in.y;
}

template <class T>
template <class R>
bool Vector2<T>::operator!=(const Vector2<R>& in) const
{
    return x!=in.x || y!=in.y;
}


template <class T>
Vector2<T> Vector2<T>::Normalize(void)
{
    float Mag=Magnitude();
    if(Mag == 0)
        return Vector2<T>(0,0);
    return *this / Mag;
}

template <class T>
float Vector2<T>::Magnitude(void) const
{
    return sqrt(x * x + y * y);
}

template <class T>
Vector2<T> Vector2<T>::Perp(void) const
{
    return Vector2<T>(-y,x);
}

template <class T>
template <class R>
float Vector2<T>::Dot(const Vector2<R>& in) const
{
    return x * in.x + in.y * y;
}

template <class T>
template <class R>
float Vector2<T>::CrossProduct(const Vector2<R>& in) const
{
    return x * in.y - y * in.x;
}

template <class T>
template <class R>
Vector2<T> Vector2<T>::CrossScalar(R in)
{
    return Vector2<T>(in * y, -in * x);
}

}
#endif // SAKURA_VECTOR2_H_INCLUDED
