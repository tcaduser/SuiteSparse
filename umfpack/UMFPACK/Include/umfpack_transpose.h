/* ========================================================================== */
/* === umfpack_transpose ==================================================== */
/* ========================================================================== */

/* -------------------------------------------------------------------------- */
/* UMFPACK Copyright (c) Timothy A. Davis, CISE,                              */
/* Univ. of Florida.  All Rights Reserved.  See ../Doc/License for License.   */
/* web: http://www.cise.ufl.edu/research/sparse/umfpack                       */
/* -------------------------------------------------------------------------- */

UMFPACK_PUBLIC
int umfpack_di_transpose
(
    int n_row,
    int n_col,
    const int Ap [ ],
    const int Ai [ ],
    const double Ax [ ],
    const int P [ ],
    const int Q [ ],
    int Rp [ ],
    int Ri [ ],
    double Rx [ ]
) ;

UF_long umfpack_dl_transpose
(
    UF_long n_row,
    UF_long n_col,
    const UF_long Ap [ ],
    const UF_long Ai [ ],
    const double Ax [ ],
    const UF_long P [ ],
    const UF_long Q [ ],
    UF_long Rp [ ],
    UF_long Ri [ ],
    double Rx [ ]
) ;

UMFPACK_PUBLIC
int umfpack_zi_transpose
(
    int n_row,
    int n_col,
    const int Ap [ ],
    const int Ai [ ],
    const double Ax [ ], const double Az [ ],
    const int P [ ],
    const int Q [ ],
    int Rp [ ],
    int Ri [ ],
    double Rx [ ], double Rz [ ],
    int do_conjugate
) ;

UF_long umfpack_zl_transpose
(
    UF_long n_row,
    UF_long n_col,
    const UF_long Ap [ ],
    const UF_long Ai [ ],
    const double Ax [ ], const double Az [ ],
    const UF_long P [ ],
    const UF_long Q [ ],
    UF_long Rp [ ],
    UF_long Ri [ ],
    double Rx [ ], double Rz [ ],
    UF_long do_conjugate
) ;

