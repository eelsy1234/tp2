/*********************************************************************
Date       : Août 2026
Fichier    : grille.h

Ce module implante les structures de données et les règles de gestion
du plateau de jeu (l'othellier) pour le jeu d'Othello.

Sous-programmes publics :
 - initialiser_jeu    : Initialise l'othellier avec les jetons de départ.
 - determiner_gagnant : Détermine le joueur ayant le plus de pièces.
 - valider_coup       : Vérifie la validité d'un coup pour un joueur.
 - jouer_le_coup      : Effectue un coup sur l'othellier et retourne les pièces.
*********************************************************************/

#ifndef __GRILLE_H__
#define __GRILLE_H__

#include "GRAPH_IO.h"
#include "T_coup.h"

/*********************************************************************
* CONSTANTES
*********************************************************************/

/* Code indiquant la réussite ou la validité d'un coup. */
#define COUP_VALIDE 1

/* Code indiquant un coup non valide. */
#define COUP_INVALID 0

/* Nombre de pièces de départ sur l'othellier. */
#define NB_PIECES_DEPART 4

/* Nombre total de directions sur le plateau (horizontale, verticale, diagonale). */
#define NB_DIRECTIONS 8

/* Borne minimale d'une coordonnée utilisateur (1 à 8). */
#define MIN_COORD_CLIENT 1

/* Borne maximale d'une coordonnée utilisateur (1 à 8). */
#define MAX_COORD_CLIENT 8

/*********************************************************************
* STRUCTURES ET TYPES
*********************************************************************/

/* Type représentant la grille de jeu 8x8. */
typedef t_joueur t_grille[NB_LIGNES_PLAQUE][NB_COLONNES_PLAQUE];

/*********************************************************************
* DÉCLARATIONS DE FONCTIONS
*********************************************************************/

/*
 INITIALISER_JEU
 Initialise l'othellier avec la configuration de départ et renvoie
 le nombre de pièces au départ.

 PARAMÈTRES :
  - othellier : La grille de jeu à initialiser (type : t_grille).

 VALEUR DE RETOUR : Le nombre de pièces au départ (type : int).
*/
int initialiser_jeu(t_grille othellier);

/*
 DETERMINER_GAGNANT
 Va déterminer le gagnant du jeu selon le nombre de pièces sur l'othellier final.

 PARAMÈTRES :
  - othellier : La grille de jeu à évaluer (type : const t_grille).

 VALEUR DE RETOUR : Le joueur gagnant (JOUEUR1, JOUEUR2) ou CASE_VIDE si égalité.
*/
t_joueur determiner_gagnant(const t_grille othellier);

/*
 VALIDER_COUP
 Valide si « le_coup » est un coup valide pour le joueur « jr »
 dans l'« othellier » donné.

 PARAMÈTRES :
  - othellier : La grille de jeu (type : const t_grille).
  - jr        : Le joueur qui veut jouer (type : t_joueur).
  - le_coup   : Le coup à évaluer (type : t_coup).

 VALEUR DE RETOUR : 1 si le coup est valide, 0 sinon (type : int).
*/
int valider_coup(const t_grille othellier, t_joueur jr, t_coup le_coup);

/*
 JOUER_LE_COUP
 Effectue la mise-à-jour de l'othellier avec « le_coup » donné
 pour le joueur « jr » donné.

 PARAMÈTRES :
  - othellier : La grille de jeu à modifier (type : t_grille).
  - jr        : Le joueur qui joue (type : t_joueur).
  - le_coup   : Le coup à appliquer (type : t_coup).

 VALEUR DE RETOUR : Aucune.
*/
void jouer_le_coup(t_grille othellier, t_joueur jr, t_coup le_coup);

#endif
