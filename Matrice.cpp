#include "MatriceCarree.h"

// Les accesseurs de la classe matrice
	    int Matrice::getM() const // J'ai choisit de changer le type des accesseurs getN et getM pour les mettre en const.
	    {
	        return _m;
	    }
	    
	    int Matrice::getN() const // En effet, ils ne modifierons jamais l'objet, autant le dire au compilateur
	    {
	        return _n;
	    }
	    
	    void Matrice::setM(int const& m)
	    {
	        _m=m;
	    }
	    
	    void Matrice::setN(int const& n)
	    {
	        _n=n;
	    }
	    
	    double Matrice::getValue(int const& i, int const& j) const
	    {
	        return contenu[i][j];
	    }
	    void Matrice::setValue(int const& i, int const& j, double const& x)
	    {
	        contenu[i][j]=x;
	    }



// Constructeurs et destructeur
        Matrice::Matrice() // Constructeur vide
        {
        
        } 
        
        Matrice::Matrice(int const& m, int const& n) : _m(m), _n(n) // constructeur initialisant la matrice mais pas ses valeurs
        {
            contenu= (double**)malloc(_m*sizeof(double*));
            for (int i=0;i<_m;i++)
            {
                contenu[i]=(double *)malloc(_n*sizeof(double)); 
            }
        } 
        
        Matrice::Matrice(int const& m, int const& n, double const& x) : _m(m), _n(n) // contructeur initialisant la matrice ainsi que toute ses valeurs a x
        {
            contenu= (double**)malloc(_m*sizeof(double*));
            for (int i=0;i<_m;i++)
            {
                contenu[i]=(double *)malloc(_n*sizeof(double));
                for (int j=1;j<_n;j++)
                {
                    setValue(i,j,x);   
                }  
            }
        } 
        
        Matrice::Matrice(Matrice const& matrice) : _m(matrice._m), _n(matrice._n) // constructeur par copie
        {
           
           contenu= (double**)malloc(_m*sizeof(double*)); // Dans les constructeurs, on evite d'en apeller d'autres...
           for (int i=0;i<_m;i++)
            {
                contenu[i]=(double*)malloc(_n*sizeof(double));
                for (int j=0;j<_n;j++)
                {
                    contenu[i][j]=matrice.getValue(i,j); //remplissage...  
                }  
            }

        } 
        
        Matrice::~Matrice() // Destructeur de la matrice
        {
            // ici il faut free la matrice... on free d'abord les contenu[i] avent de free contenu d'un coup.
            for (int i=0;i<getM();i++)
            {
                free(contenu[i]);
            }     
            free(contenu);

        };



// methode autofill
        void Matrice::Matriceremplie() // Utile pour pas avoir a retaper la matrice a chaque débeugage... -> Uniquement pour les tests, a supprimer ensuite.
        {
            int k=1;
             for (int i=0;i<_m;i++)
            {
                for(int j=0;j<_n;j++)
                {
                    contenu[i][j]=k++;
                }
            }
        }



// Methodes In/out : affichage et remplissage
        void Matrice::afficher() // Affichage de la matrice
        {
            // Cette methode a pour but d'afficher la matrice, une simple double boucle 
            // avec utilisation corecte des assesseur fera l'affaire
            for (int i=0;i<getM();i++)
            { 
		        for (int j=0;j<getN();j++) // parcourt sur les lignes et les colones
                { 
			        std::cout << getValue(i,j) << "\t"; // affichage de la valeur
		        }
		        std::cout << "\n\n"; // espaçage pour que ce soit joli ;) 
	        }
        }

        void Matrice::affecter() // Remplissage de la matrice
        {
            // Proposons a l'utilisateur de remplir la matrice. Attention, ce remplissage considère que la taille
            // de la matrice est deja fixée et meme qu'elle est deja initialisée completement

            // On fera attention a verifier qu'il rentre bien des nombres dedans dans un second temps, surement via une fonction de verification.
            int a; // La variable a sera utiliser comme variable de passage

            std::cout << "Vous allez maitenant remplir votre matrice. Nous vous rapelons qu'elle est de taille " << getN() << "x" << getM() << "\n";
	        
            for (int i=0;i<getM();++i)
            {
                for(int j=0;j<getN();++j) // double boucle sur i,j pour renplir une a une les n*m valeurs de la matrice.
                {
			        std::cout << "\nLigne " << i << " Colone " << j << " : ";
                    std::cin >> a;; // c'est ici qu'il faudra verifier que les double rentré par l'utilisateur en sont bien.
		            setValue(i,j,a); // On met la valeur dans la matrice en utilisant l'acceseur prévu pour.
                }
	        }
            
            std::cout << "Votre matrice a bien été remplie\n";    
        }



