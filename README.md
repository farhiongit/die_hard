# Die Hard With a Vengeance brain teaser

The movie "Die Hard With a Vengeance" was broadcasted on TV last week.

I won't comment on the movie, but on this scene where Bruce Willis and Samuel Jackson struggle with two empty jugs, with no other indication than there capacity: one jug is 5 gallons large, and the other is 3 gallons.
They can fill the jugs from a fountain of water, empty them to a sink, or pour some water from one jug into the other.
They are asked to fill the 5 gallons jug with exactly 4 gallons of water.

How can they manage to do that ? With as few moves as possible ?
Is it possible to get other volumes, from 1 to 8 gallons of water as well ?
What about jugs with different capacities ?
What if there are more than two jugs ?

The program here answers all these questions.
It finds the shortest ways to get each of the possible capacities with all the jugs.

## Usage

Pass the volume of each jug as parameter.
There can be more than 2 jugs, some jugs can have the same capacity.

## Example (from the movie)

* Two empty jugs hold 3 gallons and 5 gallons, respectively.
* How to fill one of the jugs with exactly 4 gallons of water ?

```
$ make die_hard
$ ./die_hard
Usage: ./die_hard volume [volume]...
$./die_hard 3 5
The volume 1 is reachable in 4 moves: {0/3} {0/5} =( ~>3)=> {3/3} {0/5} =(~3~>)=> {0/3} {3/5} =( ~>3)=> {3/3} {3/5} =(~2~>)=> {1/3} {5/5} 
The volume 2 is reachable in 2 moves: {0/3} {0/5} =( ~>5)=> {0/3} {5/5} =(~3~>)=> {3/3} {2/5} 
The volume 3 is reachable in 1 moves: {0/3} {0/5} =( ~>3)=> {3/3} {0/5} 
The volume 4 is reachable in 6 moves: {0/3} {0/5} =( ~>5)=> {0/3} {5/5} =(~3~>)=> {3/3} {2/5} =(3~> )=> {0/3} {2/5} =(~2~>)=> {2/3} {0/5} =( ~>5)=> {2/3} {5/5} =(~1~>)=> {3/3} {4/5} 
The volume 5 is reachable in 1 moves: {0/3} {0/5} =( ~>5)=> {0/3} {5/5} 
The volume 6 is reachable in 3 moves: {0/3} {0/5} =( ~>3)=> {3/3} {0/5} =(~3~>)=> {0/3} {3/5} =( ~>3)=> {3/3} {3/5} 
The volume 7 is reachable in 5 moves: {0/3} {0/5} =( ~>5)=> {0/3} {5/5} =(~3~>)=> {3/3} {2/5} =(3~> )=> {0/3} {2/5} =(~2~>)=> {2/3} {0/5} =( ~>5)=> {2/3} {5/5} 
The volume 8 is reachable in 2 moves: {0/3} {0/5} =( ~>3)=> {3/3} {0/5} =( ~>5)=> {3/3} {5/5} 
```

* Answer: The volume 4 is reachable in not less than 6 moves.
