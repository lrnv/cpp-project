#include "MatriceCarree.h"
#include <cmath> // Pour la racine carrée de cholesky.

// Redefinition des constructeurs :
        MatriceCarree::MatriceCarree(){} // constructeur vide
        
        MatriceCarree::MatriceCarree( int const & n): Matrice(n,n,0) // constructeur qui alloue et remplis avec l'identitée
        {
           for ( int i=0;i<n;i++ ) { for (int j=0;j<n;j++) {
                if ( i==j )
                {
                    setValue(i,j,1); // des 1 sur la diagonale
                }
                else
                {
                    setValue(i,j,0); // et des 0 partout ailleur
                }
           }} // ça fais bien l'identitée ;)
        }
        MatriceCarree::MatriceCarree( int const & n, double const & x): Matrice(n,n,x){} // constructeur qui remplis de x.
        
        // Redefinir le contructeur par copie permetra de faire un masquage interessant.
        MatriceCarree::MatriceCarree( MatriceCarree const& matrice): Matrice(matrice){} // constructeur par copie

        MatriceCarree::MatriceCarree ( Matrice const& m ): Matrice(m) // Constructeur qui promeut une matrice en matricecaré.
        {
            if ( m.getM() != m.getN() )
            {
                std::cout<<"Vous essayez promouvoir en matricecarrée une matrice qui ne l'est manifestement pas ! Petit chenapan ;)";
                exit(EXIT_FAILURE);
            }
        }
        
        MatriceCarree::~MatriceCarree(){} // ici pas besoin de free, le destructeur de Matrice est implicitement apeller.



