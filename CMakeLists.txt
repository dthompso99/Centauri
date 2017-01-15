CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
include(ExternalProject)

set(CENTAURI_INSTALL "${PROJECT_SOURCE_DIR}/output/${CMAKE_BUILD_TYPE}" CACHE FILEPATH "Final Install Path") 
set(CENTAURI_CMAKE_GLOBALS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_EXE_LINKER_FLAGS=${CMAKE_EXE_LINKER_FLAGS} -DCMAKE_SHARED_LINKER_FLAGS=${CMAKE_SHARED_LINKER_FLAGS} -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE} -DCMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG} -DCMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE} -DCMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG} -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DCMAKE_GENERATOR=${CMAKE_GENERATOR} -DCMAKE_GENERATOR_PLATFORM=${CMAKE_GENERATOR_PLATFORM} -DCROOT=${PROJECT_SOURCE_DIR})


file(MAKE_DIRECTORY "${CENTAURI_INSTALL}")
file(MAKE_DIRECTORY "${CENTAURI_INSTALL}/lib")
file(MAKE_DIRECTORY "${CENTAURI_INSTALL}/include")
file(MAKE_DIRECTORY "${CENTAURI_INSTALL}/bin")
file(MAKE_DIRECTORY "${CENTAURI_INSTALL}/bin/assets")
file(COPY "${PROJECT_SOURCE_DIR}/assets/" DESTINATION "${CENTAURI_INSTALL}/bin/assets/" FILES_MATCHING PATTERN "*.*")

add_definitions(
        -D_CRT_SECURE_NO_WARNINGS
        -D_CRT_NONSTDC_NO_DEPRECATE
)

FILE( TO_NATIVE_PATH ${PROJECT_SOURCE_DIR}/git/chakra/src/CHAKRA/Build/Chakra.Core.sln CHAKRA_PROJECT)
MESSAGE( STATUS "CHAKRA_PROJECT:        " "${CHAKRA_PROJECT}" )

#######################################
# CHAKRA BUILD                        #
#######################################
SET(CH_LIBS 
	${PROJECT_SOURCE_DIR}/git/chakra/src/CHAKRA/lib/Jsrt/ChakraCore.h 
	${PROJECT_SOURCE_DIR}/git/chakra/src/CHAKRA/lib/Jsrt/ChakraCommon.h
	${PROJECT_SOURCE_DIR}/git/chakra/src/CHAKRA/lib/Jsrt/ChakraCommonWindows.h
	${PROJECT_SOURCE_DIR}/git/chakra/src/CHAKRA/lib/Jsrt/ChakraDebug.h
)

ExternalProject_Add (CHAKRA
	GIT_REPOSITORY https://github.com/Microsoft/ChakraCore.git
	#GIT_TAG cmake_embed_v3
	#UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/chakra/
	CONFIGURE_COMMAND ""
	BUILD_COMMAND msbuild /m /p:Platform=x64 /p:Configuration=${CMAKE_BUILD_TYPE} /p:RuntimeLib=static_library ${CHAKRA_PROJECT}
	INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/git/chakra/src/CHAKRA/Build/VcBuild/bin/x64_${CMAKE_BUILD_TYPE}/ChakraCore.dll ${CENTAURI_INSTALL}/bin
)

ExternalProject_Add_Step(CHAKRA
	COPYINC
	DEPENDEES build
	COMMENT "Coppying Includes"
	COMMAND ${CMAKE_COMMAND} -E copy ${CH_LIBS}  ${CENTAURI_INSTALL}/include
)
ExternalProject_Add_Step(CHAKRA
	COPYLIB
	DEPENDEES build
	COMMENT "Coppying Lib"
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/git/chakra/src/CHAKRA/Build/VcBuild/bin/x64_debug/ChakraCore.lib  ${CENTAURI_INSTALL}/lib
)

#######################################
# GLFW BUILD                          #
#######################################

ExternalProject_Add (GLFW
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	#GIT_TAG
	UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/GLFW
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS}
	INSTALL_DIR ${CENTAURI_INSTALL}
)

