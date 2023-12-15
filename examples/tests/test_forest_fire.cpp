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

  // testing the getStateCount function 
  for (int i = 0; i < 10; i++) {
    forest.run(1, forestFireUpdate);
    std::cout << "Time step #" << i+1 << ": " << std::endl; 
    std::cout << "# of trees not on fire: " << forest.getStateCount(0) << std::endl;
    std::cout << "# of trees on fire: " << forest.getStateCount(1) << std::endl; 
    std::cout << "# of charred trees: " << forest.getStateCount(2) << std::endl << std::endl; 
  }


  return 0;
}
