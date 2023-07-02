# Installing and running

Bash:
```
cd 03-snowflakes
mkdir build
cd build
cmake ..
make
./snowflakes
```

Note: This solution was devloped using Windows Subsystem for Linux 2 with Ubuntu 20.04.6 LTS. cmake version 3.16. I have also used the OpenCV and OpenGL GLUT packages.

# Usage
Use left and right arrow keys to increase or decrease the order of the displayed snowflake

# Implementation

This is a very simple minimal version of the interactive Koch Snowflake program. I took an object oriented approach to this problem. Each line in the snowflake is a `Segment` object. To create order 0 of the snowflake I can simply create three Segments in the shape of an equilaternal triangle. Then to generate subsequent orders, each Segment has a function to generate its four "children".

**Naming Conventions**
```
            C
            /\
           /  \
          /    \
_________/      \_________
A       L        R        B
```

To generate the children of a segment I use a series of vector operations. 
- The origin is the Vector A. 
- To get L we scale B by ⅟3
- To get R we subtract L from B
- To get C we rotate L by 60⁰ and add L.

We can then create `Segment` object for each of the lines AL, LC, CR and RB. These become the children.

There are some very minimal optimisations already implemented. Firstly, when each order is generated, the segments are saved to an array, so they can be easily displayed later without needing to regenerate the entire snowflake. The second optimisation is very effective. In order to reduce unnessesrary computation, when creating a snowflake we can check whether the length of a segment is greater than the size of a pixel. If the segments are too small to be visible we do not neeed to compute the next order, and we can simply display the previous snowflake. 

There are some optimisations that could be implemented to improve the efficiency of this solution. Firstly, instead of starting with four segments and generating each of their children, we could start with just the base of the triangle. To complete the snowflake then, we simply copy the first segment twice and translate and rotate these copies into the positions of the other two sides of the triangle.

Currently, without the pixel/segment size optimisation, this solution can generate up to order 11. It currently uses a large amount of memory to store all previous orders. To ipmrove the application and generate higher orders, I will need to improve the memory usage.