#######################################
# LIBROCKET BUILD                     #
#######################################

SET(ENV{FREETYPE_DIR} ${CENTAURI_INSTALL})
SET(FREETYPE_DIR ${CENTAURI_INSTALL})
FIND_PACKAGE(FREETYPE 2.7.1 REQUIRED)
MESSAGE( STATUS "FREETYPE_DIR:        " ${FREETYPE_DIR} )
MESSAGE( STATUS "FREETYPE_FOUND:        " ${FREETYPE_FOUND} )
MESSAGE( STATUS "FREETYPE_LIBRARIES:        " "${FREETYPE_LIBRARIES}" )

ExternalProject_Add (LIBROCKET
	GIT_REPOSITORY https://github.com/libRocket/libRocket.git
	#GIT_TAG
	UPDATE_DISCONNECTED 1
	CONFIGURE_COMMAND ${CMAKE_COMMAND} ${CENTAURI_CMAKE_GLOBALS} -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> <SOURCE_DIR>/Build
	PREFIX ${PROJECT_SOURCE_DIR}/git/LIBROCKET
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS} -DFREETYPE_LIBRARY=${FREETYPE_LIBRARY} -DFREETYPE_DIR=${CENTAURI_INSTALL} -DFREETYPE_INCLUDE_DIR_freetype2=${FREETYPE_INCLUDE_DIR_freetype2} -DFREETYPE_INCLUDE_DIR_ft2build=${FREETYPE_INCLUDE_DIR_ft2build}
	INSTALL_DIR ${CENTAURI_INSTALL}
)


#######################################
# FREETYPE BUILD                      #
#######################################

ExternalProject_Add (FREETYPE
	GIT_REPOSITORY http://git.sv.nongnu.org/r/freetype/freetype2.git
	GIT_TAG VER-2-6-5
	UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/FREETYPE
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS}
	INSTALL_DIR ${CENTAURI_INSTALL}
)


#######################################
# CORRADE BUILD                       #
#######################################

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

ExternalProject_Add (CORRADE
	GIT_REPOSITORY https://github.com/mosra/corrade.git
	#GIT_TAG snapshot-2015-05-compatibility
	UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/CORRADE
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS} -DBUILD_STATIC=OFF -DBUILD_TESTS=OFF -DMSVC2015_COMPATIBILITY=ON
	INSTALL_DIR ${CENTAURI_INSTALL}
)

#######################################
# MAGNUM BUILD                          #
#######################################

ExternalProject_Add (MAGNUM
	GIT_REPOSITORY https://github.com/mosra/magnum.git
	#GIT_TAG snapshot-2015-05-compatibility
	UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/MAGNUM
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS} -DBUILD_STATIC=OFF -DBUILD_TESTS=OFF -DCORRADE_INCLUDE_DIR=${CENTAURI_INSTALL}/include -DWITH_DEBUGTOOLS=ON -DWITH_GLFWAPPLICATION=ON -DWITH_GLUTAPPLICATION=OFF -DWITH_SDL2APPLICATION=OFF -DMAGNUM_BUILD_MULTITHREADED=ON -DWITH_TEXT=ON
	INSTALL_DIR ${CENTAURI_INSTALL}
)

#######################################
# MAGNUMPLUGINS                      #
#######################################

ExternalProject_Add (MAGNUMPLUGINS
	GIT_REPOSITORY https://github.com/mosra/magnum-plugins.git
	#GIT_TAG
	UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/MAGNUMPLUGINS
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS} -DBUILD_STATIC=OFF -DWITH_FREETYPEFONT=ON -DWITH_ANYIMAGEIMPORTER=ON -DWITH_PNGIMPORTER=ON -DWITH_JPEGIMPORTER=ON
	INSTALL_DIR ${CENTAURI_INSTALL}
)

#######################################
# MAGNUMEXTRAS                      #
#######################################

ExternalProject_Add (MAGNUMEXTRAS
	GIT_REPOSITORY https://github.com/mosra/magnum-integration.git
	#GIT_TAG
	UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/MAGNUMEXTRAS
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS} -DBUILD_STATIC=OFF
	INSTALL_DIR ${CENTAURI_INSTALL}
)

