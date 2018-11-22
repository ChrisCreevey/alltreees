# alltreees
A simple piece of code that generates all possible unrooted trees in tree-space, given a certain number of taxa

This is a simple piece of code that prints all possible unrooted trees in tree space.

This is essentially the code from [Clann](https://github.com/ChrisCreevey/clann) that does this.
 
On Line 11 you can define the size of the trees that you want to generate.
 
To compile the software use the command:  

```
cc alltrees.c -o alltrees -lm”
```

To run, just use the command 

```
./alltrees
```

This will prints all the trees to the screen (the taxa will be numbers from 1 to the total number of taxa specified in Line 11).
 
The core of this code is a function that generates a tree given a number between 1 and the total number of trees in tree-space.

This is how all-tree searches are carreid out in Clann as well as the generation of random trees, basically we just pick a number and then give it to the function “intToTree” and it generates the tree that represents that number in tree space.


More detailed explaination of how this works to come.......
