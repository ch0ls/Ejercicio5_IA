# Ejercicio5_IA
Código para aplicar en un grafo de nodos, la búsqueda A_estrella y la búsqueda por costo uniforme, como solución para llegar desde el nodo inicial al nodo objetivo

README:
Primero hay que borrar las // a la(s) línea(s):
 //busqueda_costo_uniforme(nodo_init,nodo_goal);
 //busqueda_A_estrella(nodo_init,nodo_goal);
 dependiendo cual búsqueda se desea ejecutar}
 
Se compila el código en la terminal con:
g++ tarea.cpp -o tarea_ia

Se debe crear un archivo.txt con el formato:
Init: <nodo_inicial>
Goal: <nodo_objetivo>
<Nodo1> <valor_heuristica1>
<Nodo2> <valor_heurística2>
.....
<Nodo1>, <nodo2>, <costo> // en el caso en que exista una arista entre nodo1 y nodo2
.....
  
Para luego ejecutarlo con
./tarea_ia < "Nombre del archivo"

Como salida entregara la ruta de los nodos, el costo del camino, cada nodo con las veces que se expandió y por último la cantidad de nodos expandidos, en ese mismo orden.
