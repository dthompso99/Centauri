CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project (Centauri)

MESSAGE( STATUS "PROJECT_SOURCE_DIR:        " "${PROJECT_SOURCE_DIR}" )
MESSAGE( STATUS "PROJECT_BINARY_DIR:        " "${PROJECT_BINARY_DIR}" )
MESSAGE( STATUS "INCLUDES DIR:        		" "${CINCLUDES}" )
MESSAGE( STATUS "ROOT DIR:        			" "${CROOT}" )
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH} "${CMAKE_INSTALL_PREFIX}/share/cmake")

INCLUDE_DIRECTORIES(include ${CINCLUDES} ${PROJECT_BINARY_DIR} )

FILE(GLOB CENTAURI_SOURCE *.cpp)
FILE(GLOB CENTAURI_SOURCE_UI UI/*.cpp)

find_package(Corrade REQUIRED)
corrade_add_resource(Centauri_RESOURCES res/resources.conf)





FIND_LIBRARY(CHAKRA_LIBRARY ChakraCore PATHS ${CMAKE_INSTALL_PREFIX}/lib)

find_package(Magnum REQUIRED GlfwApplication Shaders Text)
find_package(MagnumPlugins REQUIRED FreeTypeFont)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/configure.h.cmake ${CMAKE_INSTALL_PREFIX}/include/configure.h)


include_directories(
	include, 
	${CMAKE_INSTALL_PREFIX}/include
)

add_executable(Centauri  ${CENTAURI_SOURCE} ${CENTAURI_SOURCE_UI} ${CROOT}/rc/resources.rc ${Centauri_RESOURCES})

target_link_libraries(Centauri 
	Magnum::Application
    Magnum::Magnum
    Magnum::Shaders
    Magnum::Text
    ${CHAKRA_LIBRARY}
)



install (TARGETS Centauri DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/configure.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)