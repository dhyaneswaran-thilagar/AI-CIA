# AI CIA 1 AND 2 

This repository contains implementations of various search algorithms and the Alpha-Beta pruning technique in C++.

## CIA-1: Search Algorithms

The following algorithms are implemented in the CIA-1 file:

1. **British Museum Search**
2. **Depth First Search (DFS)**
3. **Breadth First Search (BFS)**
4. **Hill Climbing**
5. **Beam Search**
6. **Oracle**
7. **Branch and Bound Algorithm**
8. **Branch and Bound+DHP**
9. **Branch and Bound+Estimates**
10. **Best First Search**
11.- **AO* Algorithm**
12. **A* Algorithm**

### Example Graph Structure

The algorithms are demonstrated using the following graph structure:

![graph-i-used](https://github.com/user-attachments/assets/0bae0dcb-e6e5-4150-9f9e-8ced61095ad8)


  graph = {
        {'S', {{'A', 3}, {'B', 5}}},
        {'A', {{'B', 4}, {'D', 3}}},
        {'B', {{'C', 4}}},
        {'C', {{'E', 6}}},
        {'D', {{'G', 5}}},
        {'E', {}},
        {'G', {}}
    };

  heuristics = {
        {'S', 11},
        {'A', 7},
        {'B', 6},
        {'C', 7},
        {'D', 5},
        {'E', 4},
        {'G', 0}
    };
## CIA-2: Alpha Beta Pruning

The CIA-2 file consists of the alpha-beta pruning code in C++. The follwoing example is used to run the code:

![graph-i-used](https://github.com/user-attachments/assets/c84db68c-bdfd-4f39-bcf0-c266ecd2d48c)


