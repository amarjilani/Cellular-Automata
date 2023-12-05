#include <assert.h>
#include <iostream>

#include "CellularAutomata.h"

typedef Cell<int> MyCell;
typedef CA<MyCell> MyCA;

int main() {
  int x, y;

  // walled
  MyCA walled_ca(10, 10, Boundary::walled);

  // Check identifying the boundary
  x = 0;
  y = 0;
  assert(walled_ca.atBoundary(x, y));
  y = 1;
  assert(walled_ca.atBoundary(x, y));
  x = 1;
  assert(!walled_ca.atBoundary(x, y));
  x = 9;
  assert(walled_ca.atBoundary(x, y));
  y = 9;
  assert(walled_ca.atBoundary(x, y));
  x = 10;
  assert(!walled_ca.atBoundary(x, y));
  y = 500;
  assert(!walled_ca.atBoundary(x, y));
  x = -10;
  assert(!walled_ca.atBoundary(x, y));
  y = -10;
  assert(!walled_ca.atBoundary(x, y));

  // Check insideBoundary
  x = 0;
  y = 0;
  assert(walled_ca.insideBoundary(x, y));
  y = 1;
  assert(walled_ca.insideBoundary(x, y));
  x = 1;
  assert(walled_ca.insideBoundary(x, y));
  x = 9;
  assert(walled_ca.insideBoundary(x, y));
  y = 9;
  assert(walled_ca.insideBoundary(x, y));
  x = 10;
  assert(!walled_ca.insideBoundary(x, y));
  y = 500;
  assert(!walled_ca.insideBoundary(x, y));
  x = -10;
  assert(!walled_ca.insideBoundary(x, y));
  y = -10;
  assert(!walled_ca.insideBoundary(x, y));

  // check getRelativeCell
  // set each cell's value to a unique int to
  // check we get the right cell
  for (int x = 0; x < walled_ca.getX(); x++) {
    for (int y = 0; y < walled_ca.getY(); y++) {
      auto c = walled_ca.getCell(x, y);
      c->setNextState((x * 3) + (y * 5));
      c->update();
    }
  }

  x = 0;
  y = 0;

  assert(walled_ca.getRelativeCell(x, y, 0, 0)->getState() == 0);
  assert(walled_ca.getRelativeCell(x, y, 1, 0)->getState() == 3);
  assert(walled_ca.getRelativeCell(x, y, 1, 1)->getState() == 8);
  assert(walled_ca.getRelativeCell(x, y, 5, 5)->getState() ==
         (5 * 3) + (5 * 5));

  assert(walled_ca.getRelativeCell(x, y, 5, 2)->getState() ==
         (5 * 3) + (2 * 5));
  assert(walled_ca.getRelativeCell(x, y, 10, 10) == nullptr);
  assert(walled_ca.getRelativeCell(x, y, -10, 10) == nullptr);
  assert(walled_ca.getRelativeCell(x, y, -10, -10) == nullptr);

  std::cout << "ALL TESTS PASSED" << std::endl;
  return 0;
}
