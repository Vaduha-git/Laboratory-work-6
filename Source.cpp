#include "myGrid.h"

typedef struct Pear {
	float e;
	int i;	
};

void downHeap(Pear* a, long k, long n) {
	float new_elem;
	int i_ne;
	int child;
	new_elem = a[k].e;
	i_ne = a[k].i;

	while (k <= n / 2) {



		child = 2 * k;

		if (child < n && a[child].e < a[child + 1].e) {
			child++;
		}
		if (new_elem >= a[child].e) break;
		a[k].e = a[child].e;    
		a[k].i= a[child].i;
		k = child;
	}
	a[k].e= new_elem;
	a[k].i = i_ne;
}

void heapSort(Pear* a, long size) {
	long i;
	float temp;
	int itemp;
	for (i = size / 2 - 1; i >= 0; --i) {
		downHeap(a, i, size - 1);
		//for (int i = 0; i < size; i++) printf("%f ", (*(a + i)).e);
		//printf("\n");
	}
	printf("\n\n");

	for (i = size - 1; i > 0; --i) {
		itemp = a[i].i;
		a[i].i = a[0].i;
		a[0].i = itemp;
		temp = a[i].e;
		a[i].e = a[0].e;
		a[0].e = temp;
		downHeap(a, 0, i - 1);
		//for (int i = 0; i < size; i++) printf("%f ", (*(a + i)).e);
		//printf("\n");
	}
}

float get_min(float* mass, int size) {
	float min = *mass;
	for (int i = 0; i < size; i++) if (*(mass + i) < min) min = *(mass + i);
	return min;
}

int main() {
	Grid A = getGrid((char*)"A.txt");
	Pear* min_mass = (Pear*)malloc(A.y * sizeof(Pear));

	for (int i = 0; i < A.y; i++) {
		(*(min_mass + i)).e = get_min(A.grid + i * A.x, A.x);
		(*(min_mass + i)).i = i;
		printf("%f ", (*(min_mass + i)).e);
	}
	printf("\n\n");
	heapSort(min_mass, A.y);
	
	for (int i = 0; i < A.y; i++) printf("%f  = %d \n", (*(min_mass + i)).e, (*(min_mass + i)).i);

	printf("\n");

	Grid B = newGrid(A.x, A.y);
	for (int i = 0; i < B.y; i++) for (int j = 0; j < B.x; j++) *(B.grid + B.x*i + j) = *(A.grid + A.x*min_mass[i].i + j);
	prindGrid(B);
}