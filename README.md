# 274b-final
Cellular Automata Software Library

# Library Overview

The CA library is built on two main classes: `Cell` and `CA`. 

The `Cell` class captures the state and logic contained within a cell of the cellular automata grid. A base `Cell` class is provided with the two key components, a `current_state` and `next_state` and update logic. From this, the user can inherit from this base class and extend additional cell functionality. 

The `CA` class handles all the operations of the cellular automata grid. It stores an array of `Cell`s, provides functionality to index, update, print, and find cells within the grid. 

Most importantly, the `CA` class has a `run` method which takes in a function that is used to update the cells in the grid based on specified rules. We have a pre-defined set of rules that can be used, individually or in successsion with eachother, or the user can provide their own custom update logic. 

## Directories

*going to leave this til later in case we decide we want to un-template and move to ints*


## Quickstart

Here we use a simple forest fire example to demonstrate the functionalities and use of the library. Later, we will extend this to a more sophisticated traffic example that we believe truly showcases the power of our library.

In this example we will have a grid of trees, each tree can either be 'normal' (0), 'on fire' (1), or 'charred' (2). A normal tree will stay normal until one of its neighbors is on fire, then it too will catch on fire. If a tree is on fire, then in the next state it will become charred.

First, let's create a `CA` with a grid of 100 rows x 100 columns. `CA(int rows, int cols, Boundary boundary)`. Here, since we only need a single state, we can use the base `Cell` class. We have a choice of what boundary to use. For our forest, we will make it walled, which just means the grid 'ends' at the edges:

```
#include "CellularAutomata.h"

CA<Cell<int>> forest(100, 100, walled);

```

Now we need to specify what the initial state of the trees. There's a few ways we can set these states:

We can manually specify a particular cell at `row`, `col` and explicitly set its next state (then call update to push the change to the current_state).

```
forest.getCell(20, 20)->setNextState(1)
forest.getCell(1, 15)->setNextState(1)
forest.updateAll();
```

Or, we can specify a state to randomly populate based on some probability with the `void CA::randomInit(T state, double prob)` method. You can either specify a state directly, or if you have created your own cell type, you can specify a `setVoidState` and `setDefaultState`, which can perform more complex actions to set up a cell's state. Here, we specify a 20% chance of making each cell on fire.

```
forest.randomInit(1, 0.2);
```

Now, we may want to see the state of the automata at the start. There are a few options. First, you can do a simple print to the console with the `void CA::print()` method.

```
forest.print()
```

> PUT ouTPUT HERE

Or, we can set up more sophisticated io by providing a file path to write to with `void CA::enableCSV(std::string)`. This will write each iteration of the CA to the specified file:

```
forest.enableCSV("test_forest_fire.csv"); 
```

This can be turned off with: 
```
forest.disableCSV();
```

Now to add our rules! Our library uses a passed in update function to allow the user to specify their rules for the model update. We provide a number of common rules that can be put together to form complex models. Each of the pre-defined rules modify a cells `next_state` attribute, only once all rules have been applied do the updates actually apply and mutate the `current_state`. Therefore, you can specify multiple rules back to back and the `CA` will only update after all rules are applied. If you did want to update in-between rules, the user does have the option to manually call `void CA::updateAll()`.

Let's set up our rules for the forest fire. First, we can to specify that any tree that is on fire (1) at time T will be charred (2) at time T+1. We also want to specify that any normal tree whose Moore neighbor is on fire at time T should also be on fire at time T+1. But, we don't want charred trees to turn back on fire. 

```
#include "Rules.h"

void forestFireUpdate(CA<Cell<int>>& forest) {

    // Set on-fire trees to be charred
    conditionalTransitionRule(forest, 1, 2);

    // Now, spread the fire based on Moore neighborhood
    // specify to exclude state 2
    conditionalRuleMoore(forest, 1, 1, {2});
}
```

First, we apply the `void conditionalTransitionRule(CA<Cell<T>>& ca, T start_state, T end_state)` transforms any trees that are on fire to charred. We could alternatively give a map of states as shown below:

```
// Could alternatively set a mapping if there are multiple states to update

std::unordered_map<int, int> state_map;

state_map[0] = 0; // normal trees stay normal
state_map[1] = 2; // on fire trees turn charred
state_map[2] = 2; // charred trees stay charred

conditionalTransitionRule(forest, sate_map);

```

Then, we use the `void conditionalRuleMoore(CA<Cell<T>>& ca, T trigger_state, T end_state, std::vector<T> exclude)` function to specify that any cell whose neighborhood contains a cell with the `trigger_state` (fire), should be set to `end_state` (fire). But, we also don't want any already charred trees to be put back on fire! To prevent this we pass the charred state to the `exclude` argument so that any cell matching a state in the exclude list will not be affected.

Now that we have set up our CA and our update logic, its time to run the model! We use the `CA::run(int iterations, std::function<void(CA<CellType>& ca))>)` method for running:

```
forest.run(10, forestFireUpdate);
```

The program in its entirety is as follows:

```
#include "CellularAutomata.h"
#include "Rules.h"

void forestFireUpdate(CA<Cell<int>>& forest) {

    // Set on-fire trees to be charred
    conditionalTransitionRule(forest, 1, 2);

    // Now, spread the fire based on Moore neighborhood
    // specify to exclude state 2
    conditionalRuleMoore(forest, 1, 1, {2});
}

int main() {

  CA<Cell<int>> forest(100, 100, walled);
  forest.randomInit(1, 0.2);

  forest.enableCSV("test_forest_fire.csv"); 


  forest.run(10, forestFireUpdate);

 return 0;
}

```

Now, to compile the program we must specify the proper include directories for the `CellularAutomata.h`, `Cell.h`, and the libmyrandom library. If this program is located at `examples/tests/test_forest_fire.cpp`, then we would compile with the following:

`g++ -std=c++11 -O3 test_forest_fire.cpp -e ../bin/test_forest_fire -I../../include -I../include -L../../lib -lmyrandom`

Running the program with yields the `test_forest_fire.csv`. Now, we can visualize the results!

** PUT INFORMATION ON VISUALIZATION **


## Brief API reference


## Our Traffic Application






