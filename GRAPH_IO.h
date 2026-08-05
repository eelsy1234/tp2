/********************************************************************/
/* Par        : Frederick Henri                                     */
/* Revise par : Eric Thé                                            */
/* Fichier    : GRAPH_IO.H                                          */
/*                                                                  */
/* Ce module implante des fonctions graphiques pour jouer au        */
/* Othello.                                                         */
/* NOTE: Ce module sera fourni aux élèves.                          */
/********************************************************************/

#if !defined(__GRAPH_IO__)
#define __GRAPH_IO__

/********************************************************************/
/*					DEFINITIONS DE CONSTANTES		                */
/********************************************************************/

/* Les couleurs disponibles a l'usager.								*/
enum couleurs {
	NOIR, BLEU, VERT, BLEU_CYAN, ROUGE, ROUGE_MAGENTA, BRUN, GRIS_PALE, GRIS_FONCE,
	BLEU_CLAIR, VERT_PALE, BLEU_CYAN_CLAIR, ROUGE_CLAIR, ROUGE_MAGENTA_CLAIR, JAUNE, 
	BLANC
};

/* Constantes necessaires a l'introduction.							*/
static const char * const NOM_JEU = "OTHELLO";

/* Constantes necessaires a l'affichage du jeu (cases et bordure).	*/
static const enum couleurs COULEUR_DE_FOND = VERT_PALE;
static const enum couleurs COULEUR_BORDURE = NOIR;
static const enum couleurs COULEUR_OMBRE   = GRIS_FONCE;
static const enum couleurs COULEUR_CASE	   = BLANC;

#define NB_LIGNES_PLAQUE	8
#define NB_COLONNES_PLAQUE	8
static const int ESPACE_TEXTE_BAS	= 25;   /* En pixels */
static const int TAILLE_CASE		= 48;	/* En pixels */
static const int TAILLE_BORDURE		=  3;   /* En pixels */
static const int TAILLE_OMBRE		=  4;	/* En pixels */


/* Constantes necessaires a l'affichage des jetons.					*/
typedef enum {CASE_VIDE, JOUEUR1, JOUEUR2} t_joueur;

static const enum couleurs COULEUR_JETON_JOUEUR1 = BLEU;
static const enum couleurs COULEUR_JETON_JOUEUR2 = ROUGE;
static const enum couleurs COULEUR_CONTOUR_JETON = NOIR;
static const double TAILLE_RAYON = 0.4;		/* [0.1, 0.5]			*/

/* Constantes necessaires au clignotement des jetons.				*/
static const int NB_CLIGNOTEMENTS = 5;
static const unsigned int DELAI_CLIGNOTEMENT = 200;	/* En ms */

/* Constantes necessaires a la saisie des coups.				  */
static const char * MOT_LIGNE   = "Ligne : ";
static const char * MOT_COLONNE = "Colonne : ";


/********************************************************************/
/*					DECLARATIONS DE FONCTIONS	                    */
/********************************************************************/
int initialiser_interface_graphique(void);
/* Cette fonction demarre le mode graphique.						*/
/* Elle retourne 1 en cas de succes, 0 sinon.						*/

void afficher_titre(void);
/* Cette fonction permet d'afficher le titre du jeu.			*/
/* ATTENTION : La fonction initialiser_interface_graphique doit	*/
/*			   prealablement avoir ete appele avec succes.		*/

void afficher_plaque_vide(void);
/* Cette fonction permet d'afficher la plaque de jeu vide.		*/
/* ATTENTION : La fonction initialiser_interface_graphique doit	*/
/*			   prealablement avoir ete appele avec succes.		*/

void afficher_jeton(int ligne, int colonne, t_joueur joueur);
/* Cette fonction affiche un jeton du joueur specifie dans la case	*/
/* demandee.												        */
/* PARAMETRES :												        */
/*		- ligne   : La ligne de la case ([0, NB_LIGNES_PLAQUE[.	    */
/*		- colonne : La colonne de la case ([0, NB_COLONNES_PLAQUE[. */
/*		- joueur  : Le joueur a qui appartient le jeton.		    */
/* ATTENTION : Aucune validation des parametres n'est effectuee.    */
/* ATTENTION : La fonction initialiser_interface_graphique doit	    */
/*			   prealablement avoir ete appele avec succes.		    */

void faire_clignoter_jeton(int ligne, int colonne, t_joueur joueur);
/* Cette fonction fait clignoter un jeton du joueur specifie dans   */
/* la case demandee. Suite au clignotement, le jeton reste affiche.	*/
/* PARAMETRES :							                            */
/*		- ligne   : La ligne de la case ([0, NB_LIGNES_PLAQUE[.	    */
/*		- colonne : La colonne de la case ([0, NB_COLONNES_PLAQUE[. */
/*		- joueur  : Le joueur a qui appartient le jeton.		    */
/* ATTENTION : Aucune validation des parametres n'est effectuee.    */
/* ATTENTION : La fonction initialiser_interface_graphique doit	    */
/*			   prealablement avoir ete appele avec succes.		    */

void vider_case(int ligne, int colonne);
/* Cette fonction vide la case specifiee.				            */
/* PARAMETRES :											            */
/*		- ligne   : La ligne de la case ([0, NB_LIGNES_PLAQUE[.	    */
/*		- colonne : La colonne de la case ([0, NB_COLONNES_PLAQUE[.	*/
/* ATTENTION : Aucune validation des parametres n'est effectuee.	*/
/* ATTENTION : La fonction initialiser_interface_graphique doit		*/
/*			   prealablement avoir ete appele avec succes.	        */

char * saisir_coup_joueur(void);
/* Cette fonction retourne une chaine de caractere contenant le		*/
/* coup du joueur.						                            */
/* ATTENTION : Aucune validation de ce qui est entre au clavier		*/
/*			   n'est effectue.				                        */
/* ATTENTION : La fonction initialiser_interface_graphique doit		*/
/*			   prealablement avoir ete appele avec succes.          */

void afficher_message(const char * message);
/* Cette fonction affiche un message dans le bas de l'ecran.	    */
/* ATTENTION : La fonction initialiser_interface_graphique doit		*/
/*			   prealablement avoir ete appele avec succes.		    */

void fermer_interface_graphique(void);
/* Cette fonction termine le mode graphique.					    */
/* ATTENTION : La fonction initialiser_interface_graphique doit		*/
/*			   prealablement avoir ete appele avec succes.		    */

void effectuer_delai(unsigned int millisecondes);
/* Cette fonction effectue un delai d'une duree de millisecondes.	*/
/* PARAMETRES :								                        */
/*			- millisecondes : La duree du delai (en ms.).           */
/* ATTENTION : Il n'est pas possible de faire des delais tres       */
/*			   precis (ex. : 3 ms).					                */

void effectuer_pause(void);
/* Cette fonction attend l'entree d'un caractere au clavier.	    */

#endif