// Methode sous-matrice, transposée et produit de kronecker
        Matrice Matrice::sousMatrice(int const &i, int const &j, int const &k, int const &l) const
        {
            // Cette méthode renvois la sous-matrice comprise entre les lignes i et j et entre les colones k et l;
            // vérification de sécuritée : véifier que 0<i<j<n, que 0<k<l<m avec n et m les taille de la matrice d'orgine.
                // il nous faut donc créé une matrice de la bonne taille :
                Matrice m=Matrice(j-i+1,l-k+1);

                // On a considéré ici que la sous matrice se faisait en INCLUANT les lignes i,j et les colones k,l. 
                // D'ou les +1 qui aparaisse ci-sessus dans la declaration et ci-dessous dans les for

                for (int p=i;p<j+1;p++) // parcourt sur les lignes entre i et j de la matrice d'entrée
                {
                    for (int q=k;q<l+1;q++) // parcourt sur les colones de k a l
                    {
                        m.setValue(p-i,q-k,getValue(p,q)); // copie de la valeur dans la nouvelle matrice.
                        // le setValue est un accesseur de m et le getValue est un accesseur de l'objet principal.
                    }
                }
                return m;
        }

        Matrice Matrice::transpose() const
        {
            // Cette méthode a pour but de renvoyer sous forme de nouvelle matrice la transposée de la matrice.
            // Nous devons donc créé une nouvelle matrice de taille getN * getM ( transposée )
            // et la remplir avec les ellements de l'ancienne, m.set(m,n)=get(n,m)
            // Attention, la nouvelle matrice n'aura pas la meme taille ( enfait n=m et m=n ) dans le cas ou la matrice en entrée n'est pas carré ?
        
            Matrice m=Matrice(getN(),getM(),0);

            // Remplissage : 
            for ( int i=0;i<m.getM();i++ )
            {
                for ( int j=0;j<m.getN();j++)
                {
                    m.setValue(i,j,getValue(j,i)); // 'linversion des i,j en j,i suffit pour transposée la matrice...
                }
            }
            return m;
        }   

        Matrice Matrice::kronecker(Matrice const& B) const
        {
            // Cette méthode a pour but de renvoyer le produit de kronecker de la matrice avec une matrice B passée en parametre.
            // nous allons donc créé une matrice de la bonne taille ( c'est a dire de longeur produit des deux et de largeur
            // produit des deux, puis faire une quadruple boucle pour la remplir
            int a=getM()*B.getM();
            int b=getN()*B.getN();
            int y,z;
            double value;
            Matrice m=Matrice(a,b,0); // on se permet de mettre des zero dedans, est-ce bien utile ? A tester.

            // Remplissage :
            for (int i=0;i<getM();i++) { for (int j=0;j<getN();j++) { // Boucle sur (i,j) pour la matrice principale ( nomé A dans l'enoncé )
                for (int k=0;k<B.getM();k++) { for ( int l=0;l<B.getN();l++ ){ // Boucle sur (k,l) pour la seconde matrice B
                    // il nous faut donc atribuer a notre matrice m en (y,z) la valeur a(i,j)*b(k,l)
                    // pour determiner y,z en fonction de i,j,k,l, on va simlpement dire que :
                    // y=i*tailledeB+k
                    // z=j*tailledeB+l avec tailledeB qui vaut getM en hauteur et getN en largeur
                    y=k+i*B.getM();
                    z=l+j*B.getN();
                    value=(getValue(i,j))*(B.getValue(k,l));
                    m.setValue(y,z,value); // Normalement ça le fait, mais bon. 
                    // Il y a surement des erreur d'indices sales, le prgm fonctione pour des matrice de beaucoup de taille, 
                    // mais 2x2 * 2x3 il veut absolument pas. Va savoir pourquoi..
                }}
            }}
            return m;
        }



