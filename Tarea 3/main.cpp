#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* ****
 * Struct Nodo
 ******
 * Nodo para lista de adyacencia
 ******
 * Input:
 * ninguno
 ******
 * Returns:
 * ninguno
 **** */
struct Nodo {
    int destino;
    Nodo* siguiente;

    Nodo(int d) {
        destino = d;
        siguiente = nullptr;
    }
};

/******
* Struct Edificio
******
* Almacena datos para ordenar la salida
******
* Input:
* Ninguno
******
* Returns:
* Ninguno
******/
struct Edificio{
    int id;
    int tiempo_inicio;
};

/******
* void merge
******
* Función auxiliar para mezclar sub-arreglos en mergeSort
******
* Input:
* Edificio* arr : Arreglo a ordenar
* int inicio : Índice de inicio
* int medio : Índice central
* int fin : Índice de término
******
* Returns:
* void, modifica el arreglo original
******/
void merge(Edificio* arr, int inicio, int medio, int fin){
    int n1 = medio - inicio + 1;
    int n2 = fin = medio;
    Edificio* L = new Edificio[n1];
    Edificio* R = new Edificio[n2];
    
    for (int i = 0; i < n1; i++){
        L[i] = arr[inicio + i];
    }
    for (int j = 0; j < n2; j++){
        R[j] = arr[medio + 1 + j];
    }
    
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2){
        bool L_menor = false;
        if (L[i].tiempo_inicio < R[j].tiempo_inicio){
            L_menor = true;
        }
        else if (L[i].tiempo_inicio == R[j].tiempo_inicio && L[i].id < R[j].id){
            L_menor = true;
        }
        
        if (L_menor){
            arr[k++] = L[i++];
        }
        else{
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1){
        arr[k++] = L[i++];
    }
    while (j < n2){
        arr[k++] = R[j++];
    }
    
    delete[] L;
    delete[] R;
}

class Cola {
private:
    int* datos;
    int frente;
    int final;
    int capacidad;

public:

    Cola(int tam) {
        capacidad = tam;
        datos = new int[capacidad];

        frente = 0;
        final = 0;
    }

    ~Cola() {
        delete[] datos;
    }

    bool estaVacia() {
        return frente == final;
    }

    void push(int valor) {
        datos[final] = valor;
        final++;
    }

    int pop() {
        int valor = datos[frente];
        frente++;
        return valor;
    }
};

/* ****
 * Class Grafo
 ******
 * Almacena edificios y dependencias
 **** */
class Grafo {
private:
    int cantidadEdificios;
    int* tiempos;
    Nodo** adyacencia;

public:

    Grafo(int n) {
        cantidadEdificios = n;

        tiempos = new int[n + 1];

        adyacencia = new Nodo*[n + 1];

        for(int i = 0; i <= n; i++) {
            adyacencia[i] = nullptr;
            tiempos[i] = 0;
        }
    }

    ~Grafo() {

        for(int i = 1; i <= cantidadEdificios; i++) {

            Nodo* actual = adyacencia[i];

            while(actual != nullptr) {
                Nodo* borrar = actual;
                actual = actual->siguiente;
                delete borrar;
            }
        }

        delete[] adyacencia;
        delete[] tiempos;
    }

    void cambiarTiempo(int edificio, int nuevoTiempo) {
        tiempos[edificio] = nuevoTiempo;
    }

    int obtenerTiempo(int edificio) {
        return tiempos[edificio];
    }

    void agregarArista(int origen, int destino) {

        Nodo* nuevo = new Nodo(destino);

        nuevo->siguiente = adyacencia[origen];

        adyacencia[origen] = nuevo;
    }

    void imprimirGrafo() {

        for(int i = 1; i <= cantidadEdificios; i++) {

            cout << i << ": ";

            Nodo* actual = adyacencia[i];

            while(actual != nullptr) {
                cout << actual->destino << " ";
                actual = actual->siguiente;
            }

            cout << endl;
        }
    }

    Nodo* obtenerLista(int edificio) {
        return adyacencia[edificio];
    }

    int obtenerCantidadEdificios() {
        return cantidadEdificios;
    }

    int* calcularGrado() {

        int* grado = new int[cantidadEdificios + 1];

        for(int i = 0; i <= cantidadEdificios; i++) {
            grado[i] = 0;
        }

        for(int i = 1; i <= cantidadEdificios; i++) {

            Nodo* actual = adyacencia[i];

            while(actual != nullptr) {

                grado[actual->destino]++;

                actual = actual->siguiente;
            }
        }

        return grado;
    }

    void imprimirGrado() {

        int* grado = calcularGrado();

        cout << endl;
        cout << "Grado:" << endl;

        for(int i = 1; i <= cantidadEdificios; i++) {

            cout << "Edificio "
                << i
                << " -> "
                << grado[i]
                << endl;
        }

        delete[] grado;
    }

    bool tieneCiclo() {

        int* grado = calcularGrado();

        Cola cola(cantidadEdificios + 1);

        for(int i = 1; i <= cantidadEdificios; i++) {

            if(grado[i] == 0) {
                cola.push(i);
            }
        }

        int visitados = 0;

        while(!cola.estaVacia()) {

            int actual = cola.pop();

            visitados++;

            Nodo* vecino = adyacencia[actual];

            while(vecino != nullptr) {

                grado[vecino->destino]--;

                if(grado[vecino->destino] == 0) {
                    cola.push(vecino->destino);
                }

                vecino = vecino->siguiente;
            }
        }

        delete[] grado;
        return visitados != cantidadEdificios;
    }

    void probarCiclo() {

        if(tieneCiclo()) {
            cout << endl;
            cout << "Hay ciclo" << endl;
        }
        else {
            cout << endl;
            cout << "No hay ciclo" << endl;
        }
    }
};

int main() {

    int n;
    int m;
    int q;

    cin >> n >> m >> q;

    Grafo grafo(n);

    for(int i = 1; i <= n; i++) {

        int tiempo;
        cin >> tiempo;

        grafo.cambiarTiempo(i, tiempo);
    }

    for(int i = 0; i < m; i++) {

        int a;
        int b;

        cin >> a >> b;

        grafo.agregarArista(a, b);
    }


    grafo.imprimirGrafo();

    grafo.imprimirGrado();

    grafo.probarCiclo();

    cout << "Lectura completada" << endl;

    return 0;
}
