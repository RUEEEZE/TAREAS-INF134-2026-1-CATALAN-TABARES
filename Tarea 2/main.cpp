#include <iostream>
#include "Linea.h"
#include <string>

class Linea{
private:
    struct Nodo{
        Nodo* izquierda;
        Nodo* derecha;
        Nodo* padre;
        std::string texto;
        unsigned int peso;
    };

    Nodo* raiz;
    int w;

public:

    // Función auxiliar para crear un nodo hoja con el texto dado
    Nodo* crearHoja(string texto){
        Nodo* nuevo = new Nodo;
        nuevo->izquierda = NULL;
        nuevo->derecha = NULL;
        nuevo->padre = NULL;
        nuevo->texto = texto;
        nuevo->peso = texto.length();
        return nuevo;
    }

    // Función auxiliar para unir dos nodos y crear un nodo padre
    Nodo* unir(Nodo* izquierda, Nodo* derecha){
        Nodo* padre = new Nodo;
        padre->izquierda = izquierda;
        padre->derecha = derecha;
        padre->padre = NULL;
        izquierda->padre = padre;
        derecha->padre = padre;
        padre->texto = "";
        padre->peso = obtenerPesoTotal(izquierda);
        return padre;
    }

    // Función auxiliar para calcular el peso total de un nodo (suma de los pesos de sus hojas)
    unsigned int obtenerPesoTotal(Nodo* nodo){
        if (nodo == NULL){
            return 0;
        }
        if (nodo->izquierda == NULL && nodo->derecha == NULL){
            return nodo->peso;
        }
        return obtenerPesoTotal(nodo->izquierda) + obtenerPesoTotal(nodo->derecha);
    }

    Linea(std::string str, int w);

    // Función auxiliar para destruir el árbol de nodos
    void Linea::destruir(Nodo* nodo) {

        if (nodo == NULL){
            return;
        }

        destruir(nodo->izquierda);

        destruir(nodo->derecha);

        delete nodo;
    }

    Linea::~Linea() {

        destruir(raiz);
    }

    ~Linea(void);

    //Función para agregar un nuevo caracter en una posición dada
    void insertar(int posicion, char caracter){
        Nodo* actual = raiz;

        while (actual->izquierda || actual->derecha){
             if (posicion <= actual->peso && actual->izquierda) {
                actual->peso++; 
                actual = actual->izquierda;
            } 
             else{
                posicion -= actual->peso;
                actual = actual->derecha;
            }
        }

        std::string nuevoTexto = "";
        for (int i = 0; i < actual->texto.length(); i++) {
            if (i == posicion) nuevoTexto += caracter;
            nuevoTexto += actual->texto[i];
        }
        if (posicion == actual->texto.length()) {
            nuevoTexto += caracter;
        }
        actual->texto = nuevoTexto;
        actual->peso++;

        if (actual->texto.length() > w) {
            std::string textoCompleto = actual->texto;
            actual->texto = "";
            
            int mitad = textoCompleto.length() / 2;
            
            Nodo* hijoIzq = crearHoja(textoCompleto.substr(0, mitad));
            hijoIzq->padre = actual;

            Nodo* hijoDer = crearHoja(textoCompleto.substr(mitad));
            hijoDer->padre = actual;

            actual->izquierda = hijoIzq;
            actual->derecha = hijoDer;
            actual->peso = hijoIzq->peso;
        }
    }

    void eliminar(int posicion);

    int Linea::largoSubarbol(Nodo* nodo)
{
        if(nodo == nullptr)
            return 0;

        // nodo hoja
        if(nodo->izquierda == nullptr && nodo->derecha == nullptr)
            return nodo->texto.length();

        return largoSubarbol(nodo->izquierda) +
            largoSubarbol(nodo->derecha);
    }

    void concatenar(Linea* linea){
        if(linea == nullptr || linea->raiz == nullptr)
            return;

        if(this->raiz == nullptr)
        {
            this->raiz = linea->raiz;
            linea->raiz = nullptr;
            return;
        }

        Nodo* nuevaRaiz = new Nodo;

        nuevaRaiz->izquierda = this->raiz;
        nuevaRaiz->derecha = linea->raiz;

        nuevaRaiz->padre = nullptr;

        nuevaRaiz->texto = "";

        nuevaRaiz->peso = largoSubarbol(this->raiz);

        this->raiz->padre = nuevaRaiz;
        linea->raiz->padre = nuevaRaiz;

        this->raiz = nuevaRaiz;

        // evitar double free
        linea->raiz = nullptr;
    }

    void invertir(void);

    int print(void);
};

using namespace std;


void mostrarMenu() {
    cout << "\n===== MENU =====" << endl;
    cout << "1. Imprimir linea" << endl;
    cout << "2. Insertar caracter" << endl;
    cout << "3. Eliminar caracter" << endl;
    cout << "4. Invertir linea" << endl;
    cout << "5. Concatenar linea" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {

    string textoInicial;
    int w;

    cout << "Ingrese texto inicial: ";
    getline(cin, textoInicial);

    cout << "Ingrese valor de w: ";
    cin >> w;

    cin.ignore();

    Linea linea(textoInicial, w);

    int opcion = -1;

    while (opcion != 0) {

        mostrarMenu();
        cin >> opcion;

        if (opcion == 1) {

            cout << "\nContenido actual:" << endl;
            linea.print();
            cout << endl;

        }

        else if (opcion == 2) {

            int posicion;
            char caracter;

            cout << "Posicion: ";
            cin >> posicion;

            cout << "Caracter: ";
            cin >> caracter;

            linea.insertar(posicion, caracter);

            cout << "Caracter insertado." << endl;
        }

        else if (opcion == 3) {

            int posicion;

            cout << "Posicion a eliminar: ";
            cin >> posicion;

            linea.eliminar(posicion);

            cout << "Caracter eliminado." << endl;
        }

        else if (opcion == 4) {

            linea.invertir();

            cout << "Linea invertida." << endl;
        }

        else if (opcion == 5) {

            cin.ignore();

            string nuevoTexto;

            cout << "Texto a concatenar: ";
            getline(cin, nuevoTexto);

            Linea* nuevaLinea = new Linea(nuevoTexto, w);

            linea.concatenar(nuevaLinea);

            cout << "Concatenacion realizada." << endl;
        }

        else if (opcion == 0) {

            cout << "Saliendo..." << endl;
        }

        else {

            cout << "Opcion invalida." << endl;
        }
    }

    return 0;
}
