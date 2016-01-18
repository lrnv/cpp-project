#include <iostream>
#include <stdlib.h>
#include "MatriceCarree.h"



///////////////// QUELQUES FONCTIONS PREALABLES /////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////// QUELQUES FONCTIONS PREALABLES ///////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int choix_matrice(int nombre){
    // Cette fonction, bien que simpliste, est très utile pour le main.
    // Elle permet juste de choisir une matrice parmis les matrices disponibles.
    int choix;
    std::cout<<"Pour choisir une matrice, entrez un nombre entre 1 et "<<nombre<<" : ";
    std::cin>>choix;
    if ( 0 < choix && choix <=nombre ) 
    {
        return choix-1; // N'oublions pas que le tableau de matrices est indéxé a partir de 0.
    }
    else
    {
        std::cout<<"Nous n'avons pas compris votre choix";
        exit(EXIT_FAILURE);
    }
}

void sauver_ou_afficher( bool conserver, Matrice M, Matrice** &tab, int &nombre ){
    // Plutot que de recopier N fois ce bout de code, autant en faire directement une fonction.
    
    // Cette fonction sert juste a finaliser le travail sur une matrice : soit on l'affiche soit on l'enregistre.
    if ( conserver )
    {
        // Sauver la matrice revient a mettre son adresse dans la case suivante du tableau, et d'incrémenter.
        // mais vérfiions quand meme d'abord qu'elle n'est pas carrée :
        if ( M.getN() != M.getM() )
        {
            tab[nombre]=new Matrice(M);
        }
        else
        {
            tab[nombre]=new MatriceCarree(M); // Au cas ou, autant enregistrer les matrice carées dans la bonne classe !
        }
        nombre++;
        std::cout<<"\n    Votre resultat a été sauvé sous le nom Matrice "<<nombre<<"\n";
    }
    else
    {
        std::cout<<"\n    Voicit donc votre résultat :\n";
        M.afficher();
        // Si on ne souhaite pas la conserver, on l'affiche quand meme...
    }
}

bool souhaitez_vous_conserver_la_matrice_entree(){

    // L'utilitées de cette fonction se lit dans son nom, explicite.

    // Mettre cette fonction ici permet de rendre le Main encore un peu plus clair, meme si elle n'est au final que peu utilisée,
    // cela découpe le code en petit bouts et le rend plus lisibile;
    char choix;
    std::cout<<"\nVous allez pouvoir effectuer des opérations sur votre matrice. Si vous ne souhaitez pas conserver votre resultat, il sera perdu.\nDans le cas contraire, il sera ajouter comme une nouvelle matrice aux matrices disponibles.\n\nSouhaitez-vous conserver votre resultat ? (Y/n) ( Yes par deffaut ) : ";
    std::cin>>choix;
    if ( choix == 'n' ) 
    { 
        return false; 
    }
    else 
    { 
        return true;
    }
    // Si choix vaut n, on considèrera que l'on ne souhaite pas conserver la matrice
    // Sinon, on considerera qu'on souhaite une simple extraction dans une nouvelle matrice, que l'on souhaite enregistrer.
}

