#include "CellularAutomata.h"
#include "Rules.h"

void forestFireUpdate(CA<Cell<int>>& forest) {
  // Set on-fire trees to be charred
  conditionalTransitionRule(forest, 1, 2);

  // Spread the fire based on Moore neighborhood
  // specify to exclude state 2
  conditionalTransitionRuleMoore(forest, 1, 1, {1, 2});
}

int main() {
  CA<Cell<int>> forest(20, 20, walled);
  forest.randomInit(1, 0.01);

  forest.print();

  forest.enableCSV("test_forest_fire.csv");

  forest.run(10, forestFireUpdate);

  return 0;
}
