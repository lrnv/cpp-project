#include <iostream>
#include <stdlib.h>




//#include "Matrice.h"
#include "MatriceCarree.h"

int main() 
{
    // On fera ici attention a fait que dans TOUTES les manipulations sur les matrices, elles sont indexées de 0 a n-1 et m-1,
    //donc dans les cas ou l'on demande des lignes ou des colones a l'utilisateur ( je pense a un choix de sous-matrice par exemple ),
    //il faudra rectifier cela sinon la sous-matrice affichée sera décalée vers en bas a droite par rapport a ce que demande l'USER.

/*
    //creation d'une 1ere matrice..
    int m,n;
    std::cout << "Vous allez creer une matrice, commencez par renseigner ses dimentions.\n Nombre de lignes ? ";
    std::cin >> m;
    std::cout << " \n Nombre de colones ? ";
    std::cin >> n;
    Matrice mat(m,n,0);
    mat.affecter();
    mat.afficher();
    
   //création d'une 2eme matrice CAREE
    std::cout << "Vous allez creer une matrice caree, commencez par renseigner sa taille : ";
    int m;
    std::cin >> m;
    MatriceCarree mat2(m);
    mat2.affecter();
    mat2.afficher();

/* DIFERENTS TESTS SUCCESFULL
// Création d'une sous-matrice + test de transpose + autres tests
std::cout<<"extraction sous matrice"<<std::endl;
Matrice mat3=mat2.sousMatrice(1,2,1,3);
std::cout<<"fin extract\n";
mat3.afficher();
Matrice mat4=mat3.transpose();
mat4.afficher();



//Test de DP
if ( mat2.positive() ) { std::cout << " Votre matrice est défiinie positive "; }
else { std::cout << " Votre matrice n'est pas définit positive "; }

// test de symetrique :
    if (mat2.symetrique()) { std::cout << "Votre matrice est symetrique"; } else { std::cout << "Votre matrice n'est pas symetrique"; }

// Test de determinant : 
    std::cout << " Le determinant de votre matrice est : " << mat2.det();

// Test des methodes inversible et inverse :    
    if (mat2.inversible()) 
    { 
        std::cout << "votre matrice est inversible, voicit son inverse : \n";
        mat2.inverse().afficher();
    }
    else { std::cout << " Votre matrice n'est pas inversible" ; }


// test du produit de kronecker
    std::cout << "\n Voicit le produit de kronecker de vos matrices :\n";
    mat.kronecker(mat2).afficher();

// Test des opérateurs surchargés externe a la classe
    std::cout << "\n voicit le test d'égalitée de vos deux matrices : \n";
    if (mat==mat2) { std::cout << "Vos deux matrices sont egales"; } else { std::cout << "vos deux matrices ne sont pas egales"; }

    std::cout << " \n voicit le test d'inégalitée de vos deux matrices : \n";
    if ( mat != mat2 ) { std::cout << " Vos deux matrices sont inégales"; } else { std::cout << "vos deux matrices ne sont pas inégales"; }

    std::cout << " \n voicit la somme de votre premiere matrice et de la constante 3\n";
    (mat+3).afficher();

    std::cout << "\n Voicit la somme de vos deux matrices : \n";
    Matrice k=mat+mat2;
    k.afficher();

    std::cout << "\n Vocit votre deuxiemme matrice - 2 \n";
    (mat2-2).afficher();

    std::cout << "\n voicit votre premiere matrice moins la deuxiemme \n";
    (mat-mat2).afficher();

    std::cout << " \n Voicit 3 fois votre première matrice \n";
    (mat*3).afficher();

    std::cout << " \n Voicit le produit standard de vos deux matrice \n";
    (mat*mat2).afficher();

// Tests des surcharges d'opé suivantes interne a la classe
    std::cout << " Ici comence les test de la deuxiemme fournée d'opérateurs";

    std::cout << "\n voicit A+=3 \n";
    (mat+=mat2).afficher();
    
    std::cout << "\n voicit A+=B\n";
    (mat+=mat2).afficher();

    std::cout << "\n voicit A-=3\n";
    (mat-=3).afficher();
    
    std::cout << "\n voicit A-=B\n";
    (mat-=mat2).afficher();

    std::cout << "\n voicit A*=4\n";
    (mat*=4).afficher();
*/

// Codage du menu : 
/*
    LE MENU :
    Dans votre main.cpp, créez un menu permettant à l’utilisateur de créer une ou plusieurs matrices,
et d’effectuer les diverses opérations implémentées lors de ce projet à l’aide d’une boucle do { }
while () et d’un switch. Vous stockerez les matrices dans une collection hétérogène (Matrice
**tab) pouvant contenir indifféremment objets de types Matrice et MatriceCarree, et utiliserez
le mécanisme de résolution dynamique des liens (mot-clef virtual) afin d’appeler les méthodes de
la bonne classe.
*/

// Création du tableau hétérogène. Il faudrat recopier dans matrice.h et matrice.cpp les méthodes utilisé par matricecarree
// et leur faire renvoyer une simple erreur. ( tout cela en virtual )
// De cette manière, on pourra stoquer les matrices carré comme des matrices avec les autres dans un tableau de matrices,
// et leur appliquer les méthodes de matricecarréé sans aucun soucis : Au moment d el'appel de la méthode,
// a condition qu'elle existe en virtual dans matrice, le compilateur appliquera la methode qui va bien. 

int ctrl;
int i;

Matrice **tab=new Matrice*[100]; // création du tableau de matrices
int nombre=0; // le nombre de matrice en mémoire
do {
	
    // Questionement sur quoi faire et on met le choix dans ctrl
    std::cout << " Choisissez quoi faire : \n1 - Afficher les Matrices disponible \n2 - Créé une matrice \n3 - Transposer une matrice \n4 - Calculer le produit de Kronecker de deux matrices \n5 - Extraire une sous-matrice d'une de vos matrices \n6 - Faire des opération élémentaires entre une de vos matrice et un scalaire \n7 - Faire des opération élémentaire entre deux de vos matrices \n8 - Verifier qu'une matrice carrée est inversible, l'inverser. \n9 - Verifier qu'une matrice carree est symetrique \n10 - Verifier qu'une matrice carree est bien définie positive \n11 - Calculer la factorisation de choleky d'une matrice définie positive ( a venir )\n12 - Calculer le determinant d'une matrice carree \n13 - Supprimer une matrice\n\n0 - Quiter le programe\n";
    std::cin>>ctrl;
    switch(ctrl)
    {
        case 1:{ // Afficher les matrices disponibles
            // Une boulce for jusqu'au nombre de matrices en mémoire avec des affichages fera l'affaire. Verifions quand meme qu'il y en a :

            if ( nombre == 0 )
            {
                std::cout<< " Vous n'avez aucunes matrice en mémoire ! Créez-en une avent d'essayer de l'afficher ;)";
            }
            else
            {
                for (int i=0;i<nombre;i++)
                {
                    tab[i]->afficher();
                }
            }
                // Cela devrais suffire pour l'instant. On pourra essayer d'impove l'affichage, en en mettant quelqu'unes cote a cote, maybe ? 
        break; }

        case 2:{ // Créer une matrice

            // Il va ici faloire créé une matrice et ajouter un au compteur du tableau
            int m,n;
            std::cout<<"Vous allez créer une matrice. Veuillez renseigner sa largeur : ";
            std::cin>>m;
            std::cout<<"Sa hauteur : ";
            std::cin>>n;
            
            if ( n != m ) // La matrice n'est donc pas carrée.
            {
                tab[i]=new Matrice(n,m);
            }
            else // La matrice est donc carrée.
            {
                tab[i]=new MatriceCarree(n);
            }
            // Ne laissons pas cette pauvre matrice vide, affectons lui des valeurs :
            tab[i]->affecter();
            nombre++;


        break; }

        case 3:{ // Transposer une matrice

        break; }

        case 4:{ // Calculer le produit de kronecker de deux matrices
        
        break; }

        case 5 :{ // Etraire une sous-matrice d'une de vos matrices

        break; }

        case 6:{ // Faire des opérations ellementaire entre une matrice et un scalaire

        break; }

        case 7:{ // Faire des opérations ellementaires entre deux matrices

        break; }

        case 8:{ // Verifier qu'une matrice carréé est inversible, l'inverser

        break; }

        case 9:{ // Verifier qu'une matrice carree est symetrique

        break; }

        case 10:{ // Verifier qu'une matrice carree symetrique est bien DP

        break; }

        case 11:{ // Calculer la factorisation de cholesky d'une matrice définie positive

        break; }

        case 12:{ // Calculer le determinant d'une matrice carrée.

        break; }
        
        case 13:{ // Supprimer une matrice
        
                    
            // pour supprimer : 
           // delete tab[i];

        break; }

        default :{}
    }


} while ( ctrl !=0 );

    // Liberation de l'espace mémoire du new avent de quitter le programme
    delete tab[0];
    delete [] tab;
    return 0;
}
