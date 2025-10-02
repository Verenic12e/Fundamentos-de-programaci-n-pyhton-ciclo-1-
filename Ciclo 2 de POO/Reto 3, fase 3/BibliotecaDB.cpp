// BibliotecaDB.cpp
#include "BibliotecaDB.h"
#include <cstdio>

// Método plantilla para verificar existencia de ID
template<typename T>
bool BibliotecaDB::existeID(const vector<T>& vec, int id) const {
    return any_of(vec.begin(), vec.end(), [id](const T& e){ return e.id == id; });
}

// Obtiene el siguiente ID (max + 1)
template<typename T>
int BibliotecaDB::siguienteID(const vector<T>& vec) const {
    int maxId = 0;
    for (const auto& e : vec) maxId = max(maxId, e.id);
    return maxId + 1;
}

// Verificaciones de existencia
bool BibliotecaDB::autorExiste(int id) const { return existeID(autores, id); }
bool BibliotecaDB::editorialExiste(int id) const { return existeID(editoriales, id); }
bool BibliotecaDB::estudianteExiste(int id) const { return existeID(estudiantes, id); }
bool BibliotecaDB::libroExiste(int id) const { return existeID(libros, id); }
bool BibliotecaDB::prestamoExiste(int id) const { return existeID(prestamos, id); }

// Verifica disponibilidad de libro
bool BibliotecaDB::libroDisponible(int id_libro) const {
    for (const auto& p : prestamos) {
        if (p.id_libro == id_libro && p.fecha_devolucion.empty()) return false;
    }
    return true;
}

// Verificaciones para referencias
bool BibliotecaDB::autorEnUso(int id_autor) const {
    for (const auto& l : libros) {
        if (l.id_autor == id_autor) return true;
    }
    return false;
}

bool BibliotecaDB::editorialEnUso(int id_editorial) const {
    for (const auto& l : libros) {
        if (l.id_editorial == id_editorial) return true;
    }
    return false;
}

bool BibliotecaDB::libroEnUso(int id_libro) const {
    for (const auto& p : prestamos) {
        if (p.id_libro == id_libro) return true;
    }
    return false;
}

bool BibliotecaDB::estudianteEnUso(int id_estudiante) const {
    for (const auto& p : prestamos) {
        if (p.id_estudiante == id_estudiante) return true;
    }
    return false;
}

// Validar formato de fecha YYYY-MM-DD
bool BibliotecaDB::validarFecha(const string& fecha) const {
    regex formato(R"(\d{4}-\d{2}-\d{2})");
    if (!regex_match(fecha, formato)) return false;
    // Validación adicional: parsear y verificar rangos
    int ano, mes, dia;
    sscanf(fecha.c_str(), "%d-%d-%d", &ano, &mes, &dia);
    if (mes < 1 || mes > 12 || dia < 1 || dia > 31) return false;  // Chequeo básico, ignora meses con 30/31 días
    return true;
}

// --- CRUD para Autor ---
bool BibliotecaDB::agregarAutor(const Autor& a) {
    Autor nuevo = a;
    nuevo.id = siguienteID(autores);
    autores.push_back(nuevo);
    cout << "[OK] Autor agregado\n";
    return true;
}

void BibliotecaDB::listarAutores() const {
    cout << "\n--- Lista de Autores ---\n";
    if (autores.empty()) {
        cout << "(sin autores)\n";
        return;
    }
    for (const auto& a : autores) {
        cout << "ID: " << a.id << "\tNombre: " << a.nombre << "\tNacionalidad: " << a.nacionalidad << "\n";
    }
}

bool BibliotecaDB::eliminarAutor(int id) {
    if (!autorExiste(id)) {
        cout << "[ERROR] Autor no existe ID: " << id << "\n";
        return false;
    }
    if (autorEnUso(id)) {
        cout << "[ERROR] Autor en uso en libros, no se puede eliminar ID: " << id << "\n";
        return false;
    }
    auto it = remove_if(autores.begin(), autores.end(), [id](const Autor& a){ return a.id == id; });
    autores.erase(it, autores.end());
    cout << "[OK] Autor eliminado\n";
    return true;
}

