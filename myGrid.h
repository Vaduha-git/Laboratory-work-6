#include<stdio.h>
#include<stdlib.h>
#include<math.h> 

typedef struct Grid
{
	int x = 0;
	int y = 0;
	float* grid;
};

void deleteGrid(Grid a) {
	free(a.grid);
}

Grid newGrid(int x, int y) {
	Grid a;
	a.x = x;
	a.y = y;
	a.grid = (float*)malloc(a.x*a.y * sizeof(float));
	return a;
}

void prindGrid(Grid a) {
	printf("\n");
	for (int i = 0; i < a.y; i++) {
		printf("|");
		for (int j = 0; j < a.x; j++) printf(" %4.5f |", *(a.grid + i * a.x + j));
		printf("\n");
		for (int j = 0; j < a.x; j++) printf("-------");
		printf("\n");
	}
	printf("\n");
}

Grid getGrid(char* c) {
	int x, y;
	FILE *file;
	fopen_s(&file, c, "r");
	fscanf_s(file,"%d", &x);
	fscanf_s(file, "%d", &y);
	Grid a = newGrid(x, y);
	for (int i = 0; i < a.y; i++)  for (int j = 0; j < a.x; j++) fscanf_s(file, "%f", (a.grid + i * a.x + j));
	prindGrid(a);
	fclose(file);
	return a;
}

Grid Sum(Grid a, Grid b) {
	if (a.x != b.x && b.y != a.y) {
		printf("Error: matrix not sum");
		return a;
	}
	Grid c = newGrid(a.x, a.y);
	for (int i = 0; i < c.y; i++)  for (int j = 0; j < c.x; j++) {
		*(c.grid + i * c.x + j) = *(a.grid + i * c.x + j) + *(b.grid + i * c.x + j);
	}
	return c;
}

Grid Diff(Grid a, Grid b) {
	if (a.x != b.x && b.y != a.y) {
		printf("Error: matrix not sum");
		return a;
	}
	Grid c = newGrid(a.x, a.y);
	for (int i = 0; i < c.y; i++)  for (int j = 0; j < c.x; j++) {
		*(c.grid + i * c.x + j) = *(a.grid + i * c.x + j) - *(b.grid + i * c.x + j);
	}
	return c;
}

Grid myltiGrid(Grid a, Grid b) {
	if (a.x != b.y) {
		printf("Error: Matrix not mylyiplay");
		return a;
	}
	Grid c = newGrid(b.x, a.y);
	for (int i = 0; i < c.y; i++)  for (int j = 0; j < c.x; j++) {
		//int sss = 0;
		float sss = 0;
		for (int k = 0; k < a.x; k++) sss += (*(a.grid + i * a.x + k)) * (*(b.grid + k * b.x + j));
		*(c.grid + i * c.x + j) = sss;
	}
	return c;
}

Grid TranspGrid(Grid Matr) {
	Grid a = newGrid(Matr.x, Matr.y);
	for (int i = 0; i < a.y; i++)  for (int j = 0; j < a.x; j++) *(a.grid + i * a.x + j) = *(Matr.grid + j * Matr.x + i);
	return a;
}

int getOPR(Grid a) {
	if (a.x == 1) return *a.grid;
	else if (a.x == 2) return (*(a.grid + 3) * *(a.grid) - *(a.grid + 2) * *(a.grid + 1));
	else
	{
		int sss = 0;
		for (int m = 0; m < a.x; m++) {
			Grid buf = newGrid(a.x - 1, a.y - 1);
			int count = 0;
			for (int i = 0; i < a.y; i++) for (int j = 0; j < a.x; j++) {
				if (i != 0 && j != m) {
					*(buf.grid + count) = *(a.grid + i * a.x + j);
					count++;
				}
			}
			sss += *(a.grid + m) * getOPR(buf) * pow(-1, m);
			deleteGrid(buf);
		}
		return sss;
	}
}

Grid getOBR_matrix(Grid a) {
	int det = getOPR(a);
	if (det == 0) {
		printf("ERROR: not obr matrix");
		return a;
	}
	Grid bufM = newGrid(a.x, a.y);
	for (int m = 0; m < a.y; m++) for (int n = 0; n < a.x; n++) {
		Grid buf = newGrid(a.x-1, a.y-1);
		int count = 0;
		for (int i = 0; i < a.y; i++) for (int j = 0; j < a.x; j++) {
			if (i != m && j != n) {
				*(buf.grid + count) = *(a.grid + i * a.x + j);
				count++;
			}
		}
		*(bufM.grid + m * bufM.x + n) = getOPR(buf) * pow(-1, m + n) / det;
		deleteGrid(buf);
	}
	bufM = TranspGrid(bufM);
	return bufM;
}