// Inversibilitée, inversion
        // fonction préalable : la valeur absolue
        double valeurabsolue(double k)
        {
            if ( k>=0 ) { return k; } else { return -k; }
        }

        bool MatriceCarree::inversible() const
        {
            // Cette fonction vérifie que la matrice est bien inversible. 
            // le plus simple est a mon avis d'utiliser l'agorythme de gauss,
            // de ne l'apliquer qu'a la matrice ( et pas a une matrice Id suplementaire )
            // et de tester juste si tout les pivots sont non-nuls. Dans ce cas la la matrice est inversible.


            // l'Opérateur de copie nous transforme une MatriceCarree en Matrice, ce qui n'est pas grave vu qu'elle reste carrée ;)
            Matrice Kikou=Matrice(*this); // la matrice a laquelle on apliquera l'algorythme, la matrice en entrée etant typée const.
            
            // Il a été choisit de coler des -1 a tous les indices lors des accès aux valeurs. On travaille ainsi avec des indice de 1 jusqu'a N, ce qui est plus joli et evite d'initalisé r a -1..
            // quelques variables de passages :
            int r=0;
            int n;
            double scalaire,multiplicatuer;
            n=Kikou.getM(); // = Kikou.getN() car la matrice est carée : pas besoin de se trimbaler 2 variables. 
            for (int j=1;j<=n;j++) // j decris les indices de colones
            {
                // recherche du max des valeur absolue des getValue(i,j) pour r+1 <= i <= n; on notera k l'indice de ligne de ce maximum
                int k=r+1;
                double max=valeurabsolue(Kikou.getValue(r,j-1));
                for (int i=r+1;i<=n;i++)
                {
                    if (valeurabsolue(Kikou.getValue(i-1,j-1))>max)
                    {
                        // on réassigne le max, et on change l'indice k
                        max=valeurabsolue(Kikou.getValue(i-1,j-1));
                        k=i;
                        
                    }
                
                }

                // getValue(k,j) est donc le pivot
                if ( Kikou.getValue(k-1,j-1) != 0 )
                {
                    r=r+1;
                    scalaire=1/Kikou.getValue(k-1,j-1);
                    Kikou.multiplier_ligne_par_scal(k-1,(1/Kikou.getValue(k-1,j-1)));
                    Kikou.echanger_deux_lignes(k-1,r-1);                
                    for ( int i=1;i<=n;i++)
                    {
                        if ( i != r )
                        {
                            multiplicatuer=Kikou.getValue(i-1,j-1);
                            Kikou.soustr_mult_ligne1_a_ligne2(r-1,i-1,multiplicatuer);
                        }
                    }

                }
                else
                {
                    // Si le maximum de la colone est nul, alors toute la colone est nulle ( en valeur aboslue ) et la matrice n'est pas inversible 
                    // nous returnons donc false
                    return false;
                }
            
            }
            // Dans le cas contraire, si l'algorythme de gauss se finit, c'est que la matrice est bien inversible. 
            return true;
        }


		Matrice MatriceCarree::inverse_call() const
		{
			if(inversible())
            {
                return this->inverse();
		    }
            else
            {
                std::cout<<"Votre matrice carrée n'est pas inversible, désolé !";
                

            }
        } // Cette fonction supplementaire a été mise a place quand je me suis apercut de 'limpossibilitée de passer en polymorphisme la fonction inverse : 
        // Comme la fonction inverse renvoit une matricecarrée, il est impossbile de la définir dans la classe matrice ( pour des raisons logique que le compilateur explique très bien : 
        // Cela reconduirais enfait a une forme de boulce infinie de classes... Ainsi, ne pouvant PAS passer ma méthode inverse() en virtual, 
        // j'ai contourner le problème en créant une fonction invers_call qui ELLE sera passer en virtual. 
        // Comme elle ne retourne ( du coup ) qu'une Matrice, le contructeur par copie-promotion sera utiliser avec de manière a reproduire le fonctionement souhaité 
        // de la fonction inverse. 
        // Il aurais été plus propre de directement déclarer comme Matrice la fonction inverse, mais le sujet impose cela.

        MatriceCarree MatriceCarree::inverse() const
        {
            // Cette méthode retourne l'inverse de la matrice. Pour calculer cela, nous utiliserons l'algorythme de gauss-jordan
            // et ce bien sur a condition que la matrice soit inversible ! C'est pourquoi cette fonction de s'appliquera qu'après avoir verifier l'inversibilitée de la matrice.
            
            // Le code de cette fonction part d'un copié/colé de la fonction du dessut, commentaire compris.

            Matrice Kikou=Matrice(*this); // la matrice a laquelle on apliquera l'algorythme, la matrice en entrée etant typée const.
            
            // Il a été choisit de coler des -1 a tous les indices lors des accès aux valeurs. On travaille ainsi avec des indice de 1 jusqu'a N, ce qui est plus joli et evite d'initalisé r a -1..
            // quelques variables de passages :
            int r=0;
            int n;
            double scalaire,multiplicatuer;
            n=Kikou.getM(); // = Kikou.getN() car la matrice est carée : pas besoin de se trimbaler 2 variables. 
            
            // Definition de la matrice identitée :
            MatriceCarree Id=MatriceCarree(n);
            
            for (int j=1;j<=n;j++) // j decris les indices de colones
            {
                // recherche du max des valeur absolue des getValue(i,j) pour r+1 <= i <= n; on notera k l'indice de ligne de ce maximum
                int k=r+1;
                double max=valeurabsolue(Kikou.getValue(r,j-1));
                for (int i=r+1;i<=n;i++)
                {
                    if (valeurabsolue(Kikou.getValue(i-1,j-1))>max)
                    {
                        // on réassigne le max, et on change l'indice k
                        max=valeurabsolue(Kikou.getValue(i-1,j-1));
                        k=i;
                        
                    }
                
                }

                // getValue(k,j) est donc le pivot
                if ( Kikou.getValue(k-1,j-1) != 0 )
                {
                    r=r+1;
                    scalaire=1/Kikou.getValue(k-1,j-1);
                    Kikou.multiplier_ligne_par_scal(k-1,scalaire);
                    Kikou.echanger_deux_lignes(k-1,r-1);                
                        // Ici, on aplique les memes changements a la deuxiemme matrice :
                        Id.multiplier_ligne_par_scal(k-1,scalaire);
                        Id.echanger_deux_lignes(k-1,r-1);

                    for ( int i=1;i<=n;i++)
                    {
                        if ( i != r )
                        {
                            multiplicatuer=Kikou.getValue(i-1,j-1);
                            Kikou.soustr_mult_ligne1_a_ligne2(r-1,i-1,multiplicatuer);
                                // Idem
                                Id.soustr_mult_ligne1_a_ligne2(r-1,i-1,multiplicatuer);
                        }
                    }

                }
                // Pas besoin du Else ce coup ci : la matrice est inversible quoi qu'il arrive.            
            }
            // L'algorythme de gauss etant finis, il ne nous reste qu'a retourner la matrice ID qui est entre temps devenu l'inverce de Kikou. 
            return Id;    
        }  



