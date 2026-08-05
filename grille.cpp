/*********************************************************************
Date       : Août 2026
Fichier    : grille.cpp

Ce module implante la logique du plateau de jeu Othello :
initialisation, validation des coups et mise à jour de la grille.
*********************************************************************/

#include "grille.h"

/*********************************************************************
* CONSTANTES INTERNES AU MODULE
*********************************************************************/

/* Déplacements en ligne pour les 8 directions cardinales et diagonales. */
static const int D_LIGNE[NB_DIRECTIONS] = { -1, -1, -1, 0, 0, 1, 1, 1 };

/* Déplacements en colonne pour les 8 directions cardinales et diagonales. */
static const int D_COLONNE[NB_DIRECTIONS] = { -1, 0, 1, -1, 1, -1, 0, 1 };

/*********************************************************************
* FONCTION PRIVÉE : est_dans_limites
*********************************************************************/
/*
 EST_DANS_LIMITES
 Vérifie si les indices spécifiés sont situés à l'intérieur de la grille 8x8.
*/
static int est_dans_limites(int ligne, int colonne)
{
	return (ligne >= 0 && ligne < NB_LIGNES_PLAQUE &&
		colonne >= 0 && colonne < NB_COLONNES_PLAQUE);
}

/*********************************************************************
* FONCTION : initialiser_jeu
*********************************************************************/
int initialiser_jeu(t_grille othellier)
{
	int lig; /* Indice de parcours des lignes. */
	int col; /* Indice de parcours des colonnes. */

	/* Re-initialisation de toutes les cases à l'état vide. */
	for (lig = 0; lig < NB_LIGNES_PLAQUE; ++lig)
	{
		for (col = 0; col < NB_COLONNES_PLAQUE; ++col)
		{
			othellier[lig][col] = CASE_VIDE;
		}
	}

	/* Coordonnées de départ :
	   - Bleu  (JOUEUR1) en (4,4) et (5,5) -> indices 3,3 et 4,4
	   - Rouge (JOUEUR2) en (4,5) et (5,4) -> indices 3,4 et 4,3
	*/
	othellier[3][3] = JOUEUR1;
	othellier[4][4] = JOUEUR1;
	othellier[3][4] = JOUEUR2;
	othellier[4][3] = JOUEUR2;

	/* Affichage des pièces initiales sur l'interface graphique. */
	afficher_jeton(3, 3, JOUEUR1);
	afficher_jeton(4, 4, JOUEUR1);
	afficher_jeton(3, 4, JOUEUR2);
	afficher_jeton(4, 3, JOUEUR2);

	return NB_PIECES_DEPART;
}

/*********************************************************************
* FONCTION : determiner_gagnant
*********************************************************************/
t_joueur determiner_gagnant(const t_grille othellier)
{
	int lig;                  /* Indice de ligne pour le comptage. */
	int col;                  /* Indice de colonne pour le comptage. */
	int nb_jetons_joueur1;    /* Compteur des pièces de JOUEUR1 (Bleu). */
	int nb_jetons_joueur2;    /* Compteur des pièces de JOUEUR2 (Rouge). */
	t_joueur resultat_gagnant;/* Le joueur victorieux ou CASE_VIDE. */

	nb_jetons_joueur1 = 0;
	nb_jetons_joueur2 = 0;

	/* Comptage des jetons sur l'ensemble de l'othellier. */
	for (lig = 0; lig < NB_LIGNES_PLAQUE; ++lig)
	{
		for (col = 0; col < NB_COLONNES_PLAQUE; ++col)
		{
			if (othellier[lig][col] == JOUEUR1)
			{
				nb_jetons_joueur1 = nb_jetons_joueur1 + 1;
			}
			else if (othellier[lig][col] == JOUEUR2)
			{
				nb_jetons_joueur2 = nb_jetons_joueur2 + 1;
			}
		}
	}

	/* Comparaison pour déterminer le gagnant. */
	if (nb_jetons_joueur1 > nb_jetons_joueur2)
	{
		resultat_gagnant = JOUEUR1;
	}
	else if (nb_jetons_joueur2 > nb_jetons_joueur1)
	{
		resultat_gagnant = JOUEUR2;
	}
	else
	{
		resultat_gagnant = CASE_VIDE;
	}

	return resultat_gagnant;
}

