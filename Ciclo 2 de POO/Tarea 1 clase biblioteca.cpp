#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

class Libro {
public:
    std::string titulo;
    std::string autor;
    int anio_publicacion;
    bool estaDisponible;
    std::string nombre_usuario; 

    Libro() : anio_publicacion(0), estaDisponible(true) {}

    Libro(std::string t, std::string a, int anio, bool disponible = true)
        : titulo(t), autor(a), anio_publicacion(anio), estaDisponible(disponible), nombre_usuario("") {}

    void mostrarDetallesCompletos() {
        std::cout << "titulo: " << titulo << std::endl;
        std::cout << "autor: " << autor << std::endl;
        std::cout << "anio de publicacion: " << anio_publicacion << std::endl;
        std::cout << "disponibilidad: "
                  << (estaDisponible ? "si, esta disponible para prestarse" : "no, no esta disponible")
                  << std::endl;
        if (!estaDisponible && !nombre_usuario.empty()) {
            std::cout << "prestado usuarios: " << nombre_usuario << std::endl;
        }
    }
};

class Usuario {
public:
    std::string nombre_usuario;
    std::vector<std::string> libros_prestados;

    Usuario() = default;
    explicit Usuario(std::string n) : nombre_usuario(std::move(n)) {}

    bool tieneLibro(const std::string& titulo) const {
        return std::find(libros_prestados.begin(), libros_prestados.end(), titulo) != libros_prestados.end();
    }
};

class Biblioteca {
private:
    std::vector<Libro> coleccion;
    std::vector<Usuario> usuarios;

public:
    void agregarLibro(const Libro& nuevo_libro) {
        for (const auto& l : coleccion) {
            if (l.titulo == nuevo_libro.titulo) {
                std::cout << "Ya existe un libro con ese titulo '" << nuevo_libro.titulo
                          << "'. no se agrego.\n";
                return;
            }
        }
        coleccion.push_back(nuevo_libro);
        std::cout << "El libro esta agregado: " << nuevo_libro.titulo << std::endl;
    }

    void mostrarInventario() {
        if (coleccion.empty()) {
            std::cout << "la biblioteca no tiene ese libro " << std::endl;
            return;
        }

        std::cout << "Biblioteca de libros" << std::endl;
        for (auto& libro : coleccion) {
            libro.mostrarDetallesCompletos();
        }
    }

    Libro* buscarLibro(const std::string& titulo_buscado) {
        for (auto& libro : coleccion) {
            if (libro.titulo == titulo_buscado) {
                return &libro;
            }
        }
        return nullptr;
    }

    
    Usuario* buscar_usuarios(const std::string& nombre_usuario_buscado) {
        for (auto& u : usuarios) {
            if (u.nombre_usuario == nombre_usuario_buscado) return &u;
        }
        return nullptr;
    }

    void registrar_usuarios(const std::string& nombre_usuario_nuevo) {
        if (buscar_usuarios(nombre_usuario_nuevo)) {
            std::cout << "El usuarios '" << nombre_usuario_nuevo << "' ya existe.\n";
            return;
        }
        usuarios.emplace_back(nombre_usuario_nuevo);
        std::cout << "usuarios '" << nombre_usuario_nuevo << "' registrado.\n";
    }

   
    void prestar_libro_usuario(const std::string& titulo_prestamo, const std::string& nombre_usuario_prestamo) {
        Libro* libro = buscarLibro(titulo_prestamo);
        if (!libro) {
            std::cout << "El libro '" << titulo_prestamo << "' no se encuentra en la biblioteca." << std::endl;
            return;
        }
        Usuario* u = buscar_usuarios(nombre_usuario_prestamo);
        if (!u) {
            std::cout << "El usuarios '" << nombre_usuario_prestamo << "' no existe, puedes registralo con la opcion 6.\n";
            return;
        }
        if (!libro->estaDisponible) {
            std::cout << "El libro '" << libro->titulo << "' esta prestado.\n";
            return;
        }
        if (u->tieneLibro(libro->titulo)) {
            std::cout << "El usuarios '" << u->nombre_usuario << "' ya tiene este libro registrado.\n";
            return;
        }
        libro->estaDisponible = false;
        libro->nombre_usuario = u->nombre_usuario;
        u->libros_prestados.push_back(libro->titulo);
        std::cout << "El libro '" << libro->titulo << "' ha sido prestado '" << u->nombre_usuario << "'.\n";
    }

