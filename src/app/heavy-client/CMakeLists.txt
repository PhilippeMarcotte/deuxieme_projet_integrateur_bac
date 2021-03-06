
# Trouver le path des .lib des librairies externes
find_library(tinyxml_LIB
    tinyxml_D_x64
    "${CMAKE_SOURCE_DIR}/ext/tinyxml2/lib"
)

find_library(glew_LIB
    glew32s
    "${CMAKE_SOURCE_DIR}/ext/GLEW/lib"
)

find_library(ftgl_LIB
    ftgl
    "${CMAKE_SOURCE_DIR}/ext/FTGL/lib"
)

find_library(freeType_LIB
    freetype246_D_x64 
    "${CMAKE_SOURCE_DIR}/ext/FreeType/lib"
)

find_library(freeImage_LIB
    FreeImage    
    "${CMAKE_SOURCE_DIR}/ext/FreeImage/lib"
)

find_library(fmod_LIB
    fmodexL64_vc
    "${CMAKE_SOURCE_DIR}/ext/FMOD/lib"
)

find_library(box2d_LIB
    Box2D_D_x64
    "${CMAKE_SOURCE_DIR}/ext/Box2D/lib"
)

find_library(assimp_LIB
    assimp
    "${CMAKE_SOURCE_DIR}/ext/assimp/lib"
)

find_package(OpenGL REQUIRED)

# Permettre d'inclure des fichiers d'entêtes des librairies externes sans spécifier le path complet
include_directories(
    ${CMAKE_SOURCE_DIR}/ext/RapidJSON/include
    ${CMAKE_SOURCE_DIR}/ext/glm/include
    ${CMAKE_SOURCE_DIR}/ext/GLEW/include
    ${CMAKE_SOURCE_DIR}/ext/FreeType/include
    ${CMAKE_SOURCE_DIR}/ext/FreeImage/include
    ${CMAKE_SOURCE_DIR}/ext/FMOD/include
    ${CMAKE_SOURCE_DIR}/ext/Box2D/include
    ${CMAKE_SOURCE_DIR}/ext/assimp/include
    ${CMAKE_SOURCE_DIR}/ext/FTGL/include
    ${CMAKE_SOURCE_DIR}/ext/tinyxml2/include
    ${OpenGL_INCLUDE_DIRS}
)

set(EXTERNAL_LIBRARIES
    ${tinyxml_LIB}
    ${glew_LIB}
    ${ftgl_LIB}
    ${freeType_LIB}
    ${freeImage_LIB}
    ${fmod_LIB}
    ${box2d_LIB}
    ${assimp_LIB}
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    Winmm.lib
)

include_directories(
    util/
    util/Modele
    util/OpenGL
    util/Vue
    ui/Enum)

# Ajout de la librairie utilitaire
add_subdirectory(util)

# Ajout de la librairie model
add_subdirectory(model)

# Ajout du projet C# pour l'interface graphique
include_external_msproject(ui 
    ${CMAKE_SOURCE_DIR}/src/app/heavy-client/ui/ui.csproj)

set_property(TARGET ui PROPERTY FOLDER "app/heavy-client")

# Ajout du projet C# pour les Enum
include_external_msproject(enum 
    ${CMAKE_SOURCE_DIR}/src/app/heavy-client/ui/enum/enum.csproj)

set_property(TARGET enum PROPERTY FOLDER "app/heavy-client")
