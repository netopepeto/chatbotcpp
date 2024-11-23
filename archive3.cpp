#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Estructura que define los datos básicos de una persona
struct Persona {
    string nombre;
    string dui; 
    int edad;
    string telefono;
    string lugarTrabajo;
    string correo;
    string direccion;
};

// Función para guardar mensajes
void guardarMensaje(const string& mensaje) {
    ofstream archivo("registro_de_mensajes.txt", ios::app); // Abre el archivo en modo de agregar
    if (archivo.is_open()) {
        archivo << mensaje << endl; // Escribe el mensaje en el archivo
        archivo.close(); // Cierra el archivo
    } else {
        cerr << "No se pudo abrir el archivo de mensajes." << endl; // Error si no se puede abrir
    }
}

// Función para guardar los datos de una persona en "datos_personales.txt"
// Cada registro incluye todos los campos de la estructura Persona.
void guardarDatosPersona(const Persona& persona) {
    ofstream archivo("datos_personales.txt", ios::app); // Abre el archivo en modo de agregar
    if (archivo.is_open()) {
        // Escribe los datos de la persona en el archivo
        archivo << "Nombre: " << persona.nombre << endl;
        archivo << "DUI: " << persona.dui << endl;
        archivo << "Edad: " << persona.edad << endl;
        archivo << "Teléfono: " << persona.telefono << endl;
        archivo << "Lugar de Trabajo: " << persona.lugarTrabajo << endl;
        archivo << "Correo: " << persona.correo << endl;
        archivo << "Dirección: " << persona.direccion << endl;
        archivo << "------------------------" << endl;
        archivo.close(); // Cierra el archivo
    } else {
        cerr << "No se pudo abrir el archivo de datos personales." << endl; // Error si no se puede abrir
    }
}

// Función para mostrar el contenido de un archivo en la consola
// Recibe el nombre del archivo y muestra cada línea que contiene.
void mostrarArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo); // Abre el archivo en modo de lectura
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            cout << linea << endl; // Imprime cada línea del archivo
        }
        archivo.close(); // Cierra el archivo
    } else {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl; // Error si no se puede abrir
    }
}

// Función para convertir una cadena a mayúsculas útil para comparar comandos del usuario sin importar el formato.
string convertirMayusculas(const string& entrada) {
    string mayuscula = entrada; // Copia la entrada original
    // Convierte cada carácter a mayúscula
    transform(mayuscula.begin(), mayuscula.end(), mayuscula.begin(), ::toupper);
    return mayuscula; // Devuelve la cadena convertida
}

// Función para permitir al usuario ingresar datos de una persona
void ingresarDatosPersona() {
    Persona persona;
    cout << "Ingrese el nombre completo: ";
    getline(cin, persona.nombre);
    cout << "Ingrese el DUI: ";
    getline(cin, persona.dui);
    cout << "Ingrese la edad: ";
    cin >> persona.edad;
    cin.ignore(); // Limpia el buffer antes de leer más cadenas
    cout << "Ingrese el teléfono celular: ";
    getline(cin, persona.telefono);
    cout << "Ingrese el lugar de trabajo: ";
    getline(cin, persona.lugarTrabajo);
    cout << "Ingrese el correo electrónico: ";
    getline(cin, persona.correo);
    cout << "Ingrese la dirección de su residencia: ";
    getline(cin, persona.direccion);

    guardarDatosPersona(persona); // Guarda los datos en el archivo
}

// Función para actualizar los datos de una persona en "datos_personales.txt"
void actualizarDatosPersona(const string& dui) {
    ifstream archivoEntrada("datos_personales.txt"); // Archivo original
    ofstream archivoTemporal("temp.txt"); // Archivo temporal para guardar cambios

    if (!archivoEntrada.is_open() || !archivoTemporal.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    Persona personaActualizada;
    bool encontrado = false;

    while (getline(archivoEntrada, linea)) {
        // Busca el registro por el DUI
        if (linea.find("DUI: " + dui) != string::npos) {
            encontrado = true;
            // Solicita nuevos datos para actualizar
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

            // Escribe los datos actualizados en el archivo temporal
            archivoTemporal << "Nombre: " << personaActualizada.nombre << endl;
            archivoTemporal << "DUI: " << dui << endl;
            archivoTemporal << "Edad: " << personaActualizada.edad << endl;
            archivoTemporal << "Teléfono: " << personaActualizada.telefono << endl;
            archivoTemporal << "Lugar de Trabajo: " << personaActualizada.lugarTrabajo << endl;
            archivoTemporal << "Correo: " << personaActualizada.correo << endl;
            archivoTemporal << "Dirección: " << personaActualizada.direccion << endl;
            archivoTemporal << "------------------------" << endl;

            // Salta las siguientes 6 líneas del archivo original (registro viejo)
            for (int i = 0; i < 6; ++i) getline(archivoEntrada, linea);
        } else {
            archivoTemporal << linea << endl; // Copia las líneas no modificadas
        }
    }

    //cierra los archivos
    archivoEntrada.close();
    archivoTemporal.close();

    if (encontrado) {
        // Reemplaza el archivo original con el actualizado
        remove("datos_personales.txt");
        rename("temp.txt", "datos_personales.txt");
        cout << "Datos actualizados correctamente.\n";
    } else {
        remove("temp.txt"); // Borra el archivo temporal si no se encuentra el DUI
        cout << "DUI no encontrado.\n";
    }
}

// Función para eliminar un registro completo basado en el DUI
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
            // Salta las siguientes 6 líneas para omitir el registro
            for (int i = 0; i < 6; ++i) getline(archivoEntrada, linea);
        } else {
            archivoTemporal << linea << endl; // Copia las líneas no eliminadas
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

// Función para calcular la suma de varios números
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

// Función principal: Controla el flujo del programa
int main() {
    string entrada;
    cout << "Hola, soy Bingo 3000. ;)\nEscribe un comando para interactuar.\n";

    while (true) {
        cout << "Comando: ";
        getline(cin, entrada);
        guardarMensaje("Comando: " + entrada); // Guarda el comando en el registro
        string comando = convertirMayusculas(entrada); // Convierte el comando a mayúsculas

        if (comando == "INGRESO DE DATOS") {
            ingresarDatosPersona();
        } else if (comando == "ACTUALIZAR DATOS") {
            string dui;
            cout << "Ingrese el DUI del registro que desea actualizar: ";
            getline(cin, dui);
            actualizarDatosPersona(dui);
        } else if (comando == "BORRAR DATOS") {
            string dui;
            cout << "Ingrese el DUI del registro que desea borrar: ";
            getline(cin, dui);
            borrarDatosPersona(dui);
        } else if (comando == "MOSTRAR DATOS PERSONALES") {
            mostrarArchivo("datos_personales.txt");
        } else if (comando == "SUMA") {
            calcularSuma();
        } else if (comando == "AYUDA") {
            cout << "Comandos disponibles:\n";
            cout << "- INGRESO DE DATOS: Registrar nueva persona.\n";
            cout << "- ACTUALIZAR DATOS: Modificar los datos de una persona.\n";
            cout << "- BORRAR DATOS: Eliminar un registro por DUI.\n";
            cout << "- MOSTRAR DATOS PERSONALES: Mostrar todos los datos registrados.\n";
            cout << "- SUMA: Calcular la suma de varios números.\n";
            cout << "- SALIR: Terminar el programa.\n";
        } else if (comando == "SALIR") {
            cout << "OK. Bye! :)" << endl;
            break;
        } else {
            cout << "Comando no reconocido. Escribe 'AYUDA' para ver los comandos disponibles.\n";
        }
    }

    return 0;
}
