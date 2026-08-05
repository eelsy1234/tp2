/*********************************************************************
Date       : Août 2026
Fichier    : main.cpp

Ce programme implante la première partie du jeu d'Othello (jeu de base).
Le joueur humain (Rouge) affronte l'ordinateur (Bleu) qui joue ses coups
de façon totalement aléatoire parmi les coups valides.

Stratégie de résolution :
 1. Initialisation de l'interface graphique BGI et de l'othellier.
 2. Création de la liste chaînée de coups valides.
 3. Alternance des tours entre le joueur humain et l'ordinateur.
 4. Validation stricte des coups selon les 8 directions encadrantes.
 5. Gestion du passage de tour si aucun coup n'est possible.
 6. Détection automatique de la fin de partie et affichage du vainqueur.
*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "GRAPH_IO.h"
#include "T_coup.h"
#include "grille.h"
#include "liste_coups.h"

/*********************************************************************
* CONSTANTES
*********************************************************************/

/* Valeur booléenne pour VRAI. */
#define VRAI 1

/* Valeur booléenne pour FAUX. */
#define FAUX 0

/* Délai d'affichage des messages d'erreur en millisecondes. */
#define DELAI_MESSAGE_ERREUR 1200

/* Délai de réflexion simulé pour l'ordinateur en millisecondes. */
#define DELAI_REFLEXION_ORDI 800

/*********************************************************************
* DÉCLARATIONS DES FONCTIONS DU FICHIER PRINCIPAL
*********************************************************************/

/*
 LIRE_COUP_JOUEUR
 Va saisir un coup de l'utilisateur à l'aide de la fonction
 « saisir_coup_joueur() » de Graph_io.h.

 PARAMÈTRES :
  - le_coup : Pointeur de structure pour stocker le coup (type : t_coup *).

 VALEUR DE RETOUR : Aucune.
*/
void lire_coup_joueur(t_coup *le_coup);

/*
 GENERER_COUPS_VALIDES
 Va générer la « liste » de tous les coups valides à partir de
 l'othellier donné pour le joueur « jr » donné.

 PARAMÈTRES :
  - othellier : La grille de jeu (type : const t_grille).
  - jr        : Le joueur actif (type : t_joueur).
  - liste     : La liste chaînée devant recevoir les coups (type : t_listecoups).

 VALEUR DE RETOUR : Le nombre de coups valides générés (type : int).
*/
int generer_coups_valides(const t_grille othellier, t_joueur jr, t_listecoups liste);

/*
 CHOIX_COUP_ORDI
 Va choisir « le_coup » de l'ordinateur aléatoirement parmi tous
 les coups valides dans la « liste ».

 PARAMÈTRES :
  - liste   : La liste des coups valides (type : const t_listecoups).
  - taille  : Le nombre de coups valides disponibles (type : int).
  - le_coup : Pointeur où stocker le coup choisi (type : t_coup *).

 VALEUR DE RETOUR : Aucune.
*/
void choix_coup_ordi(const t_listecoups liste, int taille, t_coup *le_coup);

/*********************************************************************
* IMPLÉMENTATION DES FONCTIONS DU FICHIER PRINCIPAL
*********************************************************************/

void lire_coup_joueur(t_coup *le_coup)
{
	char *chaine_lue; /* Pointeur vers la chaîne saisie au clavier. */
	char char_ligne;  /* Caractère représentant la ligne. */
	char char_col;    /* Caractère représentant la colonne. */
	int num_ligne;    /* Numéro de ligne converti en entier. */
	int num_col;      /* Numéro de colonne converti en entier. */

	num_ligne = 0;
	num_col = 0;

	/* Appel de la fonction de saisie du module graphique. */
	chaine_lue = saisir_coup_joueur();

	/* Vérification que la chaîne lue contient au moins deux caractères. */
	if (chaine_lue != NULL && chaine_lue[0] != '\0' && chaine_lue[1] != '\0')
	{
		char_ligne = chaine_lue[0];
		char_col = chaine_lue[1];

		/* Conversion des caractères représentant les chiffres en entiers. */
		num_ligne = char_ligne - (int)'0';
		num_col = char_col - (int)'0';
	}

	/* Affectation des valeurs dans la structure du coup. */
	set_coup(le_coup, num_ligne, num_col);
}

