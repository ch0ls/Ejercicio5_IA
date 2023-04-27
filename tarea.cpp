#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

//definimos la estructura nodo con sus datos respectivos, con un vector de nodos hijos con sus costos
//respectivos, un puntero a su padre y una función para agregarHijo

struct Nodo{ 
    string nombre;
    int heuristica;
    int costo_acumulado;
    vector<pair<Nodo*,int>> hijos;
    Nodo* padre;
    Nodo(string nombre, int heuristica){
        this->nombre = nombre;
        this->heuristica = heuristica;
        this->padre = NULL;
        this->costo_acumulado = 0;
    }
    void agregarHijo(Nodo* hijo, int costo){
        hijos.push_back(make_pair(hijo, costo));
    }
    int calcularCostoTotal(){ //función que se utiliza para A_estrella
    return costo_acumulado + heuristica;
}

};
//definimos la estructura ComparadorNodos que compara los nodos en la priority_queue y elige el nodo
//que tenga el menor costo acumulado
struct ComparadorNodos{
    bool operator() (Nodo* nodo1, Nodo* nodo2){
            return nodo1->costo_acumulado > nodo2->costo_acumulado;
    }
};


void busqueda_costo_uniforme(Nodo* nodo_inicial, Nodo* nodo_objetivo) { //función que realiza la búsqeda por costo uniforme
    priority_queue<Nodo*, vector<Nodo*>, ComparadorNodos> nodos_abiertos; //se utiliza una priority queue para los nodos que aun no han sido explorados
    map<string, Nodo*> nodos_visitados;        //y dos mapas para registrar los nodos visitados y las veces que se ha expandido cada uno
    map<string, int> nodos_expandidos;
    nodos_abiertos.push(nodo_inicial);
    while (!nodos_abiertos.empty()) {       //se extrae el nodo con menor costo y se examina si es la meta
        Nodo* nodo_actual = nodos_abiertos.top();
        nodos_abiertos.pop();   // contabilizar que se ha expandido el nodo actual
        nodos_expandidos[nodo_actual->nombre]++;
        if (nodo_actual == nodo_objetivo) {  // si se encuentra el nodo objetivo, se construye el camino hacia atrás
            vector<string> camino;
            int costo_total= 0;
            Nodo* nodo = nodo_actual;
            costo_total += nodo->costo_acumulado;
            while (nodo != NULL) {
                camino.insert(camino.begin(), nodo->nombre);
                nodo = nodo->padre;
            }
            for (int i = 0; i < camino.size(); i++) {  //imprimimos segun el camino segun el formato pedido
                cout << camino[i];
                if (i != camino.size() - 1) {
                 cout << "->";
                 }
            }
            cout << endl;
            cout << "Costo: " << costo_total << endl; //imprimimos el costo total del camino
            for (auto it = nodos_expandidos.begin(); it != nodos_expandidos.end(); it++){  //se imprime las veces que cada nodo se expandió y el total de nodos expandidos
                     cout << "Nodo " << it->first << ": " << it->second << endl;
                 }
            cout << "Total de nodos expandidos: " << nodos_expandidos.size() << endl;
            return;
        }

        // si el nodo no ha sido visitado, se agrega a la lista de nodos visitados
        if (nodos_visitados.find(nodo_actual->nombre) == nodos_visitados.end()){  
            nodos_visitados[nodo_actual->nombre] = nodo_actual;
            for (pair<Nodo*, int> hijo : nodo_actual->hijos) {  // se actualiza el costo acumulado para cada hijo y guardamos como padre de cada hijo, el nodo actual
                Nodo* nodo_hijo = hijo.first;
                int costo_hijo = hijo.second;
                nodo_hijo->costo_acumulado = nodo_actual->costo_acumulado+costo_hijo;
                nodo_hijo->padre = nodo_actual;
                nodos_abiertos.push(nodo_hijo);
            }   
        }
        //Este proceso se sigue hasta que se encuentre el nodo objetivo o se vacie la priority queue
    }

    // no se encontró el nodo objetivo
    cout << "No se encontró un camino" << endl;
}

struct ComparadorNodos_A{ //comparador de nodos A_estrella, donde a diferencia del costo uniforme, compara el costo acumulado + la heurística de cada nodo
    bool operator() (Nodo* nodo1, Nodo* nodo2){ 
            return nodo1->calcularCostoTotal() > nodo2->calcularCostoTotal();
    }
};

