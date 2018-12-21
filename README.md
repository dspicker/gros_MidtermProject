gros_MidtermProject   
Midterm Project of lecture "Advanced Introduction to C++, scientific computing and machine learning".   
Wintersemester 2018/19

# Description
### 2.20 Pathfinding
Supervisor: [Emanuele Varriale](mailto:varriale@itp.uni-frankfurt.de)   
Pathfinding algorithms have to find the optimal path between two points on a map (1). A map can
be represented as a graph, the easiest way being "discretizing" the map into a grid: cells are nodes that
are connected, for example, with nearest neighbours.
In an unweighted graph one can use a Breadth first search algorithm to explore the graph, enumerate
all possible paths and then find the shortest paths to the targets (2).
The graph can also be weighted, representing, for example, the cost of walking over different terrains.
The Uniform Cost Search algorithm (4) (similar to Dijkstra's algorithm) takes the weights into account
by enumerating all possible paths, but prioritizing the ones with the least cost.
Another possibility is the greedy best first search (3), that has a heuristic measure of distance to the
target and first explore the paths with the least distance. One such heuristic on a square grid can be, for
example, the Manhattan distance `d = |x1 - x2| + |y1 - y2| `. It is faster than the other approaches but it
is not guaranteed to find the optimal solution.
The A* algorithm (5) also prioritizes the search but it combines the calculated distance and the
heuristic distance. With the right heuristic itfinds the optimal solution, but exploring less paths than
Uniform cost algorithm.
Your task is to implement these algorithms, compare the time performance, optimality of solution
on different kind of maps. You should consider maps with normal cells with weight 1, walls, i.e. cells
that cannot be visited, and, "forest" cells with weight 5. Use these elements to create interesting geometries
showing different behaviours of the algorithms. As an implementation detail, `std::queue` and
`std::priority_queue` can be used to store the nodes to visit next.   
(1) [Pathfinding](https://en.wikipedia.org/wiki/Pathfinding)   
(2) [Breadthfirst search](https://en.wikipedia.org/wiki/Breadth-first_search)   
(3) [Greedy best first](https://en.wikipedia.org/wiki/Best-first_search)   
(4) [Uniform cost search](https://algorithmicthoughts.wordpress.com/2012/12/15/artificial-intelligence-uniform-cost-searchucs/)   
(5) [A* algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm)   