bool BibliotecaDB::actualizarAutor(int id, const Autor& nuevo) {
    if (!autorExiste(id)) {
        cout << "[ERROR] Autor no existe ID: " << id << "\n";
        return false;
    }
    if (nuevo.id != id && autorExiste(nuevo.id)) {
        cout << "[ERROR] Nuevo ID duplicado: " << nuevo.id << "\n";
        return false;
    }
    for (auto& a : autores) {
        if (a.id == id) {
            a = nuevo;
            cout << "[OK] Autor actualizado\n";
            return true;
        }
    }
    return false;
}

// --- CRUD para Editorial --- (similar a Autor)
bool BibliotecaDB::agregarEditorial(const Editorial& e) {
    Editorial nuevo = e;
    nuevo.id = siguienteID(editoriales);
    editoriales.push_back(nuevo);
    cout << "[OK] Editorial agregada\n";
    return true;
}

void BibliotecaDB::listarEditoriales() const {
    cout << "\n--- Lista de Editoriales ---\n";
    if (editoriales.empty()) {
        cout << "(sin editoriales)\n";
        return;
    }
    for (const auto& e : editoriales) {
        cout << "ID: " << e.id << "\tNombre: " << e.nombre << "\n";
    }
}

bool BibliotecaDB::eliminarEditorial(int id) {
    if (!editorialExiste(id)) {
        cout << "[ERROR] Editorial no existe ID: " << id << "\n";
        return false;
    }
    if (editorialEnUso(id)) {
        cout << "[ERROR] Editorial en uso en libros, no se puede eliminar ID: " << id << "\n";
        return false;
    }
    auto it = remove_if(editoriales.begin(), editoriales.end(), [id](const Editorial& e){ return e.id == id; });
    editoriales.erase(it, editoriales.end());
    cout << "[OK] Editorial eliminada\n";
    return true;
}

bool BibliotecaDB::actualizarEditorial(int id, const Editorial& nuevo) {
    if (!editorialExiste(id)) {
        cout << "[ERROR] Editorial no existe ID: " << id << "\n";
        return false;
    }
    if (nuevo.id != id && editorialExiste(nuevo.id)) {
        cout << "[ERROR] Nuevo ID duplicado: " << nuevo.id << "\n";
        return false;
    }
    for (auto& e : editoriales) {
        if (e.id == id) {
            e = nuevo;
            cout << "[OK] Editorial actualizada\n";
            return true;
        }
    }
    return false;
}

// --- CRUD para Libro ---
bool BibliotecaDB::agregarLibro(const Libro& l) {
    Libro nuevo = l;
    nuevo.id = siguienteID(libros);
    if (!autorExiste(nuevo.id_autor)) {
        cout << "[ERROR] Autor no existe ID: " << nuevo.id_autor << "\n";
        return false;
    }
    if (!editorialExiste(nuevo.id_editorial)) {
        cout << "[ERROR] Editorial no existe ID: " << nuevo.id_editorial << "\n";
        return false;
    }
    if (nuevo.ano_publicacion <= 0) {
        cout << "[ERROR] Ano de publicacion invalido: " << nuevo.ano_publicacion << "\n";
        return false;
    }
    libros.push_back(nuevo);
    cout << "[OK] Libro agregado\n";
    return true;
}

void BibliotecaDB::listarLibros() const {
    cout << "\n--- Lista de Libros ---\n";
    if (libros.empty()) {
        cout << "(sin libros)\n";
        return;
    }
    for (const auto& l : libros) {
        string nombreAutor = "Desconocido";
        string nombreEditorial = "Desconocida";
        // Simular join: buscar nombre de autor y editorial
        for (const auto& a : autores) if (a.id == l.id_autor) nombreAutor = a.nombre;
        for (const auto& e : editoriales) if (e.id == l.id_editorial) nombreEditorial = e.nombre;
        cout << "ID: " << l.id << "\tTitulo: " << l.titulo
             << "\tISBN: " << l.isbn << "\tAno: " << l.ano_publicacion
             << "\tAutor: " << nombreAutor << "\tEditorial: " << nombreEditorial << "\n";
    }
}

