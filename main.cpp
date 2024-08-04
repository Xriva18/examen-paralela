#include <iostream>
#include <chrono>
#include <sys/resource.h> // Para uso de memoria
#include <unistd.h>       // Para obtener el uso de CPU
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "./lib/lib-include.h" // Añadir al proyecto
#include <vector>

// Función para obtener el uso de memoria en KB
long getMemoryUsage()
{
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0)
    {
        return usage.ru_maxrss; // Memoria en KB
    }
    else
    {
        return -1; // Error al obtener uso de memoria
    }
}

// Función para obtener el uso de CPU en porcentaje
double getCpuUsage()
{
    static unsigned long long prev_total_time = 0;
    static unsigned long long prev_idle_time = 0;

    std::ifstream file("/proc/stat");
    if (!file.is_open())
    {
        return -1; // Error al abrir el archivo
    }

    std::string line;
    std::getline(file, line); // Lee la primera línea que contiene el total de tiempos de CPU
    file.close();

    std::istringstream iss(line);
    std::string cpu;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    iss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    unsigned long long total_time = user + nice + system + idle + iowait + irq + softirq + steal;
    unsigned long long idle_time = idle + iowait;

    double cpu_usage = 0.0;
    if (prev_total_time != 0)
    {
        unsigned long long total_diff = total_time - prev_total_time;
        unsigned long long idle_diff = idle_time - prev_idle_time;

        cpu_usage = ((double)(total_diff - idle_diff) / total_diff) * 100.0;
    }

    prev_total_time = total_time;
    prev_idle_time = idle_time;

    return cpu_usage;
}

int main()
{
    // Medir tiempo de ejecución
    auto start = std::chrono::high_resolution_clock::now();

    Utility u;
    StbImageImplementation stb;
    HistogramHandler h; // Instancia a la clase histograma
    int width, height;

    // Medir el uso de CPU antes de guardar la imagen
    double cpu_usage_before = getCpuUsage();
    //-------------------------------------------------------------------------------------------------------------------
    double **image = stb.imread("/home/xriva20/Documentos/examen-paralela/ImagensPrueba/IMG5000.jpg", width, height); // Lectura de imagen
    int **histeq = h.histeq(image, width, height);                                                                    // Equaliza el histograma de la imagen

    // Guardar imagen
    stb.imwrite("image.jpg", histeq, width, height);

    // Liberar puntero
    u.free_memory(histeq, height);
    //-------------------------------------------------------------------------------------------------------------------
    // Medir el uso de CPU después de guardar la imagen
    double cpu_usage_after = getCpuUsage();

    // Medir tiempo de ejecución
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Obtener el uso de memoria
    long memory_usage = getMemoryUsage();

    // Imprimir resultados
    std::cout << "Tiempos------------------------------------\n";
    std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos\n";
    std::cout << "Uso de CPU: " << (cpu_usage_after - cpu_usage_before) << " %\n";
    std::cout << "Uso de memoria: " << memory_usage << " KB\n";

    return 0;
}
