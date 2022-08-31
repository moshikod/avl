# AVL tree library in C++

## AVL - Adelson-Velsky and Landis

level order representation of an AVL tree
```
               ┌───────────────22───────────────┐               
       ┌───────12───────┐              ┌───────28───────┐       
   ┌───8────┐      ┌───19───┐      ┌───25              30───┐   
 ┌─2        9      18      21      24                      31   
 1                                                              
```

### What are the language requirements?
C++ 11

### How to use the AVL tree library?
Start by including `avl.h` and declare a variable of type `AvlTree`.
```c++
#include "avl.h"

AvlTree<int> tree;
// ...do something with tree
```

### How to print an AVL tree content to the standard output?
You may include "avl_tool.h" in your project and use any character stream derived from `std::basic_ostream`, for example:
```c++
#include <iostream>
#include "avl_tool.h"

AvlTree<int> tree;
// ...populate the tree
cout << avl_levelorder << tree;
```

### How to run the demo program?
Compile and run "demo.cpp" to experience the AVL tree behavior using text animation.

Linux
```Shell
make run
```
Linux - using docker
```Shell
make docker
```
Windows - using docker
```Batchfile
docker-run.bat
```

### What if I need an example?
Look at "example.cpp" to learn how to create, populate and display an AVL tree.

Linux
```Shell
make run TARGET=example
```
Linux - using docker
```Shell
make docker TARGET=example
```
Windows - using docker
```Batchfile
docker-run.bat example
```

### What about tests?
Look at "test.cpp" for a basic coverage set of tests.

Linux
```Shell
make run TARGET=test
```
Linux - using docker
```Shell
make docker TARGET=test
```
Windows - using docker
```Batchfile
docker-run.bat test
```

### How to remove the executable product files?

#### Linux
```
make clean
```
#### Windows or Linux using docker
Unneeded since docker automatically cleans up the container and removes the file system when the container exits.

### How to remove the docker images
Linux
```Shell
make docker-clean
```
Windows
```Batchfile
docker-clean.bat
```

Enjoy!
