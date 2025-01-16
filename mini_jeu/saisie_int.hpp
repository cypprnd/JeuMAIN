#include <iostream>
#include <limits>

using namespace std;

#ifndef SAISIE_INT_HPP_INCLUDED
#define SAISIE_INT_HPP_INCLUDED

bool saisirEntier(int &n)
{
    while(!(std::cin >> n))
    {
        if(cin.eof())
        {
            return false;
        }
        else if(cin.fail())
        {
            cout << "Entrée invalide ! Recommencez" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            cout << "Entrée incorrecte ! Recommencez" << endl;
        }
    }
    return true;
}

#endif // MATH_HPP_INCLUDED
