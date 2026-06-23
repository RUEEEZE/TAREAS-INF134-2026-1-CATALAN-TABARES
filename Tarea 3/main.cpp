#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* ****
 * Struct Edificio
 ******
 * Almacena id y tiempo de inicio para ordenamiento
 **** */
struct Edificio {
    int id;
    int tiempo_inicio;
};

/* ****
 * void merge
 ******
 * Mezcla dos subarreglos ordenados
 **** */
void merge(Edificio* arr, int inicio, int medio, int fin){
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;
    Edificio* L = new Edificio[n1];
    Edificio* R = new Edificio[n2];
    
    for(int i = 0; i < n1; i++){
        L[i] = arr[inicio + i];
    }
    for (int j = 0; j < n2; j++){
        R[j] = arr[medio + 1 + j];
    }
    
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2){
        if (L[i].tiempo_inicio < R[j].tiempo_inicio || (L[i].tiempo_inicio == R[j].tiempo_inicio && L[i].id < R[j].id)){
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

/* ****
 * void mergeSort
 ******
 * Algoritmo de ordenamiento recursivo
 **** */
void mergeSort(Edificio* arr, int inicio, int fin){
    if (inicio >= fin){
        return;
    }
    
    int medio = inicio + (fin - inicio) / 2;
    mergeSort(arr, inicio, medio);
    mergeSort(arr, medio + 1, fin);
    merge(arr, inicio, medio, fin);
}

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

    /******
    * Grafo Grafo
    ******
    * Constructor de la clase Grafo. Inicializa arreglos de tiempos y adyacencias.
    ******
    * Input:
    * int n : Cantidad total de edificios en el grafo
    ******
    * Returns:
    * Ninguno
    ******/
    Grafo(int n) {
        cantidadEdificios = n;

        tiempos = new int[n + 1];

        adyacencia = new Nodo*[n + 1];

        for(int i = 0; i <= n; i++) {
            adyacencia[i] = nullptr;
            tiempos[i] = 0;
        }
    }

    /******
    * ~Grafo ~Grafo
    ******
    * Destructor de la clase Grafo. Libera toda la memoria dinámica utilizada.
    ******
    * Input:
    * Ninguno
    ******
    * Returns:
    * Ninguno (Destructor)
    ******/
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

    /******
    * void cambiarTiempo
    ******
    * Actualiza el tiempo de construcción de un edificio específico.
    ******
    * Input:
    * int edificio : ID del edificio a modificar
    * int nuevoTiempo : Nueva duración de la construcción
    ******
    * Returns:
    * void, actualiza el arreglo de tiempos internamente
    ******/
    void cambiarTiempo(int edificio, int nuevoTiempo) {
        tiempos[edificio] = nuevoTiempo;
    }

    /******
    * int obtenerTiempo
    ******
    * Retorna el tiempo de construcción asignado a un edificio.
    ******
    * Input:
    * int edificio : ID del edificio consultado
    ******
    * Returns:
    * int, la duración de la construcción de dicho edificio
    ******/
    int obtenerTiempo(int edificio) {
        return tiempos[edificio];
    }

    /******
    * void agregarArista
    ******
    * Agrega una dependencia indicando que 'origen' debe construirse antes que 'destino'.
    ******
    * Input:
    * int origen : ID del edificio prerrequisito
    * int destino : ID del edificio que depende del origen
    ******
    * Returns:
    * void, inserta un nuevo nodo en la lista de adyacencia
    ******/
    void agregarArista(int origen, int destino) {

        if(existeArista(origen, destino)) {
            return;
        }

        Nodo* nuevo = new Nodo(destino);

        nuevo->siguiente = adyacencia[origen];

        adyacencia[origen] = nuevo;
    }

    /******
    * void imprimirGrafo
    ******
    * Imprime por consola la lista de adyacencia del grafo con fines de depuración.
    ******
    * Input:
    * Ninguno
    ******
    * Returns:
    * void, imprime los datos en pantalla
    ******/
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

    /******
    * Nodo* obtenerLista
    ******
    * Retorna el puntero inicial a la lista de vecinos de un edificio.
    ******
    * Input:
    * int edificio : ID del edificio consultado
    ******
    * Returns:
    * Nodo*, puntero al primer elemento de la lista enlazada de vecinos
    ******/
    Nodo* obtenerLista(int edificio) {
        return adyacencia[edificio];
    }

    /******
    * int obtenerCantidadEdificios
    ******
    * Retorna el número total de edificios registrados en el grafo.
    ******
    * Input:
    * Ninguno
    ******
    * Returns:
    * int, cantidad de nodos (edificios) del grafo
    ******/
    int obtenerCantidadEdificios() {
        return cantidadEdificios;
    }

    /******
    * int* calcularGrado
    ******
    * Calcula la cantidad de prerrequisitos (grado de entrada) de todos los edificios.
    ******
    * Input:
    * Ninguno
    ******
    * Returns:
    * int*, arreglo dinámico con los grados de entrada de cada nodo
    ******/
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

    /******
    * void imprimirGrado
    ******
    * Imprime por consola los grados de entrada de cada edificio.
    ******
    * Input:
    * Ninguno
    ******
    * Returns:
    * void, imprime datos de depuración en pantalla
    ******/
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

    /******
    * bool tieneCiclo
    ******
    * Verifica si existe un ciclo de dependencias en el grafo usando Kahn's Algorithm.
    ******
    * Input:
    * Ninguno
    ******
    * Returns:
    * bool, retorna true si hay un ciclo, false en caso contrario
    ******/
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

    /******
    * void probarCiclo
    ******
    * Imprime un mensaje indicando si el grafo actual posee un ciclo o no.
    ******
    * Input:
    * Ninguno
    ******
    * Returns:
    * void, imprime mensaje por consola
    ******/
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

    /******
    * void eliminarArista
    ******
    * Busca y elimina una dependencia específica entre dos edificios.
    ******
    * Input:
    * int origen : ID del edificio prerrequisito
    * int destino : ID del edificio que ya no depende del origen
    ******
    * Returns:
    * void, actualiza la lista enlazada quitando el nodo correspondiente
    ******/
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

    /******
    * bool existeArista
    ******
    * Verifica si una dependencia específica existe en el grafo actual.
    ******
    * Input:
    * int origen : ID del edificio prerrequisito
    * int destino : ID del edificio dependiente
    ******
    * Returns:
    * bool, true si la arista existe, false en caso contrario
    ******/
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

    /******
    * int* ordenTopologico
    ******
    * Genera un orden de construcción válido utilizando un ordenamiento topológico.
    ******
    * Input:
    * int& cantidad : Referencia para guardar la cantidad de nodos ordenados
    ******
    * Returns:
    * int*, arreglo con el orden. Retorna nullptr si hay un ciclo.
    ******/
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

    /******
    * void imprimirOrdenConstruccion
    ******
    * Imprime por consola el orden topológico directo sin reordenamiento posterior.
    ******
    * Input:
    * Ninguno
    ******
    * Returns:
    * void, imprime el arreglo por consola o -1 si falla
    ******/
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

    /******
    * int calcularTiempoTotal
    ******
    * Calcula el tiempo total necesario para terminar todos los edificios en el orden actual.
    ******
    * Input:
    * Ninguno
    ******
    * Returns:
    * int, cantidad de tiempo que dura la ruta crítica del grafo
    ******/
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


    /******
    * void imprimirEstado
    ******
    * Verifica ciclos, calcula tiempos, ordena los edificios según tiempo de inicio e imprime el parche.
    ******
    * Input:
    * Ninguno
    ******
    * Returns:
    * void, salida por consola con el formato exigido para los parches
    ******/
    void imprimirEstado(){
        int cantidad;
        int* orden = ordenTopologico(cantidad);

        if(orden == nullptr){
            cout << -1 << endl;
            return;
        }

        int* inicio = new int[cantidadEdificios + 1];
        int* termino = new int[cantidadEdificios + 1];

        for(int i = 1; i <= cantidadEdificios; i++){
            inicio[i] = 0;
            termino[i] = tiempos[i];
        }

        for(int k = 0; k < cantidad; k++){
            int actual = orden[k];
            Nodo* vecino = adyacencia[actual];

            while(vecino != nullptr){
                int siguiente = vecino->destino;
                if(termino[actual] > inicio[siguiente]){
                    inicio[siguiente] = termino[actual];
                    termino[siguiente] = inicio[siguiente] + tiempos[siguiente];
                }
                vecino = vecino->siguiente;
            }
        }

        int tiempoMaximo = 0;
        for(int i = 1; i <= cantidadEdificios; i++){
            if(termino[i] > tiempoMaximo) tiempoMaximo = termino[i];
        }

        Edificio* arregloOrdenar = new Edificio[cantidad];
        for(int k = 0; k < cantidad; k++){
            int id_edificio = orden[k];
            arregloOrdenar[k].id = id_edificio;
            arregloOrdenar[k].tiempo_inicio = inicio[id_edificio];
        }

        mergeSort(arregloOrdenar, 0, cantidad - 1);
        for(int i = 0; i < cantidad; i++){
            cout << arregloOrdenar[i].id;
            if(i < cantidad - 1) cout << " ";
        }
        cout << endl << tiempoMaximo << endl;

        delete[] inicio;
        delete[] termino;
        delete[] orden;
        delete[] arregloOrdenar;
    }
};

int main(){

    // Optimización para evitar exceder el límite de 1 segundo
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int m;
    int q;

    // Evita errores si el archivo está vacío
    if (!(cin >> n >> m >> q)){
        return 0;
    }
    
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
    
        if(tipo == 1){
            int edificio, tiempo;
            cin >> edificio >> tiempo;
    
            grafo.cambiarTiempo(edificio, tiempo);
        }
        else if(tipo == 2){
            int a, b;
            cin >> a >> b;
    
            grafo.agregarArista(a,b);
        }
        else if(tipo == 3){
            int a, b;
            cin >> a >> b;
    
            grafo.eliminarArista(a, b);
        }
    
        // cada sqrt(q) consultas
        if(i % bloque == 0){
            grafo.imprimirEstado();
        }
    }

    return 0;
}
