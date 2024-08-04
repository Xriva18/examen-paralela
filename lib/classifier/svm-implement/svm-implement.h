#include "./svm/svm-train.h"
#include "./svm/svm.h"
#include "./svm/svm.cpp"
#include "./svm/svm-predict.h"

class SvmImplement
{
private:
public:
    /**
     * @brief Entrenar modelo svm con los parametros por defecto
     * @param featureFile ruta del archivo  que contiene el vector de caracteristicas
     * @param modelOutFile ruta donde se va a guaradar el modelo
     */
    void svmTrain(const char *featureFile, const char *modelOutFile, double gamma, double C);

    /**
     * @brief Evalua el mmodelo entrenado
     * @param testFeatureFile ruta del archivo que contiene el vector de caracteristicas
     * @param modelFile ruta del archivo que contiene el modelo
     * @param resultFile ruta donde se va a guaradar los resultados
     */
    void svmTest(const char *testFeatureFile, const char *modelFile, const char *resultFile);
};

/**
 * Entrena un modelo SVM utilizando un archivo de características y guarda el modelo resultante en un archivo.
 * No ha falta apralelizar la funcion ya esta apralelizada
 * @param featureFile El archivo de características utilizado para entrenar el modelo.
 * @param modelOutFile El archivo donde se guardará el modelo entrenado.
 * @param gamma El valor del parámetro gamma utilizado en el entrenamiento del modelo SVM.
 * @param C El valor del parámetro C utilizado en el entrenamiento del modelo SVM.
 */
void SvmImplement::svmTrain(const char *featureFile, const char *modelOutFile, double gamma, double C)
{
    train_model(featureFile, modelOutFile, gamma, C);
}

/**
 * @brief Realiza la prueba del clasificador SVM utilizando un archivo de características de prueba.
 * No ha falta apralelizar la funcion ya esta apralelizada
 * @param testFeatureFile Ruta del archivo de características de prueba.
 * @param modelFile Ruta del archivo del modelo SVM entrenado.
 * @param resultFile Ruta del archivo de resultados de la prueba.
 */
void SvmImplement::svmTest(const char *testFeatureFile, const char *modelFile, const char *resultFile)
{
    evalue(testFeatureFile, modelFile, resultFile);
}
