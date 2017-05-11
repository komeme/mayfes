#pragma once

#include <Arduino.h>

/*
 * 構造体
 */
struct Point2i {
  // コンストラクタ
  Point2i(int x, int y): x(x), y(y) {}
  
  Point2i& operator=(const Point2i& p) {
    this->x = p.x;
    this->y = p.y;
  }
  
  static Point2i UnitX() {
    return Point2i(1, 0);
  }

   static Point2i UnitY() {
    return Point2i(0, 1);
  }

  Point2i& operator+=(const Point2i& p)
  {
    this->x += p.x;
    this->y += p.y;
    return *this;
  }

  Point2i& operator-=(const Point2i& p)
  {
    this->x -= p.x;
    this->y -= p.y;
    return *this;
  }
  int x;
  int y;
};

/*
 * Point2i a(1, 0);
 * Point2i b(0, 1);
 * Point2i c = a + b; // c.x is 1, c.y is 1
 * みたいなベクトル同士の足し算ができるようになる。
 */
inline Point2i operator+(const Point2i& lhs, const Point2i& rhs)
{
  return Point2i(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Point2i operator*(const Point2i& lhs, int value)
{
  return Point2i(lhs.x * value, lhs.y * value);
}

inline Point2i operator*(int value, const Point2i& rhs)
{
   return Point2i(rhs.x * value, rhs.y * value);
}

inline Point2i operator-(const Point2i& lhs, const Point2i& rhs)
{
  return Point2i(lhs.x - rhs.x, lhs.y - rhs.y);
}

typedef Point2i Vec2i;

/*
 * 列挙型　
 * 　今回はタッチセンサの3つの状態を0,1,2とはせず。
 *   列挙型を使い、TouchState::Touched, TouchState::Touching, TouchState::None
 *   と管理する。
 */
enum TouchState
{
  Touched, // タッチパネルに触れた瞬間である
  Touching, // タッチパネルに触れている状態である
  None // タッチパネルに触れていない状態である。
};


