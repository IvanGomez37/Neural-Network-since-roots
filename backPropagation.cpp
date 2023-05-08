/*
    ---- ALGORITMO PARA ENTRENAMIENTO DE RED NEURONAL POR MEDIO DE FEED FODWARD Y BACK PROPAGATION ----
    *DESCRIPCION:
        Algoritmo para entrenamiento de una red neuronal creada totalmente a decision del usuario,
        desde el numero de capas intermedias hasta el numero de unidades en cada capa. Su proceso se basa
        en una tasa de aprendizaje l y una razon de paro en el aprendizaje que puede ser modificada a 
        necesidad especifica. El proceso de aprendizaje se realiza con los algoritmos de feed fordward
        y back propagation. El programa funciona para inputs numéricos y se cree que puede modificarse 
        para aceptar inputs de tipo char.
    *DESARROLLADORES:
        Ivan Yahir Gómez Mancilla
*/

// IMPORTS
#include <bits/stdc++.h>
using namespace std;

// DEFINICIONES DE ESTRUCTURAS
// Definicion para unidad de capa de entrada
typedef struct unidadInput
{
    float input = 0;
} unidadInput;

// Definicion para unidad de capas intermedias
typedef struct unidadInter
{
    float input = 0;
    float output = 0;
    float error = 0;
    float bias = 0;
    vector <float> pesos;
} unidadInter;

// Definicion para unidad de capa de salida
typedef struct unidadOutput
{
    float input = 0;
    float output = 0;
    float error = 0;
    float bias = 0;
    float outputDeseado = 0;
    vector <float> pesos;
} unidadOutput;

// DECLARACION DE CONSTANTES
#define e 2.718281
#define l 1 // Cambiar a gusto en caso de querer modificar la tasa de aprendizaje

// PROTOTIPOS DE FUNCION
void feedFodward(vector <unidadInput> &vectorInput, vector <vector <unidadInter>> &vectorInter, vector <unidadOutput> &vectorOutput);
void backPropagation(vector <unidadInput> &vectorInput, vector <vector <unidadInter>> &vectorInter, vector <unidadOutput> &vectorOutput);

