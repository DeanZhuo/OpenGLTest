cmake_minimum_required(VERSION 3.10)
project(OpenGLTest)

set(CMAKE_CXX_STANDARD 17)

if(MINGW)

  if ("${GLUT}" STREQUAL "")
  message(FATAL_ERROR "GLUT libs not defined")
  endif()

  if ("${GLEW}" STREQUAL "")
  message(FATAL_ERROR "GLEW libs not defined")
  endif()

  if ("${GLFW}" STREQUAL "")
  message(FATAL_ERROR "GLFW libs not defined")
  endif()

  set(CMAKE_PREFIX_PATH "${MINGW_HOME};${GLUT};${GLEW};${GLFW}")
  set(radar_DIR "C:/Users/Bee/Documents/CCPP/dev/libs/radar-1.0/lib/cmake/radar")
  set(GLUT_INCLUDE_DIR "${GLUT}/include")
endif()

# Find OpenGL, GLFW, GLEW and GLUT (prefer freeglut)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.4 REQUIRED)
find_package(radar 1.0 REQUIRED)

if (MINGW)
  include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
endif()

file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(OpenGLTest ${SRC_FILES})

target_include_directories(OpenGLTest PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    "C:/Users/Bee/Documents/CCPP/dev/libs/glm-1.0.1/include"

)

target_link_libraries(OpenGLTest
  ${OPENGL_LIBRARIES}
  GLUT::GLUT
  GLEW::GLEW
  radar::radar_core
  radar::radar_opengl
  radar::radar_packet
  glfw
)


if (MINGW)
  # Get the path to the executable's output directory
  get_target_property(OUTPUT_DIR OpenGLTest RUNTIME_OUTPUT_DIRECTORY)

  # Find the DLLs
  # For freeglut
  find_file(FREEGLUT_DLL libfreeglut.dll HINTS ${GLUT} PATH_SUFFIXES bin)
  # For GLEW
  find_file(GLEW_DLL glew32.dll HINTS ${GLEW} PATH_SUFFIXES bin)
  # For libstdc++-6.dll from MinGW
  find_file(STDCPP_DLL libstdc++-6.dll HINTS ${CMAKE_CXX_COMPILER} PATH_SUFFIXES ../bin)
  # For libgcc_s_seh-1.dll from MinGW
  find_file(GCC_S_SEH_DLL libgcc_s_seh-1.dll HINTS ${CMAKE_CXX_COMPILER} PATH_SUFFIXES ../bin)
  # For libwinpthread-1.dll from MinGW
  find_file(WIN_PTHREAD_DLL libwinpthread-1.dll HINTS ${CMAKE_CXX_COMPILER} PATH_SUFFIXES ../bin)

  # Add a custom command to copy the DLLs after the build
  if(FREEGLUT_DLL AND GLEW_DLL AND STDCPP_DLL AND GCC_S_SEH_DLL AND WIN_PTHREAD_DLL)
    add_custom_command(
      TARGET OpenGLTest POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${FREEGLUT_DLL}
      ${OUTPUT_DIR}
      COMMENT "Copying freeglut dll"
    )
    add_custom_command(
      TARGET OpenGLTest POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${GLEW_DLL}
      ${OUTPUT_DIR}
      COMMENT "Copying glew32 dll"
    )
    add_custom_command(
      TARGET OpenGLTest POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${STDCPP_DLL}
      ${OUTPUT_DIR}
      COMMENT "Copying libstdc++ dll"
    )
    add_custom_command(
      TARGET OpenGLTest POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${GCC_S_SEH_DLL}
      ${OUTPUT_DIR}
      COMMENT "Copying libwinpthread dll"
    )
    add_custom_command(
      TARGET OpenGLTest POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${WIN_PTHREAD_DLL}
      ${OUTPUT_DIR}
      COMMENT "Copying libgcc_s_seh dll"
      )
  else()
    message("One of the runtimes dll not found")
  endif()
endif()