/********************************************************************/
/* Par       : Eric Thé                                             */
/* Fichier   : T_COUP.H                                             */
/*                                                                  */
/* Ce module implante des fonctions pour gérer un coup de Othello.  */
/* NOTE: Ce module sera fourni aux élèves.                          */
/********************************************************************/

#ifndef __TCOUP_H__
#define __TCOUP_H__

//declaration du type structuré pour un coup (ran, col)
typedef struct{
  int ran, col;
} t_coup;

/*************************************************************
* Fonctions informatrices et mutatrices d'un t_coup.
*************************************************************/
void  get_coup(const t_coup *, int *, int *);

void  set_coup(t_coup *, int , int );

#endif