add_executable(CyanoSim WIN32)

target_sources(CyanoSim PRIVATE 
    Program.cpp
    Colors.cpp
    Cyanotype.cpp
    Simulator.cpp
    States/State.cpp
    States/AboutInfoState.cpp
    States/ImageBathState.cpp
    States/MixSolutionsState.cpp
    States/RunToEndState.cpp
    States/FinalResultState.cpp
    States/MainMenuState.cpp
    States/PaintSheetState.cpp
    States/SelectPictureState.cpp
    States/UVExposureState.cpp)

target_include_directories(CyanoSim PRIVATE include)

target_link_libraries(CyanoSim PRIVATE 
    sfml-system 
    sfml-window 
    sfml-graphics 
    sfml-main 
    imgui
    escapi
    tinyfiledialogs)

set_target_properties(CyanoSim PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)