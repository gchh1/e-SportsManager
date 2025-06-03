add_library(views)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/heads HEAD)

target_sources(views 
PRIVATE 
    ${SRC}
PUBLIC 
    ${HEAD}
)

target_include_directories(views 
PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/heads
    ${CMAKE_SOURCE_DIR}/src/controllers/heads
    ${CMAKE_SOURCE_DIR}/src/models/heads
    ${CMAKE_SOURCE_DIR}/src/dataHandlers/heads)

# Link the views library against controllers so that symbols are resolved
target_link_libraries(views 
PUBLIC
    controllers
)