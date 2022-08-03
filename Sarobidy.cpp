// RAVELOSON Hasina Sarobidy
// ravelosonsarobidy7@gmail.com
// +261346748683

//--------------------------------------------------------------------


#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
using namespace std;


void displayMatrix(float** A, float* B, int N);
void error(string message);
void ** getData(float**& A, float *& B, float *& X, int &N);
void enfileData(float**& A, float *& B, float *&X, int &N);
void triangularisation(float**& A, float*& B, float*& X, int N);


int main () {   
    float **A(0), *B(0), *X(0);
    int i, j, N;
    cout << "La dimension de la matrice: \n\n N = ";
    cin >> N;
    enfileData(A, B, X, N);
    cout << "Le syteme est : \n";
    displayMatrix(A, B, N);
    triangularisation(A, B, X, N);
    system("pause");

    return 0;
} 


//Résolution 
void triangularisation(float**& A, float*& B, float*& X, int N) {
    int k=0, i=0, j=0, Lpiv;
    float s(0), piv, tpiv(0), t(0);

    for (k=0; k<N-1; k++){
        //  Recherche du plus grand pivot
        piv=0; 

        for (i=k; i<N; i++){
            if (fabs(A[i][k])>piv){
                piv=fabs(A[i][k]);
                Lpiv=i; 
            }
        }

        //permutation des lignes pour A
        for (j=k; j<N; j++){
            tpiv=A[k][j];
            A[k][j]=A[Lpiv][j];
            A[Lpiv][j]=tpiv;
        }
        //pour B
        t=B[k];
        B[k]=B[Lpiv];
        B[Lpiv]=t;

        //Triangularisation 
        for(i=k+1; i<=N-1; i++) {
            for(j=k+1; j<=N-1; j++) {
                A[i][j]=A[i][j]-A[i][k]*A[k][j]/A[k][k];
            }
            B[i]=B[i]-A[i][k]*B[k]/A[k][k];
            A[i][k]=0;
        }
    }
    
    for (i=N-1; i>=0; i--){
        s=0;
        for (j=i+1; j<N; j++)
            s=s+A[i][j]*X[j];
        
            X[i]=(B[i]-s)/A[i][i];
        
    }
    


        cout << "\n     METHODE DE GAUSS AVEC PIVOT PARTIEL\n";
        cout << "\n     La matrice apres elimination de Gauss est:\n";
        displayMatrix(A, B, N);
        cout << "\n * Apres resolution on obtient:\n\n\n";
        for (i=0; i<N; i++)
        cout << "X" << i+1 <<  " = " << X[i] << endl;   
    }

void error(string message){
    cout << " Erreur: " << message << endl;
    exit(1);
}

void** getData(float**& A, float*& B, float*& X, int& N){
    //création des matrices et vecteurs
    A=new (nothrow) float *[N];
    if(A){
        for(int i=0; i<N; i++){
            A[i] = new (nothrow) float [N];
            if(!A[i]) error("Probleme de memoire pour A[i]!");
        }
    } else error("Problème de memoire de A!");

    B= new (nothrow) float [N];
    if(!B) error("Problème de memoire de B!");

    X = new (nothrow) float [N];
    if(!X) error("Probleme de memoire de X!");
}

void enfileData(float**& A, float*&  B, float*& X, int& N){
    ifstream pfile(0);
    int i=0, j=0;

    //creation des matrices et vecteurs
    pfile.open("data.txt");

//     veuillez entrez les donnees de la sorte que les nombres sont suivis d'espaces
//
// 4
// 2 1 0 4
// -4 -2 3 -7
// 4 1 -2 8
// 0 -3 -12 -1
// 2
// -9
// 2
// 2
//
// avec la 1ere ligne la dimension les N dernieres lignes les valeurs de B[]
    if(!pfile) error("Fichier introuvable!");
    pfile >> N;
    getData(A, B, X, N);

    
    //transcription des donnees
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            pfile >> A[i][j];
        }
    }

    for(i=0; i<N; i++)
    pfile >> B[i];

    //fermer le fichier
    pfile.close();

}

void displayMatrix(float** A, float* B, int N){
    int i,j;
    printf("\n\n");
    for (i=0; i<N; i++)
    {
        cout << " [";
        for (j=0; j<N; j++)
            cout << A[i][j] << "\t";
        
        cout << "] [" << B[i] << "]";
        cout << "\n";
    }
  
}
