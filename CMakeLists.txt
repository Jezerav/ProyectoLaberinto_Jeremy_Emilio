cmake_minimum_required(VERSION 3.16)

project(ProyectoLaberinto_Jeremy_Emilio VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        # Archivos de MenuPrincipal
        MenuPrincipal/mainwindow.cpp
        MenuPrincipal/mainwindow.h
        MenuPrincipal/mainwindow.ui

        # Archivos de Juego (aquí los irás añadiendo conforme los crees)
        # Juego/jugador.cpp
        # Juego/jugador.h
        # Juego/mapa.cpp
        # Juego/mapa.h
)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ProyectoLaberinto_Jeremy_Emilio
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Juego/juego.h Juego/juego.cpp
        Juego/jugador.h Juego/jugador.cpp
        Juego/nivel.h Juego/nivel.cpp
        Juego/salida.h Juego/salida.cpp
        Recursos/recursos.qrc
        MenuPrincipal/manual.h MenuPrincipal/manual.cpp MenuPrincipal/manual.ui
    )

# Ejemplo de lo que deberías tener en tu CMakeLists.txt
target_include_directories(ProyectoLaberinto_Jeremy_Emilio PRIVATE 
    MenuPrincipal
    Juego
)

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ProyectoLaberinto_Jeremy_Emilio APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ProyectoLaberinto_Jeremy_Emilio SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ProyectoLaberinto_Jeremy_Emilio
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ProyectoLaberinto_Jeremy_Emilio PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ProyectoLaberinto_Jeremy_Emilio)
endif()
set_target_properties(ProyectoLaberinto_Jeremy_Emilio PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ProyectoLaberinto_Jeremy_Emilio
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ProyectoLaberinto_Jeremy_Emilio)
endif()
