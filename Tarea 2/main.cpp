#include <iostream>
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
        nuevo->izquierda = nullptr;
        nuevo->derecha = nullptr;
        nuevo->padre = nullptr;
        nuevo->texto = texto;
        nuevo->peso = texto.length();

        return nuevo;
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

        if(nodo == nullptr){
            return 0;
        }
        if(nodo->izquierda == nullptr && nodo->derecha == nullptr){
            return nodo->peso;
        }

        return obtenerPesoTotal(nodo->izquierda) + obtenerPesoTotal(nodo->derecha);
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
        padre->padre = nullptr;
        if(izquierda){
            izquierda->padre = padre;
        }
        if(derecha){
            derecha->padre = padre;
        }
        padre->texto = "";
        padre->peso = obtenerPesoTotal(izquierda);

        return padre;
    }


    /*****
    * Nodo* construirArbol
    ******
    * Función recursiva auxiliar para dividir el texto inicial si supera w.
    ******
    * Input:
    * std::string str : Texto a dividir.
    * int limite_w : Límite de caracteres por hoja.
    ******
    * Returns:
    * Nodo*, Puntero a la raíz del subárbol generado.
    *****/
    Nodo* construirArbol(std::string str, int limite_w){
        if (str.length() <= limite_w){
            return crearHoja(str);
        }
        int mitad = str.length() / 2;
        Nodo* izq = construirArbol(str.substr(0, mitad), limite_w);
        Nodo* der = construirArbol(str.substr(mitad), limite_w);
        return unir(izq, der);
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
        if(nodo->izquierda == nullptr && nodo->derecha == nullptr){
            return nodo->texto.length();
        }
        return largoSubarbol(nodo->izquierda) + largoSubarbol(nodo->derecha);
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
    * Recorre el árbol para invertir el texto de cada hoja y luego intercambia los hijos de cada nodo. (Solución Problema 4)
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

        // Intercambiar hijos
        Nodo* temp = nodo->izquierda;
        nodo->izquierda = nodo->derecha;
        nodo->derecha = temp;

        // Actualizar el peso del nodo padre (es vital porque el subárbol izquierdo cambió)
        nodo->peso = largoSubarbol(nodo->izquierda);
    }

    /*****
    * Nodo* eliminarRecursivo
    ******
    * Función auxiliar que elimina un carácter, reestructura si un nodo queda vacío y ajusta pesos. (Solución Problema 5)
    ******
    * Input:
    * Nodo* nodo : Nodo actual.
    * int posicion : Posición a eliminar.
    ******
    * Returns:
    * Nodo*, La nueva raíz del subárbol tras la eliminación.
    *****/
    Nodo* eliminarRecursivo(Nodo* nodo, int posicion) {
        if (nodo == nullptr) return nullptr;

        // Si es nodo hoja
        if (nodo->izquierda == nullptr && nodo->derecha == nullptr) {
            if (posicion >= 0 && posicion < nodo->texto.length()) {
                nodo->texto.erase(posicion, 1);
                nodo->peso = nodo->texto.length();
                
                // Si la hoja se queda sin texto, la eliminamos para no dejar basura.
                if (nodo->texto.empty()) {
                    delete nodo;
                    return nullptr; 
                }
            }
            return nodo;
        }

        // Búsqueda en nodos internos
        if (posicion < nodo->peso && nodo->izquierda != nullptr) {
            nodo->izquierda = eliminarRecursivo(nodo->izquierda, posicion);
            if (nodo->izquierda) nodo->izquierda->padre = nodo;
        } else if (nodo->derecha != nullptr) {
            nodo->derecha = eliminarRecursivo(nodo->derecha, posicion - nodo->peso);
            if (nodo->derecha) nodo->derecha->padre = nodo;
        }

        // Reestructuración si un hijo fue eliminado
        if (nodo->izquierda == nullptr && nodo->derecha == nullptr) {
            delete nodo;
            return nullptr;
        } else if (nodo->izquierda == nullptr) {
            Nodo* temp = nodo->derecha;
            temp->padre = nodo->padre;
            delete nodo;
            return temp;
        } else if (nodo->derecha == nullptr) {
            Nodo* temp = nodo->izquierda;
            temp->padre = nodo->padre;
            delete nodo;
            return temp;
        }

        // Actualizar el peso obligatoriamente de abajo hacia arriba
        nodo->peso = obtenerPesoTotal(nodo->izquierda);
        return nodo;
    }

public:
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
        if(str.empty()){
            raiz = nullptr;
        } 
        else{
            //Genera el árbol dividido si es necesario
            raiz = construirArbol(str, w); 
        }
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
       if(raiz == nullptr){
            std::string s(1, caracter);
            raiz = crearHoja(s);
            return;
        }
        
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

        raiz = eliminarRecursivo(raiz, posicion);
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
    std::cout << "Ingrese texto inicial: ";
    std::getline(std::cin, textoInicial);

    std::cout << "Ingrese valor de w: ";
    std::cin >> w;

    cin.ignore();

    Linea linea(textoInicial, w);
    int opcion = -1;
    
    while (opcion != 0){
        mostrarMenu();
        std::cin >> opcion;
        
        if (opcion == 1){
            std::cout << "\nContenido actual:" << endl;
            linea.print();
            std::cout << endl;
        }

        else if (opcion == 2){
            int posicion;
            char caracter;

            std::cout << "Posicion: ";
            std::cin >> posicion;

            std::cout << "Caracter: ";
            std::cin >> caracter;
            linea.insertar(posicion, caracter);
            std::cout << "Caracter insertado." << std::endl;
        }

        else if (opcion == 3){
            int posicion;

            std::cout << "Posicion a eliminar: ";
            std::cin >> posicion;

            linea.eliminar(posicion);
            std::cout << "Caracter eliminado." << std::endl;
        }

        else if (opcion == 4){
            linea.invertir();
            std::cout << "Linea invertida." << std::endl;
        }

        else if (opcion == 5){
            std::cin.ignore();
            std::string nuevoTexto;

            std::cout << "Texto a concatenar: ";
            std::getline(std::cin, nuevoTexto);
            Linea* nuevaLinea = new Linea(nuevoTexto, w);

            linea.concatenar(nuevaLinea);
            std::cout << "Concatenacion realizada." << std::endl;
        }

        else if (opcion == 0){
            std::cout << "Saliendo..." << std::endl;
        }

        else{
            std::cout << "Opcion invalida." << std::endl;
        }
    }
    
    return 0;
}

