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

    void eliminarArista(int origen, int destino) {

        Nodo* actual = adyacencia[origen];
        Nodo* previo = nullptr;

        while(actual != nullptr) {

            if(actual->destino == destino) {

                if(previo == nullptr) {
                    adyacencia[origen] = actual->siguiente;
                } else {
                    previo->siguiente = actual->siguiente;
                }
 
                delete actual;
                return;
            }

            previo = actual;
            actual = actual->siguiente;
        }
    }

    bool existeArista(int origen, int destino) {

        Nodo* actual = adyacencia[origen];

        while(actual != nullptr) {

            if(actual->destino == destino) {
                return true;
            }

            actual = actual->siguiente;
        }

        return false;
    }

    int* ordenTopologico(int& cantidad) {

        int* grado = calcularGrado();

        Cola cola(cantidadEdificios + 1);

        for(int i = 1; i <= cantidadEdificios; i++) {

            if(grado[i] == 0) {
                cola.push(i);
            }
        }

        int* orden = new int[cantidadEdificios];
        cantidad = 0;

        while(!cola.estaVacia()) {

            int actual = cola.pop();

            orden[cantidad] = actual;
            cantidad++;

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

        if(cantidad != cantidadEdificios) {

            delete[] orden;
            return nullptr;
        }

        return orden;
    }

    void imprimirOrdenConstruccion() {

        int cantidad;

        int* orden = ordenTopologico(cantidad);

        if(orden == nullptr) {
            cout << -1 << endl;
            return;
        }

        for(int i = 0; i < cantidad; i++) {

            cout << orden[i];

            if(i < cantidad - 1) {
                cout << " ";
            }
        }

        cout << endl;

        delete[] orden;
    }

    int calcularTiempoTotal() {

        int cantidad;

        int* orden = ordenTopologico(cantidad);

        if(orden == nullptr) {
            return -1;
        }

        int* inicio = new int[cantidadEdificios + 1];
        int* termino = new int[cantidadEdificios + 1];

        for(int i = 1; i <= cantidadEdificios; i++) {

            inicio[i] = 0;

            termino[i] = tiempos[i];
        }

        for(int k = 0; k < cantidad; k++) {

            int actual = orden[k];

            Nodo* vecino = adyacencia[actual];

            while(vecino != nullptr) {

                int siguiente = vecino->destino;

                if(termino[actual] > inicio[siguiente]) {

                    inicio[siguiente] = termino[actual];

                    termino[siguiente] =
                        inicio[siguiente] +
                        tiempos[siguiente];
                }

                vecino = vecino->siguiente;
            }
        }

        int respuesta = 0;

        for(int i = 1; i <= cantidadEdificios; i++) {

            if(termino[i] > respuesta) {
                respuesta = termino[i];
            }
        }

        delete[] inicio;
        delete[] termino;
        delete[] orden;

        return respuesta;
    }


    void imprimirEstado() {

        if(tieneCiclo()) {

            cout << -1 << endl;
            return;
        }

        imprimirOrdenConstruccion();

        cout << calcularTiempoTotal() << endl;
    }

};

int main() {

    int n;
    int m;
    int q;

cin >> n >> m >> q;

Grafo grafo(n);

// leer tiempos
for(int i = 1; i <= n; i++) {
    int tiempo;
    cin >> tiempo;
    grafo.cambiarTiempo(i, tiempo);
}

// leer aristas iniciales
for(int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    grafo.agregarArista(a, b);
}

// imprimir estado inicial
grafo.imprimirEstado();

// calcular raíz de q
int bloque = 1;

while(bloque * bloque < q) {
    bloque++;
}

// leer consultas
for(int i = 1; i <= q; i++) {

    int tipo;
    cin >> tipo;

    if(tipo == 1) {

        int edificio, tiempo;
        cin >> edificio >> tiempo;

        grafo.cambiarTiempo(edificio, tiempo);
    }

    else if(tipo == 2) {

        int a, b;
        cin >> a >> b;

        grafo.agregarArista(a, b);
    }

    else if(tipo == 3) {

        int a, b;
        cin >> a >> b;

        grafo.eliminarArista(a, b);
    }

    // cada sqrt(q) consultas
    if(i % bloque == 0) {
        grafo.imprimirEstado();
    }
}
}
