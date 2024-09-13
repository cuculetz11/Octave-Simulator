//Cucu Viorel-Cosmin 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define mod 10007

int *realocare_vect(int nr, int *v)
{
	int *a = (int *)realloc(v, nr * sizeof(int));
	if (!a) {
		printf("mallocvect() failed\n");
		return v;
	} else {
		return a;
	}
}

int ***realocare_mat_nr(int nr, int ***v)
{
	int ***a = (int ***)realloc(v, nr * sizeof(int **));
	if (!a) {
		printf("mallocvect() failed\n");
		return v;
	} else {
		return a;
	}
}

void citire_matrice(int *n, int *m, int ***mat)
{
	int **v = (int **)malloc(*n * sizeof(int *));
	if (!v) {
		printf("malloc() for matrix failed\n");
		*mat = NULL;
		return;
	}

	*mat = v;

	for (int i = 0; i < *n; i++) {
		v[i] = (int *)malloc(*m * sizeof(int));
		if (!v[i]) {
			printf("malloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(v[j]);
			free(v);
			*mat = NULL;
			return;
		}
	}

	for (int i = 0; i < *n; i++) {
		for (int j = 0; j < *m; j++)
			scanf("%d", &v[i][j]);
	}
}

void afisare_mat(int n, int m, int **mat)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}

void free_matrix_clasic(int n, int **mat)
{
	for (int i = 0; i < n; i++)
		free(mat[i]);
	free(mat);
}

