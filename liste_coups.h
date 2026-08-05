/*********************************************************************
Date       : Août 2026
Fichier    : liste_coups.h

Ce module définit la structure de données de liste chaînée simple
utilisée pour conserver l'ensemble des coups valides dans le jeu d'Othello.

Sous-programmes publics :
 - creer_liste_coups    : Alloue et initialise une nouvelle liste de coups.
 - ajouter_coup         : Ajoute un coup à la fin de la liste.
 - enlever_premier_coup : Retire le premier coup de la liste.
 - vider_liste_coups    : Supprime tous les nœuds de la liste.
 - obtenir_coup_index   : Consulte un coup à un indice donné.
 - detruire_liste_coups : Libère la mémoire allouée pour la liste.
*********************************************************************/

#ifndef __LISTE_COUPS_H__
#define __LISTE_COUPS_H__

#include "T_coup.h"

/*********************************************************************
* CONSTANTES
*********************************************************************/

/* Code de succès d'une opération sur la liste. */
#define SUCCES_LISTE 1

/* Code d'échec d'une opération sur la liste. */
#define ECHEC_LISTE 0

/*********************************************************************
* STRUCTURES ET TYPES
*********************************************************************/

/* Structure d'un nœud de la liste chaînée de coups. */
typedef struct t_noeud_coup t_noeud_coup;
struct t_noeud_coup
{
	t_coup coup;              /* Le coup stocké dans le nœud. */
	t_noeud_coup *suivant;    /* Pointeur vers le nœud suivant. */
};

/* Structure de contrôle de la liste chaînée de coups. */
struct t_liste_coups
{
	t_noeud_coup *premier;    /* Pointeur vers le premier nœud. */
	t_noeud_coup *dernier;    /* Pointeur vers le dernier nœud. */
	int taille;               /* Nombre de coups dans la liste. */
};

/* Type pointeur vers la structure de liste de coups. */
typedef struct t_liste_coups * t_listecoups;

/*********************************************************************
* DÉCLARATIONS DE FONCTIONS
*********************************************************************/

/*
 CREER_LISTE_COUPS
 Cette fonction alloue dynamiquement la structure de gestion de liste
 et l'initialise à vide.

 PARAMÈTRES : Aucun.
 VALEUR DE RETOUR : Pointeur vers la nouvelle liste (type : t_listecoups).
*/
t_listecoups creer_liste_coups(void);

/*
 AJOUTER_COUP
 Cette fonction ajoute un coup à la fin de la liste chaînée.

 PARAMÈTRES :
  - liste : Pointeur vers la liste de coups (type : t_listecoups).
  - coup  : Le coup à ajouter (type : t_coup).

 VALEUR DE RETOUR : Aucune.
*/
void ajouter_coup(t_listecoups liste, t_coup coup);

/*
 ENLEVER_PREMIER_COUP
 Cette fonction retire et retourne le premier coup de la liste chaînée.

 PARAMÈTRES :
  - liste : Pointeur vers la liste de coups (type : t_listecoups).
  - coup  : Pointeur où copier le coup retiré (type : t_coup *).

 VALEUR DE RETOUR : 1 en cas de succès, 0 si la liste est vide (type : int).
*/
int enlever_premier_coup(t_listecoups liste, t_coup *coup);

/*
 VIDER_LISTE_COUPS
 Cette fonction supprime tous les nœuds de la liste et réinitialise sa taille à zéro.

 PARAMÈTRES :
  - liste : Pointeur vers la liste de coups (type : t_listecoups).

 VALEUR DE RETOUR : Aucune.
*/
void vider_liste_coups(t_listecoups liste);

/*
 OBTEBNIR_COUP_INDEX
 Cette fonction consulte l'élément à la position spécifiée dans la liste.

 PARAMÈTRES :
  - liste : Pointeur vers la liste de coups (type : const t_listecoups).
  - index : L'indice du coup désiré, basé sur 0 (type : int).
  - coup  : Pointeur où copier le coup trouvé (type : t_coup *).

 VALEUR DE RETOUR : 1 en cas de succès, 0 si l'indice est invalide (type : int).
*/
int obtenir_coup_index(const t_listecoups liste, int index, t_coup *coup);

/*
 DETRUIRE_LISTE_COUPS
 Cette fonction vide la liste et libère la mémoire de la structure de contrôle.

 PARAMÈTRES :
  - ptr_liste : Adresse du pointeur de la liste à détruire (type : t_listecoups *).

 VALEUR DE RETOUR : Aucune.
*/
void detruire_liste_coups(t_listecoups *ptr_liste);

#endif
