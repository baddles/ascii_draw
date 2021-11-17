# ascii_draw
This is a program intended to load and view data from a given ascii bits of 0s and 1s.
Originally, it was used to aid for an assignment related to loading these data for Arithmetic Neural Network assignment. However, with an expanded functionality, this can be used for other purposes.

# Usage
./ascii
The above command would load the grid view for editing.
./ascii -l | -r "0, 1, 0, 1, "
The above command would load an old output of the program.
Difference between -l and -r is -r would only load and view the image, and end program, while -l loads and allows editing.

# Input during draw mode
There are 3 different input types: c, t, an integer, a range of integers between 00-99, a matrix of integers by 00x99.
This also supports multiple inputs, seperated by spaces, e.g. "09 10"
Currently the max input and output only support 00-99, but adding support for a-z should be easy but I don't have time.
c would change input direction, for example, by default input mode is horizontal, which means 09 stands for "toggle pixel row 0, column 9 (top right corner)", changing input direction will change mode from "-" to "|" (vertical mode), and now if you input 09, "pixel column 0, row 9 (bottom left corner) will be toggled.
t would toggle input mode. By default the program is in both mode, which works like a lamp switch. Then there is on mode, which means any pixel already toggled on will not turn off when being toggled, and off mode is vice-versa. On/off mode is useful if you want to toggle multiple rows/columns altogether.
When toggling pixels, you can toggle pixel location, e.g. "09 10 11" would toggle all 3 pixels.
"09-19" would toggle pixels from row 0 column 9 to row 1 column 9.
"10x22" would toggle pixels in a rectangle area between 10 and 22.
"-1" would end the program and output the pixels data, which is formatted in vertical by default.

# Compilation
Any c++ compiler would normally works.
g++ ascii.cpp -o ascii
chmod +x ascii