void resize_mat(int l, int c, int ***mat, int lin_i, int *l1, int *c1)
{
	int **v = (int **)malloc(l * sizeof(int *));
	if (!v) {
		printf("malloc() for matrix failed\n");
		*mat = NULL;
		return;
	}
/*fac o matrice cu valorile de pe liniile si coloanele date, apoi eliberez
matricea intiala si o proiectez spre matricea creata*/
	for (int i = 0; i < l; i++) {
		v[i] = (int *)malloc(c * sizeof(int));
		if (!v[i]) {
			printf("malloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(v[j]);
			free(v);
			*mat = NULL;
			return;
		}
	}
	for (int i = 0; i < l; i++)
		for (int j = 0; j < c; j++)
			v[i][j] = (*mat)[l1[i]][c1[j]];
	free_matrix_clasic(lin_i, *mat);
	*mat = v;
}

void prod_mat(int n1, int m1, int m2, int **mat1, int **mat2, int ***mat)
{
	int **v = (int **)calloc(n1, sizeof(int *));
	if (!v) {
		printf("calloc() for matrix failed\n");
		*mat = NULL;
		return;
	}

	*mat = v;

	for (int i = 0; i < n1; i++) {
		v[i] = (int *)calloc(m2, sizeof(int));
		if (!v[i]) {
			printf("calloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(v[j]);
			free(v);
			*mat = NULL;
			return;
		}
	}
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < m2; j++)
			for (int k = 0; k < m1; k++) {
				long long rezult = (long long)mat1[i][k] * mat2[k][j];
				rezult = rezult % 10007;
				if (rezult < 0)
					rezult = rezult + 10007;
				v[i][j] = (v[i][j] + rezult) % 10007;
			}
}

int s_mat(int n, int m, int **mat)
{
	int s = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			s = s + mat[i][j];
	if (s < 0)
		s = s % mod + mod;
	else
		s = s % mod;
	return s;
}

void schimbare_mat(int i, int j, int ***mat)
{
//pur si simplu un swap pentru matrici
	int **aux = mat[i];
	mat[i] = mat[j];
	mat[j] = aux;
}

void schimbare_vectdim(int i, int j, int *vect)
{
	int aux = vect[j];
	vect[j] = vect[i];
	vect[i] = aux;
}

void sortare_mat(int nr_mat, int ***mat, int *l, int *c)
{
	for (int i = 0; i < nr_mat - 1; i++)
		for (int j = i + 1; j < nr_mat; j++)
			if (s_mat(l[i], c[i], mat[i]) > s_mat(l[j], c[j], mat[j])) {
				schimbare_mat(i, j, mat);
				schimbare_vectdim(i, j, l);
				schimbare_vectdim(i, j, c);
			}
}

void transpunere_mat(int *n, int *m, int ***mat)
{
	int **v = (int **)malloc(*m * sizeof(int *));
	if (!v) {
		printf("malloc() for matrix failed\n");
		*mat = NULL;
		return;
	}
	for (int i = 0; i < *m; i++) {
		v[i] = (int *)malloc(*n * sizeof(int));
		if (!v[i]) {
			printf("malloc() for matrix in line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(v[j]);

			free(v);
			*mat = NULL;
			return;
		}
	}
/*fac o matrice noua ce este egala cu transpusa matricei initiale, apoi
eliberez matricea initala si dupa o proiectez spre matricea creata*/
	for (int i = 0; i < *m; i++)
		for (int j = 0; j < *n; j++)
			v[i][j] = (*mat)[j][i];

	free_matrix_clasic(*n, *mat);

	*mat = v;
	int aux = *n;
	*n = *m;
	*m = aux;
}

int **prod_mat_patratice(int n, int **mat1, int **mat2)
{
	int **v = (int **)calloc(n, sizeof(int *));
	if (!v)
		printf("calloc() for matrix failed\n");

	for (int i = 0; i < n; i++) {
		v[i] = (int *)calloc(n, sizeof(int));
		if (!v[i]) {
			printf("calloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(v[j]);
			free(v);
			return NULL;
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				long long rezult = (long long)mat1[i][k] * mat2[k][j];
				rezult = rezult % 10007;
				if (rezult < 0)
					rezult = rezult + 10007;
				v[i][j] = (v[i][j] + rezult) % 10007;
			}

	return v;
}

void pow_mat(int n, int ***mat, int p)
{
	int **r = (int **)calloc(n, sizeof(int *));
	if (!r) {
		printf("calloc() for matrix failed\n");
		*mat = NULL;
		return;
	}

	for (int i = 0; i < n; i++) {
		r[i] = (int *)calloc(n, sizeof(int));
		if (!r[i]) {
			printf("calloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(r[j]);
			free(r);
			*mat = NULL;
			return;
		}
	}
	for (int i = 0; i < n; i++)
		r[i][i] = 1;
/*creez o matrice identitate, apoi aplic algoritmul de ridicare la putere
in timp logaritmic*/
	while (p > 0) {
		if (p % 2 == 1) {
			int **aux = prod_mat_patratice(n, r, *mat);
			free_matrix_clasic(n, r);
			r = aux;
/*aici fac un auxiliar care este egal cu produsul dintre r si matricea ce
vreau sa o ridic, apoi elberez r-ul anterior*/
		}
		int **aux = prod_mat_patratice(n, *mat, *mat);
		free_matrix_clasic(n, *mat);
		*mat = aux;
		p = p / 2;
	}
	free_matrix_clasic(n, *mat);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (r[i][j] < 0)
				r[i][j] = r[i][j] % mod + mod;
			else
				r[i][j] = r[i][j] % mod;
	*mat = r;
}

void eliberare_mat(int ***mat, int nr_mat, int index, int *l, int *c)
{
 //matricea cu indexul dat o proiectez spre matricea urmatoare
 //iar vectorii ce retin linii si coloane obtin urmatoarea valoare
	for (int i = index; i < nr_mat - 1; i++) {
		mat[i] = mat[i + 1];
		l[i] = l[i + 1];
		c[i] = c[i + 1];
	}
}

void eliberare_mem(int nr_mat, int *lin, int ***mat)
{	//eliberez memoria matricei 3D
	for (int i = 0; i < nr_mat; i++)
		for (int j = 0; j < lin[i]; j++)
			free(mat[i][j]);

	for (int i = 0; i < nr_mat; i++)
		free(mat[i]);

	free(mat);
}

int verif_put2(int n)
{
	while (n > 1) {
		if (n % 2 == 1)
			return 0;
		n = n / 2;
	}
	return 1;
}

void alocare_matpatratice(int ***a, int n)
{
	int **v = (int **)calloc(n, sizeof(int *));
	if (!v) {
		printf("malloc() for matrix failed\n");
		*a = NULL;
		return;
	}
	*a = v;
	for (int i = 0; i < n; i++) {
		v[i] = (int *)calloc(n, sizeof(int));
		if (!v[i]) {
			printf("malloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(v[j]);
			free(v);
			*a = NULL;
			return;
		}
	}
}

void add_mat(int ***rez, int **a, int **b, int n)
{
	alocare_matpatratice(rez, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			(*rez)[i][j] = a[i][j] + b[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if ((*rez)[i][j] > 0)
				(*rez)[i][j] = (*rez)[i][j] % mod;
			else
				(*rez)[i][j] = (*rez)[i][j] % mod + mod;
}

void dif_mat(int ***rez, int **a, int **b, int n)
{
	alocare_matpatratice(rez, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			(*rez)[i][j] = a[i][j] - b[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if ((*rez)[i][j] > 0)
				(*rez)[i][j] = (*rez)[i][j] % mod;
			else
				(*rez)[i][j] = (*rez)[i][j] % mod + mod;
}

void add_mat1(int **rez, int **a, int **b, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			rez[i][j] = a[i][j] + b[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (rez[i][j] > 0)
				rez[i][j] = rez[i][j] % mod;
			else
				rez[i][j] = rez[i][j] % mod + mod;
}

void dif_mat1(int **rez, int **a, int **b, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			rez[i][j] = a[i][j] - b[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (rez[i][j] > 0)
				rez[i][j] = rez[i][j] % mod;
			else
				rez[i][j] = rez[i][j] % mod + mod;
}

void strassen(int **a, int **b, int ***c, int n)
{
	if (n == 1) {
		(*c)[0][0] = a[0][0] * b[0][0];
		return;
	}
	int **a11, **a12, **a21, **a22, **b11, **b12, **b21, **b22;
	int **c11, **c12, **c21, **c22, new_n = n / 2;

	alocare_matpatratice(&a11, new_n), alocare_matpatratice(&a12, new_n);
	alocare_matpatratice(&a21, new_n), alocare_matpatratice(&a22, new_n);
	alocare_matpatratice(&b11, new_n), alocare_matpatratice(&b12, new_n);
	alocare_matpatratice(&b21, new_n), alocare_matpatratice(&b22, new_n);
	alocare_matpatratice(&c11, new_n), alocare_matpatratice(&c12, new_n);
	alocare_matpatratice(&c21, new_n), alocare_matpatratice(&c22, new_n);
	for (int i = 0; i < new_n; i++)
		for (int j = 0; j < new_n; j++) {
			a11[i][j] = a[i][j], b22[i][j] = b[i + new_n][j + new_n];
			a12[i][j] = a[i][j + new_n], a21[i][j] = a[i + new_n][j];
			a22[i][j] = a[i + new_n][j + new_n], b11[i][j] = b[i][j];
			b12[i][j] = b[i][j + new_n], b21[i][j] = b[i + new_n][j];
		}
	int **p1, **p2, **p3, **p4, **p5, **p6, **p7;
	alocare_matpatratice(&p1, new_n), alocare_matpatratice(&p2, new_n);
	alocare_matpatratice(&p3, new_n), alocare_matpatratice(&p4, new_n);
	alocare_matpatratice(&p5, new_n), alocare_matpatratice(&p6, new_n);
	alocare_matpatratice(&p7, new_n);

	int **ad1, **ad2, **ad3, **ad4, **ad5, **ad6, **sc1;
	int **sc2, **sc3, **sc4;
	add_mat(&ad1, a11, a22, new_n), add_mat(&ad2, b11, b22, new_n);
	add_mat(&ad3, a21, a22, new_n), dif_mat(&sc1, b12, b22, new_n);
	dif_mat(&sc2, b21, b11, new_n), add_mat(&ad4, a11, a12, new_n);
	dif_mat(&sc3, a21, a11, new_n), add_mat(&ad5, b11, b12, new_n);
	dif_mat(&sc4, a12, a22, new_n), add_mat(&ad6, b21, b22, new_n);
	strassen(ad1, ad2, &p1, new_n), strassen(ad3, b11, &p2, new_n);
	strassen(a11, sc1, &p3, new_n), strassen(a22, sc2, &p4, new_n);
	strassen(ad4, b22, &p5, new_n), strassen(sc3, ad5, &p6, new_n);
	strassen(sc4, ad6, &p7, new_n);
	free_matrix_clasic(new_n, a11), free_matrix_clasic(new_n, a12);
	free_matrix_clasic(new_n, a21), free_matrix_clasic(new_n, a22);
	free_matrix_clasic(new_n, b11), free_matrix_clasic(new_n, b12);
	free_matrix_clasic(new_n, b21), free_matrix_clasic(new_n, b22);
	free_matrix_clasic(new_n, ad1), free_matrix_clasic(new_n, ad2);
	free_matrix_clasic(new_n, ad3), free_matrix_clasic(new_n, sc1);
	free_matrix_clasic(new_n, sc2), free_matrix_clasic(new_n, ad4);
	free_matrix_clasic(new_n, sc3), free_matrix_clasic(new_n, ad5);
	free_matrix_clasic(new_n, sc4), free_matrix_clasic(new_n, ad6);

	add_mat1(c12, p3, p5, new_n), add_mat1(c21, p2, p4, new_n);
	int **aux1, **aux2, **aux3, **aux4;
	add_mat(&aux1, p1, p4, new_n), dif_mat(&aux2, aux1, p5, new_n);
	add_mat1(c11, aux2, p7, new_n);
	dif_mat(&aux3, p1, p2, new_n), add_mat(&aux4, p3, p6, new_n);
	add_mat1(c22, aux3, aux4, new_n);
	free_matrix_clasic(new_n, p1), free_matrix_clasic(new_n, p2);
	free_matrix_clasic(new_n, p3), free_matrix_clasic(new_n, p4);
	free_matrix_clasic(new_n, p5), free_matrix_clasic(new_n, p6);
	free_matrix_clasic(new_n, p7), free_matrix_clasic(new_n, aux1);
	free_matrix_clasic(new_n, aux2), free_matrix_clasic(new_n, aux3);
	free_matrix_clasic(new_n, aux4);
	int **aux;
	alocare_matpatratice(&aux, new_n * 2);
	if (!aux) {
		printf("Memory allocation for aux failed\n");
		return;
	}
	if (*c)
		free_matrix_clasic(new_n * 2, *c);
	*c = aux;
	for (int i = 0; i < new_n; i++)
		for (int j = 0; j < new_n; j++) {
			aux[i][j] = c11[i][j];
			aux[i][j + new_n] = c12[i][j];
			aux[i + new_n][j] = c21[i][j];
			aux[i + new_n][j + new_n] = c22[i][j];
		}
	free_matrix_clasic(new_n, c11), free_matrix_clasic(new_n, c12);
	free_matrix_clasic(new_n, c21), free_matrix_clasic(new_n, c22);
}

void exec_L(int *nr_mat, int ****m, int **lin, int **col,
			int *capacitate, int *dim)
{
/*vad daca capacitatea este suficienta, iar daca nu este, o dublez si realoc
	memorie pentru vectorii lin si col si pentru matricea m*/
	if (*dim >= *capacitate) {
		*capacitate = 2 * *dim;
		*lin = realocare_vect(*capacitate, *lin);
		*col = realocare_vect(*capacitate, *col);
		*m = realocare_mat_nr(*capacitate, *m);
	}
	scanf("%d%d", (*lin) + *nr_mat, (*col) + *nr_mat);
	citire_matrice((*lin) + *nr_mat, (*col) + *nr_mat, (*m) + *nr_mat);
	(*nr_mat)++, (*dim)++;
}

void exec_D(int nr_mat, int *lin, int *col)
{
	int index;
	scanf("%d", &index);
	if (index >= nr_mat || index < 0)
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", lin[index], col[index]);
}

void exec_P(int nr_mat, int ***m, int *lin, int *col)
{
	int index;
	scanf("%d", &index);
	if (index >= nr_mat || index < 0)
		printf("No matrix with the given index\n");
	else
		afisare_mat(lin[index], col[index], m[index]);
}

void exec_C(int nr_mat, int ***m, int *lin, int *col)
{
	int index, nr_de_lin, nr_de_col;

	scanf("%d%d", &index, &nr_de_lin);

	int nr_l[nr_de_lin];

	for (int i = 0; i < nr_de_lin; i++)
		scanf("%d", &nr_l[i]);

	scanf("%d", &nr_de_col);

	int nr_c[nr_de_col];
	for (int i = 0; i < nr_de_col; i++)
		scanf("%d", &nr_c[i]);

	if (index >= nr_mat || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		resize_mat(nr_de_lin, nr_de_col, m + index, lin[index], nr_l, nr_c);
		//le schimb valorile vectorilor lin si col cu cele noi
		lin[index] = nr_de_lin;
		col[index] = nr_de_col;
	}
}

void exec_M(int *nr_mat, int ****m, int **lin, int **col,
			int *capacitate, int *dim)
{
	int m_1, m_2;
	scanf("%d %d", &m_1, &m_2);
	if (m_1 >= *nr_mat || m_2 >= *nr_mat || m_1 < 0 || m_2 < 0) {
		printf("No matrix with the given index\n");
	} else {
		if ((*col)[m_1] != (*lin)[m_2]) {
			printf("Cannot perform matrix multiplication\n");
		} else {
			if (*dim >= *capacitate) {
				*capacitate = 2 * *dim;
				*lin = realocare_vect(*capacitate, *lin);
				*col = realocare_vect(*capacitate, *col);
				*m = realocare_mat_nr(*capacitate, *m);
			}
			(*lin)[*nr_mat] = (*lin)[m_1];
			(*col)[*nr_mat] = (*col)[m_2];
			prod_mat((*lin)[m_1], (*col)[m_1], (*col)[m_2],
					 (*m)[m_1], (*m)[m_2], (*m) + *nr_mat);
			(*nr_mat)++, (*dim)++;
		}
	}
}

void exec_T(int nr_mat, int ***m, int *lin, int *col)
{
	int index;
	scanf("%d", &index);
	if (index >= nr_mat || index < 0)
		printf("No matrix with the given index\n");
	else
		transpunere_mat(lin + index, col + index, m + index);
}

void exec_R(int nr_mat, int ***m, int *lin, int *col)
{
	int p, index;
	scanf("%d%d", &index, &p);
	if (index >= nr_mat || index < 0)
		printf("No matrix with the given index\n");
	else if (p < 0)
		printf("Power should be positive\n");
	else if (lin[index] != col[index])
		printf("Cannot perform matrix multiplication\n");
	else
		pow_mat(lin[index], m + index, p);
}

void exec_F(int *nr_mat, int ****m, int **lin, int **col,
			int *capacitate, int *dim)
{
	int index;
	scanf("%d", &index);
	if (index >= *nr_mat || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		free_matrix_clasic((*lin)[index], (*m)[index]);
		//eliberez matricea cu idexul dat
		eliberare_mat(*m, *nr_mat, index, *lin, *col);
		(*nr_mat)--;
		(*dim)--;
		//scad numarul de matrici si dim(ce reperzinta nr_mat+1)
		/*daca cumva dim a ajuns la jumate din capacitayea vectorului
		de matrici, realocam vectorii pentru a lucra eficient cu memoria*/
		if (*dim == *capacitate / 2) {
			*capacitate = *capacitate / 2;
			*lin = realocare_vect(*capacitate, *lin);
			*col = realocare_vect(*capacitate, *col);
			*m = realocare_mat_nr(*capacitate, *m);
		}
	}
}

void exec_S(int *nr_mat, int ****m, int **lin, int **col,
			int *capacitate, int *dim)
{
	int index1, index2;
	scanf("%d%d", &index1, &index2);
	if (index1 >= *nr_mat || index1 < 0 ||
		index2 >= *nr_mat || index2 < 0) {
		printf("No matrix with the given index\n");
	} else if ((*lin)[index1] != (*col)[index1] ||
		       (*lin)[index2] != (*col)[index2] ||
			   (*lin)[index1] != (*col)[index2]) {
		if (verif_put2((*lin)[index1]) == 0)
			printf("Cannot perform matrix multiplication\n");
	} else {
		if (*dim >= *capacitate) {
			*capacitate = 2 * (*dim);
			*lin = realocare_vect(*capacitate, *lin);
			*col = realocare_vect(*capacitate, *col);
			*m = realocare_mat_nr(*capacitate, *m);
		}
		(*lin)[*nr_mat] = (*lin)[index1];
		(*col)[*nr_mat] = (*col)[index1];
		alocare_matpatratice((*m) + *nr_mat, (*lin)[index1]);
		//initalizez matricea de la coada vectoriului de matrici
		strassen((*m)[index1], (*m)[index2], (*m) + *nr_mat, (*lin)[index1]);
		//aplicam algoritmul lui strassen

		(*nr_mat)++;
		(*dim)++;
	}
}

void exec_Q(int nr_mat, int ***mat, int *lin, int *col)
{
	eliberare_mem(nr_mat, lin, mat);
	free(col);
	free(lin);
}

int main(void)
{
	char s;
	int dim = 1, capacitate = 2, nr_mat = 0;
	int ***m = (int ***)calloc(dim, sizeof(int **));
	int *lin = (int *)calloc(dim, sizeof(int));
	int *col = (int *)calloc(dim, sizeof(int));
	while (1) {
		scanf(" %c", &s);
		if (strchr("LPQFMSDCOTR", s) == 0)
			printf("Unrecognized command\n");
		if (s == 'L')
			exec_L(&nr_mat, &m, &lin, &col, &capacitate, &dim);
		if (s == 'D')
			exec_D(nr_mat, lin, col);
		if (s == 'P')
			exec_P(nr_mat, m, lin, col);
		if (s == 'C')
			exec_C(nr_mat, m, lin, col);
		if (s == 'M')
			exec_M(&nr_mat, &m, &lin, &col, &capacitate, &dim);
		if (s == 'O')
			sortare_mat(nr_mat, m, lin, col);
		if (s == 'T')
			exec_T(nr_mat, m, lin, col);
		if (s == 'R')
			exec_R(nr_mat, m, lin, col);
		if (s == 'F')
			exec_F(&nr_mat, &m, &lin, &col, &capacitate, &dim);
		if (s == 'S')
			exec_S(&nr_mat, &m, &lin, &col, &capacitate, &dim);
		if (s == 'Q') {
			exec_Q(nr_mat, m, lin, col);
			break;
		}
	}
}
