Descricion:
Realiza el algoritmo del Scan de Graham a partir de una imagen pgm de entrada.
Se obtiene una imagen con la figura original, la envolvente convexa (en rojo) y los puntos pertenecientes a la envolvente (en verde)
Un archivo de texto, de nombre "Convex Hull Points.txt" es generado con las coordenadas de los puntos en la envolvente convexa.

Instruccines de compilación:
    	g++ Graham.cpp $(pkg-config --cflags --libs cairo)
	./a.out Dino.pgm
