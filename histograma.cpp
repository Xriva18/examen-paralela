#include "./lib-img/lib/lib-include.h"
int main()
{
    Utility u;
    StbImageImplementation stb;
    HistogramHandler h; // instancia a la clase histograma
    int width, height;
    double **image = stb.imread("/home/xriva20/Documentos/Proyectogit/ImagenesParalela/prueba2.jpg", width, height); // Lectura de imagen
    int **histeq = h.histeq(image, width, height);                                                                   // equaliza el histograma de la imagen
    // Guardar imagen
    stb.imwrite("imagehis.jpg", histeq, width, height);
    // Liberar puntero
    u.free_memory(histeq, height);
}