bool BibliotecaDB::eliminarLibro(int id) {
    if (!libroExiste(id)) {
        cout << "[ERROR] Libro no existe ID: " << id << "\n";
        return false;
    }
    if (libroEnUso(id)) {
        cout << "[ERROR] Libro en uso en préstamos, no se puede eliminar ID: " << id << "\n";
        return false;
    }
    auto it = remove_if(libros.begin(), libros.end(), [id](const Libro& l){ return l.id == id; });
    libros.erase(it, libros.end());
    cout << "[OK] Libro eliminado\n";
    return true;
}

bool BibliotecaDB::actualizarLibro(int id, const Libro& nuevo) {
    if (!libroExiste(id)) {
        cout << "[ERROR] Libro no existe ID: " << id << "\n";
        return false;
    }
    if (nuevo.id != id && libroExiste(nuevo.id)) {
        cout << "[ERROR] Nuevo ID duplicado: " << nuevo.id << "\n";
        return false;
    }
    if (!autorExiste(nuevo.id_autor)) {
        cout << "[ERROR] Autor no existe ID: " << nuevo.id_autor << "\n";
        return false;
    }
    if (!editorialExiste(nuevo.id_editorial)) {
        cout << "[ERROR] Editorial no existe ID: " << nuevo.id_editorial << "\n";
        return false;
    }
    if (nuevo.ano_publicacion <= 0) {
        cout << "[ERROR] Ano de publicacion invalido: " << nuevo.ano_publicacion << "\n";
        return false;
    }
    for (auto& l : libros) {
        if (l.id == id) {
            l = nuevo;
            cout << "[OK] Libro actualizado\n";
            return true;
        }
    }
    return false;
}

// --- CRUD para Estudiante ---
bool BibliotecaDB::agregarEstudiante(const Estudiante& e) {
    Estudiante nuevo = e;
    nuevo.id = siguienteID(estudiantes);
    estudiantes.push_back(nuevo);
    cout << "[OK] Estudiante agregado\n";
    return true;
}

void BibliotecaDB::listarEstudiantes() const {
    cout << "\n--- Lista de Estudiantes ---\n";
    if (estudiantes.empty()) {
        cout << "(sin estudiantes)\n";
        return;
    }
    for (const auto& e : estudiantes) {
        cout << "ID: " << e.id << "\tNombre: " << e.nombre << "\tGrado: " << e.grado << "\n";
    }
}

bool BibliotecaDB::eliminarEstudiante(int id) {
    if (!estudianteExiste(id)) {
        cout << "[ERROR] Estudiante no existe ID: " << id << "\n";
        return false;
    }
    if (estudianteEnUso(id)) {
        cout << "[ERROR] Estudiante en uso en préstamos, no se puede eliminar ID: " << id << "\n";
        return false;
    }
    auto it = remove_if(estudiantes.begin(), estudiantes.end(), [id](const Estudiante& e){ return e.id == id; });
    estudiantes.erase(it, estudiantes.end());
    cout << "[OK] Estudiante eliminado\n";
    return true;
}

bool BibliotecaDB::actualizarEstudiante(int id, const Estudiante& nuevo) {
    if (!estudianteExiste(id)) {
        cout << "[ERROR] Estudiante no existe ID: " << id << "\n";
        return false;
    }
    if (nuevo.id != id && estudianteExiste(nuevo.id)) {
        cout << "[ERROR] Nuevo ID duplicado: " << nuevo.id << "\n";
        return false;
    }
    for (auto& e : estudiantes) {
        if (e.id == id) {
            e = nuevo;
            cout << "[OK] Estudiante actualizado\n";
            return true;
        }
    }
    return false;
}

