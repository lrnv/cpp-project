#ifndef MATRICE_HPP
#define MATRICE_HPP
#include <iostream>
#include <stdlib.h>
//#define OUTPUT_DEBUG

class Matrice {
	public:
	    // On mettra ici les methodes de la classe
	    
	    
	    // Les accesseurs de la classe
	        int getM() const;
	        int getN() const;
	        void setM(int const& m);
	        void setN(int const& n);
	        double getValue(int const& i, int const& j) const;
	        void setValue(int const& i, int const& j, double const& x);

	    // Constructeurs et destructeur
	        Matrice(); // Constructeur vide
	        Matrice(int const& m, int const& n); // constructeur initialisant la matrice mais pas ses valeurs
	        Matrice(int const& m, int const& n, double const& x); // contructeur initialisant la matrice ainsi que toute ses valeurs a x
	        Matrice(Matrice const&); // constructeur par copie
	        virtual ~Matrice(); // Destructeur

        // autofill
        void Matriceremplie();

        // Methode In/Out : affichage et remplissage;
            void affecter();
            void afficher();

        // Methode pour la sous-matrice, la transposée, et le prduit de kronecker
            Matrice sousMatrice(int const &i, int const &j, int const &k, int const &l) const;
            Matrice transpose() const;
	        Matrice kronecker(Matrice const& B) const;

        // Methode meme-taille, utile pour coder les surcharges d'opérateurs.
            bool memeTaille(Matrice const& A) const;
	
	    // Les opérateur racourcits : leur place est dans la classe car ce sont des méthodes.
            Matrice& operator+=(double const& x);
            Matrice& operator+=(Matrice const& A);
            Matrice& operator-=(double const& x);
            Matrice& operator-=(Matrice const& A);
            Matrice& operator*=(double const& x);

        // methodes utiles pour les calculs d'inversibilitée et d'inversion, qui sont valables pour les matrices non-carrées:
            void echanger_deux_lignes(int const &i,int const &j);
            void multiplier_ligne_par_scal(int const &i, double const& x);
            void soustr_mult_ligne1_a_ligne2(int const& i, int const &j,double const &x);
            
        // methodes non-valables pour les matrices non carée, mais utiles en virtual pour le polymorphisme
            //En effet, si les méthode de la classe matricecarée ne sont pas définie ici en virtual, le tableau deointeurs indférienciés
            // sur des matrices ou des matricecaréé contiendra des matricecarrée n'ayant pas acces a ces méthodes. 
            // En contrepartie, il faudra coder ces méthodes pour la classe matrice, et leur faire renvoyer une erreur.

            // Inversibilitée, inversion :
                virtual bool inversible() const;
                virtual MatriceCaree inverse() const;

            // Symetrique, définie-positive ( tests )
                virtual bool symetrique() const;
                virtual bool positive() const;
        
            // Determinant :
                virtual double det() const;

	protected:
        // On mettra ici les attribus d'un ellement de la classe
     
            int _m; // le nombre de lignes de la matrice
            int _n; // son nombre de colones
            double** contenu;
        



};


// Les surcharges d'opérateurs : ( en dehors de la classe... ) // sont marqué d'un //* ceux qui ont été retapés.
    bool operator==(Matrice const& A, Matrice const& B);
    bool operator!=(Matrice const& A, Matrice const& B);
    Matrice operator+(Matrice const& A, double const& x); //*
    Matrice operator+(Matrice const& A, Matrice const& B); //*
    Matrice operator-(Matrice const& A, double const& x); //*
    Matrice operator-(Matrice const& A, Matrice const& B); //*
    Matrice operator*(Matrice const& A, double const& x); //*
    Matrice operator*(Matrice const& A, Matrice const& B);




// le endif qui va bien pour finir le fichier :
#endif

