Descricion:
Realiza el algoritmo de la Marcha de Jarvis mostrando una imagen de n puntos generados aleatoriamente en un espacio cuadrado en el intervalo [-10,10] para los ejes coordenados.
El usuario debe ingresar por la terminal el valor de n cuando el programa lo solicite.
Un archivo de texto, de nombre "Convex Hull Points.txt" es generado con las coordenadas de los puntos en la envolvente convexa.

Instruccines de compilación:
    	g++ marcha_jarvis.cpp $(pkg-config --cflags --libs cairo)
	./a.out
