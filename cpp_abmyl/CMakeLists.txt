cmake_minimum_required(VERSION 3.0)
project(cpp_abmyl)

# Configuración del ejecutable
add_executable(cpp_abmyl 
    src/main.cpp
    src/database.cpp
    src/user.cpp
    src/game.cpp
)

# Configuración de directorios de inclusión
target_include_directories(cpp_abmyl PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Configuración de opciones de compilación
target_compile_options(cpp_abmyl PRIVATE
    -std=c++11
    -Wall
)

# Configuración de enlaces (por ejemplo, con SQLite3)
target_link_libraries(cpp_abmyl
    sqlite3
)
