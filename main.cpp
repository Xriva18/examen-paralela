#include "./lib-img/lib/lib-include.h"
int main()
{
    StbImageImplementation stb;
    Utility u;
    GaussianFilter g;
    int width, height;
    double **image = stb.imread("ruta_imagen/imagen.jpg", width, height); // Lectura de imagen
    double sigma = 1;                                                     // Valor ajustable
    image = g.gaussianFilter(image, width, height, sigma);                // Aplica filtro gaussiano
    // Guardar imagen
    stb.imwrite("image.jpg", image, width, height);
    // Liberar puntero
    u.free_memory(image, height);
}