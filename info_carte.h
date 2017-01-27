#ifndef INFO_CARTE_H
#define INFO_CARTE_H
#include <strings.h>

/////////////////////////////////////////////////////////////
// Structure représentant les informations de chaque carte
/////////////////////////////////////////////////////////////
using namespace std;

typedef struct {
    bool plug = false; std::string mNom;
} DL_IN;

typedef struct {
int mNbr_io = 0, mNbr_i = 0, mNbr_o = 0;
string mNom;} INFO_CARTE;



#endif // INFO_CARTE_H
