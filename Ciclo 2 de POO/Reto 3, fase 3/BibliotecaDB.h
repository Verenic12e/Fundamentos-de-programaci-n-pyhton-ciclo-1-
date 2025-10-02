// BibliotecaDB.h
#ifndef BIBLIOTECADB_H
#define BIBLIOTECADB_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>  // Para parsing de CSV
#include <regex>    // Para validación de fechas
#include <filesystem>

using namespace std;

struct Autor {
    int id;
    string nombre;
    string nacionalidad;
};

struct Editorial {
    int id;
    string nombre;
};

struct Libro {
    int id;
    string titulo;
    string isbn;
    int ano_publicacion;
    int id_autor;    
    int id_editorial; 
};

struct Estudiante {
    int id;
    string nombre;
    string grado;
};

struct Prestamo {
    int id;
    int id_libro;      
    int id_estudiante; 
    string fecha_prestamo;
    string fecha_devolucion;
};

class BibliotecaDB {
private:
    // Método plantilla para verificar existencia de ID en un vector de structs
    template<typename T>
    bool existeID(const vector<T>& vec, int id) const;
    
    // Obtiene el siguiente ID (max(id) + 1) para un vector de entidades
    template<typename T>
    int siguienteID(const vector<T>& vec) const;

    // Verificaciones específicas para existencia
    bool autorExiste(int id) const;
    bool editorialExiste(int id) const;
    bool estudianteExiste(int id) const;
    bool libroExiste(int id) const;
    bool prestamoExiste(int id) const;

    // Verifica si un libro está disponible (no prestado sin devolución)
    bool libroDisponible(int id_libro) const;

    // Verificaciones para referencias antes de eliminar
    bool autorEnUso(int id_autor) const;      // Si el autor está referenciado en libros
    bool editorialEnUso(int id_editorial) const;
    bool libroEnUso(int id_libro) const;      // Si el libro está en préstamos
    bool estudianteEnUso(int id_estudiante) const;
    
    // Función auxiliar para validar formato de fecha YYYY-MM-DD
    bool validarFecha(const string& fecha) const;

    // Directorio base para leer/escribir archivos
    string baseDir;
    string filePath(const string& nombre) const {
        using std::filesystem::path;
        if (baseDir.empty()) return nombre;
        return (path(baseDir) / nombre).string();
    }

public:
    vector<Autor> autores;
    vector<Editorial> editoriales;
    vector<Libro> libros;
    vector<Estudiante> estudiantes;
    vector<Prestamo> prestamos;

    // CRUD para Autor
    bool agregarAutor(const Autor& a);
    void listarAutores() const;
    bool eliminarAutor(int id);
    bool actualizarAutor(int id, const Autor& nuevo);

    // CRUD para Editorial
    bool agregarEditorial(const Editorial& e);
    void listarEditoriales() const;
    bool eliminarEditorial(int id);
    bool actualizarEditorial(int id, const Editorial& nuevo);

    // CRUD para Libro
    bool agregarLibro(const Libro& l);
    void listarLibros() const;
    bool eliminarLibro(int id);
    bool actualizarLibro(int id, const Libro& nuevo);

    // CRUD para Estudiante
    bool agregarEstudiante(const Estudiante& e);
    void listarEstudiantes() const;
    bool eliminarEstudiante(int id);
    bool actualizarEstudiante(int id, const Estudiante& nuevo);

    // CRUD para Prestamo
    bool agregarPrestamo(const Prestamo& p);
    void listarPrestamos() const;
    bool eliminarPrestamo(int id);
    bool actualizarPrestamo(int id, const Prestamo& nuevo);
    void buscarPrestamosPorEstudiante(int id_estudiante) const;

    // Persistencia
    void guardarDatos() const;
    void cargarDatos();

    // Configurar el directorio base (ej. carpeta del ejecutable)
    void setBaseDir(const string& dir) { baseDir = dir; }
};

#endif