// Surchages d'opérateurs ( et méthode préalables )
        // les opérateurs ont été re-codé avec l'utilisation des opérateurs racourcits sous forme de méthode, mais l'ancien code est encore entre /* et */

        bool Matrice::memeTaille(Matrice const& A) const
        {
            // Cette méthode revoit simplement true si la matrice objet et A ont la meme taille,
            return ( getM() == A.getM() && getN() == A.getN() );
            // en renvoyant tout simplement la valeur du test...
        }

        bool operator==(Matrice const& A, Matrice const& B)
        {
            // Cet opérateur teste l'égalitée entre deux matrice, que nous définirons donc ici comme l'égalitée de toute leur valeur séparement. 
            if ( ! ( A.memeTaille(B) ) )
            {
                return false; // Si a n'a pas la meme taille que B, elles ne sont pas egales...
            }
            else
            {
                for (int i=0;i<A.getM();i++) { for ( int j=0;j<A.getN();j++) { // le double-for classique déja utilisé ci-dessut
                    if ( A.getValue(i,j) != B.getValue(i,j) )
                    {
                        return false;   // Et si A a des valeurs diferentes de B, elles ne sont pas egales.
                    }
                }}
            }
            return true; // Dans tout les autres cas, A=B trivialement.
        }

        bool operator!=(Matrice const& A, Matrice const& B)
        {
            // cet opérateur est sensé renvoyer true si A!=B et false si A=B. Il renvois donc l'inverse de l'opérateur ==, et donc : 
            return !(A==B);
        }

        Matrice operator+(Matrice const& A, double const& x)
        {
            /* // ANCIENNE VERSION
            // cet opérateur ajoute un scalaire a une matrice, c'est a dire a toute les valeur de la diagonale de cette matrice. 
            // On utilisera donc le constructeur de copie, puis une double boucle ajoutant x.

            Matrice m(A);
            for ( int i=0;i<A.getM();i++) { for ( int j=0;j<A.getN();j++) {
                if (i==j)
                {
                    m.setValue(i,j,(A.getValue(i,j)+x)); // On ajoute la valeur que si on est sur la diagonale...
                }
            }}
            // et on retourne le resultat sous forme d'une matrice : 
            return m;
            */

            // NOUVELLE VERSION :
            Matrice m(A);
            return m+=x;
        }
        
        Matrice operator+(Matrice const& A, Matrice const& B)
        {
            /* // ANCIENNE VERSION
            // cet opérateur sert a faire la somme de deux matrices. On va donc faire exactement comme 
            //ci dessut, mais en replaçant la valeur par un getValue sur la deuxiemme matrice...
            // Tout ceci a condition, bien sur, que les deux matrice aie la meme taille ;)

            if ( A.memeTaille(B) )
            {
                Matrice m(A); // constructeur de copie
                for ( int i=0;i<A.getM();i++) { for ( int j=0;j<A.getN();j++) { // double boucle de parcourt de la matrice
                   m.setValue(i,j,(A.getValue(i,j)+B.getValue(i,j)));
                }}
                // et on retourne le resultat sous forme d'une matrice : 
                return m;
            }
            else
            {
                // la somme n'est pas possible, donc EXIT
                std::cout << " Vos deux matrice n'ont pas la meme taille, vous ne pouvez donc pas les soustraire !";
                exit(EXIT_FAILURE); 
            }
            */

            // NOUVELLE VERSION :
            Matrice m(A);
            return m+=B;
        }
        Matrice operator-(Matrice const& A, double const& x)
        {
            /* // ANCIENNE VERSION
            // Cet operateur fait la soustraction entre une matrice et un scalaire, c'est a dire qu'on va enlever la valeur uniquement sur la diagonale.
            // On va faire exactement pareil que pour l'opé somme, mais avec juste un moins dans la formule.
            Matrice m(A); // copie
            for ( int i=0;i<A.getM();i++) { for ( int j=0;j<A.getN();j++) { // double boucle comme d'habitude..
                if (i==j)
                {
                    m.setValue(i,j,(A.getValue(i,j)-x)); // On soustrait la valeur que si on est sur la diagonale...
                }
            }}
            // et on retourne le resultat sous forme d'une matrice : 
            return m;
            */

            // NOUVELLE VERSION :
            Matrice m(A);
            return m-=x;

        }

        Matrice operator-(Matrice const& A, Matrice const& B)
        {
            /* // ANCIENNE VERSION
            // Cet opérateur fait lui la soustraction entre deux matrice, et ce uniquement si elles sont de la meme taille...
            // On va donc récuperer le code de la somme, et ajouter un moins.
            // La relecture du code n'est meme pas nécéssaire, c'est juste le meme avec un signe qui change...
            if ( A.memeTaille(B) )
            {
                Matrice m(A); // constructeur de copie
                for ( int i=0;i<A.getM();i++) { for ( int j=0;j<A.getN();j++) { // double boucle de parcourt de la matrice
                   m.setValue(i,j,(A.getValue(i,j)-B.getValue(i,j))); // Le moins est inséré ici !
                }}
                // et on retourne le resultat sous forme d'une matrice : 
                return m;
            }
            else
            {
                // Les deux matrices n'ont pas la meme taille, on ne les soustraira donc pas : EXIT
                std::cout << " Vos deux matrices n'ont pas la meme taille, vous ne pouvez pas les soustraire !";
                exit(EXIT_FAILURE);
            }
            */

            // NOUVELLE VERSION
            Matrice m(A);
            return m-=B;

        }

        Matrice operator*(Matrice const& A, double const& x)
        {
            /* // ANCIENNE VERSION
            // Cet opérateur fait le produit entre une matrice et une constante, définis comme le produit de toute les valeur de la matrice 
            // par le multiplicateur x. On va donc faire trivialement une double boucle sur la matrice et setValue le produit en question
            // sur une nouvelle matrice préalablement copié.
            Matrice m(A); // Le constructeur par copie permet ici de ne pas se faire chier avec des get/setValue : c'est plsu jolie non ? 

            for ( int i=0; i<A.getM();i++) { for ( int j=0;j<A.getN();j++){ // après la copie, A.getM/N = m.getM/N, donc on prend l'un ou l'autre au choix.
                m.setValue(i,j,(x*A.getValue(i,j))); 
                // Le getvalue dans matrice devant se rapporte bien evidement a la matrice objet donc cette fonction est une méthode....
            }}
            return m;
            */

            // NOUVELLE VERSION
            Matrice m(A);
            return m*=x;
        }

        Matrice operator*(Matrice const& A, Matrice const& B)
        {
            /* Pas de nouvelle version possible pour cet opérateur */

            // Cet opérateur doit renvoyer le produit matriciel standard entre deux matrice. Ainsi, 
            // pour tout i,j convenable ( i.e de la bonne taille )

            // Verifions au préalable que la première matrice a le meme nombre de colones ( getN ) que le nombre de lignes ( getM ) de la seconde,
            // seule condition mathématique pour que le produit existe.

            if ( A.getN() == B.getM() )
            {
                // Donc le produit existe. 
                // Sa taille sera alors le produit de A.get(M) et de B.get(N). Nous pouvons donc déclarer la matrice qu'on l'on va return :
                Matrice m(A.getM(),B.getN());
                
                // Produit(i,j) = somme sur k=0 jusqu'a A.getN = B.getM, de B(i,k) * B(k,j) classiquement. Faisons donc une double boucle :
                for (int i=0;i<A.getM();i++) { for ( int j=0;j<B.getN(); j++) {
                    // Assignons donc a m(i,j) la valeur somme ( A(i,k) * B(k,j) );
                    double somme=0;
                    for (int k=0;k<A.getN();k++) // On fait la somme sur le nombre de ligne de A ( ou le nombre de colone de B, c'est pareil )
                    {
                        somme+=(A.getValue(i,k))*(B.getValue(k,j));
                    }
                    m.setValue(i,j,somme); // Une fois la somme fait, on l'assigne a la valeur (i,j) de la nouvelle matrice.
                    
                }}
                return m; // On return la matrice produit ainsi créé.
            }
            else
            {
                // Le produit de deux matrices n'ayant pas des tailles corespondante etant impossible, EXIT
                std::cout << " Vos deux matrices ne sont pas multipliable : elles n'ont des tailles apropriées. petit chenapan ;) ";
                exit(EXIT_FAILURE);
            }
            
        }