int generer_coups_valides(const t_grille othellier, t_joueur jr, t_listecoups liste)
{
	int ran;           /* Indice de ligne de 1 à 8. */
	int col;           /* Indice de colonne de 1 à 8. */
	t_coup coup_teste; /* Structure de coup temporaire pour le test. */

	/* Nettoyage préalable de la liste de coups. */
	vider_liste_coups(liste);

	/* Balayage de toutes les cases de l'othellier. */
	for (ran = MIN_COORD_CLIENT; ran <= MAX_COORD_CLIENT; ++ran)
	{
		for (col = MIN_COORD_CLIENT; col <= MAX_COORD_CLIENT; ++col)
		{
			set_coup(&coup_teste, ran, col);

			/* Si le coup est valide, on l'ajoute à la liste chaînée. */
			if (valider_coup(othellier, jr, coup_teste) == COUP_VALIDE)
			{
				ajouter_coup(liste, coup_teste);
			}
		}
	}

	/* Retourne la taille de la liste complétée. */
	return liste->taille;
}

void choix_coup_ordi(const t_listecoups liste, int taille, t_coup *le_coup)
{
	int index_aleatoire; /* Indice tiré au hasard dans la liste. */

	if (liste != NULL && taille > 0)
	{
		/* Sélection aléatoire d'un indice entre 0 et taille - 1. */
		index_aleatoire = rand() % taille;

		/* Extraction du coup correspondant. */
		obtenir_coup_index(liste, index_aleatoire, le_coup);
	}
}

