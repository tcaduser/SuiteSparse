/* ========================================================================== */
/* === umfpack_free_numeric ================================================= */
/* ========================================================================== */

/* -------------------------------------------------------------------------- */
/* UMFPACK Copyright (c) Timothy A. Davis, CISE,                              */
/* Univ. of Florida.  All Rights Reserved.  See ../Doc/License for License.   */
/* web: http://www.cise.ufl.edu/research/sparse/umfpack                       */
/* -------------------------------------------------------------------------- */

UMFPACK_PUBLIC
void umfpack_di_free_numeric
(
    void **Numeric
) ;

void umfpack_dl_free_numeric
(
    void **Numeric
) ;

UMFPACK_PUBLIC
void umfpack_zi_free_numeric
(
    void **Numeric
) ;

void umfpack_zl_free_numeric
(
    void **Numeric
) ;

/*
double int Syntax:

    #include "umfpack.h"
    void *Numeric ;
    umfpack_di_free_numeric (&Numeric) ;

double UF_long Syntax:

    #include "umfpack.h"
    void *Numeric ;
    umfpack_dl_free_numeric (&Numeric) ;

complex int Syntax:

    #include "umfpack.h"
    void *Numeric ;
    umfpack_zi_free_numeric (&Numeric) ;

complex UF_long Syntax:

    #include "umfpack.h"
    void *Numeric ;
    umfpack_zl_free_numeric (&Numeric) ;

Purpose:

    Deallocates the Numeric object and sets the Numeric handle to NULL.  This
    routine is the only valid way of destroying the Numeric object.

Arguments:

    void **Numeric ;	    Input argument, set to (void *) NULL on output.

	Numeric points to a valid Numeric object, computed by umfpack_*_numeric.
	No action is taken if Numeric is a (void *) NULL pointer.
*/