    void devolver_libro_usuario(const std::string& titulo_devolucion, const std::string& nombre_usuario_devol) {
        Libro* libro = buscarLibro(titulo_devolucion);
        if (!libro) {
            std::cout << "El libro '" << titulo_devolucion << "' no pertenece a la biblioteca." << std::endl;
            return;
        }
        Usuario* u = buscar_usuarios(nombre_usuario_devol);
        if (!u) {
            std::cout << "El usuarios '" << nombre_usuario_devol << "' no existe, puedes registralo con la opcion 6.\n";
            return;
        }
        if (libro->estaDisponible) {
            std::cout << "El libro '" << libro->titulo << "' ya estaba disponible en la biblioteca." << std::endl;
            return;
        }
        if (libro->nombre_usuario != u->nombre_usuario) {
            std::cout << "El libro '" << libro->titulo << "' esta registrado como prestado a un usuarios '"
                      << libro->nombre_usuario << "'. no puede devolverlo '" << u->nombre_usuario << "'.\n";
            return;
        }
        
        libro->estaDisponible = true;
        libro->nombre_usuario.clear();
        auto it = std::remove(u->libros_prestados.begin(), u->libros_prestados.end(), libro->titulo);
        if (it != u->libros_prestados.end()) u->libros_prestados.erase(it, u->libros_prestados.end());
        std::cout << "El libro '" << libro->titulo << "' ha sido devuelto por '" << u->nombre_usuario
                  << "' y ahora esta disponible." << std::endl;
    }
};

int main() {
    Biblioteca miBiblioteca;
    int opcion = 0;

    Libro libroInicial;
    libroInicial.titulo = "Housemaid";
    libroInicial.autor = "Freida McFadden";
    libroInicial.anio_publicacion = 2022;
    miBiblioteca.agregarLibro(libroInicial);

    while (opcion != 5) {
        std::cout << "\n Bienvenido a la biblioteca de key" << std::endl;
        std::cout << "1. Anadir libro" << std::endl;
        std::cout << "2. Mostrar inventario" << std::endl;
        std::cout << "3. Prestar libro" << std::endl;
        std::cout << "4. Devolver libro" << std::endl;
        std::cout << "5. Registrar usuarios" << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";

        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida...intenta de nuevo por favor.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                std::string titulo, autor, anioStr, dispStr;

                std::cout << "Titulo: ";
                std::getline(std::cin, titulo);
                std::cout << "Autor: ";
                std::getline(std::cin, autor);
                std::cout << "Anio de publicacion: ";
                std::getline(std::cin, anioStr);
                int anio = 0;

                try {
                    if (!anioStr.empty()) anio = std::stoi(anioStr);
                } catch (...) {
                    std::cout << "Anio invalido .\n";
                    anio = 0;
                }

                std::cout << "Esta disponible ¿? (s/n): ";
                std::getline(std::cin, dispStr);
                bool disponible = !dispStr.empty() && (dispStr[0] == 's' || dispStr[0] == 'S');

                miBiblioteca.agregarLibro(Libro(titulo, autor, anio, disponible));
                break;
            }

            case 2:
                miBiblioteca.mostrarInventario();
                break;

            case 3: {
                std::string titulo, nombre_usuario;
                std::cout << "Titulo o nombre del libro que deseas prestar: ";
                std::getline(std::cin, titulo);
                std::cout << "Nombre del usuarios: ";
                std::getline(std::cin, nombre_usuario);
                miBiblioteca.prestar_libro_usuario(titulo, nombre_usuario);
                break;
            }

            case 4: {
                std::string titulo, nombre_usuario;
                std::cout << "Titulo del libro que vas a devolver: ";
                std::getline(std::cin, titulo);
                std::cout << "Nombre del usuarios que devuelve: ";
                std::getline(std::cin, nombre_usuario);
                miBiblioteca.devolver_libro_usuario(titulo, nombre_usuario);
                break;
            }


            case 5: {
                std::string nombre_usuario;
                std::cout << "Nombre del nuevo usuarios: ";
                std::getline(std::cin, nombre_usuario);
                miBiblioteca.registrar_usuarios(nombre_usuario);
                break;
            }
            case 6:
                std::cout << "Saliendo...\n";
                break;

            default:
                std::cout << "Opcion no valida...intenta de nuevo por favor.\n";
                break;
        }
    }

    return 0;
}
