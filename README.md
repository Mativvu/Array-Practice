# Not a project, just learning

## Describtion

Made structures for matrixes, torn arrays and triangle arrays and functions to operate them.

## Details

### Matrixes

Made functions to construct matrixes with dynamic and static arrays, input and print values, sum and multiply two matrixes, transpose a matrix 
and free memory.

### Torn array

> Torn array is an array with different lengths of rows.

Made functions to input and print values, free memory.

#### How it works

At first you need to input number of rows, after that a dynamic array is created to store lengths of rows. Then you input lengths of each row.
I create a dynamic array to store how many bytes each row occupies to next be able to access the right place in memory when putting/printing values.
Just for practice I decided not to allocate all memory for the array in one operation, but to use `realloc()` to allocate more memory each time 
new row is being inputted. 

### Triangle

> Triangle is an one dimensional array to store half of square table of data. For example, if each row and column is a football team number and
in each cell you store a letter to show who won, you need only half of square. So, using one dimensional array you will save half of the memory
you would`ve used for the whole table.

Made functions to create triangle from a table, print values like its a two dimensional array and free memory.

## Source
These were tasks given me on summer school before the start of my first year in MIPT.

## Authors
Egor Matveychuk, (almost) first year MIPT student.
