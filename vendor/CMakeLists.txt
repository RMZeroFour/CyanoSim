find_package(OpenGL REQUIRED)

set(SFML_DIR ${CMAKE_CURRENT_LIST_DIR}/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio main GLOBAL)

add_library(imgui STATIC)
target_sources(imgui PRIVATE
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui-SFML.cpp)
target_include_directories(imgui PUBLIC imgui/include)
target_link_libraries(imgui PRIVATE sfml-system sfml-window sfml-graphics opengl32)

add_library(tinyfiledialogs STATIC)
target_sources(tinyfiledialogs PRIVATE tinyfiledialogs/tinyfiledialogs.c)
target_include_directories(tinyfiledialogs PUBLIC tinyfiledialogs)

add_library(escapi STATIC)
target_sources(escapi PRIVATE escapi/escapi.cpp)
target_include_directories(escapi PUBLIC escapi)