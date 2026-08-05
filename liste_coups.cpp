/*********************************************************************
Date       : Août 2026
Fichier    : liste_coups.cpp

Ce module implante les fonctions de gestion d'une liste chaînée simple
contenant des coups de jeu pour Othello.
*********************************************************************/

#include <stdlib.h>
#include "liste_coups.h"

/*********************************************************************
* FONCTION : creer_liste_coups
*********************************************************************/
t_listecoups creer_liste_coups(void)
{
	t_listecoups nouvelle_liste; /* Pointeur vers la nouvelle structure de liste. */

	/* Allocation dynamique de la structure de contrôle de la liste. */
	nouvelle_liste = (t_listecoups)malloc(sizeof(struct t_liste_coups));

	/* Verification de l'allocation mémoire. */
	if (nouvelle_liste != NULL)
	{
		/* Initialisation des champs de la liste vacante. */
		nouvelle_liste->premier = NULL;
		nouvelle_liste->dernier = NULL;
		nouvelle_liste->taille = 0;
	}

	return nouvelle_liste;
}

/*********************************************************************
* FONCTION : ajouter_coup
*********************************************************************/
void ajouter_coup(t_listecoups liste, t_coup coup)
{
	t_noeud_coup *nouveau_noeud; /* Pointeur vers le nouveau nœud à insérer. */

	/* Vérification que la liste passée en paramètre n'est pas nulle. */
	if (liste != NULL)
	{
		/* Allocation dynamique du nouveau nœud. */
		nouveau_noeud = (t_noeud_coup *)malloc(sizeof(t_noeud_coup));

		if (nouveau_noeud != NULL)
		{
			/* Copie de la valeur du coup et initialisation du pointeur suivant. */
			nouveau_noeud->coup = coup;
			nouveau_noeud->suivant = NULL;

			/* Insertion à la fin de la liste chaînée. */
			if (liste->premier == NULL)
			{
				/* La liste était vide : le nouveau nœud est à la fois premier et dernier. */
				liste->premier = nouveau_noeud;
				liste->dernier = nouveau_noeud;
			}
			else
			{
				/* La liste contient déjà des éléments : on rattache le nœud à la suite du dernier. */
				liste->dernier->suivant = nouveau_noeud;
				liste->dernier = nouveau_noeud;
			}

			/* Incrémentation de la taille de la liste. */
			liste->taille = liste->taille + 1;
		}
	}
}

/*********************************************************************
* FONCTION : enlever_premier_coup
*********************************************************************/
int enlever_premier_coup(t_listecoups liste, t_coup *coup)
{
	int resultat_retrait;        /* Drapeau indiquant si le retrait a réussi. */
	t_noeud_coup *noeud_a_retirer; /* Pointeur temporaire vers le premier nœud. */

	resultat_retrait = ECHEC_LISTE;

	/* On s'assure que la liste et le réceptacle sont valides. */
	if (liste != NULL && coup != NULL && liste->premier != NULL)
	{
		/* Récupération du premier nœud. */
		noeud_a_retirer = liste->premier;

		/* Copie des coordonnées du coup. */
		*coup = noeud_a_retirer->coup;

		/* Déplacement du pointeur de tête. */
		liste->premier = noeud_a_retirer->suivant;

		/* Si la liste devient vide, le dernier pointeur doit aussi valoir NULL. */
		if (liste->premier == NULL)
		{
			liste->dernier = NULL;
		}

		/* Libération du nœud détaché. */
		free(noeud_a_retirer);

		/* Décrémentation du nombre d'éléments. */
		liste->taille = liste->taille - 1;

		resultat_retrait = SUCCES_LISTE;
	}

	return resultat_retrait;
}

/*********************************************************************
* FONCTION : vider_liste_coups
*********************************************************************/
void vider_liste_coups(t_listecoups liste)
{
	t_noeud_coup *courant;  /* Pointeur de parcours des nœuds. */
	t_noeud_coup *suivant;  /* Pointeur pour sauvegarder le nœud suivant. */

	if (liste != NULL)
	{
		courant = liste->premier;

		/* Libération séquentielle de chacun des nœuds. */
		while (courant != NULL)
		{
			suivant = courant->suivant;
			free(courant);
			courant = suivant;
		}

		/* Réinitialisation de la structure de contrôle. */
		liste->premier = NULL;
		liste->dernier = NULL;
		liste->taille = 0;
	}
}

/*********************************************************************
* FONCTION : obtenir_coup_index
*********************************************************************/
int obtenir_coup_index(const t_listecoups liste, int index, t_coup *coup)
{
	int resultat_consultation;  /* Drapeau de succès de la consultation. */
	int compteur_index;         /* Indice courant lors du parcours. */
	t_noeud_coup *courant;      /* Pointeur de parcours de la liste. */

	resultat_consultation = ECHEC_LISTE;

	/* Validation de la plage de l'indice demandé. */
	if (liste != NULL && coup != NULL && index >= 0 && index < liste->taille)
	{
		courant = liste->premier;
		compteur_index = 0;

		/* Avancement jusqu'à l'élément recherché. */
		while (courant != NULL && compteur_index < index)
		{
			courant = courant->suivant;
			compteur_index = compteur_index + 1;
		}

		/* Si le nœud cible est trouvé, on recopie le coup. */
		if (courant != NULL)
		{
			*coup = courant->coup;
			resultat_consultation = SUCCES_LISTE;
		}
	}

	return resultat_consultation;
}

/*********************************************************************
* FONCTION : detruire_liste_coups
*********************************************************************/
void detruire_liste_coups(t_listecoups *ptr_liste)
{
	if (ptr_liste != NULL && *ptr_liste != NULL)
	{
		/* Vider d'abord l'ensemble des nœuds chaînés. */
		vider_liste_coups(*ptr_liste);

		/* Libérer la structure de contrôle elle-même. */
		free(*ptr_liste);

		/* Remettre le pointeur à NULL pour éviter les dangles. */
		*ptr_liste = NULL;
	}
}
