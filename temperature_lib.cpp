#include <stdio.h>
#include "temperature.h"

static int n, m;

int main() {
	scanf("%d%d", &n, &m);
	
	int *x = new int[n];
	int *y = new int[n];
	int *temp = new int[n];
	
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", x + i, y + i, temp + i);
	}
	
	init(n, x, y, temp);
	
	for (int i = 0; i < m; i++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		printf("%d\n", query(x1, y1, x2, y2));
	}
	
	delete[] x;
	delete[] y;
	delete[] temp;
}
