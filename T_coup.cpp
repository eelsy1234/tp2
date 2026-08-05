/********************************************************************/
/* Par       : Eric Thé                                             */
/* Fichier   : T_COUP.CPP                                           */
/*                                                                  */
/* Ce module implante des fonctions pour gérer un coup de Othello.  */
/* NOTE: Ce module est donné aux élèves.                            */
/********************************************************************/
#include"T_coup.h"

/**************************************************************
* FONCTIONS get_coup, set_coup
* Fonctions informatrices et mutatrices d'un t_coup.
**************************************************************/
void  get_coup(const t_coup *coup, int *ran, int *col)
{ *ran = coup->ran;
  *col = coup->col;
}

/*************************************************************/
void  set_coup(t_coup *coup, int ran, int col)
{ coup->ran = ran;
  coup->col = col;
}

/*************************************************************/