/********************************************************************/
/* Par        : Frederick Henri			                            */
/* Revise par : Eric Thé                                            */
/* Fichier    : GRAPH_IO.CPP                                        */
/*                                                                  */
/* Ce module implante des fonctions graphiques pour jouer au        */
/* Othello.                                                         */
/* NOTE: Ce module sera fourni aux élèves.                          */
/********************************************************************/

#include "graph_io.h"
#include "WinBGIm.h"

/********************************************************************/
/*				DEFINITIONS DE VARIABLES GLOBALES PRIVÉES           */
/********************************************************************/
static int largeur_ecran;
static int hauteur_ecran;
static int debut_plaque_x;
static int debut_plaque_y;


/********************************************************************/
/*				DEFINITIONS DE FONCTIONS PRIVEES                    */
/********************************************************************/
static int coord_x_case(int ligne, int colonne)
/* Cette fonction retourne la coordonnee x du debut d'une case.		*/
{
	return debut_plaque_x + colonne * (TAILLE_CASE + TAILLE_BORDURE);
}

/********************************************************************/
static int coord_y_case(int ligne, int colonne)
/* Cette fonction retourne la coordonnee y du debut d'une case.		*/
{
	return debut_plaque_y + ligne * (TAILLE_CASE + TAILLE_BORDURE);
}

/********************************************************************/
static void dessiner_rectangle(int x1, int y1, int x2, int y2,
							   int couleur, int epaisseur)
/* Cette fonction dessine un rectangle de la couleur demandee et	*/
/* aux coordonnees specifiees.										*/
{
	/* On affiche le contour de la case.						*/
	setcolor(couleur);
	for (int i = 0; i < epaisseur; ++i)
		rectangle(x1 + i, y1 + i, x2 - i, y2 - i);
}

/********************************************************************/
static void dessiner_case(int ligne, int colonne)
/* Dessine une case.							    */
/* ATTENTION :	0 <= ligne   <= NB_LIGNES_PLAQUE	*/
/*            0 <= colonne <= NB_COLONNES_PLAQUE	*/
{	int x = coord_x_case(ligne, colonne);
	int y = coord_y_case(ligne, colonne);

	/* On affiche le contour de la case.							*/
	dessiner_rectangle(x, y, x + TAILLE_CASE + 2 * TAILLE_BORDURE - 1,
						     y + TAILLE_CASE + 2 * TAILLE_BORDURE - 1,
						     COULEUR_BORDURE, TAILLE_BORDURE);

	/* On affiche l'interieur de la case.							*/
	setcolor(COULEUR_CASE);
	setfillstyle(SOLID_FILL, COULEUR_CASE);
	bar(x + TAILLE_BORDURE, y + TAILLE_BORDURE,
		x + TAILLE_BORDURE + TAILLE_CASE -1,
		y + TAILLE_BORDURE + TAILLE_CASE -1);
}

/********************************************************************/
static void ajouter_ombre_a_la_plaque(void)
{	int fin_plaque_x = coord_x_case(NB_LIGNES_PLAQUE, NB_COLONNES_PLAQUE) + TAILLE_BORDURE;
	int fin_plaque_y = coord_y_case(NB_LIGNES_PLAQUE, NB_COLONNES_PLAQUE) + TAILLE_BORDURE;

	setcolor(COULEUR_OMBRE);
	for (int i = 0; i < TAILLE_OMBRE; ++i){
		line(debut_plaque_x + i, fin_plaque_y + i, fin_plaque_x + i + 1, fin_plaque_y + i);
		line(fin_plaque_x + i, debut_plaque_y + i, fin_plaque_x + i, fin_plaque_y + i);
	}
}


/********************************************************************/
/*				DEFINITIONS DE FONCTIONS PUBLIQUES                  */
/********************************************************************/
int initialiser_interface_graphique(void)
{	// On tente d'initialiser le mode graphique.
	int gdriver = DETECT, gmode;

	initgraph(&gdriver, &gmode, "");    

	if (graphresult() != grOk)	return 0;

	largeur_ecran = getmaxx() + 1;
	hauteur_ecran = getmaxy() + 1;
	debut_plaque_x = (largeur_ecran - NB_COLONNES_PLAQUE * 
		             (TAILLE_CASE + TAILLE_BORDURE) - TAILLE_BORDURE) / 2;
	debut_plaque_y = (hauteur_ecran - NB_LIGNES_PLAQUE * 
		             (TAILLE_CASE + TAILLE_BORDURE) - TAILLE_BORDURE - ESPACE_TEXTE_BAS) / 2;

	return 1;
}

/********************************************************************/
void afficher_titre(void)
{
	// On determine les caracteristiques du texte.
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(ROUGE);

	settextstyle(6, HORIZ_DIR, 8);
	outtextxy(largeur_ecran/2, hauteur_ecran/2, NOM_JEU);
	effectuer_delai(2000);    //pour 2 secondes
	
	//ici il est important de remettre les parametres de texte par defaut!!
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(BLANC);
}


