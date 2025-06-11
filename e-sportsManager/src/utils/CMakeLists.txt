add_library(utils)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

target_sources(utils PRIVATE ${SRC})

target_include_directories(utils PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/heads
    ${CMAKE_SOURCE_DIR}/src/include)
