#include "./lib-img/lib/lib-include.h"
int main()
{
    Utility u;
    StbImageImplementation stb;
    GaussianFilter g;
    int width, height;
    double **image = stb.imread("/home/xriva20/Documentos/Proyectogit/ImagenesParalela/prueba2.jpg", width, height); // Lectura de imagen
    double sigma = 1;                                                                                                // Valor ajustable
    image = g.gaussianFilter(image, width, height, sigma);                                                           // Aplica filtro gaussiano
    // Guardar imagen
    stb.imwrite("imageGas.jpg", image, width, height);
    // Liberar puntero
    u.free_memory(image, height);
}