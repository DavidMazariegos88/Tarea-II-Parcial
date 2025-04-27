#include <iostream>
#include <fstream>
#include <string>
#include <cstring> // Para strcpy
using namespace std;

struct Estudiante {
    int id;
    char nombre[50];
    char apellido[50];
    float notas[4];
    float promedio;
    char resultado[10];
};

void calcularPromedioYResultado(Estudiante* e) {
    e->promedio = (e->notas[0] + e->notas[1] + e->notas[2] + e->notas[3]) / 4.0f;
    if (e->promedio >= 60) {
        strcpy(e->resultado, "Aprobado");
    } else {
        strcpy(e->resultado, "Reprobado");
    }
}

template<typename T>
void validarEntrada(T& valor, const string& mensaje) {
    while (!(cin >> valor)) {
        cout << "Entrada inválida. " << mensaje << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void agregarEstudiante() {
    int cantidad;
    cout << "Ingrese la cantidad de estudiantes a agregar: " << endl;
    validarEntrada(cantidad, "Ingrese un número entero válido: ");

    Estudiante* estudiantes = new Estudiante[cantidad];
    ofstream archivo("notas.dat", ios::binary | ios::app);

    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        cout << endl << "--- Estudiante " << i + 1 << " ---" << endl;
        cout << "ID: " << endl;
        validarEntrada(estudiantes[i].id, "Ingrese un número entero: ");
        cin.ignore();
        cout << "Nombre: " << endl;
        cin.getline(estudiantes[i].nombre, 50);
        cout << "Apellido: " << endl;
        cin.getline(estudiantes[i].apellido, 50);
        for (int j = 0; j < 4; j++) {
            cout << "Nota " << j + 1 << ": " << endl;
            validarEntrada(estudiantes[i].notas[j], "Ingrese una nota válida: ");
        }
        calcularPromedioYResultado(&estudiantes[i]);
        archivo.write(reinterpret_cast<char*>(&estudiantes[i]), sizeof(Estudiante));
    }

    archivo.close();
    delete[] estudiantes;
    cout << "Estudiantes agregados correctamente." << endl;
}

void mostrarEstudiantes() {
    Estudiante est;
    ifstream archivo("notas.dat", ios::binary);

    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    cout << endl << "--- Lista de Estudiantes ---" << endl;
    while (archivo.read(reinterpret_cast<char*>(&est), sizeof(Estudiante))) {
        cout << "ID: " << est.id << endl;
        cout << "Nombre: " << est.nombre << endl;
        cout << "Apellido: " << est.apellido << endl;
        cout << "Notas: " << est.notas[0] << ", " << est.notas[1] << ", " << est.notas[2] << ", " << est.notas[3] << endl;
        cout << "Promedio: " << est.promedio << endl;
        cout << "Resultado: " << est.resultado << endl;
        cout << "------------------------------" << endl;
    }

    archivo.close();
}

void actualizarEstudiante() {
    Estudiante est;
    fstream archivo("notas.dat", ios::binary | ios::in | ios::out);

    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    int idBusqueda;
    cout << "Ingrese el ID del estudiante a actualizar: " << endl;
    validarEntrada(idBusqueda, "Ingrese un número entero válido: ");

    bool encontrado = false;
    while (archivo.read(reinterpret_cast<char*>(&est), sizeof(Estudiante))) {
        if (est.id == idBusqueda) {
            cin.ignore();
            cout << "Nuevo Nombre: " << endl;
            cin.getline(est.nombre, 50);
            cout << "Nuevo Apellido: " << endl;
            cin.getline(est.apellido, 50);
            for (int i = 0; i < 4; i++) {
                cout << "Nueva Nota " << i + 1 << ": " << endl;
                validarEntrada(est.notas[i], "Ingrese una nota válida: ");
            }
            calcularPromedioYResultado(&est);

            int pos = archivo.tellg();
            archivo.seekp(pos - sizeof(Estudiante));
            archivo.write(reinterpret_cast<char*>(&est), sizeof(Estudiante));
            encontrado = true;
            cout << "Estudiante actualizado correctamente." << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "Estudiante no encontrado." << endl;
    }

    archivo.close();
}

void eliminarEstudiante() {
    Estudiante est;
    ifstream archivoLectura("notas.dat", ios::binary);
    ofstream archivoTemporal("temp.dat", ios::binary);

    if (!archivoLectura || !archivoTemporal) {
        cout << "Error al abrir los archivos." << endl;
        return;
    }

    int idBusqueda;
    cout << "Ingrese el ID del estudiante a eliminar: " << endl;
    validarEntrada(idBusqueda, "Ingrese un número entero válido: ");

    bool encontrado = false;
    while (archivoLectura.read(reinterpret_cast<char*>(&est), sizeof(Estudiante))) {
        if (est.id != idBusqueda) {
            archivoTemporal.write(reinterpret_cast<char*>(&est), sizeof(Estudiante));
        } else {
            encontrado = true;
        }
    }

    archivoLectura.close();
    archivoTemporal.close();

    remove("notas.dat");
    rename("temp.dat", "notas.dat");

    if (encontrado) {
        cout << "Estudiante eliminado correctamente." << endl;
    } else {
        cout << "Estudiante no encontrado." << endl;
    }
}

int main() {
    int opcion;
    do {
        cout << endl << "====== MENU PRINCIPAL ======" << endl;
        cout << "1. Agregar Estudiantes" << endl;
        cout << "2. Mostrar Estudiantes" << endl;
        cout << "3. Actualizar Estudiante" << endl;
        cout << "4. Eliminar Estudiante" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: " << endl;
        validarEntrada(opcion, "Ingrese una opción válida: ");

        switch (opcion) {
            case 1: agregarEstudiante(); break;
            case 2: mostrarEstudiantes(); break;
            case 3: actualizarEstudiante(); break;
            case 4: eliminarEstudiante(); break;
            case 5: cout << "Saliendo del programa..." << endl; break;
            default: cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (opcion != 5);

    return 0;
}

