#include "types.h"

void test_Point2i()
{
 
  Point2i test1(1, 0);
  Point2i test2(0, 1);
  Point2i ans1 = test1 + test2; // x is 1 + 0 = 1 and y is 0 + 1 = 1
  
  Point2i ans2 = 2 * Point2i::UnitX() + 3 * Point2i::UnitY();

  ans1 += ans2;
}


void test_TouchState()
{
  TouchState state = TouchState::None;
  if (true) {
    state = TouchState::Touched;
  }

  switch (state) {
    case TouchState::None:
      //
      break;
    case TouchState::Touched:
      //
      break;
    case TouchState::Touching:
      //
      break;
    default:
      break;
  }
}