// --- CRUD para Prestamo ---
bool BibliotecaDB::agregarPrestamo(const Prestamo& p) {
    Prestamo nuevo = p;
    nuevo.id = siguienteID(prestamos);
    if (!libroExiste(nuevo.id_libro)) {
        cout << "[ERROR] Libro no existe ID: " << nuevo.id_libro << "\n";
        return false;
    }
    if (!estudianteExiste(nuevo.id_estudiante)) {
        cout << "[ERROR] Estudiante no existe ID: " << nuevo.id_estudiante << "\n";
        return false;
    }
    if (!libroDisponible(nuevo.id_libro)) {
        cout << "[ERROR] Libro no disponible para préstamo ID: " << nuevo.id_libro << "\n";
        return false;
    }
    if (!validarFecha(nuevo.fecha_prestamo)) {
        cout << "[ERROR] Formato de fecha inválido (debe ser YYYY-MM-DD): " << nuevo.fecha_prestamo << "\n";
        return false;
    }
    prestamos.push_back(nuevo);
    cout << "[OK] Prestamo agregado\n";
    cout << "[INFO] Prestamos en memoria: " << prestamos.size() << "\n";
    // Guardar inmediatamente para persistir en prestamos.txt
    guardarDatos();
    return true;
}

void BibliotecaDB::listarPrestamos() const {
    cout << "\n--- Lista de Prestamos (" << prestamos.size() << ") ---\n";
    if (prestamos.empty()) {
        cout << "(sin prestamos)\n";
        return;
    }
    for (const auto& p : prestamos) {
        string nombreLibro = "Desconocido";
        string nombreEstudiante = "Desconocido";
        // Simular join: buscar nombres
        for (const auto& l : libros) if (l.id == p.id_libro) nombreLibro = l.titulo;
        for (const auto& e : estudiantes) if (e.id == p.id_estudiante) nombreEstudiante = e.nombre;
        string estado = p.fecha_devolucion.empty() ? "No devuelto" : "Devuelto";
        cout << "ID: " << p.id << "\tLibro: " << nombreLibro << "\tEstudiante: " << nombreEstudiante
             << "\tFecha prestamo: " << p.fecha_prestamo << "\tFecha devolucion: " << (p.fecha_devolucion.empty() ? "-----" : p.fecha_devolucion)
             << "\tEstado: " << estado << "\n";
    }
}

bool BibliotecaDB::eliminarPrestamo(int id) {
    if (!prestamoExiste(id)) {
        cout << "[ERROR] Prestamo no existe ID: " << id << "\n";
        return false;
    }
    auto it = remove_if(prestamos.begin(), prestamos.end(), [id](const Prestamo& p){ return p.id == id; });
    prestamos.erase(it, prestamos.end());
    cout << "[OK] Prestamo eliminado\n";
    // Guardar inmediatamente cambios en prestamos
    guardarDatos();
    return true;
}

bool BibliotecaDB::actualizarPrestamo(int id, const Prestamo& nuevo) {
    if (!prestamoExiste(id)) {
        cout << "[ERROR] Prestamo no existe ID: " << id << "\n";
        return false;
    }
    if (nuevo.id != id && prestamoExiste(nuevo.id)) {
        cout << "[ERROR] Nuevo ID duplicado: " << nuevo.id << "\n";
        return false;
    }
    if (!libroExiste(nuevo.id_libro)) {
        cout << "[ERROR] Libro no existe ID: " << nuevo.id_libro << "\n";
        return false;
    }
    if (!estudianteExiste(nuevo.id_estudiante)) {
        cout << "[ERROR] Estudiante no existe ID: " << nuevo.id_estudiante << "\n";
        return false;
    }
    if (!nuevo.fecha_devolucion.empty() && !validarFecha(nuevo.fecha_devolucion)) {
        cout << "[ERROR] Formato de fecha de devolucion invalido: " << nuevo.fecha_devolucion << "\n";
        return false;
    }
    if (!validarFecha(nuevo.fecha_prestamo)) {
        cout << "[ERROR] Formato de fecha de prestamo invalido: " << nuevo.fecha_prestamo << "\n";
        return false;
    }
    // Nota: No verificamos disponibilidad aquí, asumiendo que actualización no cambia estado si ya prestado
    for (auto& p : prestamos) {
        if (p.id == id) {
            p = nuevo;
            cout << "[OK] Prestamo actualizado\n";
            // Guardar inmediatamente cambios en prestamos
            guardarDatos();
            return true;
        }
    }
    return false;
}

