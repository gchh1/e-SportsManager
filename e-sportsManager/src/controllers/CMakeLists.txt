add_library(controllers)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/heads HEAD)

target_sources(controllers 
PRIVATE 
    ${SRC}
PUBLIC 
    ${HEAD}
)

target_include_directories(controllers 
PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/src/models/heads
    ${CMAKE_CURRENT_SOURCE_DIR}/heads
    ${CMAKE_SOURCE_DIR}/src/dataHandlers/heads
)

# Link controllers with its dependencies so the interface propagates to consumers
target_link_libraries(controllers
PUBLIC
    models
    dataHandlers
    utils
)
