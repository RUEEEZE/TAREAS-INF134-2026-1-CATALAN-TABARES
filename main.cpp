#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// clase de arreglo extensible
class ArregloExtensible {
private:
    int* B;
    unsigned long n;
    unsigned long capacidad;

    unsigned long siguiente_potencia(unsigned long x){
        if(x == 0) return 0;
        unsigned long p = 1;
        while(p < x) p *= 2;
        return p;
    }

    void redimensionar(unsigned long nuevaCapacidad) {
        int* nuevo = new int[nuevaCapacidad];

        for (unsigned long i = 0; i < n; i++) {
            nuevo[i] = B[i];
        }

        delete[] B;
        B = nuevo;
        capacidad = nuevaCapacidad;
    }

public:
    ArregloExtensible() {
        B = NULL;
        n = 0;
        capacidad = 0;
    }

    ArregloExtensible(unsigned long inicial_n){
        n = inicial_n;
        capacidad = siguiente_potencia(n);

        if(capacidad > 0)
            B = new int[capacidad];
        else
            B = NULL;
    }

    ArregloExtensible(unsigned long inicial_n, int v){
        n = inicial_n;
        capacidad = siguiente_potencia(n);

        if(capacidad > 0){
            B = new int[capacidad];
            for(unsigned long i = 0; i < n; i++){
                B[i] = v;
            }
        } else {
            B = NULL;
        }
    }

    ~ArregloExtensible() {
        delete[] B;
    }

    bool setValue(unsigned long i, int v) {
        if (i >= n) return false;
        B[i] = v;
        return true;
    }

    int getValue(unsigned long i) {
        if (i >= n) {
            cerr << "Error de acceso al arreglo" << endl;
            exit(1);
        }
        return B[i];
    }

    void append(int v) {
        if (n == capacidad) {
            unsigned long nueva = (capacidad == 0) ? 1 : capacidad * 2;
            redimensionar(nueva);
        }
        B[n++] = v;
    }

    void remove() {
        if (n == 0) return;

        n--;

        if (n > 0 && n <= capacidad / 2) {
            redimensionar(capacidad / 2);
        }
    }

    unsigned long size() {
        return n;
    }
};

// función segura para leer enteros
bool leerEntero(int &x) {
    if (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    return true;
}

// leer archivo
void leerArchivo(ArregloExtensible &arr, string nombre) {
    ifstream file(nombre);

    if (!file) {
        cout << "Error al abrir archivo" << endl;
        return;
    }

    int num;
    while (file >> num && num != -1) {
        arr.append(num);
    }

    file.close();
    cout << "Archivo leído correctamente" << endl;
}

// menu
void menu() {
    cout << "\n1. Append\n";
    cout << "2. Remove\n";
    cout << "3. Get\n";
    cout << "4. Set\n";
    cout << "5. Size\n";
    cout << "6. Salir\n";
}

// main
int main() {
    ArregloExtensible arr;
    string archivo;

    cout << "Ingrese nombre del archivo: ";
    cin >> archivo;

    leerArchivo(arr, archivo);

    int opcion;

    do {
        menu();
        cout << "Opcion: ";

        if (!leerEntero(opcion)) {
            cout << "Entrada invalida\n";
            continue;
        }

        if (opcion == 1) {
            int v;
            cout << "Valor: ";
            if (leerEntero(v)) {
                arr.append(v);
            } else {
                cout << "Entrada invalida\n";
            }
        }

        else if (opcion == 2) {
            arr.remove();
        }

        else if (opcion == 3) {
            int i;
            cout << "Indice: ";
            if (leerEntero(i)) {
                cout << arr.getValue(i) << endl;
            } else {
                cout << "Entrada invalida\n";
            }
        }

        else if (opcion == 4) {
            int i, v;
            cout << "Indice y valor: ";
            if (leerEntero(i) && leerEntero(v)) {
                if (!arr.setValue(i, v)) {
                    cout << "Indice invalido\n";
                }
            } else {
                cout << "Entrada invalida\n";
            }
        }

        else if (opcion == 5) {
            cout << "Size: " << arr.size() << endl;
        }

    } while (opcion != 6);

    return 0;
}