// Operateurs racourcits
        // le typage de ces opérateurs est clairement diferent des précédents : ils renvoit des pointeurs vers des 
        // matrices et pas des matrices.. de plus, ce sont des méthodes intrinsèque a la classe, d'ou le return *this.

        Matrice& Matrice::operator+=(double const& x)
        {
            // le but de cet opérateur est d'ajouter un scalaire a la matrice
            for (int i=0;i<getM();i++) { for (int j=0;j<getN();j++ ) { // double boucle sur la matrice...
                if ( i == j )
                {
                    setValue(i,i,(getValue(i,i)+x)); // On ne rajoute x que sur la diagonale !
                }
            }}
            return *this; // le return *this; est standard pour ce type d'opérateur : On renvois l'adresse uniquement.
        }
        Matrice& Matrice::operator+=(Matrice const& A)
        {
            // le but de cet opérateur est d'ajouter la matrice A a la matrice objet. On va donc d'abord tester si 
            //elles ont la meme taille, histoire de ne pas faire naWak.
            // Dans le cas contraire, on EXIT après un mesage d'erreur

            if ( memeTaille(A) )
            {
                // du coup on peut faire la somme : double boucle comme d'habitude...
                for ( int i=0;i<getM();i++) { for (int j=0;j<getN();j++) {
                    setValue(i,j,getValue(i,j)+A.getValue(i,j)); // On ajoute les valeur de l'autre matrice...
                }}
                return *this; // et on return this.
            }
            else
            {
                std::cout << " Vos deux matrices n'ont pas la meme taille, vous ne pouvez pas les aditioner. Petit chanapan ;)";
                exit(EXIT_FAILURE);
            }
        }

        Matrice& Matrice::operator-=(double const& x)
        {
            // Operateur de soustraction de scalaire a une matrice
            // C'est pareil que d'ajouter un scalaire a une matrice, non ? 

            return (*this+=(-x));
        }
        
        Matrice& Matrice::operator-=(Matrice const& A)
        {
            // Operateur de soustraction de matrice. Cela resemble beaucoup a l'adition de matrice, mais on ne peut pas exploiter le code
            // recopions le donc en changeant le signe au bon endroit :
            if ( memeTaille(A) )
            {
                // du coup on peut faire la soustraction: double boucle comme d'habitude...
                for (int i=0;i<getM();i++) { for (int j=0;j<getN();j++) {
                    setValue(i,j,getValue(i,j)-A.getValue(i,j)); // On a juste changer un signe ici !
                }}
                return *this; // et on return this.
            }
            else
            {
                std::cout << " Vos deux matrices n'ont pas la meme taille, vous ne pouvez pas les soustraire. Petit chenapan ;)";
                exit(EXIT_FAILURE);
            }
        }

        Matrice& Matrice::operator*=(double const& x)
        {
            // Opérateur de multiplication de matrice par un scalaire. Cela revient a multiplier toute les valeur de la matrice par le scalaire,
            // On fera donc une traditionelle double-boucle sur la matrice, puis on setValue x*getValue :
            for (int i=0;i<getM();i++) { for ( int j=0;j<getN();j++){
                setValue(i,j,(x*getValue(i,j)));
            }}
            return *this;
        }