/*
double int Syntax:

    #include "umfpack.h"
    int n_row, n_col, status, *Ap, *Ai, *P, *Q, *Rp, *Ri ;
    double *Ax, *Rx ;
    status = umfpack_di_transpose (n_row, n_col, Ap, Ai, Ax, P, Q, Rp, Ri, Rx) ;

double UF_long Syntax:

    #include "umfpack.h"
    UF_long n_row, n_col, status, *Ap, *Ai, *P, *Q, *Rp, *Ri ;
    double *Ax, *Rx ;
    status = umfpack_dl_transpose (n_row, n_col, Ap, Ai, Ax, P, Q, Rp, Ri, Rx) ;

complex int Syntax:

    #include "umfpack.h"
    int n_row, n_col, status, *Ap, *Ai, *P, *Q, *Rp, *Ri, do_conjugate ;
    double *Ax, *Az, *Rx, *Rz ;
    status = umfpack_zi_transpose (n_row, n_col, Ap, Ai, Ax, Az, P, Q,
	Rp, Ri, Rx, Rz, do_conjugate) ;

complex UF_long Syntax:

    #include "umfpack.h"
    UF_long n_row, n_col, status, *Ap, *Ai, *P, *Q, *Rp, *Ri, do_conjugate ;
    double *Ax, *Az, *Rx, *Rz ;
    status = umfpack_zl_transpose (n_row, n_col, Ap, Ai, Ax, Az, P, Q,
	Rp, Ri, Rx, Rz, do_conjugate) ;

packed complex Syntax:

    Same as above, except Az are Rz are NULL.

Purpose:

    Transposes and optionally permutes a sparse matrix in row or column-form,
    R = (PAQ)'.  In MATLAB notation, R = (A (P,Q))' or R = (A (P,Q)).' doing
    either the linear algebraic transpose or the array transpose. Alternatively,
    this routine can be viewed as converting A (P,Q) from column-form to
    row-form, or visa versa (for the array transpose).  Empty rows and columns
    may exist.  The matrix A may be singular and/or rectangular.

    umfpack_*_transpose is useful if you want to factorize A' or A.' instead of
    A.  Factorizing A' or A.' instead of A can be much better, particularly if
    AA' is much sparser than A'A.  You can still solve Ax=b if you factorize
    A' or A.', by solving with the sys argument UMFPACK_At or UMFPACK_Aat,
    respectively, in umfpack_*_*solve.

Returns:

    UMFPACK_OK if successful.
    UMFPACK_ERROR_out_of_memory if umfpack_*_transpose fails to allocate a
	size-max (n_row,n_col) workspace.
    UMFPACK_ERROR_argument_missing if Ai, Ap, Ri, and/or Rp are missing.
    UMFPACK_ERROR_n_nonpositive if n_row <= 0 or n_col <= 0
    UMFPACK_ERROR_invalid_permutation if P and/or Q are invalid.
    UMFPACK_ERROR_invalid_matrix if Ap [n_col] < 0, if Ap [0] != 0,
	if Ap [j] > Ap [j+1] for any j in the range 0 to n_col-1,
	if any row index i is < 0 or >= n_row, or if the row indices
	in any column are not in ascending order.

Arguments:

    Int n_row ;		Input argument, not modified.
    Int n_col ;		Input argument, not modified.

	A is an n_row-by-n_col matrix.  Restriction: n_row > 0 and n_col > 0.

    Int Ap [n_col+1] ;	Input argument, not modified.

	The column pointers of the column-oriented form of the matrix A.  See
	umfpack_*_symbolic for a description.  The number of entries in
	the matrix is nz = Ap [n_col].  Ap [0] must be zero, Ap [n_col] must be
	=> 0, and Ap [j] <= Ap [j+1] and Ap [j] <= Ap [n_col] must be true for
	all j in the range 0 to n_col-1.  Empty columns are OK (that is, Ap [j]
	may equal Ap [j+1] for any j in the range 0 to n_col-1).

    Int Ai [nz] ;	Input argument, not modified, of size nz = Ap [n_col].

	The nonzero pattern (row indices) for column j is stored in
	Ai [(Ap [j]) ... (Ap [j+1]-1)].  The row indices in a given column j
	must be in ascending order, and no duplicate row indices may be present.
	Row indices must be in the range 0 to n_row-1 (the matrix is 0-based).

    double Ax [nz] ;	Input argument, not modified, of size nz = Ap [n_col].
			Size 2*nz if Az or Rz are NULL.
    double Az [nz] ;	Input argument, not modified, for complex versions.

	If present, these are the numerical values of the sparse matrix A.
	The nonzero pattern (row indices) for column j is stored in
	Ai [(Ap [j]) ... (Ap [j+1]-1)], and the corresponding real numerical
	values are stored in Ax [(Ap [j]) ... (Ap [j+1]-1)].  The imaginary
	values are stored in Az [(Ap [j]) ... (Ap [j+1]-1)].  The values are
	transposed only if Ax and Rx are present.
	This is not an error conditions; you are able to transpose
	and permute just the pattern of a matrix.

	If Az or Rz are NULL, then both real
	and imaginary parts are contained in Ax[0..2*nz-1], with Ax[2*k]
	and Ax[2*k+1] being the real and imaginary part of the kth entry.

    Int P [n_row] ;		Input argument, not modified.

	The permutation vector P is defined as P [k] = i, where the original
	row i of A is the kth row of PAQ.  If you want to use the identity
	permutation for P, simply pass (Int *) NULL for P.  This is not an error
	condition.  P is a complete permutation of all the rows of A; this
	routine does not support the creation of a transposed submatrix of A
	(R = A (1:3,:)' where A has more than 3 rows, for example, cannot be
	done; a future version might support this operation).

    Int Q [n_col] ;		Input argument, not modified.

	The permutation vector Q is defined as Q [k] = j, where the original
	column j of A is the kth column of PAQ.  If you want to use the identity
	permutation for Q, simply pass (Int *) NULL for Q.  This is not an error
	condition.  Q is a complete permutation of all the columns of A; this
	routine does not support the creation of a transposed submatrix of A.

    Int Rp [n_row+1] ;	Output argument.

	The column pointers of the matrix R = (A (P,Q))' or (A (P,Q)).', in the
	same form as the column pointers Ap for the matrix A.

    Int Ri [nz] ;	Output argument.

	The row indices of the matrix R = (A (P,Q))' or (A (P,Q)).' , in the
	same form as the row indices Ai for the matrix A.

    double Rx [nz] ;	Output argument.
			Size 2*nz if Az or Rz are NULL.
    double Rz [nz] ;	Output argument, imaginary part for complex versions.

	If present, these are the numerical values of the sparse matrix R,
	in the same form as the values Ax and Az of the matrix A.

	If Az or Rz are NULL, then both real
	and imaginary parts are contained in Rx[0..2*nz-1], with Rx[2*k]
	and Rx[2*k+1] being the real and imaginary part of the kth entry.

    Int do_conjugate ;	Input argument for complex versions only.

	If true, and if Ax and Rx are present, then the linear
	algebraic transpose is computed (complex conjugate).  If false, the
	array transpose is computed instead.
*/