// MAIN
int main()
{   
    // INICIALIZACION DE RED NEURONAL
    // Declaracion de numero de unidades en capa de entrada
    int nUnidadesInput = 0, nCapasInter = 0;
    cout << "Numero de unidades de entrada en Red Neuronal" << endl;
    cin >> nUnidadesInput;
    vector <unidadInput> capaInput(nUnidadesInput);

    // Declaracion de numero de capas en capas intermedias
    cout << "Numero de capas intermedias en Red Neuronal" << endl;
    cin >> nCapasInter;
    vector <vector <unidadInter>> capaInter;

    // Declaracion de numero de unidades en capa intermedia i
    for(int i = 0; i < nCapasInter; ++i)
    {
        int nUnidadesCapaInterI;
        cout << "Numero de unidades en Capa intermedia " << i + 1 << endl;
        cin >> nUnidadesCapaInterI;
        vector <unidadInter> capaTemp(nUnidadesCapaInterI);
        if(i == 0)
        {
            for(int j = 0; j < nUnidadesCapaInterI; ++j)
            {
                capaTemp[j].pesos.resize(capaInput.size(), 1);
            }
        }
        else
        {
            for(int j = 0; j < nUnidadesCapaInterI; ++j)
            {
                capaTemp[j].pesos.resize(capaInter[i - 1].size(), 1);
            }
        }
        capaInter.push_back(capaTemp);
    }

    // Declaracion de capa de salida
    cout << "Numero de unidades en capa de salida en Red Neuronal" << endl;
    int nUnidadesOutput;
    cin >> nUnidadesOutput;
    vector <unidadOutput> capaOutput(nUnidadesOutput);
    for(int i = 0; i < nUnidadesOutput; ++i)
    {
        capaOutput[i].pesos.resize(capaInter[capaInter.size() - 1].size(), 1);
    }

    // INICIALIZACION VALORES ENTRADA Y VALORES ESPERADOS DE SALIDA
    // Lectura de valores de entrada
    for(int i = 0; i < nUnidadesInput; ++i)
    {
        cout << "Valor de entrada para unidad de capa de entrada " << i + 1 << endl;
        cin >> capaInput[i].input;
    }

    // Lectura de valores esperados
    for(int i = 0; i < nUnidadesOutput; ++i)
    {
        cout << "Valor esperado de salida para unidad de capa de salida " << i + 1 << endl;
        cin >> capaOutput[i].outputDeseado;
    }

    // ALGORITMO DE AJUSTE DE PESOS POR FEED FORDWARD Y BACKPROPAGATION
    bool flag = false;
    while(flag == false)
    {
        feedFodward(capaInput, capaInter, capaOutput); // Llamada al algoritmo feed fordward
        backPropagation(capaInput, capaInter, capaOutput); // Llamada al algoritmo back propagation

        int conta = 0;
        for(int i = 0; i < capaOutput.size(); ++i)
        {
            if(abs(capaOutput[i].outputDeseado - capaOutput[i].output) <= 0.01) // Condicion de paro, modificar segun la necesidad
            {
                conta++;
            }
        }

        if(conta == capaOutput.size())
        {
            flag = true;
        }
        
        cout << "Output unidad ";
        for(int i = 0; i < capaOutput.size(); ++i)
        {
           cout << capaOutput[i].output << " ";
        }
        cout << endl;
    }
        
  
    // IMPRESION DE VALORES
    cout << endl << "IMPRESION DE VALORES" << endl;
    // Impresion capa de entrada
    cout << "Capa de entrada" << endl;
    for(int i = 0; i < nUnidadesInput; ++i)
    {
        cout << "Unidad " << i + 1 << endl;
        cout << "Input " << capaInput[i].input << endl;
        cout << endl;
    }
    cout << endl << endl;

    // Impresion capas intermedias
    cout << "Capas intermedias" << endl;
    for(int i = 0; i < nCapasInter; ++i)
    {
        for(int j = 0; j < capaInter[i].size(); ++j)
        {
            cout << "Unidad " << i + 1 << " " << j + 1 << endl;
            cout << "Input " << capaInter[i][j].input << endl;
            cout << "Output " << capaInter[i][j].output << endl;
            cout << "Error " << capaInter[i][j].error << endl;
            cout << "Bias " << capaInter[i][j].bias << endl;
            cout << "Pesos ";
            for(int k = 0; k < capaInter[i][j].pesos.size(); ++k)
            {
                cout << capaInter[i][j].pesos[k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl << endl;

    // Impresion capa salida
    cout << "Capa salida" << endl;
    for(int i = 0; i < nUnidadesOutput; ++i)
    {
         cout << "Unidad " << i + 1 << endl;
        cout << "Input " << capaOutput[i].input << endl;
        cout << "Output " << capaOutput[i].output << endl;
        cout << "Error " << capaOutput[i].error << endl;
        cout << "Bias " << capaOutput[i].bias << endl;
        cout << "Output deseado " << capaOutput[i].outputDeseado << endl;
        cout << "Pesos ";
        for(int k = 0; k < capaOutput[i].pesos.size(); ++k)
        {
            cout << capaOutput[i].pesos[k] << " ";
        }
        cout << endl;
        cout << endl;
    }
    
    return 0;
}

// ALGORITMO DE FEED FORDWARD
void feedFodward(vector <unidadInput> &vectorInput, vector <vector <unidadInter>> &vectorInter, vector <unidadOutput> &vectorOutput)
{
    // Feed fodward para capas intermedias
    for(int i = 0; i < vectorInter.size(); ++i)
    {
        for(int j = 0; j < vectorInter[i].size(); ++j)
        {
            float input = 0;
            if(i == 0)
            {
                for(int k = 0; k < vectorInput.size(); ++k)
                {
                    input += vectorInput[k].input * vectorInter[i][j].pesos[k];
                }
            }
            else
            {
                for(int k = 0; k < vectorInter[i - 1].size(); ++k)
                {
                    input += vectorInter[i - 1][k].input * vectorInter[i][j].pesos[k];
                }
            }
            vectorInter[i][j].input = input + vectorInter[i][j].bias;
            vectorInter[i][j].output = (float)1 / ((float)1 + pow(e, (float)(- 1) * vectorInter[i][j].input));
        }
    }

    // Feed fordward para capa de salida
    for(int i = 0; i < vectorOutput.size(); ++i)
    {
        float input = 0;
        for(int j = 0; j < vectorOutput[i].pesos.size(); ++j)
        {
            input += vectorInter[vectorInter.size() - 1][j].output * vectorOutput[i].pesos[j];
        }
        vectorOutput[i].input = input + vectorOutput[i].bias;
        vectorOutput[i].output = (float)1 / ((float)1 + pow(e, (float)(-1) * vectorOutput[i].input));
    }
}

// ALGORITMO DE BACK PROPAGATION
void backPropagation(vector <unidadInput> &vectorInput, vector <vector <unidadInter>> &vectorInter, vector <unidadOutput> &vectorOutput)
{
    // OBTENCION DE ERRORES
    // Back propagation para capa de salida
    for(int i = 0; i < vectorOutput.size(); ++i)
    {
        vectorOutput[i].error = vectorOutput[i].output * (1 - vectorOutput[i].output) * (vectorOutput[i].outputDeseado - vectorOutput[i].output);
    }

    // Back propagation para capas intermedias
    for(int i = vectorInter.size() - 1; i >= 0; --i)
    {
        for(int j = vectorInter[i].size() - 1; j >= 0; --j)
        {
            float sum = 0;
            if(i == vectorInter.size() - 1)
            {
                for(int k = 0; k < vectorOutput.size(); ++k)
                {
                    sum += vectorOutput[k].error * vectorOutput[k].pesos[j];
                }
            }
            else
            {
                for(int k = 0; k < vectorInter[i + 1].size(); ++k)
                {
                    sum += vectorInter[i + 1][k].error * vectorInter[i + 1][k].pesos[j];
                }
            }
            vectorInter[i][j].error = vectorInter[i][j].output * ((float)1 - vectorInter[i][j].output) * sum;
        }
    }

    // ACTUALIZACION DE PESOS
    // Actualizacion de pesos para capas intermedias
    for(int i = 0; i < vectorInter.size(); ++i)
    {
        for(int j = 0; j < vectorInter[i].size(); ++j)
        {
            if(i == 0)
            {
                for(int k = 0; k < vectorInter[i][j].pesos.size(); ++k)
                {
                    float difPeso = l * vectorInter[i][j].error * vectorInput[k].input;
                    vectorInter[i][j].pesos[k] = vectorInter[i][j].pesos[k] + difPeso;
                }
            }
            else
            {
                for(int k = 0; k < vectorInter[i][j].pesos.size(); ++k)
                {
                    float difPeso = l * vectorInter[i][j].error * vectorInter[i - 1][k].output;
                    vectorInter[i][j].pesos[k] = vectorInter[i][j].pesos[k] + difPeso;
                }
            }
        }
    }

    // Actualizacion de pesos para capa de salida
    for(int i = 0; i < vectorOutput.size(); ++i)
    {
        for(int j = 0; j < vectorOutput[i].pesos.size(); ++j)
        {
            float difPeso = l * vectorOutput[i].error * vectorInter[vectorInter.size() - 1][j].output;
            vectorOutput[i].pesos[j] = vectorOutput[i].pesos[j] + difPeso;
        }
    }

    // ACTUALIZACION DE BIAS
    // Actualizacion de bias para capas intermedias
    for(int i = 0; i < vectorInter.size(); ++i)
    {
        for(int j = 0; j < vectorInter[i].size(); ++j)
        {
            float difTheta = l * vectorInter[i][j].error;
            vectorInter[i][j].bias += difTheta;
        }
    }

    //Actualizacion de bias para capas de salida
    for(int i = 0; i < vectorOutput.size(); ++i)
    {
        float difTheta = l * vectorOutput[i].error;
        vectorOutput[i].bias += difTheta;
    }
}