#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Persona {
    string nombre;
    string dui;
    int edad;
    string telefono;
    string lugarTrabajo;
    string correo;
    string direccion;
};

void guardarMensaje(const string& mensaje) {
    ofstream archivo("registro_de_mensajes.txt", ios::app);
    if (archivo.is_open()) {
        archivo << mensaje << endl;
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo de mensajes." << endl;
    }
}

void guardarDatosPersona(const Persona& persona) {
    ofstream archivo("datos_personales.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "Nombre: " << persona.nombre << endl;
        archivo << "DUI: " << persona.dui << endl;
        archivo << "Edad: " << persona.edad << endl;
        archivo << "Teléfono: " << persona.telefono << endl;
        archivo << "Lugar de Trabajo: " << persona.lugarTrabajo << endl;
        archivo << "Correo: " << persona.correo << endl;
        archivo << "Dirección: " << persona.direccion << endl;
        archivo << "------------------------" << endl;
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo de datos personales." << endl;
    }
}

void mostrarArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
}

//Función para convertir una cadena a mayúsculas
string convertirMayusculas(const string& entrada) {
    string mayuscula = entrada;
    transform(mayuscula.begin(), mayuscula.end(), mayuscula.begin(), ::toupper);
    return mayuscula;
}
/**/

void ingresarDatosPersona() {
    Persona persona;
    cout << "Ingrese el nombre completo: ";
    getline(cin, persona.nombre);
    cout << "Ingrese el DUI: ";
    getline(cin, persona.dui);
    cout << "Ingrese la edad: ";
    cin >> persona.edad;
    cin.ignore();
    cout << "Ingrese el teléfono celular: ";
    getline(cin, persona.telefono);
    cout << "Ingrese el lugar de trabajo: ";
    getline(cin, persona.lugarTrabajo);
    cout << "Ingrese el correo electrónico: ";
    getline(cin, persona.correo);
    cout << "Ingrese la dirección de su residencia: ";
    getline(cin, persona.direccion);

    guardarDatosPersona(persona);
}

//Función para calcular la suma de 5 números
void calcularSuma() {
    int cuantas;
    int suma = 0;
    int numero;

    cout << "Por favor, ingresa cuántos números quieres sumar:" << endl;
    cin >> cuantas;
    for (int i = 0; i < cuantas; i++) {
        cout << "Número " << (i + 1) << ": ";
        cin >> numero;
        suma += numero;
    }
    cout << "La suma de los " << cuantas << " números es: " << suma << endl;
}


int main() {
    string entrada;
    cout << "Hola, soy Bingo 3000. ;)" << endl << "Escribe un comando. (Consejo: procura escribir sin usar caracteres especiales como ñ, ¿, ?, entre otros)" << endl;

    while (true) {
        cout << "Comando: ";
        getline(cin, entrada);
        guardarMensaje("Comando: " + entrada);
        string comando = convertirMayusculas(entrada);

        if (comando == "INGRESO DE DATOS") {
            do {
                ingresarDatosPersona();
                cout << "¿Desea ingresar datos de otra persona? (s/n): ";
                string respuesta;
                getline(cin, respuesta);
                if (respuesta != "s" && respuesta != "S") {
                    break;
                }
            } while (true);
        } else if (comando == "HOLA"){
            cout << "Bingo3000: ¡Hola! ¿En qué puedo ayudarte?" << endl;
        } else if (comando == "COMO ESTAS"){
            cout << "Bingo3000: ¡Estoy muy bien! Tú ¿Cómo te sientes hoy?" << endl;
        } else if (comando == "BIEN"){
            cout << "Bingo3000: ¡Qué me alegro! ¿Tienes alguna pregunta?" << endl;
        } else if (comando == "MAL"){
            cout << "Bingo3000: ¡Oh! Lo lamento ¿Necesitas hablar?" << endl;
        } else if (comando == "GRACIAS"){
            cout << "Bingo3000: ¡Un placer! Estoy para servir" << endl;
        } else if (comando == "NO"){
            cout << "Bingo3000: ¡OK! ¿Tienes alguna pregunta?" << endl;
        } else if (comando == "MOSTRAR REGISTRO DE MENSAJES") {
            mostrarArchivo("registro-de-mensajes.txt");
        } else if (comando == "MOSTRAR DATOS PERSONALES") {
            mostrarArchivo("datos-personales.txt");
        } else if (comando == "SUMA") {
            calcularSuma();
        }else if (comando == "QUE EDAD TIENES") {
            cout << "Bingo3000: No tengo edad física, solo soy un programa de computadora." << endl;
        }else if (comando == "AYUDA") {
            cout << "Bingo3000: Si necesitas ayuda, puedes intentar escribiendo un comando." << endl << "Por ejemplo: Hola";
        } else if (comando == "SALIR") {
            cout << "OK. Bye!" << endl;
            break;
        } else {
            cout << "Comando no reconocido. (Consejo: procura escribir sin usar caracteres especiales como ñ, ¿, ?, entre otros)," << endl;
        }
    }

    return 0;
}
