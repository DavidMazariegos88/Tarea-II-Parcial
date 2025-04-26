#include <iostream>
#include <string>
using namespace std;

// Definimos una estructura para almacenar los datos de cada estudiante
struct Estudiante {
    int id;
    string nombre;
    string apellido;
    float nota1;
    float nota2;
    float nota3;
    float nota4;
    float promedio;
};

int main() {
    int cantidad;

    cout << "Ingrese la cantidad de estudiantes: ";
    cin >> cantidad;
    cin.ignore(); // Limpiar el buffer

    // Reservar memoria dinámica para N estudiantes
    Estudiante* estudiantes = new Estudiante[cantidad];

    // Ingreso de datos
    for (int i = 0; i < cantidad; i++) {
        cout << "\n--- Ingresando datos del estudiante #" << (i + 1) << " ---" << endl;

        cout << "ID: ";
        cin >> (estudiantes + i)->id;
        cin.ignore(); // Limpiar el buffer antes de getline

        cout << "Nombre: ";
        getline(cin, (estudiantes + i)->nombre);

        cout << "Apellido: ";
        getline(cin, (estudiantes + i)->apellido);

        cout << "Nota 1: ";
        cin >> (estudiantes + i)->nota1;
        cout << "Nota 2: ";
        cin >> (estudiantes + i)->nota2;
        cout << "Nota 3: ";
        cin >> (estudiantes + i)->nota3;
        cout << "Nota 4: ";
        cin >> (estudiantes + i)->nota4;

        // Calcular el promedio
        (estudiantes + i)->promedio = ((estudiantes + i)->nota1 + (estudiantes + i)->nota2 +
                                       (estudiantes + i)->nota3 + (estudiantes + i)->nota4) / 4.0f;
    }

    // Mostrar los resultados
    cout << "\n=== Resultados de los estudiantes ===\n";
    for (int i = 0; i < cantidad; i++) {
        cout << "\nEstudiante: " << (estudiantes + i)->nombre << " " << (estudiantes + i)->apellido << endl;
        cout << "ID: " << (estudiantes + i)->id << endl;
        cout << "Promedio: " << (estudiantes + i)->promedio << endl;

        if ((estudiantes + i)->promedio >= 60.0f) {
            cout << "Estado: Aprobado" << endl;
        } else {
            cout << "Estado: Reprobado" << endl;
        }
    }

    // Liberar la memoria dinámica
    delete[] estudiantes;

    return 0;
}

