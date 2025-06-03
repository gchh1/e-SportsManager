add_library(models)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/heads HEAD)

target_sources(models 
PRIVATE 
    ${SRC}
PUBLIC 
    ${HEAD}
)

target_include_directories(models 
PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/heads
    ${CMAKE_SOURCE_DIR}/src/dataHandlers/heads)