/********************************************************************/
void afficher_plaque_vide(void)
{	int  i, j;		/* Pour iterer sur les lignes et les colonnes.	*/
	char buff[3];

	/* On applique la couleur de fond.								*/
	setfillstyle(SOLID_FILL, COULEUR_DE_FOND);
	bar(0, 0, largeur_ecran, hauteur_ecran);

    settextstyle(6, HORIZ_DIR, 3);
	/* Ecrire numéros des lignes */
    for (i = 0; i < NB_LIGNES_PLAQUE; ++i) {
	  itoa(i+1, buff, 10);
	  outtextxy(debut_plaque_x - textwidth("0") - 5, coord_y_case(i,-1) + TAILLE_CASE/3, 
		        buff);
    }

    /* Ecrire numéros des colonnes */
    for (j = 0; j < NB_COLONNES_PLAQUE; ++j) {
      itoa(j+1, buff, 10);
	  outtextxy(coord_x_case(-1, j) + TAILLE_CASE/3, debut_plaque_y - textheight("0") - 5, 
		        buff);
    }

	/* On dessine les cases */
	for (i = 0; i < NB_LIGNES_PLAQUE; ++i)
		for (j = 0; j < NB_COLONNES_PLAQUE; ++j)
			dessiner_case(i, j);

	/* On ajoute l'ombre de la plaque */
	ajouter_ombre_a_la_plaque();
}

/********************************************************************/
void afficher_jeton(int ligne, int colonne, t_joueur joueur)
{	int x, y;		/* Le centre du jeton.							*/

	/* On calcule la coordonnee du jeton.						*/
	x = coord_x_case(ligne, colonne) + (2 * TAILLE_BORDURE + TAILLE_CASE) / 2;
	y = coord_y_case(ligne, colonne) + (2 * TAILLE_BORDURE + TAILLE_CASE) / 2;

	/* On ajuste la couleur du jeton.								*/
	if (joueur == JOUEUR1){
		setcolor(COULEUR_JETON_JOUEUR1);
		setfillstyle(SOLID_FILL, COULEUR_JETON_JOUEUR1);
	}
	else{
		setcolor(COULEUR_JETON_JOUEUR2);
		setfillstyle(SOLID_FILL, COULEUR_JETON_JOUEUR2);
	}

	/* On affiche le jeton.											*/
	pieslice(x, y, 0, 360, (int)(TAILLE_RAYON * TAILLE_CASE));

	/* On affiche un contour.										*/
	setcolor(COULEUR_CONTOUR_JETON);
	circle(x, y, (int)(TAILLE_RAYON * TAILLE_CASE));
}

/********************************************************************/
void faire_clignoter_jeton(int ligne, int colonne, t_joueur joueur)
{
	for (int i = 0; i < NB_CLIGNOTEMENTS; ++i){
		vider_case(ligne, colonne);
		effectuer_delai(DELAI_CLIGNOTEMENT);
		afficher_jeton(ligne, colonne, joueur);
		effectuer_delai(DELAI_CLIGNOTEMENT);
	}
}

/********************************************************************/
void vider_case(int ligne, int colonne)
{
	dessiner_case(ligne, colonne);
}

/********************************************************************/
char * saisir_coup_joueur(void)
{	static char reponse[3] = {0};

	/* On efface l'espace de saisie.								*/
	setfillstyle(SOLID_FILL, BLACK);
	bar(0, hauteur_ecran - ESPACE_TEXTE_BAS - 1, largeur_ecran, hauteur_ecran);

	/* On ajuste le format du texte.								*/
	setcolor(WHITE);
	settextstyle(0, HORIZ_DIR, 2);  

	/* On affiche les lettres a chaque lecture.			*/
	outtextxy(5, hauteur_ecran - ESPACE_TEXTE_BAS, MOT_LIGNE);
	reponse[0] = getch_graph();
	reponse[1] = '\0';

	outtextxy(5 + textwidth(MOT_LIGNE), hauteur_ecran - ESPACE_TEXTE_BAS,	reponse);

	outtextxy(20 + textwidth(MOT_LIGNE), hauteur_ecran - ESPACE_TEXTE_BAS, ", ");

	outtextxy(20 + textwidth(MOT_LIGNE) + textwidth(", "), hauteur_ecran - ESPACE_TEXTE_BAS,
						MOT_COLONNE);

	reponse[1] = getch_graph();

	outtextxy(20 + textwidth(MOT_LIGNE) + textwidth(", ") + textwidth(MOT_COLONNE), 
	          hauteur_ecran - ESPACE_TEXTE_BAS,	reponse + 1);

	return reponse;
}

/********************************************************************/
void afficher_message(const char * message)
{
	/* On efface l'espace de saisie.								*/
	setfillstyle(SOLID_FILL, BLACK);
	bar(0, hauteur_ecran - ESPACE_TEXTE_BAS - 1, largeur_ecran, hauteur_ecran);

	/* On ajuste le format du texte.								*/
	setcolor(WHITE);
	settextstyle(0, HORIZ_DIR, 2); 

	/* On affiche les lettres a chaque lecture.			*/
	outtextxy(5, hauteur_ecran - ESPACE_TEXTE_BAS, message);
}

/********************************************************************/
void fermer_interface_graphique(void)
{
	closegraph();
}

/********************************************************************/
void effectuer_delai(unsigned int millisecondes)
{
	delay_graph(millisecondes);
}

/********************************************************************/
void effectuer_pause(void)
{
	getch_graph();
}

/********************************************************************/
/********************************************************************/