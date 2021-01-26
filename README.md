# lem_in
Elementary algorithmic project
>  This project is meant to make you code an ant farm manager.

This is the second algorithms branch project at Hive.

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

Example map

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
**For more detail, see the subject.**

The `./generator` executable is used to generate maps for the evaluation. Use `--help` with it to see it's usage. 
