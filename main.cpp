#include <iostream>

using namespace std;

void pedirValores(int*a,int*b,int*c,int*d){
    /*Esta funcion es para pedir las dimensiones de las dos matrices a ser multiplicadas, y por ende las dimensiones
    de la matriz resultante, recordando que el numero de columnas de la primera matriz debe ser el numero de filas
    de la segunda matriz si esta condicion no se cumple se vuelve a pedir los datos para evitar errores*/
    cout << "Recuerda que el numero de columnas de la primera matriz debe ser igual al de columnas de la segunda matriz\n";
    cout << "Ingresa numero de filas de la primera matriz: ";
    cin >> *a;
    cout << "Ingresa numero de columnas de la primera matriz: ";
    cin >> *b;
    cout << "Ingresa numero de filas de la segunda matriz: ";
    cin >> *c;
    cout << "Ingresa numero de columnas de la segunda matriz: ";
    cin >> *d;
    if(*b!=*c)
        pedirValores(a,b,c,d);
}

void crearM(int**matriz,int n,int m){
    /*Funcion para crear filas en una matriz, siendo que cada valor en el arreglo matriz es un puntero que
    apunta a una direccion de memoria sin usar*/
    if(n!=1){
        crearM(matriz,n-1,m);
    }
    matriz[n-1] = new int[m];
}
/*Funciones para llenar la matriz, usando dos funciones recursivas, una que recorre las filas (llenadoM) y
otra que recorre columnas (llenarF) siendo esta la encargada de pedir los valores para cada elemento de la matriz*/
void llenarF(int**matriz,int n,int m){
    if(m!=1){
        llenarF(matriz,n,m-1);
    }
    //*(*(matriz+n)+(m-1))=n*(m-1);
    cout <<"ingresar valor para fila "<<n<<" columna "<<m-1<<": ";
    cin>>*(*(matriz+n)+(m-1));//ingresar el valor para matriz[n][m-1]
}
void llenadoM(int**matriz,int n,int m){
    if(n!=1){
        llenadoM(matriz,n-1,m);
    }
    llenarF(matriz,n-1,m);
}
//imprimir matrices
/*Funciones para mostrar la matriz, usando dos funciones recursivas, una que recorre las filas (mostrarM) y
otra que recorre columnas (mostrarF) siendo esta la que imprime cada elemento de la matriz*/
void mostrarF(int**matriz,int n,int m){
    if(m!=1){
        mostrarF(matriz,n,m-1);
    }
    cout<<*(*(matriz+n)+(m-1))<<" ";//imprimir el valor de matriz[n][m-1]
}
void mostrarM(int**matriz,int n,int m){
    if(n!=1){
        mostrarM(matriz,n-1,m);
    }
    mostrarF(matriz,n-1,m);
    cout<<"\n";
}
//multiplicacion
/*Multiplicacion de dos matrices ingresadas dividida en 3 funciones recursivas que funcionan como una iteracion, una que
recorre las filas de la matrizA (multiplicacion), una que recorre las columnas de la matrizB (columnas) y una que otorga
el valor para cada elemento de la matriz resultante*/
void elementos(int**matA,int**matB,int**matR,int n,int m,int o){
    if(o!=1){
        elementos(matA,matB,matR,n,m,o-1);
    }
    *(*(matR+n)+m)+=(*(*(matA+n)+(o-1)))*(*(*(matB+(o-1))+m));
}
void columnas(int**matA,int**matB,int**matR,int n,int m,int o){
    if(m!=1){
        columnas(matA,matB,matR,n,m-1,o);
    }
    *(*(matR+n)+m-1)=0;
    elementos(matA,matB,matR,n,m-1,o);
}
void multiplicacion(int**matA,int**matB,int**matR,int n,int m,int o){
    if(n!=1){
        multiplicacion(matA,matB,matR,n-1,m,o);
    }
    columnas(matA,matB,matR,n-1,m,o);
}
//borrar
/*Funciones para borrar las matrices creadas, usando dos funciones recursivas, una que recorre y elimina las filas (borrarF)
y otra que elimina la matriz (borrarM), siendo esto ejecutado al final para evitar errores*/
void borrarF(int**matriz,int n,int m){
    if(n!=0){
        borrarF(matriz,n-1,m);
    }
    delete[] (*(matriz+n));
}
void borrarM(int**matriz,int n,int m){
    borrarF(matriz,n-1,m);
    delete[] matriz;
}
int main()
{
    /*se crean las variables para almacenar las dimensiones de las matrices, como
    punteros para poder liberar el espacio de memoria de forma sencilla*/
    int*n=new int;
    int*m=new int;
    int*n2=new int;
    int*m2=new int;
    //funcion para ingresar las dimensiones de las matrices
    pedirValores(n,m,n2,m2);
    //se crean las matrices y se usa una funcion para crear fila por fila
    int**matrizA = new int*[*n];
    int**matrizB = new int*[*n2];
    int**matrizR = new int*[*n];
    crearM(matrizA,*n,*m);
    crearM(matrizB,*n2,*m2);
    crearM(matrizR,*n,*m2);
    //funciones para ingresar los valores de las dos matrices a ser multiplicadas
    llenadoM(matrizA,*n,*m);
    llenadoM(matrizB,*n2,*m2);
    //Se ejecuta la funcion de multiplicacion y se imprimen las matrices
    multiplicacion(matrizA,matrizB,matrizR,*n,*m2,*m);
    cout<<"matrizA:\n";
    mostrarM(matrizA,*n,*m);
    cout<<"matrizB:\n";
    mostrarM(matrizB,*n2,*m2);
    cout<<"matriz resultante:\n";
    mostrarM(matrizR,*n,*m2);
    //Se eliminan las matrices y las variables creadas para liberar el espacio de memoria
    borrarM(matrizA,*n,*m);
    borrarM(matrizB,*n2,*m2);
    borrarM(matrizR,*n,*m2);
    delete n;
    delete m;
    delete n2;
    delete m2;
    return 0;
}
