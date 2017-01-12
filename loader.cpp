#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <sstream>
using namespace std ;

long getFileSize(FILE* pFile) // Obtenir la taille d'un fichier ?
{
    long length = 0;

    fseek(pFile,0,SEEK_END);

    length = ftell(pFile);

    // Ne pas oublier de mettre le fichier à son début, sinon on ne peut pas le lire
    fseek(pFile,0,SEEK_SET);

    return length;
}


string float_to_string (float a) //Converti un réel en chaine de caractère
{
    std::ostringstream oss;
    oss << a;
    return oss.str();
}