//basicamente es lo mismo que el costo uniforme pero cambia en la forma de comparacion
void busqueda_A_estrella(Nodo* nodo_inicial, Nodo* nodo_objetivo) { //función que realiza la búsqeda A estrella
    priority_queue<Nodo*, vector<Nodo*>, ComparadorNodos> nodos_abiertos; //se utiliza una priority queue para los nodos que aun no han sido explorados
    map<string, Nodo*> nodos_visitados;        //y dos mapas para registrar los nodos visitados y las veces que se ha expandido cada uno
    map<string, int> nodos_expandidos;
    nodos_abiertos.push(nodo_inicial);
    while (!nodos_abiertos.empty()) {       //se extrae el nodo con menor (costo acumulado + heuristica) y se examina si es la meta
        Nodo* nodo_actual = nodos_abiertos.top();
        nodos_abiertos.pop();   // contabilizar que se ha expandido el nodo actual
        nodos_expandidos[nodo_actual->nombre]++;
        if (nodo_actual == nodo_objetivo) {  // si se encuentra el nodo objetivo, se construye el camino hacia atrás
            vector<string> camino;
            int costo_total= 0;
            Nodo* nodo = nodo_actual;
            costo_total += nodo->costo_acumulado;
            while (nodo != NULL) {
                camino.insert(camino.begin(), nodo->nombre);
                nodo = nodo->padre;
            }
            for (int i = 0; i < camino.size(); i++) {  //imprimimos segun el camino segun el formato pedido
                cout << camino[i];
                if (i != camino.size() - 1) {
                 cout << "->";
                 }
            }
            cout << endl;
            cout << "Costo: " << costo_total << endl; //imprimimos el costo total del camino
            for (auto it = nodos_expandidos.begin(); it != nodos_expandidos.end(); it++){  //se imprime las veces que cada nodo se expandió y el total de nodos expandidos
                     cout << "Nodo " << it->first << ": " << it->second << endl;
                 }
            cout << "Total de nodos expandidos: " << nodos_expandidos.size() << endl;
            return;
        }

        // si el nodo no ha sido visitado, se agrega a la lista de nodos visitados
        if (nodos_visitados.find(nodo_actual->nombre) == nodos_visitados.end()){  
            nodos_visitados[nodo_actual->nombre] = nodo_actual;
            for (pair<Nodo*, int> hijo : nodo_actual->hijos) {  // se actualiza el costo acumulado para cada hijo y guardamos como padre de cada hijo, el nodo actual
                Nodo* nodo_hijo = hijo.first;
                int costo_hijo = hijo.second;
                nodo_hijo->costo_acumulado = nodo_actual->costo_acumulado+costo_hijo;
                nodo_hijo->padre = nodo_actual;
                nodos_abiertos.push(nodo_hijo);
            }   
        }
        //Este proceso se sigue hasta que se encuentre el nodo objetivo o se vacie la priority queue
    }

    // no se encontró el nodo objetivo
    cout << "No se encontró un camino" << endl;
}


int main(){  //declaramos variables, creando un mapa donde almacenamos los nodos
    char linea[50];
    map<string, Nodo*> nodos; 
    string nodo_inicial, nodo_objetivo;
    while(fgets(linea, 50, stdin)){ //leemos archivo línea por línea desde stdin
        char *ptr = strtok(linea, "\n");
        if (sscanf(ptr, "Init: %s",ptr) != 0){ //dependiendo lo que se lea en linea almacenamos en nodo_inicial o nodo_objetivo
            nodo_inicial=ptr;
        }
        else if(sscanf(ptr, "Goal: %s",ptr) != 0){
            nodo_objetivo=ptr;
        }
        else if(strstr(linea, " ") != NULL && strstr(linea, ",") == NULL){ //verificamos si existe en la linea un espacio y ninguna coma
            istringstream entrada(linea);  
            string nombre;
            int heuristica;
            entrada >> nombre >> heuristica;
            Nodo* nodo = new Nodo(nombre, heuristica); //creamos un nodo al mapa de nodos con el nombre y heurística de la línea
            nodos[nombre] = nodo;
        }
        else if(strstr(linea, ",") != NULL){  
            istringstream entrada(linea);
            string nodo1, nodo2;
            int costo;
            getline(entrada, nodo1, ','); 
            getline(entrada, nodo2, ',');
            entrada >> costo;
            Nodo* padre = nodos[nodo1];
            Nodo* hijo = nodos[nodo2];
            padre->agregarHijo(hijo, costo); //agregamos la funcion AgregarHijo del nodo 1 pasando como argumento el nodo 2 y el costo del camino

        }
    }

    // se llama a la función de búsqueda de costo uniforme
 Nodo* nodo_init = nodos[nodo_inicial];
 Nodo* nodo_goal = nodos[nodo_objetivo];
 //busqueda_costo_uniforme(nodo_init,nodo_goal);
 //busqueda_A_estrella(nodo_init,nodo_goal);


    // Liberar memoria
    for (auto const& nodo : nodos) {
        delete nodo.second;
    }

    return 0;
}
