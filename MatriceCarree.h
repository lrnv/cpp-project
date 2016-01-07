#ifndef MATRICECARREE_HPP
#define MATRICECARREE_HPP
#include <iostream>
#include <stdlib.h>

#include "Matrice.h"

class MatriceCarree:public Matrice
{
    public:
        
        // Redefinition des constructeurs :
            MatriceCarree(); // constructeur vide
            MatriceCarree( int const & n); // constructeur qui alloue et remplis avec l'identitée
            MatriceCarree( int const & n, double const & x); // constructeur qui remplis de x.
            MatriceCarree( MatriceCarree const& matrice); // constructeur par copie
            MatriceCarree( Matrice const& m); // constructeur qui promeut une matrice en matrice caréé.
            virtual ~MatriceCarree();            

        // Inversibilitée, inversion :
            bool inversible() const;
            MatriceCarree inverse() const;

        // Symetrique, définie-positive ( tests )
            bool symetrique() const;
            bool positive() const;
        
        // Determinant :
            double det() const;
protected:



};
#endif
