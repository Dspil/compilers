/******************************************************************************
 *  CVS version:
 *     $Id: general.c,v 1.1 2004/05/05 22:00:08 nickie Exp $
 ******************************************************************************
 *
 *  C code file : general.c
 *  Project     : PCL Compiler
 *  Version     : 1.0 alpha
 *  Written by  : Nikolaos S. Papaspyrou (nickie@softlab.ntua.gr)
 *  Date        : May 5, 2004
 *  Description : Generic symbol table in C, general variables and functions
 *
 *  Comments: (in Greek iso-8859-7)
 *  ---------
 *  Εθνικό Μετσόβιο Πολυτεχνείο.
 *  Σχολή Ηλεκτρολόγων Μηχανικών και Μηχανικών Υπολογιστών.
 *  Τομέας Τεχνολογίας Πληροφορικής και Υπολογιστών.
 *  Εργαστήριο Τεχνολογίας Λογισμικού
 */


/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include <stdlib.h>

#include "general.h"
#include "error.h"


/* ---------------------------------------------------------------------
   ----------- Υλοποίηση των συναρτήσεων διαχείρισης μνήμης ------------
   --------------------------------------------------------------------- */

void * new1 (size_t size)
{
   void * result = malloc(size);

   if (result == NULL)
      fatal("\rOut of memory");
   return result;
}

void delete1 (void * p)
{
   if (p != NULL)
      free(p);
}


/* ---------------------------------------------------------------------
   ------- Αρχείο εισόδου του μεταγλωττιστή και αριθμός γραμμής --------
   --------------------------------------------------------------------- */

const char * filename;
int linecount;