void BibliotecaDB::buscarPrestamosPorEstudiante(int id_estudiante) const {
    cout << "\n--- Prestamos para Estudiante ID " << id_estudiante << " ---\n";
    bool found = false;
    for (const auto& p : prestamos) {
        if (p.id_estudiante == id_estudiante) {
            found = true;
            string nombreLibro = "Desconocido";
            for (const auto& l : libros) if (l.id == p.id_libro) nombreLibro = l.titulo;
            string estado = p.fecha_devolucion.empty() ? "No devuelto" : "Devuelto";
            cout << "ID Prestamo: " << p.id << "\tLibro: " << nombreLibro 
                 << "\tFecha prestamo: " << p.fecha_prestamo 
                 << "\tFecha devolucion: " << (p.fecha_devolucion.empty() ? "-----" : p.fecha_devolucion)
                 << "\tEstado: " << estado << "\n";
        }
    }
    if (!found) cout << "No se encontraron prestamos para este estudiante.\n";
}

// --- Persistencia ---
void BibliotecaDB::guardarDatos() const {
    // Lambda para guardar en archivo con delimitador '|'
    auto guardarArchivo = [this](const string& nombre, const vector<string>& lineas) {
        ofstream f(filePath(nombre));
        if (!f.is_open()) {
            cout << "[ERROR] No se pudo abrir archivo para guardar: " << nombre << "\n";
            return;
        }
        for (const auto& l : lineas) f << l << "\n";
        f.close();
    };

    vector<string> datos;

    // Autores: id|nombre|nacionalidad
    datos.clear();
    for (const auto& a : autores) {
        datos.push_back(to_string(a.id) + "|" + a.nombre + "|" + a.nacionalidad);
    }
    guardarArchivo("autores.txt", datos);

    // Editoriales: id|nombre
    datos.clear();
    for (const auto& e : editoriales) {
        datos.push_back(to_string(e.id) + "|" + e.nombre);
    }
    guardarArchivo("editoriales.txt", datos);

    // Libros: id|titulo|isbn|ano_publicacion|id_autor|id_editorial
    datos.clear();
    for (const auto& l : libros) {
        datos.push_back(to_string(l.id) + "|" + l.titulo + "|" + l.isbn + "|" + to_string(l.ano_publicacion) + "|" + to_string(l.id_autor) + "|" + to_string(l.id_editorial));
    }
    guardarArchivo("libros.txt", datos);

    // Estudiantes: id|nombre|grado
    datos.clear();
    for (const auto& e : estudiantes) {
        datos.push_back(to_string(e.id) + "|" + e.nombre + "|" + e.grado);
    }
    guardarArchivo("estudiantes.txt", datos);

    // Prestamos: id|id_libro|id_estudiante|fecha_prestamo|fecha_devolucion
    datos.clear();
    for (const auto& p : prestamos) {
        datos.push_back(to_string(p.id) + "|" + to_string(p.id_libro) + "|" + to_string(p.id_estudiante) + "|" + p.fecha_prestamo + "|" + p.fecha_devolucion);
    }
    guardarArchivo("prestamos.txt", datos);
}