/*********************************************************************
* PROGRAMME PRINCIPAL
*********************************************************************/
int main(void)
{
	t_grille othellier;                 /* Plateau de jeu 8x8. */
	t_listecoups liste_coups_valides;   /* Liste des coups valides du joueur courant. */
	t_listecoups liste_coups_adverse;   /* Liste des coups valides de l'adversaire. */
	t_coup coup_courant;                /* Le coup joué pendant le tour. */
	t_joueur joueur_actif;              /* Le joueur dont c'est le tour de jouer. */
	t_joueur joueur_adverse;            /* Le joueur en attente. */
	t_joueur gagnant;                   /* Le vainqueur final de la partie. */
	int nb_coups_actifs;                /* Nombre de coups valides du joueur actif. */
	int nb_coups_adversaire;            /* Nombre de coups valides de l'adversaire. */
	int saisie_valide;                  /* Drapeau de validation de la saisie. */
	int partie_en_cours;                /* Drapeau de la boucle de jeu. */
	int ran_ordi;                       /* Rangée du coup choisi par l'ordinateur. */
	int col_ordi;                       /* Colonne du coup choisi par l'ordinateur. */

	/* Initialisation du générateur de nombres aléatoires. */
	srand((unsigned int)time(NULL));

	/* Tentative d'initialisation de l'interface graphique. */
	if (initialiser_interface_graphique())
	{
		/* Affichage du titre du jeu et de la plaque vide. */
		afficher_titre();
		afficher_plaque_vide();

		/* Initialisation des jetons de départ sur l'othellier. */
		initialiser_jeu(othellier);

		/* Création des structures de listes de coups. */
		liste_coups_valides = creer_liste_coups();
		liste_coups_adverse = creer_liste_coups();

		/* Le joueur 2 (Rouge / Humain) débute la partie. */
		joueur_actif = JOUEUR2;
		partie_en_cours = VRAI;

		/* Boucle principale du déroulement de la partie d'Othello. */
		while (partie_en_cours == VRAI)
		{
			joueur_adverse = (joueur_actif == JOUEUR1) ? JOUEUR2 : JOUEUR1;

			/* Calcul des coups valides pour les deux joueurs. */
			nb_coups_actifs = generer_coups_valides(othellier,
				joueur_actif, liste_coups_valides);
			nb_coups_adversaire = generer_coups_valides(othellier,
				joueur_adverse, liste_coups_adverse);

			/* Si aucun des deux joueurs ne peut jouer, la partie est terminée. */
			if (nb_coups_actifs == 0 && nb_coups_adversaire == 0)
			{
				partie_en_cours = FAUX;
			}
			else if (nb_coups_actifs == 0)
			{
				/* Le joueur actif ne peut pas jouer : il saute son tour. */
				if (joueur_actif == JOUEUR2)
				{
					afficher_message("Vous n'avez aucun coup valide. Tour passe !");
				}
				else
				{
					afficher_message("L'ordinateur n'a aucun coup valide. Tour passe !");
				}

				effectuer_delai(DELAI_MESSAGE_ERREUR);

				/* Passage du tour à l'adversaire. */
				joueur_actif = joueur_adverse;
			}
			else
			{
				/* Traitement du tour selon le joueur actif. */
				if (joueur_actif == JOUEUR2)
				{
					/* Tour du joueur humain (Rouge). */
					saisie_valide = FAUX;

					while (saisie_valide == FAUX)
					{
						afficher_message("A votre tour (ROUGE). Entrez votre coup (ex: 43)...");
						lire_coup_joueur(&coup_courant);

						/* Validation du coup saisi. */
						if (valider_coup(othellier, JOUEUR2, coup_courant) == COUP_VALIDE)
						{
							saisie_valide = VRAI;
						}
						else
						{
							afficher_message("Coup invalide ! Veuillez recommencer...");
							effectuer_delai(DELAI_MESSAGE_ERREUR);
						}
					}

					/* Exécution du coup du joueur. */
					jouer_le_coup(othellier, JOUEUR2, coup_courant);
				}
				else
				{
					/* Tour de l'ordinateur (Bleu). */
					afficher_message("L'ordinateur (BLEU) reflechit...");
					effectuer_delai(DELAI_REFLEXION_ORDI);

					/* Sélection aléatoire d'un coup parmi la liste des coups valides. */
					choix_coup_ordi(liste_coups_valides, nb_coups_actifs, &coup_courant);

					/* Clignotement du coup choisi avant d'effectuer l'action. */
					get_coup(&coup_courant, &ran_ordi, &col_ordi);
					faire_clignoter_jeton(ran_ordi - 1, col_ordi - 1, JOUEUR1);

					/* Exécution du coup de l'ordinateur. */
					jouer_le_coup(othellier, JOUEUR1, coup_courant);
				}

				/* Alternance des joueurs pour le tour suivant. */
				joueur_actif = joueur_adverse;
			}
		}

		/* Détermination et affichage du vainqueur. */
		gagnant = determiner_gagnant(othellier);

		if (gagnant == JOUEUR2)
		{
			afficher_message("PARTIE FINIE ! Bravo, vous avez gagne ! Appuyez une touche...");
		}
		else if (gagnant == JOUEUR1)
		{
			afficher_message("PARTIE FINIE ! L'ordinateur a gagne. Appuyez une touche...");
		}
		else
		{
			afficher_message("PARTIE FINIE ! Match nul ! Appuyez une touche...");
		}

		/* Attente de la saisie d'une touche par l'utilisateur. */
		effectuer_pause();

		/* Destruction et libération des listes dynamiques. */
		detruire_liste_coups(&liste_coups_valides);
		detruire_liste_coups(&liste_coups_adverse);

		/* Fermeture propre de la fenêtre graphique BGI. */
		fermer_interface_graphique();
	}

	return 0;
}
