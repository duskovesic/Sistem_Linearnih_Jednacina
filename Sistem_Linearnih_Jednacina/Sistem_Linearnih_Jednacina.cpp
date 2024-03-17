#include<stdio.h>


void zameni_vrste(double a[], double b[], int n) {
	double tmp;
	int i;
	for (i = 0; i < n; i++) {
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
}


int main() {
	//setbuf(stdout, NULL);  //bez ovoga printf i scanf ne rade kako treba. Ovu liniju sam nasao na stackoverflow



	int n, i, j, k;

	printf("Unesite dimenziju sistema: ");
	scanf_s("%d", &n);
		double m[20][21];


	
		printf("\nSistem jednacina mora biti sledeceg oblika:\n");
		for (i = 0; i < n; i++) {
			for (j = 0; j < n + 1; j++) {
				if(j < n) {
					printf("a(%d, %d) * X%d", i+1, j+1, j+1);
					if(j != n-1)
						printf(" + ");
				}
				else
					printf(" = b%d\n", i+1);
			}
		}
		printf("\n");
	
	
	//Unosenje koeficijenata
		for (i = 0; i < n; i++) {
			for (j = 0; j < n + 1; j++) {
				if(j<n)
					printf("Unesite koeficijent a(%d, %d): ", i+1, j+1);
				else
					printf("Unesite koeficijent b%d: ", i+1);
				scanf_s("%lf", &m[i][j]);
			}
		}
	


	//ispis sistema linearnih jednacina koji je korisnik uneo
	printf("\nUneli ste sistem jednacina:\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n + 1; j++) {
			if (j < n) {
				printf("%f * X%d", m[i][j], j + 1);
				if (j != n - 1)
					printf(" + ");
			}
			else
				printf(" = %f\n", m[i][j]);
		}
	}
	printf("\n");


	//svodjenje matrice na trougaoni oblik
	for (k = 0; k < n; k++) {
		//ako je vodeci koeficijent jednak nuli, tu vrstu zamenimo sa prvom sledecom vrstom kojoj vodeci koeficijent nije nula
		if (m[k][k] == 0) {
			for (i = 1; i < n - k; i++) {
				if (m[k + i][k] != 0) {
					zameni_vrste(m[k], m[k + i], n + 1);
					break;
				}
			}
		}

		//ako je vodeci koeficijent i dalje nula, prelazi se na sledeci vodeci koeficijent
		if (m[k][k] == 0)
			continue;

		//vracamo se na svodjenje na trougaoni oblik
		for (i = k; i < n - 1; i++) {   //i je redni broj vrste
			double num = -1.0 * m[i + 1][k] / m[k][k];    //num je broj sa kojim mnozimo vrstu
			for (j = k; j < n + 1; j++) {   //j je redni broj kolone
				m[i + 1][j] = m[k][j] * num + m[i + 1][j];   //mnozi se vrsta sa brojem num i dodaje se sledeceoj vrsti
			}
		}
	}


	//ispis matrice nakon dobijenog trougaonog oblika
	printf("Nakon transformacija, sistem je sveden na trougaoni oblik:\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n + 1; j++) {
			if (j < n) {
				printf("%f * X%d", m[i][j], j + 1);
				if (j != n - 1)
					printf(" + ");
			}
			else
				printf(" = %f\n", m[i][j]);
		}
	}
	printf("\n");


	//proveravamo da li poslednja vrsta ima resenje
	if (m[n - 1][n - 1] == 0 && m[n - 1][n] != 0) {
		printf("Sistem je nemoguc\n");
		return 0;
	}
	else if (m[n - 1][n - 1] == 0 && m[n - 1][n] == 0) {
		int slobodne_nepoznate = 1;
		for (i = n - 2; i >= 0; i--) {
			double zbir = 0;
			for (j = 0; i + j < n; j++)
				zbir = zbir + m[i][i + j];
			if (zbir == 0 && m[i][n] != 0) {
				printf("Sistem je nemoguc\n");
				return 0;
			}
			if (zbir == 0 && m[i][i + j] == 0)
				slobodne_nepoznate++;
		}
		printf("Sistem je neodredjen i broj slobodnih nepoznatih je %d\n", slobodne_nepoznate);
		return 0;
	}

	//resavanje sistema nakon dobijenog trogugaonog oblika
	double rez[50];			//niz u kom se cuvaju resenja
	rez[n - 1] = m[n - 1][n] / m[n - 1][n - 1]; 			//resenje poslednje nepoznate

	int brojac_resenja = 1, pomocni_brojac;	//brojac resenja pamti koliko smo nepoznatih odredili
	double sum;
	for (i = n - 2; i >= 0; i--) {							//pomocni brojac nam sluzi da odredimo zbir poznatih resenja u promenljivoj sum
		pomocni_brojac = brojac_resenja;
		sum = 0;
		while (pomocni_brojac > 0) {
			sum = sum + m[i][i + pomocni_brojac] * rez[i + pomocni_brojac];
			pomocni_brojac--;
		}
		rez[i] = (m[i][n] - sum) / m[i][i];			//odredjujemo vrednost nepoznate
		brojac_resenja++;
	}



	//ispis resenja
	printf("Sistem ima jedinstveno resenje:\n");
	printf("(");
	for (i = 0; i < n; i++) {
		printf("X%d", i + 1);
		if (i != n - 1)
			printf(", ");
	}
	printf(") = (");
	for (i = 0; i < n; i++) {
		printf("%f", rez[i]);
		if (i != n - 1)
			printf(", ");
	}
	printf(")");



	return 0;
}

