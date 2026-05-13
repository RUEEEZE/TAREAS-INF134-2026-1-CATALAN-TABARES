#include <iostream>
#include <string>
include namespace std

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

    /*****
    * Nodo* crearHoja
    ******
    * Crea un nuevo nodo hoja inicializando sus punteros en NULL y asignando el texto y peso.
    ******
    * Input:
    * std::string texto : Cadena de caracteres que almacenará el nodo hoja.
    ******
    * Returns:
    * Nodo*, Puntero al nuevo nodo creado.
    *****/
    Nodo* crearHoja(std::string texto){
        Nodo* nuevo = new Nodo;
        nuevo->izquierda = NULL;
        nuevo->derecha = NULL;
        nuevo->padre = NULL;
        nuevo->texto = texto;
        nuevo->peso = texto.length();
        return nuevo;
    }

    /*****
    * Nodo* unir
    ******
    * Une dos nodos existentes bajo un nuevo nodo padre, actualizando los punteros y calculando el peso total.
    ******
    * Input:
    * Nodo* izquierda : Puntero al nodo que será el hijo izquierdo.
    * Nodo* derecha : Puntero al nodo que será el hijo derecho.
    ******
    * Returns:
    * Nodo*, Puntero al nuevo nodo padre creado.
    *****/
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

    /*****
    * unsigned int obtenerPesoTotal
    ******
    * Calcula recursivamente el peso total de un subárbol sumando los pesos de sus nodos hoja.
    ******
    * Input:
    * Nodo* nodo : Puntero al nodo raíz del subárbol a evaluar.
    ******
    * Returns:
    * unsigned int, Suma total de los pesos del subárbol.
    *****/
    unsigned int obtenerPesoTotal(Nodo* nodo){
        if (nodo == NULL){
            return 0;
        }
        if (nodo->izquierda == NULL && nodo->derecha == NULL){
            return nodo->peso;
        }
        return obtenerPesoTotal(nodo->izquierda) + obtenerPesoTotal(nodo->derecha);
    }

    /*****
    * Linea Linea
    ******
    * Constructor que inicializa el árbol con una cadena de texto y establece el límite de tamaño w.
    ******
    * Input:
    * std::string str : Cadena de texto inicial para el árbol.
    * int w : Peso máximo permitido para los nodos hoja.
    ******
    * Returns:
    * void, No aplica retorno para constructores.
    *****/
    Linea(std::string str, int w){
        this->w = w;
        raiz = crearHoja(str);
    }

    /*****
    * void destruir
    ******
    * Función auxiliar que libera recursivamente la memoria dinámica de los nodos de un subárbol.
    ******
    * Input:
    * Nodo* nodo : Puntero al nodo a partir del cual se destruirá el árbol.
    ******
    * Returns:
    * void, No retorna valor.
    *****/
    void destruir(Nodo* nodo) {
        if (nodo == NULL){
            return;
        }
        destruir(nodo->izquierda);
        destruir(nodo->derecha);
        delete nodo;
    }

    /*****
    * Linea Linea
    ******
    * Constructor que inicializa el árbol con una cadena de texto y establece el límite de tamaño w.
    ******
    * Input:
    * std::string str : Cadena de texto inicial para el árbol.
    * int w : Peso máximo permitido para los nodos hoja.
    ******
    * Returns:
    * void, No aplica retorno para constructores.
    *****/
    ~Linea(){
        destruir(raiz);
    }

    /*****
    * void insertar
    ******
    * Inserta un carácter en una posición específica. Si el nodo hoja excede w, el nodo se divide.
    ******
    * Input:
    * int posicion : Índice numérico donde se insertará el nuevo carácter.
    * char caracter : Carácter a insertar en el texto.
    ******
    * Returns:
    * void, No retorna valor.
    *****/
    void insertar(int posicion, char caracter){
        Nodo* actual = raiz;

        while (actual->izquierda || actual->derecha){
             if (posicion < actual->peso && actual->izquierda) {
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

    /*****
    * void eliminar
    ******
    * Elimina el carácter ubicado en una posición específica del árbol y actualiza los pesos de la ruta.
    ******
    * Input:
    * int posicion : Índice numérico del carácter que se desea eliminar.
    ******
    * Returns:
    * void, No retorna valor.
    *****/
    void eliminar(int posicion){
        Nodo* actual = raiz;
        
        while (actual->izquierda || actual->derecha) {
            if (posicion < actual->peso && actual->izquierda) {
                actual->peso--; 
                actual = actual->izquierda;
            } 
            else{
                posicion -= actual->peso;
                actual = actual->derecha;
            }
        }

        if (posicion >= 0 && posicion < actual->texto.length()){
            std::string nuevoTexto = "";
            for (int i = 0; i < actual->texto.length(); i++){
                if (i != posicion){
                    nuevoTexto += actual->texto[i];
                }
            }
            actual->texto = nuevoTexto;
            actual->peso--;
        }
    }

    /*****
    * int largoSubarbol
    ******
    * Calcula la longitud total del texto contenido en todas las hojas de un subárbol dado.
    ******
    * Input:
    * Nodo* nodo : Puntero al nodo raíz del subárbol.
    ******
    * Returns:
    * int, Cantidad total de caracteres en el subárbol.
    *****/
    int largoSubarbol(Nodo* nodo){
        if(nodo == nullptr){
            return 0;
        }
        
        // nodo hoja
        if(nodo->izquierda == nullptr && nodo->derecha == nullptr){
            return nodo->texto.length();
        }

        return largoSubarbol(nodo->izquierda) +
            largoSubarbol(nodo->derecha);
    }

   /*****
    * void imprimirNodos
    ******
    * Recorre el árbol recursivamente para imprimir el texto de las hojas y contar los caracteres.
    ******
    * Input:
    * Nodo* nodo : Puntero al nodo actual en el recorrido.
    * int& caracteresImpresos : Referencia al contador de caracteres impresos.
    ******
    * Returns:
    * void, No retorna valor.
    *****/ 
    void imprimirNodos(Nodo* nodo, int& caracteresImpresos){
        if(nodo == nullptr){
            return;
        }

        // si es hoja
        if(nodo->izquierda == nullptr && nodo->derecha == nullptr){
           std::cout << nodo->texto;
            caracteresImpresos += nodo->texto.length();
            return;
        }

        imprimirNodos(nodo->izquierda, caracteresImpresos);
        imprimirNodos(nodo->derecha, caracteresImpresos);
    }

    /*****
    * void invertirRecursivo
    ******
    * Recorre el árbol para invertir el texto de cada hoja y luego intercambia los hijos de cada nodo.
    ******
    * Input:
    * Nodo* nodo : Puntero al nodo actual a procesar.
    ******
    * Returns:
    * void, No retorna valor.
    *****/
    void invertirRecursivo(Nodo* nodo){
        if(nodo == nullptr){
            return;
        }

        // nodo hoja
        if(nodo->izquierda == nullptr && nodo->derecha == nullptr){
            std::string invertido = "";
            
            for(int i = (int)nodo->texto.length() - 1; i >= 0; i--){
                invertido += nodo->texto[i];
            }
            nodo->texto = invertido;
            return;
        }

        invertirRecursivo(nodo->izquierda);
        invertirRecursivo(nodo->derecha);

        // intercambiar hijos
        Nodo* temp = nodo->izquierda;
        nodo->izquierda = nodo->derecha;
        nodo->derecha = temp;
    }

    /*****
    * void concatenar
    ******
    * Une la estructura actual con un árbol Linea proporcionado, agregándolo como hijo derecho en una nueva raíz.
    ******
    * Input:
    * Linea* linea : Puntero al objeto Linea que se concatenará al final.
    ******
    * Returns:
    * void, No retorna valor.
    *****/
    void concatenar(Linea* linea){
        if(linea == nullptr || linea->raiz == nullptr)
            return;

        if(this->raiz == nullptr){
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

    /*****
    * void invertir
    ******
    * Invierte todo el texto de la estructura utilizando la función auxiliar invertirRecursivo desde la raíz.
    ******
    * Input:
    * Sin parámetros.
    ******
    * Returns:
    * void, No retorna valor.
    *****/
    void invertir(void){
        invertirRecursivo(raiz);
    }

    /*****
    * int print
    ******
    *
    * Imprime la cadena de texto completa almacenada en el árbol de izquierda a derecha.
    ******
    * Input:
    * Sin parámetros.
    ******
    * Returns:
    * int, Cantidad total de caracteres impresos.
    *****/
    int print(void){
        int caracteresImpresos = 0;
        imprimirNodos(raiz, caracteresImpresos);
        std::cout << std::endl;
        return caracteresImpresos;
    }
};



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

int main(){
    std::string textoInicial;
    int w;
    cout << "Ingrese texto inicial: ";
    getline(cin, textoInicial);

    cout << "Ingrese valor de w: ";
    cin >> w;

    cin.ignore();

    Linea linea(textoInicial, w);
    int opcion = -1;
    
    while (opcion != 0){
        mostrarMenu();
        cin >> opcion;
        
        if (opcion == 1){
            cout << "\nContenido actual:" << endl;
            linea.print();
            cout << endl;
        }

        else if (opcion == 2){
            int posicion;
            char caracter;

            cout << "Posicion: ";
            cin >> posicion;

            cout << "Caracter: ";
            cin >> caracter;

            linea.insertar(posicion, caracter);
            cout << "Caracter insertado." << endl;
        }

        else if (opcion == 3){
            int posicion;

            cout << "Posicion a eliminar: ";
            cin >> posicion;

            linea.eliminar(posicion);
            cout << "Caracter eliminado." << endl;
        }

        else if (opcion == 4){
            linea.invertir();
            cout << "Linea invertida." << endl;
        }

        else if (opcion == 5){
            cin.ignore();
            std::string nuevoTexto;

            cout << "Texto a concatenar: ";
            getline(cin, nuevoTexto);

            Linea* nuevaLinea = new Linea(nuevoTexto, w);

            linea.concatenar(nuevaLinea);
            cout << "Concatenacion realizada." << endl;
        }

        else if (opcion == 0){
            cout << "Saliendo..." << endl;
        }

        else{
            cout << "Opcion invalida." << endl;
        }
    }
    
    return 0;
}

