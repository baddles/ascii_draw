// HELP I DONT EVEN KNOW WHAT THE HECK DID I WROTE IN THIS PROGRAM BY THIS POINT ANYMORE.
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#define DEBUG 0 // Debug mode, 0 = off, 1 = on, other value would just be equal to 0.
#define GRID_WIDTH 10 // Define grid width (horizontal). This program uses j as width.
#define GRID_LENGTH 10 // Define grid length (vertical). This program uses i as length.

struct matrix { // This matrix struct is just used for get_ij function.
    int length; // i
    int width; // j
}; // get_ij function is to get number of widths and lengths from a given number.
// More explanation is in the function itself.

namespace Color { // This is here for output format, so toggled pixels can be viewed more clearly.
// SOURCE: https://stackoverflow.com/a/17469726 & https://misc.flogisoft.com/bash/tip_colors_and_formatting#colors
    enum Code {
        FG_DEFAULT          = 39,
        FG_BLACK            = 30,
        FG_RED              = 31,
        FG_GREEN            = 32,
        FG_YELLOW           = 33,
        FG_BLUE             = 34,
        FG_MAGENTA          = 35,
        FG_CYAN             = 36,
        FG_LIGHTGRAY        = 37,
        FG_DARKGRAY         = 90,
        FG_LIGHTRED         = 91,
        FG_LIGHTGREEN       = 92,
        FG_LIGHTYELLOW      = 93,
        FG_LIGHTBLUE        = 94,
        FG_LIGHTMAGENTA     = 95,
        FG_LIGHTCYAN        = 96,
        FG_WHITE            = 97,
        BG_DEFAULT          = 49,
        BG_BLACK            = 40,
        BG_RED              = 41,
        BG_GREEN            = 42,
        BG_YELLOW           = 43,
        BG_BLUE             = 44,
        BG_MAGENTA          = 45,
        BG_CYAN             = 46,
        BG_LIGHTGRAY        = 47,
        BG_DARKGRAY         = 100,
        BG_LIGHTRED         = 101,
        BG_LIGHTGREEN       = 102,
        BG_LIGHTYELLOW      = 103,
        BG_LIGHTBLUE        = 104,
        BG_LIGHTMAGENTA     = 105,
        BG_LIGHTCYAN        = 106,
        BG_WHITE            = 107,
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
} // The use of this namespace is in grid().
void output(int[GRID_LENGTH][GRID_WIDTH]);
std::string process(int[GRID_LENGTH][GRID_WIDTH], std::string);
void grid(int[GRID_LENGTH][GRID_WIDTH]);
matrix get_ij(int);
char mode = '-'; // To change input direction.
char toggle = 'b'; // Hard to explain.
int main(int argc, const char* argv[])
{
    int a[GRID_LENGTH][GRID_WIDTH];
    for (int i = 0; i < GRID_LENGTH; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            a[i][j] = 0; // Init.
    if (argc > 1) {
        if (argc != 3)
            std::cout<<"Invalid argument!\nUsage: ./ascii -r \"DATA string\"";
        else {
            std::string intepret = argv[2];
            if (DEBUG == 1)
                std::cout<<intepret;
            int i = 0, j = 0;
            for (int si = 0; si < intepret.size(); si++) {
                if (intepret[si] == ',') {
                    j++;
                    if (j == GRID_WIDTH) {
                        i++;
                        j = 0;
                    }
                }
                else if (intepret[si] != ' ')
                    a[i][j] = intepret[si] - '0';
            }
            grid(a);
        }
        std::string mode = argv[1];
        if (mode[1] == 'r' || mode[1] == 'R')
            return 0;
    }
    std::string input = "100";
    while (input[0] != '-') {
        output(a);
        std::cout<<"Input number [00-99] to change data,\nc to change input mode, t to change input type\nor -1 to print data & end program: ";
        std::getline(std::cin, input);
        input = process(a, input);
    }
    for (int i = 0; i < GRID_LENGTH; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            std::cout<<a[i][j]<<", ";
    return 0;
}

std::string process (int a[GRID_LENGTH][GRID_WIDTH], std::string s) {
    s += " ";
    std::vector<int> v;
    std::string tmp = "", tmp1 = "";
    std::string r = "+";
    if (s[0] == 'c' || s[0] == 'C') {
        (mode == '-') ? mode = '|' : mode = '-';
    }
    else if (s[0] == 't' || s[0] == 'T') {
        if (toggle == '1')
            toggle = '0';
        else if (toggle == '0')
            toggle = 'b';
        else
            toggle = '1';
    }
    else {
        bool x = false;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '-' && i - 1 != -1 && s[i-1] != ' ') {
                tmp1 = tmp;
                tmp = "";
            }
            else if (s[i] == 'x') {
                tmp1 = tmp;
                tmp = "";
                x = true;
            }
            else if (s[i] == ' ') {
                try {
                    if (tmp1.size() != 0) {
                        if (x == true) {
                            // 23x46
                            matrix a = get_ij(std::stoi(tmp1));
                            matrix b = get_ij(std::stoi(tmp));
                            int i0 = a.length, j0 = a.width, i1 = b.length, j1 = b.width;
                            for (int i = i0; i <= i1; i++) {
                                for (int j = j0; j <= j1; j++) {
                                    int push_back = i * 10 + j;
                                    v.push_back(push_back);
                                }
                            }
                            v.push_back(std::stoi(tmp)); // to push the last value because this is dumb.
                        }
                        else {
                            for (int i = std::stoi(tmp1); i < std::stoi(tmp); i++) {
                                v.push_back(i);
                            }
                        }
                    }
                    v.push_back(std::stoi(tmp));
                    tmp = "";
                    tmp1 = "";
                    x = false;
                }
                catch (std::exception &err) {
                    std::cout<<"Invalid argument!";
                    return r;
                }
            }
            else tmp += s[i];
        }
        for (int i = 0; i < v.size(); i++) {
            int input = v[i];
            if (input == -1)
                r = "-";
            else if (input < 100 && r[0] != '-') {
                matrix m = get_ij(input);
                int i = m.length, j = m.width;
                if (mode == '|') {
                    int tmp = i;
                    i = j;
                    j = tmp;
                }
                if (DEBUG == 1)
                    std::cout<<"DEBUG: i = "<<i<<" j = "<<j<<std::endl;
                if (toggle == '0')
                    a[i][j] = 0;
                else if (toggle == '1')
                    a[i][j] = 1;
                else 
                    (a[i][j] == 0) ? a[i][j] = 1 : a[i][j] = 0;
            }
        }
    }
    return r;
}

matrix get_ij(int input) {
    int n = input;
    matrix m;
    int j = n % 10, i = 0;
    n /= 10;
    if (n != 0)
        i = n % 10;
    m.length = i;
    m.width = j;
    return m;
}
void output(int a[GRID_LENGTH][GRID_WIDTH]) {
    std::cout<<"\n\n\n\n\n\n\n\n\n\ntoggle: ";
    if (toggle == '0')
        std::cout<<"off"<<std::endl;
    else if (toggle == '1')
        std::cout<<"on"<<std::endl;
    else std::cout<<"both"<<std::endl;
    std::cout<<"Current data: "<<mode<<std::endl;
    grid(a);
}

void grid(int a[GRID_LENGTH][GRID_WIDTH]) {
    Color::Modifier red(Color::FG_LIGHTCYAN);
    Color::Modifier def(Color::FG_DEFAULT);
    std::cout<<def<<"  ";
    for (int j = 0; j < GRID_WIDTH; j++) {
        std::cout<<j<<" ";
    }
    std::cout<<std::endl;
    for (int i = 0; i < GRID_LENGTH; i++) {
        std::cout<<i<<" ";
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (a[i][j] == 0)
                std::cout<<def<<"- ";
            else std::cout<<red<<"* ";
        }
        std::cout<<def<<std::endl;
    }
}