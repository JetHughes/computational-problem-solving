# Changes to main.c


**Renaming** Variables and Methods. The first step of fixing this program was to understand it. After I understood what it was meant to accomplish I renamed all the variables and method names to it is easier to understand.


**Removing Global Variables** Variables like `i`, `j`, and `count` which are used for loops should be defined in a local scope.


**Fixed sort and find function curly braces** Added Curly braces to all the sort and find functions


**Fixed swapping logic** Some of the sort methods had incorrect logic for swapping elements


**Fix nested loops in main** In the main function the for loop to search for records was placed inside the while loop which read the records. This incorrect. The program should first load all the records, then allow the user to search through them


**Fix memory allocation for data fields** When allocating memory for the data fields the amount of memory should be dependent on the size of the data type. Rather than allocating all string fields based on the size of firstName, we should allocate memory using `length_of_string * sizeof(char)`


**Close file before exiting program** This prevents memory leaks


**Change phone number data field to a string not an int** This is better and easier to work with. We also need to remember to allocate memory for it


**Use `fgets()` instead of `gets()`** This is because `gets()` is vulnerable to buffer overflow attacks


**Added prompts for user input** This makes the program much easier to use


**Freeing memory** After the program is finished we need to free the memory occupied by the data. 


**Combine search and find methods** By combining the search methods into one, and the find methods into one the code Is much easier to maintain. Because when we change the sort function we dont have to alter the code in multiple places


**Make search case insensitive** The search methods require very accurate input. To make it easier to search for records I made the search function case insensitive.


**Extract function to read data** There is too much code in the main method. To simplify the code and made it more readable and maintable I extracted the logic for loading the test data to a separate function.

# Reccomendation
Although these changes vastly improve the code, this is not an ideal way to solve the problem at hand. As a senior developer what I would reccomend to a junior developer in this situation is to create a very simple Relational Database. Relational Databases are much better suited for storage and retrieval and are made specifically for this purpose