// Methodes utiles pour les calculs d'inversibilitée et d'inversion, qui sont valables pour les matrices non-carrées:
        void Matrice::echanger_deux_lignes(int const &i,int const &j)
        {
            // Cette methode echange deux lignes de la matrice. elle remplace donc la ligne i par la ligne j;
            //il faut donc alouer une nouvelle ligne pour pouvoir faire cela.
                double* ligne_de_passage=(double *)malloc(getN()*sizeof(double));
            
            // une petite boucle tranquilou ( Sur les colones, OFC ) pour faire les echanges :
            for (int k=0;k<getN();k++)
            {
                ligne_de_passage[k]=getValue(i,k);
                setValue(i,k,getValue(j,k));
                setValue(j,k,ligne_de_passage[k]);
            }

        }
        
        void Matrice::multiplier_ligne_par_scal(int const &i, double const& x)
        {
            // Cette méthode multiplie la ligne i de la matrice par le scalaire x.
            // on fait donc une boucle et on assigne getValue(i,j)*x a chaque passage...

            for ( int j=0;j<getN();j++)
            {
                setValue(i,j,getValue(i,j)*x);       
            }
        }
        
        void Matrice::soustr_mult_ligne1_a_ligne2(int const& i, int const &j,double const &x)
        {
            // Cette méthode soustrait un multiple de la ligne i a la ligne j :
            // On fait donc une boucle sur les colones, et a chaque passage, on soustrait a la cas i*k x * case j*k

            for ( int k=0;k<getN();k++)
            {
                setValue(j,k,getValue(j,k)-(x*getValue(i,k)));
            }
        }



