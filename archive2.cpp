#include <iostream>
#include <locale>
using namespace std;
// Función para convertir una cadena a mayúsculas
string convertirMayusculas(const string& entrada) {
    string mayuscula = entrada;
    transform(mayuscula.begin(), mayuscula.end(), mayuscula.begin(), ::toupper);
    return mayuscula;
}

// Función para calcular la suma de 5 números
void calcularSuma() {
    int suma = 0;
    int numero;

    cout << "Por favor, ingresa 5 números para calcular su suma:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Número " << (i + 1) << ": ";
        cin >> numero;
        suma += numero;
    }

    cout << "La suma de los 5 números es: " << suma << endl;
}

// Función para calcular la suma de la diagonal secundaria de una matriz 3x3
void calcularDiagonalSecundaria() {
    int matriz[3][3];
    int sumaDiagonalSecundaria = 0;

    cout << "Ingresa los elementos de la matriz 3x3:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Elemento [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        sumaDiagonalSecundaria += matriz[i][2 - i];
    }

    cout << "La suma de los elementos de la diagonal secundaria es: " << sumaDiagonalSecundaria << endl;
}

int main() {
    setlocale(LC_ALL, "Spanish");
    string entrada;

    cout << "Hola, soy el chatbot Bingo 3000. ¿En qué puedo ayudarte? \n(Consejo: procura escribir sin usar caracteres especiales)" << endl;

    while (true) {
        cout << "\nTú: ";
        getline(cin, entrada); // Leer el mensaje del usuario
        string mensaje = convertirMayusculas(entrada);

        // Respuestas predefinidas
        if (mensaje == "HOLA") {
            cout << "Chatbot: ¡Hola! ¿En qué puedo ayudarte?" << endl;
        } else if (mensaje == "SUMA") {
            calcularSuma();
        } else if (mensaje == "MATRIZ") {
            calcularDiagonalSecundaria();
        } 
        // Nueva interacción: ¿Cómo estás?
        else if (mensaje == "COMO ESTAS" || mensaje.find("COMO ESTAS") != string::npos) {
            cout << "Chatbot: ¡Estoy bien, gracias por preguntar! ¿Y tú?" << endl;
        } 
        // Nueva interacción: ¿Qué edad tienes?
        else if (mensaje == "QUE EDAD TIENES" || mensaje.find("QUE EDAD TIENES") != string::npos) {
            cout << "Chatbot: No tengo edad física, soy un programa de computadora." << endl;
        } 
        // Salir del chatbot
        else if (mensaje == "SALIR") {
            cout << "Chatbot: Ok, nos vemos pronto. ¡Adiós!" << endl;
            break;
        } 
        // Respuesta por defecto si no se reconoce el comando
        else {
            cout << "Chatbot: Lo siento, no entiendo tu solicitud. \n(Consejo: Utiliza palabras como 'suma', 'matriz' o 'salir')" << endl;
        }
    }

    return 0;
}