// Determinant
        double MatriceCarree::det() const
        {
            // Cette méthode renverra le determinant de la matrice. Il a été choisit de coder d''abord le determinant pour ensuite l'exploiter dans les autres fonctions ( notament la positivitée ).
            // D'autre part, la fonction d'inversibilitée ne sera pas re-codée avec un determinant, meme si cela serais quand meme beaucoup plus propre.

            // Le determinant sera calculer ici avec l'algorythme de gauss, que nous copie-colerons de la fonction inversible. On rajoutera juste les compteurs sufisant :
            // p le nombre de permutations de lignes, et 
            // pivots[] les diferents pivots. 
            // le determinant de la matrice a pour valeur (-1)^p * Produit ( pivots );

            double determinant=1; // 1 est le zero de la multiplication, qui sera la première opération appliquée au det.

            Matrice Kikou=Matrice(*this); // la matrice a laquelle on apliquera l'algorythme, la matrice en entrée etant typée const.
            
            // Il a été choisit de coler des -1 a tous les indices lors des accès aux valeurs. On travaille ainsi avec des indice de 1 jusqu'a N, ce qui est plus joli et evite d'initalisé r a -1..
            // quelques variables de passages :
            int r=0;
            int n;
            double scalaire,multiplicatuer;
            n=Kikou.getM(); // = Kikou.getN() car la matrice est carée : pas besoin de se trimbaler 2 variables. 
            for (int j=1;j<=n;j++) // j decris les indices de colones
            {
                // recherche du max des valeur absolue des getValue(i,j) pour r+1 <= i <= n; on notera k l'indice de ligne de ce maximum
                int k=r+1;
                double max=valeurabsolue(Kikou.getValue(r,j-1));
                for (int i=r+1;i<=n;i++)
                {
                    if (valeurabsolue(Kikou.getValue(i-1,j-1))>max)
                    {
                        // on réassigne le max, et on change l'indice k
                        max=valeurabsolue(Kikou.getValue(i-1,j-1));
                        k=i;
                        
                    }
                
                }
                // getValue(k,j) est donc le pivot
                if ( Kikou.getValue(k-1,j-1) != 0 )
                {
                        // Multiplions le determinant par le pivot : 
                        determinant*=Kikou.getValue(k-1,j-1);
                    r=r+1;
                    scalaire=1/Kikou.getValue(k-1,j-1);
                    Kikou.multiplier_ligne_par_scal(k-1,(1/Kikou.getValue(k-1,j-1)));
                    Kikou.echanger_deux_lignes(k-1,r-1);   // Si k est different de r, c'est une permutation.
                        if ( k!=r )
                        {
                            determinant=-determinant; // On multipli donc le determinant par -1
                        }
                    for ( int i=1;i<=n;i++)
                    {
                        if ( i != r )
                        {
                            multiplicatuer=Kikou.getValue(i-1,j-1);
                            Kikou.soustr_mult_ligne1_a_ligne2(r-1,i-1,multiplicatuer);
                        }
                    }

                }
                else
                {
                    // Si le maximum de la colone est nul, alors toute la colone est nulle et le determinant est nul lui aussi, on return donc 0 :
                    return 0;
                }
            
            }
            // Dans le cas contraire, si l'algorythme de gauss se finit, retournons le determinant :
            return determinant;
            // Cette fonction de clalcul de determinant a été DIRECTEMENT exploité de l'agorythme de gauss...
            // Cependant, le fait de recopier ( 3 fois deja : inversibilité, inverse et det ) le meme algorythme le rendra plus dur a maintenir
            // Il est donc probable que la version d'origine d'inversibilitée devienne obsolette et ne soit remplacée par une version exploitant la fonction determinant. 
            // L'ancien code sera laisser en commentaire, mais ne sera plus maintenu, gare donc a ceux qui voudrons le faire tourner.
        }



