cmake_minimum_required(VERSION 3.1)
include(FetchContent)

project (visforvector VERSION 1.0
		DESCRIPTION "V Is For Vectors"
		LANGUAGES CXX C)

option(MAX_WARNINGS "Treat all warnings as errors" OFF)
set(OpenGL_GL_PREFERENCE "GLVND")
add_library(glad STATIC "${CMAKE_SOURCE_DIR}/external/glad/src/glad.c")

add_executable(visforvector 
	src/main.cpp 
	src/Shader.cpp
	src/Scene.cpp
	src/GameScene.cpp
	src/FPCamera.cpp
	src/Game.cpp
	src/Vector.cpp
	src/Line.cpp
	src/TextRenderer.cpp
	src/HighscoreScene.cpp
	include/stdafx.h
	include/Shader.h
	include/Scene.h
	include/GameScene.h
	include/FPCamera.h
	include/Game.h
	include/Vector.h
	include/TextRenderer.h
	include/Line.h
	include/HighscoreScene.h
	
	external/stb_image/stb_image.h
) 

# Note, for glfw3, in future for easier
# user installation we could put the source of glfw3
# in ./external/glfw3 and recompile it as a git submodule
# Instructions would be at https://www.glfw.org/docs/latest/build.html#build_link_cmake_source
# AFAIK, there isn't instructions for Freetype, but the process should be similiar

# AFAIK, this is not needed for OpenGL as it _should_ be included by default in Linux/Visual Studio
# and Mac (thnough it's been deprecated for Mac and that may change and the framework would need)
# to be installed manually
# But anyway, apparently I'm not using OpenGL directly so I don't need to link it.

# In future, probably a good idea to use FetchContent_Declare for GLFW and Freetype
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)



if (NOT glfw3_FOUND)
	message("GLFW NOT FOUND")
endif()

if (NOT OpenGL_GLX_FOUND)
	message("GLX NOT FOUND")
endif()

if (NOT Freetype_FOUND)
    message("FREETYPE NOT FOUND")
endif()

set(GLAD_INCLUDE "${CMAKE_SOURCE_DIR}/external/glad/include")
set(GLM_INCLUDE "${CMAKE_SOURCE_DIR}/external/glm/")

target_include_directories(glad PUBLIC
	"${GLAD_INCLUDE}"
	"${GLM_INCLUDE}")
target_include_directories(visforvector PRIVATE
    "${CMAKE_SOURCE_DIR}/external/stb_image"
	"${CMAKE_SOURCE_DIR}/include"
	"${OPENGL_INCLUDE_DIR}" 
    "${FREETYPE_INCLUDE_DIRS}")
target_compile_features(visforvector PUBLIC cxx_std_17)
set_target_properties(visforvector PROPERTIES CXX_EXTENSIONS OFF)

if(MAX_WARNINGS)
    if(MSVC)
        target_compile_options(visforvector PRIVATE /W4 /WX)
    else()
        target_compile_options(visforvector PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endif()

target_link_libraries(visforvector PRIVATE 
    glad
    glfw
    ${OPENGL_gl_LIBRARY}
    ${FREETYPE_LIBRARIES}
    ${CMAKE_DL_LIBS})