/*********************************************************************
* FONCTION : valider_coup
*********************************************************************/
int valider_coup(const t_grille othellier, t_joueur jr, t_coup le_coup)
{
	int ran;               /* Rangée de la case du coup (1-8). */
	int col;               /* Colonne de la case du coup (1-8). */
	int idx_lig;           /* Indice de ligne 0-7. */
	int idx_col;           /* Indice de colonne 0-7. */
	int coup_est_valide;   /* Indicateur de validité du coup. */
	int idx_dir;           /* Indice de direction. */
	t_joueur jr_adverse;   /* Couleur du joueur adverse. */
	int r;                 /* Indice de ligne de balayage. */
	int c;                 /* Indice de colonne de balayage. */
	int nb_pions_adverses; /* Nombre de pièces adverses alignées. */

	get_coup(&le_coup, &ran, &col);

	/* Conversion des coordonnées utilisateur [1,8] en indices du tableau [0,7]. */
	idx_lig = ran - 1;
	idx_col = col - 1;

	/* Un coup doit être posé sur une case valide et vide. */
	if (!est_dans_limites(idx_lig, idx_col) || othellier[idx_lig][idx_col] != CASE_VIDE)
	{
		return COUP_INVALID;
	}

	/* Détermination du joueur adverse. */
	jr_adverse = (jr == JOUEUR1) ? JOUEUR2 : JOUEUR1;
	coup_est_valide = COUP_INVALID;

	/* Examen des 8 directions autour de la case choisie. */
	idx_dir = 0;
	while (idx_dir < NB_DIRECTIONS && coup_est_valide == COUP_INVALID)
	{
		r = idx_lig + D_LIGNE[idx_dir];
		c = idx_col + D_COLONNE[idx_dir];
		nb_pions_adverses = 0;

		/* Déplacement continu tant que l'on rencontre des jetons de l'adversaire. */
		while (est_dans_limites(r, c) && othellier[r][c] == jr_adverse)
		{
			nb_pions_adverses = nb_pions_adverses + 1;
			r = r + D_LIGNE[idx_dir];
			c = c + D_COLONNE[idx_dir];
		}

		/* Le coup est valide si la séquence se termine par un jeton du joueur actif. */
		if (nb_pions_adverses > 0 && est_dans_limites(r, c) && othellier[r][c] == jr)
		{
			coup_est_valide = COUP_VALIDE;
		}

		idx_dir = idx_dir + 1;
	}

	return coup_est_valide;
}

/*********************************************************************
* FONCTION : jouer_le_coup
*********************************************************************/
void jouer_le_coup(t_grille othellier, t_joueur jr, t_coup le_coup)
{
	int ran;                /* Rangée du coup (1-8). */
	int col;                /* Colonne du coup (1-8). */
	int idx_lig;            /* Indice de ligne 0-7. */
	int idx_col;            /* Indice de colonne 0-7. */
	int idx_dir;            /* Indice de direction. */
	t_joueur jr_adverse;    /* Couleur de l'adversaire. */
	int r;                  /* Indice de ligne de balayage. */
	int c;                  /* Indice de colonne de balayage. */
	int r_fin;              /* Indice de ligne de fin d'encadrement. */
	int c_fin;              /* Indice de colonne de fin d'encadrement. */
	int nb_pions_adverses;  /* Compteur de pièces adverses sur la ligne. */

	get_coup(&le_coup, &ran, &col);

	idx_lig = ran - 1;
	idx_col = col - 1;

	/* Pose de la pièce du joueur sur la case ciblée. */
	othellier[idx_lig][idx_col] = jr;
	afficher_jeton(idx_lig, idx_col, jr);

	jr_adverse = (jr == JOUEUR1) ? JOUEUR2 : JOUEUR1;

	/* Analyse des 8 directions pour retourner les pièces encadrées. */
	for (idx_dir = 0; idx_dir < NB_DIRECTIONS; ++idx_dir)
	{
		r_fin = idx_lig + D_LIGNE[idx_dir];
		c_fin = idx_col + D_COLONNE[idx_dir];
		nb_pions_adverses = 0;

		/* Repérage des jetons adverses consécutifs. */
		while (est_dans_limites(r_fin, c_fin) && othellier[r_fin][c_fin] == jr_adverse)
		{
			nb_pions_adverses = nb_pions_adverses + 1;
			r_fin = r_fin + D_LIGNE[idx_dir];
			c_fin = c_fin + D_COLONNE[idx_dir];
		}

		/* Si encadrement valide, retournement de toutes les pièces intermédiaires. */
		if (nb_pions_adverses > 0 && est_dans_limites(r_fin, c_fin) &&
			othellier[r_fin][c_fin] == jr)
		{
			r = idx_lig + D_LIGNE[idx_dir];
			c = idx_col + D_COLONNE[idx_dir];

			while (r != r_fin || c != c_fin)
			{
				othellier[r][c] = jr;
				afficher_jeton(r, c, jr);
				r = r + D_LIGNE[idx_dir];
				c = c + D_COLONNE[idx_dir];
			}
		}
	}
}
