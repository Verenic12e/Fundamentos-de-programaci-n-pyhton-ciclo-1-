#include "BibliotecaDB.h"
#include <limits>
#include <regex>
#include <filesystem>

// Utilidades de entrada validada
int leerEntero(const string& prompt) {
    regex soloDigitos(R"(^\d+$)");
    while (true) {
        cout << prompt;
        string linea;
        if (!getline(cin, linea)) {
            cout << "[ERROR] Entrada invalida. Intenta de nuevo.\n";
            cin.clear();
            continue;
        }
        if (regex_match(linea, soloDigitos)) {
            try {
                long long valor = stoll(linea);
                if (valor >= std::numeric_limits<int>::min() && valor <= std::numeric_limits<int>::max()) {
                    return static_cast<int>(valor);
                }
            } catch(...) {}
        }
        cout << "[ERROR] Ingrese solo numeros enteros validos.\n";
    }
}

string leerNombre(const string& prompt) {
    // Acepta únicamente letras y espacios (sin acentos ni caracteres especiales)
    regex letrasEspacios(R"(^[A-Za-z ]+$)");
    while (true) {
        cout << prompt;
        string linea;
        if (!getline(cin, linea)) {
            cout << "[ERROR] Entrada invalida. Intenta de nuevo.\n";
            cin.clear();
            continue;
        }
        if (!linea.empty() && regex_match(linea, letrasEspacios)) {
            return linea;
        }
        cout << "[ERROR] Ingrese solo letras y espacios (sin caracteres especiales).\n";
    }
}

string leerSoloDigitos(const string& prompt) {
    regex soloDigitos(R"(^\d+$)");
    while (true) {
        cout << prompt;
        string linea;
        if (!getline(cin, linea)) {
            cout << "[ERROR] Entrada invalida. Intenta de nuevo.\n";
            cin.clear();
            continue;
        }
        if (!linea.empty() && regex_match(linea, soloDigitos)) {
            return linea;
        }
        cout << "[ERROR] Ingrese solo numeros.\n";
    }
}

void mostrarMenu() {
    cout << "\n===== MENU BIBLIOTECA =====\n\n"
         << "[ AUTORES ]\n"
         << "  1. Agregar Autor\n"
         << "  2. Lista de Autores\n"
         << "  3. Eliminar Autor\n"
         << "  4. Actualizar Autor\n\n"
         << "[ EDITORIALES ]\n"
         << "  5. Agregar Editorial\n"
         << "  6. Lista de Editoriales\n"
         << "  7. Eliminar Editorial\n"
         << "  8. Actualizar Editorial\n\n"
         << "[ LIBROS ]\n"
         << "  9.  Agregar Libro\n"
         << "  10. Lista de Libros\n"
         << "  11. Eliminar Libro\n"
         << "  12. Actualizar Libro\n\n"
         << "[ ESTUDIANTES ]\n"
         << "  13. Agregar Estudiante\n"
         << "  14. Lista de Estudiantes\n"
         << "  15. Eliminar Estudiante\n"
         << "  16. Actualizar Estudiante\n\n"
         << "[ PRESTAMOS ]\n"
         << "  17. Agregar Prestamo\n"
         << "  18. Lista de Prestamos\n"
         << "  19. Eliminar Prestamo\n"
         << "  20. Actualizar Prestamo (Devolucion)\n"
         << "  21. Buscar Prestamos por Estudiante\n\n"
         << "--------------------------------------\n"
         << "  0. Salir\n\n"
         << "Ingrese opcion: ";
}