void BibliotecaDB::cargarDatos() {
    autores.clear();
    editoriales.clear();
    libros.clear();
    estudiantes.clear();
    prestamos.clear();

    // Lambda para leer líneas de archivo
    auto leerArchivo = [this](const string& nombre) -> vector<string> {
        vector<string> lineas;
        ifstream f(filePath(nombre));
        if (!f.is_open()) {
            cout << "[ERROR] No se pudo abrir archivo para cargar: " << nombre << "\n";
            return lineas;
        }
        string linea;
        while (getline(f, linea)) {
            if (!linea.empty()) lineas.push_back(linea);
        }
        f.close();
        return lineas;
    };

    // Función auxiliar para split por delimitador '|'
    auto split = [](const string& s, char delim) -> vector<string> {
        vector<string> result;
        stringstream ss(s);
        string item;
        while (getline(ss, item, delim)) {
            result.push_back(item);
        }
        return result;
    };

    // Cargar Autores
    for (auto& linea : leerArchivo("autores.txt")) {
        auto campos = split(linea, '|');
        if (campos.size() != 3) continue;  // Línea inválida
        try {
            Autor a;
            a.id = stoi(campos[0]);
            a.nombre = campos[1];
            a.nacionalidad = campos[2];
            autores.push_back(a);
        } catch (...) {
            cout << "[ERROR] Error al pasar linea en autores.txt: " << linea << "\n";
        }
    }

    // Cargar Editoriales
    for (auto& linea : leerArchivo("editoriales.txt")) {
        auto campos = split(linea, '|');
        if (campos.size() != 2) continue;
        try {
            Editorial e;
            e.id = stoi(campos[0]);
            e.nombre = campos[1];
            editoriales.push_back(e);
        } catch (...) {
            cout << "[ERROR] Error al pasar linea en editoriales.txt: " << linea << "\n";
        }
    }

    // Cargar Libros
    for (auto& linea : leerArchivo("libros.txt")) {
        auto campos = split(linea, '|');
        if (campos.size() != 6) continue;
        try {
            Libro l;
            l.id = stoi(campos[0]);
            l.titulo = campos[1];
            l.isbn = campos[2];
            l.ano_publicacion = stoi(campos[3]);
            l.id_autor = stoi(campos[4]);
            l.id_editorial = stoi(campos[5]);
            libros.push_back(l);
        } catch (...) {
            cout << "[ERROR] Error al pasar linea en libros.txt: " << linea << "\n";
        }
    }

    // Cargar Estudiantes
    for (auto& linea : leerArchivo("estudiantes.txt")) {
        auto campos = split(linea, '|');
        if (campos.size() != 3) continue;
        try {
            Estudiante e;
            e.id = stoi(campos[0]);
            e.nombre = campos[1];
            e.grado = campos[2];
            estudiantes.push_back(e);
        } catch (...) {
            cout << "[ERROR] Error al pasar linea en estudiantes.txt: " << linea << "\n";
        }
    }

    // Cargar Prestamos
    for (auto& linea : leerArchivo("prestamos.txt")) {
        auto campos = split(linea, '|');
        if (campos.size() < 4) continue;  // Mínimo 4 campos requeridos
        try {
            Prestamo p;
            p.id = stoi(campos[0]);
            p.id_libro = stoi(campos[1]);
            p.id_estudiante = stoi(campos[2]);
            p.fecha_prestamo = campos[3];
            p.fecha_devolucion = (campos.size() > 4) ? campos[4] : "";  // fecha_devolucion puede estar vacía
            prestamos.push_back(p);
        } catch (...) {
            cout << "[ERROR] Error al pasar linea en prestamos.txt: " << linea << "\n";
        }
    }

    // Resumen de carga
    cout << "[INFO] Carga completa: "
         << autores.size() << " autores, "
         << editoriales.size() << " editoriales, "
         << libros.size() << " libros, "
         << estudiantes.size() << " estudiantes, "
         << prestamos.size() << " prestamos." << "\n";
}