# Proyecto BibliotecaDB en C++

## Descripción
Este proyecto implementa un sistema básico de gestión de biblioteca usando C++. Incluye las entidades normalizadas hasta la Tercera Forma Normal (3FN):

- Autor
- Editorial
- Libro
- Estudiante
- Préstamo

Para representar datos usa structs y vector para guardar registros en memoria, con un menú interactivo para operaciones CRUD y consultas. Los datos se guardan y cargan en archivos CSV para persistencia.

## Comandos del menú

- Agregar y listar autores, editoriales, libros, estudiantes y préstamos.
- Buscar préstamos por estudiante.
- Verificación de IDs duplicados.
- Control de disponibilidad para préstamos de libros.

## Como compilar

Con g++:
```bash
g++ -o biblioteca main.cpp BibliotecaDB.cpp

## Como ejecutar
./biblioteca
