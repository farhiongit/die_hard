# Die Hard With a Vengeance brain teaser

Last weekwas the movie "Die Hard With a Vengeance" was broadcasted on TV.

I won't comment on the movie, but on this scene where Bruce Willis and Samuel Jackson struggle with two empty jugs, with no other indication than there capacity: one jug is 5 gallons large, and the other is 3 gallons.
They can fill the jugs from a fountain of water, empty them to a sink, or pour some water from one jug into the other.
They are asked to fill the 5 gallons jug with excatly 4 gallons of water.

How can they manage to do that ? With as few moves as possible ?
Is it possible to get other volimes, from 1 to 8 gallons of water as well ?
What about jugs with different capacities ?
What if there are more than two jugs ?

The program here answers all theses questions.

## Usage

Pass the volume of each jug as parameter.
There can be more than 2 jugs, some jugs can have the same capacity.

## Example (from the movie)

* Two empty jugs hold 3 gallons and 5 gallons, respectively.
* How to fill one of the jugs with exactly four gallons of water ?

```
$ make die_hard
$ ./die_hard
Usage: ./die_hard volume [volume]...
 $./die_hard 3 5
One shortest path for every possible combination of cans:
{3,0} {5,0} = {8,0} (0 moves).
{3,0} {5,0} -> {3,3} {5,0} = {8,3} (1 moves).
{3,0} {5,0} -> {3,0} {5,5} = {8,5} (1 moves).
{3,0} {5,0} -> {3,3} {5,0} -> {3,0} {5,3} = {8,3} (2 moves).
{3,0} {5,0} -> {3,3} {5,0} -> {3,3} {5,5} = {8,8} (2 moves).
{3,0} {5,0} -> {3,0} {5,5} -> {3,3} {5,2} = {8,5} (2 moves).
{3,0} {5,0} -> {3,3} {5,0} -> {3,0} {5,3} -> {3,3} {5,3} = {8,6} (3 moves).
{3,0} {5,0} -> {3,0} {5,5} -> {3,3} {5,2} -> {3,0} {5,2} = {8,2} (3 moves).
{3,0} {5,0} -> {3,3} {5,0} -> {3,0} {5,3} -> {3,3} {5,3} -> {3,1} {5,5} = {8,6} (4 moves).
{3,0} {5,0} -> {3,0} {5,5} -> {3,3} {5,2} -> {3,0} {5,2} -> {3,2} {5,0} = {8,2} (4 moves).
{3,0} {5,0} -> {3,3} {5,0} -> {3,0} {5,3} -> {3,3} {5,3} -> {3,1} {5,5} -> {3,1} {5,0} = {8,1} (5 moves).
{3,0} {5,0} -> {3,0} {5,5} -> {3,3} {5,2} -> {3,0} {5,2} -> {3,2} {5,0} -> {3,2} {5,5} = {8,7} (5 moves).
{3,0} {5,0} -> {3,3} {5,0} -> {3,0} {5,3} -> {3,3} {5,3} -> {3,1} {5,5} -> {3,1} {5,0} -> {3,0} {5,1} = {8,1} (6 moves).
{3,0} {5,0} -> {3,0} {5,5} -> {3,3} {5,2} -> {3,0} {5,2} -> {3,2} {5,0} -> {3,2} {5,5} -> {3,3} {5,4} = {8,7} (6 moves).
{3,0} {5,0} -> {3,3} {5,0} -> {3,0} {5,3} -> {3,3} {5,3} -> {3,1} {5,5} -> {3,1} {5,0} -> {3,0} {5,1} -> {3,3} {5,1} = {8,4} (7 moves).
{3,0} {5,0} -> {3,0} {5,5} -> {3,3} {5,2} -> {3,0} {5,2} -> {3,2} {5,0} -> {3,2} {5,5} -> {3,3} {5,4} -> {3,0} {5,4} = {8,4} (7 moves).
0 is reachable in 0 moves ; 1 is reachable in 4 moves ; 2 is reachable in 2 moves ; 3 is reachable in 1 moves ; 4 is reachable in 6 moves ; 5 is reachable in 1 moves ; 6 is reachable in 3 moves ; 7 is reachable in 5 moves ; 8 is reachable in 2 moves ; 
k
```

* Answer: 4 is reachable in 6 moves : {3,0} {5,0} -> {3,0} {5,5} -> {3,3} {5,2} -> {3,0} {5,2} -> {3,2} {5,0} -> {3,2} {5,5} -> {3,3} **{5,4}** = {8,7} (6 moves).
