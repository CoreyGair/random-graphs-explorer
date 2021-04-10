# random-graphs-explorer

Calculate graph statistics on different random graph models

Just a small project to learn some C++ multithreading fundamentals and do some research on a fun little area of graph theory

### Building

A working Python3 and NumPy installation is required (uses python & matplotlib hooks for plotting the data)

Clone the repo, then run in the cloned directory:

```
mkdir build
cd build
cmake ..
make
```

The program is then run as `./random-graphs-explorer`

### Usage

`./random-graphs-explorer [generation options] [statistics]`

Generates some graphs according to a model and parameters, then calculates some graph statistics and plots the data to visualise

#### Generation options

`-m, --model [model name] [model parameters]`

Selects the model of random graphs to use, as well as the parameters it takes

There are 3 models implemented:

-   Erdős–Rényi:    `-m erdosrenyi [n] [p]`

    The [Erdős–Rényi model](https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93R%C3%A9nyi_model) produces graphs G(n,p) with n vertices, where each node is connected to every other node with probability p

    This is one of the simplest models for random graphs, although it does not tend to generate many of the characteristics of graphs from real-world data

-   Watts–Strogatz: `-m wattsstrogatz [n] [k] [b]`

    The [Watts–Strogatz model](https://en.wikipedia.org/wiki/Watts%E2%80%93Strogatz_model) produces graphs G(n,k,p) with n vertices which are initially connected in a ring lattice, where each node is connected to the k next nodes

    Then, each of these initial edges are 'rewired' with probability b. If an edge (i,k) is rewired, the edge is removed and replaced with a new edge (i,j') such that j' != j and (i,j') is not already an edge in the graph

    This model was created to generate graphs which exibit the small world phenomenon, where most other vertices can be reached in a small ammount of steps (simmilar to human social networks)

-   Barabási–Albert `-m barabasialbert [n_0] [n] [m]`

    The [Barabási–Albert model](https://en.wikipedia.org/wiki/Barab%C3%A1si%E2%80%93Albert_model) initially produces a fully connected graph of n_0 vertices

    Then, it adds n new vertices which each connect to m other vertices. The probability of connecting to a specific vertex is proportional to the degree of that vertex, so well-connected vertices tend to accumulate more connections

    This model generates scale-free graphs, where the degree distribution follows a power law

`-n, --numgraphs [n]`

Specify how many (n, n>0) graphs should be generated in order to calculate statistics for (in other words, the sample size)

`-s, --seed [s]`

Specify an integer seed to use when generating the graphs. Independant executions with the same model, model parameters, number of graphs and seed will produce the same set of graphs

`-t, --threads [n]`

Specify the number of threads to use when calculating statistics. The program will attempt to evenly split the calculation work over n threads of execution

#### Statistics

`[statistics]` = a list of flags to specify which statistics to calculate over the graphs

-   `-d, --degree`

    Calculate the degree of the vertices. For a vertex v, the degree is the number of edges (i,j) such that v = i or v = j

-   `-D, --diameter`

    Calculate the diameter of the graph, the length of the longest shortest path between 2 vertices

-   `-B, --betweencentrality`

    Calculate vertex betweenness centrality. This is a measure of centrality of the vertices, or how 'important' they are

-   `-c, --components`

    Count the number of connected components in the graph

-   `-C, --clustering`

    Calculate the global clustering coefficient of the graph. This is the ratio of closed vertex triplets to all vertex triplets. A triplet is 3 vertices connected by 2 (open) or 3 (closed) edges

-   `-k, --degeneracy`

    Calculate the degeneracy of the graph, or the smallest k such that the graph is k-degenerate. This means every subgraph has a vertex with degree of at most k, and is a measure of how sparse the graph is

### Results

After the statistic calcuations are complete, a new window will open displaying a plot of the first statistic

To view subsequent statistics, just close the first window and the next one will open
