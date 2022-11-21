#include <iostream>
#include <string.h>
#define SIZE 10

using namespace std;

int main()
{
     char non_terminal;
     char beta, alpha;
     int num;
     char production[10][SIZE];
     int index = 3;
     cout << "Enter the number of productions : ";
     cin >> num;
     cout << "Enter the grammar as E->E-A|B : \n";
     for (int i = 0; i < num; i++)
     {
          cin >> production[i];
     }
     for (int i = 0; i < num; i++)
     {
          cout << "\nGRAMMAR : : : " << production[i];
          non_terminal = production[i][0];
          if (non_terminal == production[i][index])
          {
               alpha = production[i][index + 1];
               cout << " is left recursive.\n";
               while (production[i][index] != 0 && production[i][index] != '|')
               {
                    index++;
               }
               if (production[i][index] != 0)
               {
                    beta = production[i][index + 1];
                    cout << "Grammar without left recursion:\n";
                    cout << non_terminal << "->" << beta << non_terminal << "\'";
                    cout << "\n"
                         << non_terminal << "\'->" << alpha << non_terminal << "\'|E\n";
               }
               else
               {
                    cout << " can't be reduced\n";
               }
          }
          else
          {
               cout << " is not left recursive.\n";
          }
          index = 3;
     }
     return 0;
}