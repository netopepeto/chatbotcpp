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

string convertirMayusculas(const string& entrada) {
    string mayuscula = entrada;
    transform(mayuscula.begin(), mayuscula.end(), mayuscula.begin(), ::toupper);
    return mayuscula;
}

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

void actualizarDatosPersona(const string& dui) {
    ifstream archivoEntrada("datos_personales.txt");
    ofstream archivoTemporal("temp.txt");

    if (!archivoEntrada.is_open() || !archivoTemporal.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    Persona personaActualizada;
    bool encontrado = false;

    while (getline(archivoEntrada, linea)) {
        if (linea.find("DUI: " + dui) != string::npos) {
            encontrado = true;
            cout << "Registro encontrado. Ingresa los nuevos datos:\n";
            cout << "Nombre: ";
            getline(cin, personaActualizada.nombre);
            cout << "Edad: ";
            cin >> personaActualizada.edad;
            cin.ignore();
            cout << "Teléfono: ";
            getline(cin, personaActualizada.telefono);
            cout << "Lugar de Trabajo: ";
            getline(cin, personaActualizada.lugarTrabajo);
            cout << "Correo: ";
            getline(cin, personaActualizada.correo);
            cout << "Dirección: ";
            getline(cin, personaActualizada.direccion);

            archivoTemporal << "Nombre: " << personaActualizada.nombre << endl;
            archivoTemporal << "DUI: " << dui << endl;
            archivoTemporal << "Edad: " << personaActualizada.edad << endl;
            archivoTemporal << "Teléfono: " << personaActualizada.telefono << endl;
            archivoTemporal << "Lugar de Trabajo: " << personaActualizada.lugarTrabajo << endl;
            archivoTemporal << "Correo: " << personaActualizada.correo << endl;
            archivoTemporal << "Dirección: " << personaActualizada.direccion << endl;
            archivoTemporal << "------------------------" << endl;

            for (int i = 0; i < 6; ++i) getline(archivoEntrada, linea);
        } else {
            archivoTemporal << linea << endl;
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();

    if (encontrado) {
        remove("datos_personales.txt");
        rename("temp.txt", "datos_personales.txt");
        cout << "Datos actualizados correctamente.\n";
    } else {
        remove("temp.txt");
        cout << "DUI no encontrado.\n";
    }
}

void borrarDatosPersona(const string& dui) {
    ifstream archivoEntrada("datos_personales.txt");
    ofstream archivoTemporal("temp.txt");

    if (!archivoEntrada.is_open() || !archivoTemporal.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivoEntrada, linea)) {
        if (linea.find("DUI: " + dui) != string::npos) {
            encontrado = true;
            for (int i = 0; i < 6; ++i) getline(archivoEntrada, linea);
        } else {
            archivoTemporal << linea << endl;
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();

    if (encontrado) {
        remove("datos_personales.txt");
        rename("temp.txt", "datos_personales.txt");
        cout << "Datos eliminados correctamente.\n";
    } else {
        remove("temp.txt");
        cout << "DUI no encontrado.\n";
    }
}

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
            ingresarDatosPersona();
        } else if (comando == "HOLA") {
            cout << "Bingo3000: ¡Hola! ¿En qué puedo ayudarte?" << endl;
        } else if (comando == "MOSTRAR DATOS PERSONALES") {
            mostrarArchivo("datos_personales.txt");
        } else if (comando == "ACTUALIZAR DATOS") {
            cout << "Ingresa el DUI de la persona a actualizar: ";
            string dui;
            getline(cin, dui);
            actualizarDatosPersona(dui);
        } else if (comando == "BORRAR DATOS") {
            cout << "Ingresa el DUI de la persona a eliminar: ";
            string dui;
            getline(cin, dui);
            borrarDatosPersona(dui);
        } else if (comando == "SUMA") {
            calcularSuma();
        } else if (comando == "AYUDA") {
            cout << "Bingo3000: Aquí tienes una lista de comandos que puedes usar:\n";
            cout << "- INGRESO DE DATOS: Permite ingresar los datos personales de una persona.\n";
            cout << "- MOSTRAR DATOS PERSONALES: Muestra todos los datos personales registrados en el archivo.\n";
            cout << "- ACTUALIZAR DATOS: Actualiza la información de una persona según su DUI.\n";
            cout << "- BORRAR DATOS: Elimina los datos de una persona según su DUI.\n";
            cout << "- SUMA: Calcula la suma de una cantidad de números que determines.\n";
            cout << "- HOLA: Inicia una conversación amistosa con el chatbot.\n";
            cout << "- SALIR: Finaliza el programa.\n";
        } else if (comando == "SALIR") {
            cout << "OK. Bye!" << endl;
            break;
        } else {
            cout << "Comando no reconocido.\n";
        }
    }

    return 0;
}