// Méthodes symetrique, définie-positive.
        bool MatriceCarree::symetrique() const
        {
            // Methode renvoyant true si la matrice carree est bien symetrique, et false sinon.
            // Etre symetrique revient a etre egale a sa propre transposée, 
            // donc un simple test nous renvera ce qu'il faut :

            // verson longue :
            if ( Matrice::transpose().transpose() == Matrice::transpose() ) // transposer 2 fois permet de trasnformer une MatriceCarree et Matrice ;)
            {
                // Si la matrice est sa propre transposée, elle est donc symetrique 
                return true;
            }
            else
            {
                return false;
            }
            
            
            // Version courte : 
            // return ( matrice::transpose().transpose() == Matrice::transpose() );
            
        }

        bool MatriceCarree::positive() const
        {
            //Méthode renvoyant true si la matrice carré est définie positive

            // On va utiliser le critère de sylvester, et ce sera vite vu : on a deja coder les sous-matrices et le determinant.

            // Sylvester nous dit : Si la matrice est symetriques, et que tout les mineurs principaux sont de determinant positifs, alors elle est DP.
            double resultat=1; // le zero de la multiplication...    
            //Est-ce que la matrice est symetrique ? 
            if ( symetrique() )
            {
                // On va caclculer les mienurs principaux, c'est a dire les sous-matrices 0,0,n,n pour n de 0 a _m;
                for (int i=0;i<getM();i++)
                {
                    // clacul de la sous matrice,
                    MatriceCarree m(sousMatrice(0,i,0,i));
                    resultat = resultat * m.det();
                    //resultat=resultat*(sousMatrice(0,0,i,i).det());
                }
                return ( resultat >= 0 );
            }
            else // La matrice n'est pas symetrique
            {
                std::cout <<" Votre matrice n'est meme pas symetrique !";
                return false;
            }
        }


		Matrice MatriceCarree::cholesky_call() const
		{
			return this->cholesky();
		} // Meme problème, meme solution. 


        MatriceCarree MatriceCarree::cholesky() const // L'algorythme est éronné, j'ai duf aire une erreur d'indice qqpart.
        {
            // Cette méthode renvoiera la factorisation de cholesky de la matrice
            // l'algorythme a été piquer sur wikipedia :
            if ( positive() ) // si la matrice est symetrique définie positive
            {
                    MatriceCarree L(getN(),0); // Créons la pleine de zero
                    
                    // Commençons par la 1ere valeur : 
                    double valeur=sqrt(getValue(0,0));
                    L.setValue(0,0,valeur);

                    // la suite de la 1ere colone : 

                    for (int j=1;j<getN();j++)
                    {
                        valeur= getValue(0,j) / L.getValue(0,0);
                        L.setValue(0,j,valeur);
                    }

                    // Passons maintenant a la récursivitée pour les collones suivantes : 

                    for (int i=1;i<getN();i++)
                    {
                        double somme=0;
                        // pour j=i :
                        //valeur = sqrt(getValue(i,i)- Li,1 carré - ... - Li,i-1 carré
                        for (int k=0;k<i-1;k++)
                        {
                            somme+=(L.getValue(i,k)*L.getValue(i,k));
                        }
                        valeur = sqrt(getValue(i,i)-somme);
                        L.setValue(i,i,valeur);

                        // pour j>i :
                        for (int j=i+1;j<getN();j++)
                        {
                            somme=0;
                            // meme délire :
                            // valeur = getValue(i,i+1)- Li,1 * Li+1,1 - ... - Li,i-1*Li+1,i-1 le tout divisé par Li,i
                            for (int k=0;k<i;k++ )
                            {
                                somme +=( L.getValue(i,k) * L.getValue(j,k) );
                            }
                            valeur = ( getValue(i,j) - somme ) / L.getValue(i,i);

                            L.setValue(i,j,valeur);
                        }
                    }
                    return L;
            }
            else
            {
                // La factorisation de cholesky d'une matrice non-définie-positive n'existe pas.
                std::cout<<"Vous essayez de calculer la factorisation de cholesky d'une matrice carrée non-définie-positive !";

            }

        }










