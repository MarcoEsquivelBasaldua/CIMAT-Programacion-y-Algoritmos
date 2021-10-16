Descricion:
Implementa el algoritmo A* en conjunto con el algoritmo Dijkstra para ir de un punto A a un punto B en un espacio cuadriculado con obstàculos en dos dimensiones.
El usuario debe ingresar por la terminal el tamanio del mapa, siendo este un cuadrado,  cuando el programa lo solicite asi como el porcentaje de obstaculos y 
las ubicaciones del punto A (cazador) y el punto B (presa).

Instruccines de compilación:
    	g++ A_star_Marco_Esquivel.cpp Draw_map.cpp Hunting.cpp $(pkg-config --cflags --libs cairo)
	./a.out
