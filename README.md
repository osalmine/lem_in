# lem_in
Elementary algorithmic project
>  This project is meant to make you code an ant farm manager.

This is the second algorithms branch project at Hive. The objective is to create a path-finding algorithm to guide ants from the start room to the end room in as few moves as possible.

Grade:

[![osalmine's Lem_in Score](https://badge42.vercel.app/api/v2/cl2gijtz7003009mofz5pnp5t/project/1886031)](https://github.com/JaeSeoKim/badge42)

**SEE [SUBJECT](lem-in.en.pdf) FOR MORE DETAILS**

## Usage

After cloning the repo and going to it's folder, you can use these make commands:
* To compile:
  * `make`
* To clean .o files:
  * `make clean`
* To clean everything:
  * `make fclean`
* To fclean and compile:
  * `make re`

After compiling, run `./lem-in -h` to see usage.

**Example map:**

```
5
##start
start 1 4
1 0 3
2 0 2
3 0 1
4 2 2
##end
end 1 0
start-4
4-end
start-1
1-2
4-end
2-3
3-end
```

First line is the number of ants (5), ##start is a command meaning that the line after it is the start room, ##end is same for the end room.
A line like `1 0 3` denotes a room named "1" with x and y coordinates of 0 and 3.
A line like `start-1` means that there is a link between room "start" and room "1".
The program accepts comments starting with `#`.

**Output of example map:**

```
L1-4 L2-1
L1-end L2-2 L3-4 L4-1
L2-3 L3-end L4-2 L5-4
L2-end L4-3 L5-end
L4-end
```

The program outputs the input map and the lines above. These lines display the movement of the ants. Each movement starts with the letter `L` after which it displays the ant number that was moved and the room where it moved. Thus `L1-4` means that ant 1 moved to room "4".

The `./generator` executable is used to generate maps for the evaluation. Use `--help` with it to see it's usage.

### Bonuses

* `-p` flag: print the paths that are used.
* `-c` flag: color the ants according to the path it uses.
* `-l` flag: display the amount of turns taken (lines of movement output).
* `-d` flag: display info about the rooms and links.
* `-h` flag: help.

## How it works

My lem-in uses [Edmonds-Karp](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm) algorithm to find different sets of paths of which it selects the most optimal for the amount of ants present. The goal is not to find the shortest path but rather to find the most optimal combination of paths. In fact, the shortest path sometimes blocks more optimal paths. After reading and parsing the information of the map, it goes through the following steps:

1. It traverses the map starting from the start room using [BFS](https://en.wikipedia.org/wiki/Breadth-first_search). Edmonds-Karp adds flows to this. The algorithm can use links with flows that are undefined (all links initialize as undefined) or negative. Links with a flow of 0 or 1 can not be used here.
2. After it finds a path, it assigns the flows of the links in that path. If a path consists of rooms `start, 1, end`, the flow of links start->1 and 1->end are set as 1 if they were undefined. On the contrary, links end->1 and 1->start are set as -1 if they were undefined. If the flow was 1 or -1, it is set as 0.
3. When the flows are set, it tries to find as many paths as it can. At this point it only follows links with a flow of 1. It saves these paths to a set of paths.
4. If the current set is better then the current best set, it assigns the current set as the best set.
5. Repeat until no more paths are found.
6. Assign the paths from the best set to the ants according to the lenght of the paths.

**Evaluation benchmarks:**
* Time complexity: 5/5 (Well done, perfect, the program always runs around 3 seconds or less.)
* Algorithm's accuracy: 4/5 (Optimized algorithm but the result is sometimes one to two lines higher than the generator.) Accuracy was determined from the average of multiple tests. Some maps had a negative difference, some had positive.

Handy script to determine the time and difference:

`./generator --big-superposition | tee gen.map | time ./lem-in -l ; grep "line" gen.map`


Resources:

https://git.42l.fr/amamy/Lem-in

https://www.youtube.com/watch?v=RppuJYwlcI8
