#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
ofstream out("out.txt");

// Convert colors from JSON format to CSS... because I am a different kind of lazy. 

int main()
{
    char a[10001], aux[10001];
    cin.getline(a, 10001);

    while (strcmp(a, "exit") != 0)  // type "exit" to stop the program
    {
        // get rid of leading spaces
        while (a[0] == ' ')
        {
            strcpy(aux, a + 1);
            strcpy(a, aux);
        }

        // get rid of the quotation marks and the commas
        for (int i = 0; i < strlen(a); i++)
        {
            if (strchr("\"", a[i]))
            {
                strcpy(aux, a + i + 1);
                strcpy(a + i, aux);
                i--;
            }
            if (strchr(",", a[i]))
            {
                a[i] = '\0';
            }
        }

        // prepend the double dashes needed for CSS
        strcpy(aux, a);
        strcpy(a + 2, aux);
        a[0] = a[1] = '-';

        // don't forget the semicolon 
        out << a << ";\n";

        // read next line 
        cin.getline(a, 10001);
    }
}
