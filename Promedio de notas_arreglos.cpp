#include <iostream>
#include <string>
using namespace std;

const int MAX_ESTUDIANTES = 100; // Maximo de estudiantes permitidos

int main() {
    int ids[MAX_ESTUDIANTES];
    string nombres[MAX_ESTUDIANTES];
    string apellidos[MAX_ESTUDIANTES];
    float notas1[MAX_ESTUDIANTES], notas2[MAX_ESTUDIANTES], notas3[MAX_ESTUDIANTES], notas4[MAX_ESTUDIANTES];
    float promedios[MAX_ESTUDIANTES];
    int cantidad;

    cout << "¿Cuantos estudiantes desea ingresar? ";
    cin >> cantidad;

    if (cantidad > MAX_ESTUDIANTES || cantidad <= 0) {
        cout << "Cantidad invalida de estudiantes. El maximo es " << MAX_ESTUDIANTES << "." << endl;
        return 1;
    }

    // Entrada de datos
    for (int i = 0; i < cantidad; i++) {
        cout << "\nEstudiante #" << (i + 1) << endl;

        cout << "ID: ";
        cin >> ids[i];
        cin.ignore(); // Limpiar el buffer antes de usar getline

        cout << "Nombre: ";
        getline(cin, nombres[i]);

        cout << "Apellido: ";
        getline(cin, apellidos[i]);

        cout << "Nota 1: ";
        cin >> notas1[i];
        cout << "Nota 2: ";
        cin >> notas2[i];
        cout << "Nota 3: ";
        cin >> notas3[i];
        cout << "Nota 4: ";
        cin >> notas4[i];

        // Calcular promedio
        promedios[i] = (notas1[i] + notas2[i] + notas3[i] + notas4[i]) / 4.0f;
    }

    // Mostrar resultados
    cout << "\n--- Resultados ---\n";
    for (int i = 0; i < cantidad; i++) {
        cout << "\nEstudiante: " << nombres[i] << " " << apellidos[i] << endl;
        cout << "ID: " << ids[i] << endl;
        cout << "Promedio: " << promedios[i] << endl;
        if (promedios[i] >= 60) {
            cout << "Estado: Aprobado" << endl;
        } else {
            cout << "Estado: Reprobado" << endl;
        }
    }

    return 0;
}

