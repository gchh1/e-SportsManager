set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(e-sportsManager test1.cpp)

add_subdirectory(models)
add_subdirectory(dataHandlers)
add_subdirectory(controllers)
add_subdirectory(views)

target_link_libraries(e-sportsManager
PRIVATE
    models
    dataHandlers
    controllers
    views
)