int main() {
    BibliotecaDB db;
    // Establecer directorio base a la carpeta actual de trabajo
    try {
        db.setBaseDir(std::filesystem::current_path().string());
    } catch(...) {}
    db.cargarDatos();

    int opcion;

    while (true) {
        mostrarMenu();

        {
            string tmp;
            cout.flush();
            if (!getline(cin, tmp)) {
                cout << "[ERROR] Entrada invalida. Intenta de nuevo.\n";
                cin.clear();
                continue;
            }
            try { opcion = stoi(tmp); }
            catch(...) { cout << "[ERROR] Entrada invalida. Intenta de nuevo.\n"; continue; }
        }

        if (opcion == 0) {
            db.guardarDatos();
            cout << "Datos guardados. Saliendo...\n";
            break;
        }

        switch (opcion) {
            case 1: {  // Agregar Autor
                Autor a;
                a.nombre = leerNombre("Nombre: ");
                a.nacionalidad = leerNombre("Nacionalidad: ");
                db.agregarAutor(a);
                break;
            }
            case 2:  // Listar Autores
                db.listarAutores();
                break;
            case 3: {  // Eliminar Autor
                int id = leerEntero("ID Autor a eliminar: ");
                db.eliminarAutor(id);
                break;
            }
            case 4: {  // Actualizar Autor
                int id = leerEntero("ID Autor a actualizar: ");
                Autor nuevo;
                nuevo.id = id;
                nuevo.nombre = leerNombre("Nuevo Nombre: ");
                nuevo.nacionalidad = leerNombre("Nueva Nacionalidad: ");
                db.actualizarAutor(id, nuevo);
                break;
            }
            case 5: {  // Agregar Editorial
                Editorial e;
                e.nombre = leerNombre("Nombre: ");
                db.agregarEditorial(e);
                break;
            }
            case 6:  // Listar Editoriales
                db.listarEditoriales();
                break;
            case 7: {  // Eliminar Editorial
                int id = leerEntero("ID Editorial a eliminar: ");
                db.eliminarEditorial(id);
                break;
            }
            case 8: {  // Actualizar Editorial
                int id = leerEntero("ID Editorial a actualizar: ");
                Editorial nuevo;
                nuevo.id = id;
                nuevo.nombre = leerNombre("Nuevo Nombre: ");
                db.actualizarEditorial(id, nuevo);
                break;
            }
            case 9: {  // Agregar Libro
                Libro l;
                l.titulo = leerNombre("Titulo: ");
                l.isbn = leerSoloDigitos("ISBN: ");
                l.ano_publicacion = leerEntero("Ano de Publicacion: ");
                l.id_autor = leerEntero("ID Autor: ");
                l.id_editorial = leerEntero("ID Editorial: ");
                db.agregarLibro(l);
                break;
            }
            case 10:  // Listar Libros
                db.listarLibros();
                break;
            case 11: {  // Eliminar Libro
                int id = leerEntero("ID Libro a eliminar: ");
                db.eliminarLibro(id);
                break;
            }
            case 12: {  // Actualizar Libro
                int id = leerEntero("ID Libro a actualizar: ");
                Libro nuevo;
                nuevo.id = id;
                nuevo.titulo = leerNombre("Nuevo Titulo: ");
                nuevo.isbn = leerSoloDigitos("Nuevo ISBN: ");
                nuevo.ano_publicacion = leerEntero("Nuevo Ano de Publicacion: ");
                nuevo.id_autor = leerEntero("Nuevo ID Autor: ");
                nuevo.id_editorial = leerEntero("Nuevo ID Editorial: ");
                db.actualizarLibro(id, nuevo);
                break;
            }
            case 13: {  // Agregar Estudiante
                Estudiante e;
                e.nombre = leerNombre("Nombre: ");
                cout << "Grado: "; getline(cin, e.grado);
                db.agregarEstudiante(e);
                break;
            }
            case 14:  // Listar Estudiantes
                db.listarEstudiantes();
                break;
            case 15: {  // Eliminar Estudiante
                int id = leerEntero("ID Estudiante a eliminar: ");
                db.eliminarEstudiante(id);
                break;
            }
            case 16: {  // Actualizar Estudiante
                int id = leerEntero("ID Estudiante a actualizar: ");
                Estudiante nuevo;
                nuevo.id = id;
                nuevo.nombre = leerNombre("Nuevo Nombre: ");
                cout << "Nuevo Grado: "; getline(cin, nuevo.grado);
                db.actualizarEstudiante(id, nuevo);
                break;
            }
            case 17: {  // Agregar Prestamo
                Prestamo p;
                p.id_libro = leerEntero("ID Libro: ");
                p.id_estudiante = leerEntero("ID Estudiante: ");
                cout << "Fecha Prestamo (YYYY-MM-DD): "; getline(cin, p.fecha_prestamo);
                p.fecha_devolucion = "";  // Inicialmente vacío
                db.agregarPrestamo(p);
                break;
            }
            case 18:  // Listar Prestamos
                db.listarPrestamos();
                break;
            case 19: {  // Eliminar Prestamo
                int id = leerEntero("ID Prestamo a eliminar: ");
                db.eliminarPrestamo(id);
                break;
            }
            case 20: {  // Actualizar Prestamo
                int id = leerEntero("ID Prestamo a actualizar: ");
                Prestamo nuevo;
                nuevo.id = id;
                nuevo.id_libro = leerEntero("Nuevo ID Libro: ");
                nuevo.id_estudiante = leerEntero("Nuevo ID Estudiante: ");
                cout << "Nueva Fecha Prestamo (YYYY-MM-DD): "; getline(cin, nuevo.fecha_prestamo);
                cout << "Fecha Devolucion (YYYY-MM-DD o vacio): "; getline(cin, nuevo.fecha_devolucion);
                db.actualizarPrestamo(id, nuevo);
                break;
            }
            case 21: {  // Buscar Prestamos por Estudiante
                int idEst = leerEntero("ID Estudiante para buscar prestamos: ");
                db.buscarPrestamosPorEstudiante(idEst);
                break;
            }
            default:
                cout << "[ERROR] Opcion invalida. Intenta de nuevo.\n";
        }
    }

    return 0;
}
