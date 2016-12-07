#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "vec2.h"
#include "mathutils.h"

namespace muon {
namespace math {

enum RectSide {
    LEFT, RIGHT,
    TOP, BOTTOM,
    NONE
};

enum RelativePos {
    TOUCHING, INSIDE, OUTSIDE, INTERSECTING
};

template<class T>
struct Rectangle
{
    T x,y,w,h;

    Rectangle();
    Rectangle(const T& x, const T& y, const T& w, const T& h);

    inline Vec2<T> getCenter() const { return Vec2<T>(x + w/2, y + h/2); }

    inline T getSide(RectSide side) const {
        switch (side) {
        case LEFT: { return x; }
        case RIGHT: { return x + w; }
        case TOP: { return y; }
        case BOTTOM: { return y + h; }
        default: { return 0; }
        }
    }

    inline T getLeft() const { return getSide(LEFT);}
    inline T getRight() const { return getSide(RIGHT);}
    inline T getTop() const { return getSide(TOP);}
    inline T getBottom() const { return getSide(BOTTOM);}

    inline bool isInside(const Vec2<T>& point) const {
        return
            point.x >= getLeft() && point.y <= getRight() &&
            point.y >= getTop()  && point.y <= getBottom();
    }

    inline bool collides(const Rectangle<T> &other) const {
        return
            getRight() >= other.getLeft() &&
            getLeft() <= other.getRight() &&
            getTop() <= other.getBottom() &&
            getBottom() >= other.getTop();
    }

    inline RelativePos relativePos(const Rectangle<T> &other) const {

        if(getLeft() < other.getLeft() &&
           getRight() > other.getRight() &&
           getBottom() > other.getBottom() &&
           getTop() < other.getTop())
            return INSIDE;

        if(getRight() >= other.getLeft() &&
            getLeft() <= other.getRight() &&
            getTop() <= other.getBottom() &&
            getBottom() >= other.getTop() )
        {
            if(getRight() == other.getLeft() ||
                    getLeft() == other.getRight() ||
                    getTop() == other.getBottom() ||
                    getBottom() == other.getTop())
            {
                return TOUCHING;
            }
            return INTERSECTING;
        }else {
            return OUTSIDE;
        }
    }

    RectSide getCollisionSide(const Rectangle<T> &other) const {
        T r, l, t, b;
        r = getRight() - other.getLeft();
        l = other.getRight() - getLeft();
        t = other.getBottom() - getTop();
        b = getBottom() - other.getTop();

        T vals[4] = { ABS(r), ABS(l), ABS(t), ABS(b) };
        T lowest = vals[0];
        for (int i = 0; i < 4; i++) {
            if (vals[i] < lowest) {
                lowest = vals[i];
            }
        }

        return
            lowest == ABS(r) ? RIGHT :
            lowest == ABS(l) ? LEFT :
            lowest == ABS(t) ? TOP :
            lowest == ABS(b) ? BOTTOM :
            NONE;
    }

    inline bool isValid() const { return w > 0 && h > 0; }

};

template<typename T>
inline Rectangle<T>::Rectangle() : x(0), y(0), w(0), h(0) { }

template<typename T>
inline Rectangle<T>::Rectangle(const T& x, const T& y, const T& w, const T& h) : x(x), y(y), w(w), h(h) { }



typedef Rectangle<float> Rectf;
typedef Rectangle<int> Recti;
typedef Rectangle<double> Rectd;

}
}



#endif // RECTANGLE_H
