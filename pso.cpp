#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <iterator>

int i,j;

//fungsi nya f(x, y, z) = (kx * x^2) + (ky * y^2) + (kz * z^2)
//buat fungsi random nilai acak


//
/*Dimensi	konstanta	batas minimal	batas maksimal
x	3.2	10	50
y	3	30	80
z	2.5	50	150 */

struct partikels{
	int posisiPartikel[3];
	double fitnessPartikel;
	double kecPartikel[3];
	int posTerbaik[3];
	double fitTerbaik;
	
}; 

double HitungFitness(int posisi[],int data[][3]){
	double hasil = 0.0;
	
	for(i=0;i<=2;i++){
		hasil+= data[i][0] * posisi[i] * posisi[i];
	}
	return hasil;
	
	
	
}


int main(){
	srand (time(NULL));
	int jmlpartikel = 10;
	int jmliterasi = 100;
	int totalposisi = 210;
	int dimensi =3;
	int i,j;
	double fitness;
	partikels partikel[10];
	//set data
	int data[3][3];
   	data[0][0] = 3.2;
	 data[0][1]= 10;
	 data[0][2]= 50;
	
	 data[1][0]= 3;
	 data[1][1]= 30;
	 data[1][2]= 80;
	 
	 data[2][0]= 2.5;
	 data[2][1]= 50;
	 data[2][2]= 150;
	 
	 
	
	//set minkecepatan dan maks kecepatan
	int minKec[dimensi - 1];
	int maxKec[dimensi - 1];
	
	for(i=0;i<=dimensi-1;i++){
		minKec[i]= -(data[i][2] - data[i][1])/10;
		maxKec[i]= (data[i][2] - data[i][1])/10;
	
	}
	
//	inisialisasi partikel pada posisi acak
	double globalFitness = 9999999.99999 ;
	int posisiTerbaik[3];
	
	int posisi[dimensi-1];
	int indexPosisiTerbaik;
	for(i=0;i<=9;i++){
		int jumlahposisi = 0;
		do{
			jumlahposisi=0;
			for(j=0;j<=dimensi-1;j++){
				posisi[j] = data[j][1] + rand() % (data[j][2] - data[j][1] + 1);
				jumlahposisi += posisi[j];
			}
			int selisih = totalposisi - jumlahposisi;
			int  idx = rand() % 3;
			
			int posisiBaru = posisi[idx] + selisih
;			if( posisiBaru < data[idx][1]) continue;
			if( posisiBaru > data[idx][2]) continue;
			jumlahposisi = jumlahposisi - posisi[idx] + posisiBaru;
            posisi[idx] = posisiBaru;
			
		}while(jumlahposisi != totalposisi);
		//inisialisasi kecepatan partikel awal dgn kecepatan acak
		double kecepatanAcak[3];
		for(j=0;j<=2;j++){
			double lo = -1 * ((data[j][2] - data[j][1]) / 10);
            double hi = (data[j][2] - data[j][1]) / 10;
            
            kecepatanAcak[j] =  (double)rand()/(RAND_MAX+1) *(hi - lo)+lo;  
            
		}
		fitness = HitungFitness(posisi,data);
//		printf ("%lf\n",fitness);
		//set nilai ke tiap partikel
		std::copy(posisi, posisi + 3,partikel[i].posisiPartikel);
		partikel[i].fitnessPartikel = fitness;
		std::copy(kecepatanAcak, kecepatanAcak + 3,partikel[i].kecPartikel);
		std::copy(posisi, posisi + 3,partikel[i].posTerbaik);
		partikel[i].fitTerbaik = fitness;
		
		printf("Partikel ke- %d ,nilai fungsi = %lf \n",i+1,partikel[i].fitnessPartikel);
		if(partikel[i].fitnessPartikel < globalFitness){
			globalFitness =  partikel[i].fitnessPartikel;
			std::copy(partikel[i].posTerbaik,partikel[i].posTerbaik + 3, posisi );
			indexPosisiTerbaik = i ;
			
		}
		
	
	}
	printf("\nPosisi Terbaik Sementara\n");
	printf("Partikel %d nilai fungsi = %lf",indexPosisiTerbaik+1,partikel[indexPosisiTerbaik].fitnessPartikel);

	
	return 0;
	
}