// Méthodes virtuelle de la classe matricecaréé, qu'il nous faut définir ici et leur faire renvoyer une erreur.
            // Inversibilitée, inversion :
                bool Matrice::inversible() const
                {
                    std::cout<<"Cette matrice n'est pas inversible, elle n'est pas carée ! Petit chenapan ;)";
                    return false;
                }
                Matrice Matrice::inverse_call() const
                {
                    std::cout<<"Vous essayez d'inverser une matrice non carée ! Petit chenapan ;)";
                    exit(EXIT_FAILURE);
                }

            // Symetrique, définie-positive ( tests )
                bool Matrice::symetrique() const
                {
                    std::cout<<"Une matrice non-carée ne peut pas etre symetrique, voyons ! Petit chenapan ;)";
                    return false;
                }
                bool Matrice::positive() const
                {
                    std::cout<<"Vraiment, une matrice non-carée définie positive ? Vous y croyez, vous ? Chenapan, va !";
                    return false;
                }
        
            // Determinant :
                double Matrice::det() const
                {
                    std::cout<<"J'aimerais bien savoir comment on calcul le déterminant d'une matrice qui n'est pas carrée.. Chenapan, va !";
                    exit(EXIT_FAILURE);
                }

            // Cholesky :
                Matrice Matrice::cholesky_call() const
                {
                    std::cout<<"Vous essayer de calculer la factorisation de cholesky d'une matrice qui n'est meme pas carrée ! petit chenapan ;)";
                    exit(EXIT_FAILURE);
                }


