/*==========================================================*/
/*  TEST_GRAPH.CPP                                          */
/*  Ce programme offre un exemple tr�s simple d'utilisation */
/*  de la librairie d'affichage du jeu Othello.             */
/*  Permet aux �tudiants d'aboder rapidement le TP#3.       */
/*==========================================================*/

/*==========================================================*/
/* LIBRAIRIES INCLUSES                                      */
/*==========================================================*/
#include <stdlib.h>
#include <stdio.h>
#include "graph_io.h"    //la librairie d'affichage !!

/*==========================================================*/
/* LES CONSTANTES                                           */
/*==========================================================*/
#define VRAI 1
#define FAUX 0

/*==========================================================*/

int main(void){

  /* La fonction "saisir_coup_joueur" de la librairie retourne */
  /* une cha�ne de caract�res, on a besoin d'une variable pour */
  /* la saisir. On va extraire ensuite les #ligne et #colonne. */
  char * lecture_coup;	

  /* forme transitoire de ligne et colonne  */ 
  /* on passera de la string � un seul char */ 
  char chlig, chcol;
	
  /* puis on d�composera en ligne et colonne */
  /* comme entiers pour placer un jeton      */
  int lig, col;
  int lec_valide = FAUX;   /* drapeau de validation */

  if (initialiser_interface_graphique()) {   /* valider le "initgraph" */
     /* initialiser de la plaque */	
     afficher_plaque_vide();

     /* on pose deux jetons, les positions sont des valeurs dans [0,7].  */
	 faire_clignoter_jeton(2, 2, JOUEUR2);   /* JOUEUR2 == 2 (le joueur) */
	 afficher_jeton(5, 2, JOUEUR1);          /* JOUEUR1 == 1 (l'ordinateur) */
		 
     while (lec_valide == FAUX){
	    /* obtention de la string qui indique la position � jouer. eg. "36" */
	    lecture_coup = saisir_coup_joueur();
	
        chlig = lecture_coup[0];   /* extraire le no. de ligne. eg. '3' */
        chcol = lecture_coup[1];   /* extraire le no. de col. eg. '6'   */

        /* conversion des caract�res en entier    */
        /* le client donne ses valeurs dans [1,8] */
        lig = chlig - (int)'0';
        col = chcol - (int)'0';
 
		if ((col>=1 && col <=8) && (lig>=1 && lig <=8)) {
	        /* ligne et colonne doivent �tre dans [0,7] pour  */
	        /* l'affichage du jeton, on applique donc -1.     */				
	        afficher_jeton(lig-1, col-1, JOUEUR2);
	        lec_valide = VRAI;
	    }

	    if(lec_valide == FAUX){
	        afficher_message("votre entr�e n'est pas valide ...");
	        effectuer_delai(1000);				
	    }
     }

     afficher_message("C'est termin� ... Appuyez une touche!");
     effectuer_pause();             /* comme faire: system("pause") */

     fermer_interface_graphique();  /* IMPORTANT!! */
  }
}