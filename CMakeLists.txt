# Add /project_root/opengl and /project_root/opengl/include as include dirs
target_include_directories(${PROJECT_NAME} PUBLIC src PUBLIC include)

# Collect all .cpp files from wrapper classes
file(GLOB GL_SOURCE_FILES 
    src/*.cpp
)

# Create libraries with glad.c and gl.cpp to link to the project
add_library(glad src/glad.c)
add_library(gl ${GL_SOURCE_FILES})

# Add /project_root/opengl/include to the libraries include dirs
target_include_directories(glad PUBLIC include)
target_include_directories(gl PUBLIC include)

# This policy allows libraries to be linked to a target in a 
# different file than the one it was created in
cmake_policy(SET CMP0079 NEW)

# Locate GLFW (version 3.3 or higher) and set it up for linking
find_package(glfw3 3.3 REQUIRED)

# gl is dependent on glad and glfw
target_link_libraries(gl PRIVATE glad glfw)

# link glfw and gl (glad is linked to gl, so its included as well)
target_link_libraries(${PROJECT_NAME} gl)

# Check if SHADERS_DIR is already defined by the parent project
if(NOT DEFINED SHADERS_DIR)
    # Default to shaders/ in the root project directory
    set(SHADERS_DIR "${CMAKE_SOURCE_DIR}/shaders")
endif()

# Add the compile definition to the gl library
target_compile_definitions(gl PUBLIC 
    SHADERS_DIR="${SHADERS_DIR}"
)

# Optionally, validate that the directory exists
if(NOT EXISTS "${SHADERS_DIR}")
    message(WARNING "Shaders directory '${SHADERS_DIR}' does not exist. "
                   "Consider creating it or setting SHADERS_DIR in your root CMakeLists.txt")
endif()