#######################################
# MAGNUMEXAMPLES                      #
#######################################

ExternalProject_Add (MAGNUMEXAMPLES
	GIT_REPOSITORY https://github.com/mosra/magnum-examples.git
	#GIT_TAG
	#UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/MAGNUMEXAMPLES
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS} -DBUILD_STATIC=OFF -DWITH_TEXT_EXAMPLE=ON
	INSTALL_DIR ${CENTAURI_INSTALL}
)

#######################################
# ZLIB BUILD                          #
#######################################

ExternalProject_Add (ZLIB
	GIT_REPOSITORY https://github.com/madler/zlib.git
	GIT_TAG v1.2.10
	UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/ZLIB
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS}
	INSTALL_DIR ${CENTAURI_INSTALL}
)


#######################################
# LIBPNG BUILD                          #
#######################################

ExternalProject_Add (LIBPNG
	GIT_REPOSITORY https://github.com/glennrp/libpng.git
	#GIT_TAG v1.2.10
	UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/LIBPNG
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS} -DPNG_SHARED=YES
	INSTALL_DIR ${CENTAURI_INSTALL}
)

#######################################
# LIBJPEG BUILD                          #
#######################################

ExternalProject_Add (LIBJPEG
	GIT_REPOSITORY https://github.com/stohrendorf/libjpeg-cmake.git
	UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/LIBJPEG
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS} -DPNG_SHARED=YES
	INSTALL_DIR ${CENTAURI_INSTALL}
)

#######################################
# TINETWORK BUILD                     #
#######################################

ExternalProject_Add (TINETWORK
	GIT_REPOSITORY https://dthompso99@bitbucket.org/dthompso99/tinetwork.git
	#GIT_TAG
	UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/TINETWORK
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS} -DBUILD_TEST=OFF -BUILD_SHARED_LIBS=OFF
	INSTALL_DIR ${CENTAURI_INSTALL}
)


#######################################
# BULLET BUILD                          #
#######################################

ExternalProject_Add (BULLET
	GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
	GIT_TAG 2.85.1
	UPDATE_DISCONNECTED 1
	PREFIX ${PROJECT_SOURCE_DIR}/git/BULLET
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS} -DUSE_MSVC_INCREMENTAL_LINKING=OFF -DBUILD_SHARED_LIBS=OFF -DBUILD_BULLET3=OFF -DBUILD_BULLET2_DEMOS=OFF -DBUILD_CPU_DEMOS=OFF -DBUILD_EXTRAS=OFF -DBUILD_OPENGL3_DEMOS=OFF -DBUILD_UNIT_TESTS=OFF
	INSTALL_DIR ${CENTAURI_INSTALL}
)


#######################################
# CENT BUILD                          #
#######################################

ExternalProject_Add (CENTAURI
	URL ${PROJECT_SOURCE_DIR}/src
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/CENTAURI
	CMAKE_ARGS ${CENTAURI_CMAKE_GLOBALS} -DCINCLUDES=${CENTAURI_INSTALL}/include -DCLIBS=${CENTAURI_INSTALL}/lib
	INSTALL_DIR ${CENTAURI_INSTALL}
	BUILD_ALWAYS 1
)

ExternalProject_Add_Step(CENTAURI forceconfigure
	COMMAND ${CMAKE_COMMAND} -E echo "Force configure of CENTAURI"
	DEPENDEES configure
	DEPENDERS build
	ALWAYS 1
)
add_dependencies(LIBPNG ZLIB)
add_dependencies(FREETYPE LIBPNG ZLIB)
add_dependencies(MAGNUM CORRADE GLFW)
add_dependencies(MAGNUMEXTRAS BULLET MAGNUM)
add_dependencies(MAGNUMPLUGINS MAGNUM ZLIB LIBPNG FREETYPE LIBJPEG)
add_dependencies(CENTAURI CHAKRA MAGNUM TINETWORK MAGNUMPLUGINS MAGNUMEXTRAS)
add_custom_target(custom-install DEPENDS CENTAURI )
