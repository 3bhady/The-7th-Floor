cmake_minimum_required(VERSION 3.5.1)
project(Jung)

set(CMAKE_CXX_STANDARD 11)

configure_file(configuration/root_directory.h.in configuration/root_directory.h)


#sets the build directory to be in the same file
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/")

set(SOURCE_FILES main.cpp GameManager.cpp GameManager.h Mesh.h Shader.h Model.h Camera.h Model.cpp filesystem.h Input.cpp Input.h Script.cpp Script.h PlayerScript.h Collider.cpp Collider.h Mesh.cpp Collision.cpp Collision.h Model2D.cpp Model2D.h)
add_executable(main ${SOURCE_FILES} GameManager.cpp GameManager.h Script.cpp Script.h PlayerScript.h Model2D.cpp Model2D.h)

target_link_libraries(main
        -lGLEW -lglfw -lGL -lSOIL -lX11 -lpthread -lXrandr -lXi -lassimp
        )

include_directories(${CMAKE_BINARY_DIR}/configuration)
file(GLOB SHADERS
        "*.vs"
        "*.frag"
        "*.gs"
        )

foreach(SHADER ${SHADERS})
  #  if(UNIX)
    #copies the shaders into the build directory
       # file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR/bin/${SHADER} INPUT ${SHADER}  })
    file(COPY ${SHADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

   configure_file(${SHADER} ${CMAKE_CURRENT_BINARY_DIR}/bin/${SHADER})
   #file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/bin/${SHADER})

    #file(COPY ${SHADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

   #     endif(UNIX)
     endforeach(SHADER)