int main(){
/////////////////////////////// DEBUT DU MAIN ///////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////// DEBUT DU MAIN ///////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Codage du menu : 
        // Création du tableau hétérogène. Il faudrat recopier dans matrice.h et matrice.cpp les méthodes utilisé par matricecarree
        // et leur faire renvoyer une simple erreur. ( tout cela en virtual )
        // De cette manière, on pourra stoquer les matrices carré comme des matrices avec les autres dans un tableau de matrices,
        // et leur appliquer les méthodes de matricecarréé sans aucun soucis : Au moment d el'appel de la méthode,
        // a condition qu'elle existe en virtual dans matrice, le compilateur appliquera la methode qui va bien. 

    int ctrl,ctrl2,ctrl3; // Emboitage de 3 switchs maximum.
    int i,p,m,n; // variable de traitement.
    double scalaire; // Pour les somme, soustractions et produits.

    Matrice **tab=new Matrice*[100]; // création du tableau de matrices
    int nombre=3; // le nombre de matrice en mémoire -> On a mis les 3 suivantes pour faire des tests : 
    
    tab[0]=new MatriceCarree(2);
    tab[1]=new Matrice(3,4); tab[1]->Matriceremplie();
    tab[2]=new MatriceCarree(2,2); tab[2]->Matriceremplie();
    //tab[4]=new MatriceCarree(3); tab[4]->Matriceremplie();

////////////////////////////// DEBUT DU SWITCH MENU /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////// DEBUT DU SWITCH MENU //////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout<<"Bienvenue dans ce gestionaire de matrices.\n\n\n";
    do {
        // un peu de mise en forme :
        std::cout<<"\n\n******************************************************************************************************************************************\n******************************************************* MENU PRINCIPAL *******************************************************************\n******************************************************************************************************************************************\n\n";

        std::cout<<"Vous avez "<<nombre<<" matrices en mémoire. Voicit les actions a votre disposition :\n\n    1 - Afficher les matrices disponibles\n    2 - Créer une matrice.\n    3 - Calculer des choses avec vos matrices\n    4 - Afficher diverses propriétées d'une matrice\n    5 - Supprimer une matrice\n    0 - Quitter le programme\n\n Votre choix : ";
        std::cin>>ctrl;
        std::cout<<"\n\n";

        switch ( ctrl )
        {
            case 1: // Afficher les matrices disponibles : DONE
            {
                 // Une boulce for jusqu'au nombre de matrices en mémoire avec des affichages fera l'affaire. Verifions quand meme qu'il y en a :

                if ( nombre == 0 )
                {
                    std::cout<< " Vous n'avez aucunes matrice en mémoire ! Créez-en une avent d'essayer de l'afficher ;)";
                }
                else
                {
                    for (int i=0;i<nombre;i++)
                    {
                        std::cout<<"Matrice "<<i+1<<" :    \n";
                        tab[i]->afficher();
                        std::cout<<"\n\n";
                    }
                }
                    // Cela devrais suffire pour l'instant. On pourra essayer d'impove l'affichage, en en mettant quelqu'unes cote a cote, maybe ? 
  
                break;
            }

            case 2: // Créer une matrice : DONE
            {
               
                // Il va ici faloire créé une matrice et l'enregistrer. 
                std::cout<<"Vous allez créer une matrice. Veuillez renseigner sa largeur : ";
                std::cin>>n;
                std::cout<<"Sa hauteur : ";
                std::cin>>m;
                Matrice M(m,n); // on la créer
                M.affecter(); // on la remplis
                
                sauver_ou_afficher(true,M,tab,nombre); // Avec le true, on sauve la matrice directement.
                break;
            }

            case 3: // Modifier une Matrice / Extraire une matrice.
            {
                bool conserver=souhaitez_vous_conserver_la_matrice_entree();
                int matrice_choisie=choix_matrice(nombre);
                

                std::cout<<"\n\n     **********************************************************************************************************************\n     ********************************************* SOUS MENU CALCUL *******************************************************\n     **********************************************************************************************************************\n\n";

                std::cout<<"Que souhaitez vous faire avec votre matrice ?\n\n    1 - Calculer une sous-matrice\n    2 - Calculer une transposée\n    3 - Calculer un produit de kronecker\n    4 - Cacluler une somme, souscration, produit par un scalaire\n    5 - Calculer une somme, soustraction, produit par une matrice\n    6 - Calculer l'inverse\n    7 - Calcluer la factorisation de cholesky\n    0 - Revenir au menu principal\n Votre choix : ";
                std::cin>>ctrl2;
                
                switch ( ctrl2 )
                {
                    case 1: // Calculer une sous matrice : DONE
                    {
                        int i,j,k,l;
                        // Calculons donc une sous matrice de la matrice choisie. Il nous faut pour cela les 4 coordonées ;)
                        std::cout<<"La matrice que vous avez choisie est :\n";
                        tab[matrice_choisie]->afficher();
                        std::cout<<"    Pour calculer une sous-matrice, j'ai besoin de conaitre précisement les coordonées dans la matrice de base de la sous-matrice souhaitée.\n    Les lignes et les collones sont numérotées a partir de 1.\n    Notez bien que l'extraction se fera en INCLUANT les colones / lignes que vous entrerez.\n\n        Entrez la première ligne :";
                        std::cin>>i;
                        std::cout<<"        Entrez la dernière ligne :";
                        std::cin>>j;
                        std::cout<<"        Entrez la première colone :";
                        std::cin>>k;
                        std::cout<<"        Entrez la dernière colone :";
                        std::cin>>l;
                        // passons au calcul proprement dit :
                        if ( 1<=i && j<=tab[matrice_choisie]->getM() && 1<=k && l<=tab[matrice_choisie]->getN() )
                        {
                            Matrice M = tab[matrice_choisie]->sousMatrice(i-1,j-1,k-1,l-1); // les -1 vienne du fait que les humains numérote les lignes a partir de 1 et la machine a partir de 0...
                            sauver_ou_afficher(conserver,M,tab,nombre);
                        }
                        else { std::cout<<"Cette amtrice carré n'est pas possible"; }
                        
                        break;
                    }


                    case 2: // Calculer une trasnposée : DONE
                    {
                        // Calculons la trasposée de tab[matrice_choisie] :
                        sauver_ou_afficher(conserver,tab[matrice_choisie]->transpose(),tab,nombre);
                        break;
                    }

                    case 3: // Calculer un produit de Kronecker : DONE
                    {
                        // Ici, il nous faut choisir une deuxiemme matrice.
                        std::cout<<"Pour calculer un produit de kronecker, vous devez choisir une deuxiemme matrice ( pas forcément diférente.. )\n";
                        int deuxiemme_matrice_choisie=choix_matrice(nombre);
                        sauver_ou_afficher(conserver,tab[matrice_choisie]->kronecker(*tab[deuxiemme_matrice_choisie]),tab,nombre);
                        break;
                    }

                    case 4: // Calculer une somme, soustraction ou produit par un scalaire : DONE
                    {
                        // Clairement, on va utiliser un switch supplementaire. On pourrais pour plus de claretée n'utiliser qu'un seul switch en tout, si j'ai le temps j'étudierais cette possibilitée, ce sera peut-etre plus propre.
                        std::cout<<"Entrer un scalaire :";
                        std::cin>>scalaire;
                        std::cout<<"\n\n     **************************************************************************************************\n     ******************************* SOUS-SOUS MENU SCALAIRE ******************************************\n     **************************************************************************************************\n\n";

                        std::cout<<"\nQue souhaitez-vous en faire : \n    1 - L'ajouter a ma matrice\n    2 - Le soustraire a ma matrice\n    3 - Multiplier ma matrice par ce scalaire\n  Votre choix : ";
                        std::cin>>ctrl3;
                        switch ( ctrl3 )
                        {
                            case 1: // Ajouter un scalaire a la matrice : DONE
                            {
                                Matrice M=(*tab[matrice_choisie])+scalaire;
                                sauver_ou_afficher(conserver,M,tab,nombre);
                                break;
                            }

                            case 2: // Soustraire un scalaire a la matrice : DONE
                            {
                                Matrice M=(*tab[matrice_choisie])-scalaire;
                                sauver_ou_afficher(conserver,M,tab,nombre);
                                break;
                            }

                            case 3: // Multiplier la matrice par un scalaire : DONE
                            {
                                Matrice M=(*tab[matrice_choisie])*scalaire;
                                sauver_ou_afficher(conserver,M,tab,nombre);
                                break;
                            }
                            default:{}
                        }
                        break;
                    }

                    case 5: // Calculer une somme, soustraction ou produit par une autre matrice. DONE
                    {
                        // Ce case est FORTEMENT inspiré de celui du dessut ;)
                        std::cout<<"Choissisez maintenant votre deuxiemme matrice.\n";
                        int deuxiemme_matrice_choisie=choix_matrice(nombre);

                        std::cout<<"\n\n     **************************************************************************************************\n     ******************************* SOUS-SOUS MENU SCALAIRE ******************************************\n     **************************************************************************************************\n\n";

                         std::cout<<" Que souhaitez-vous faire de ces deux matrices : \n    1 - Les Additioner\n    2 - Soustraire la seconde a la première\n    3 - multiplier la 1ere par la seconde\n  Votre choix : ";
                        std::cin>>ctrl3;
                        switch ( ctrl3 )
                        {
                            case 1: // les additioner : DONE
                            {
                                Matrice M=(*tab[matrice_choisie])+(*tab[deuxiemme_matrice_choisie]);
                                sauver_ou_afficher(conserver,M,tab,nombre);
                                break;
                            }

                            case 2: // soustraire la seconde a la 1ere : DONE
                            {
                                Matrice M=(*tab[matrice_choisie])-(*tab[deuxiemme_matrice_choisie]);
                                sauver_ou_afficher(conserver,M,tab,nombre);
                                break;
                            }

                            case 3: // Multiplier la 1ere par la seconde. : DONE
                            {
                                Matrice M=(*tab[matrice_choisie])*(*tab[deuxiemme_matrice_choisie]);
                                sauver_ou_afficher(conserver,M,tab,nombre);
                                break;
                            }   
                            
                            default:{}
                        }
                        break;
                    }

                    case 6: // Calculer l'inverse : DONE
                    {
                        // Calculons l'inverse de la matrice choisie ( matrice_choisie ) :
                        sauver_ou_afficher(conserver,tab[matrice_choisie]->inverse_call(),tab,nombre); // La fonction inverse call est un HACK du sujet.
                        // Voir dans les CPP pour plus d'information.
                        break;
                    }

                    case 7: // Calculer la factorisation de cholesky : DONE
                    {
                        sauver_ou_afficher(conserver,tab[matrice_choisie]->cholesky_call(),tab,nombre);
                        // la fonction cholesky_call repond au meme besoin que la fonction inverse_call.
                    }

                    case 0: // Retour au menu principal : DONE
                    {
                        
                    }

                    default :{}
                }

                break;
            }

            case 4: // Afficher diverses propriétées sur une matrice : DONE
            {
                int matrice_choisie=choix_matrice(nombre);

                // Les propriétées affichables sont les suivantes :
                // Si la matrice est carrée : Son determinant, est-elle inversible, symetrique, semi-definie-positive.
                // Sinon, juste le dire.
                if ( tab[matrice_choisie]->getN() != tab[matrice_choisie]->getM() ) // La matrice n'est donc pas carrée
                {
                    std::cout<<"    Votre matrice n'etant pas carrée, son déterminant, le fait qu'elle soit symétrique, défini-positive ou inversible n'est pas vraiment définie. Désolé, c'est tout ce que vous saurez !";

                }
                else // La matrice est donc carrée.
                {
                    std::cout<<"    Le determinant de votre matrice est : "<<tab[matrice_choisie]->det()<<"\n";
    
                    if ( tab[matrice_choisie]->inversible() ) 
                    { 
                        std::cout<<"    Votre matrice est inversible\n"; 
                    }
                    else 
                    { 
                        std::cout<<"    Votre matrice n'est pas inversible\n"; 
                    }
                    if ( tab[matrice_choisie]->symetrique() ) 
                    { 
                        std::cout<<"    Votre matrice est symetrique\n";
                        if ( tab[matrice_choisie]->positive() )
                        {
                            std::cout<<"    Votre matrice est définie-positive\n";
                        }
                        else
                        {
                            std::cout<<"    Votre matrice n'est pas définie positive\n";
                        }
                    }
                    else 
                    { 
                        std::cout<<"    Votre matrice n'est pas symetrique ( et donc surement pas définie-positive )\n"; 
                    }
                }
                break;
            }

            case 5: // Supprimer une matrice : DONE
            {
                // On va ici proposer a l'utilisateur de supprimer une matrice.
                std::cout<<"Vous allez supprimer une matrice.\n    ";
                int matrice_choisie=choix_matrice(nombre);
                for (i=matrice_choisie;i<nombre;i++)
                {
                    tab[i]=tab[i+1]; // on ré-adresse seulement la fin du tableau : le compilateur se chargera d'apeller le destructeur.
                }
                nombre--;
                std::cout<<"    La matrice numéro "<<matrice_choisie+1<< " a bien été supprimer\n";
                if ( matrice_choisie != nombre) 
                {
                    std::cout<<"    Faite attention, comme la matrice supprimée n'est pas la dernière, les autres matrices ont été re-numérotée. Affichez-les pour vérifier.\n\n";   
                }
                break;
            }

            case 0: // Quiter le programme : DONE
            {
                std::cout<<"Merci d'avoir utiliser ce programme !"<<std::endl;
                break;
            }
        
            default :{}
        }

    }while ( ctrl !=0);

    // Liberation de l'espace mémoire avent de quitter le programme
    delete tab[0];
    delete [] tab;
    return 0;
}
