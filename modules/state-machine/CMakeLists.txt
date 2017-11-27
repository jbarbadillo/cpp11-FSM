SET(PROJ_NAME state_machine)
PROJECT(${PROJ_NAME})

# Include directories with headers
#---------------------------------------------------#
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )

# Source
#---------------------------------------------------#
FILE(GLOB ${PROJ_NAME}_SRC
    "src/*.cpp"
)
FILE(GLOB ${PROJ_NAME}_HEADERS
    "include/*.h"
)

# Create Library
#---------------------------------------------------#
ADD_LIBRARY(${PROJ_NAME} ${${PROJ_MAIN_NAME}_LIB_TYPE} ${${PROJ_NAME}_HEADERS} ${${PROJ_NAME}_SRC} )

# Link libraries with Project
#---------------------------------------------------#
LINK_DIRECTORIES( ${${PROJ_MAIN_NAME}_PATH_LIBS})
set_target_properties(${PROJ_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Install
#---------------------------------------------------#
INSTALL(TARGETS ${PROJ_NAME}
        DESTINATION "${${PROJ_MAIN_NAME}_PATH_INSTALL}/lib/"
        )
INSTALL(FILES ${${PROJ_NAME}_HEADERS}
        DESTINATION "${${PROJ_MAIN_NAME}_PATH_INSTALL}/include/${PROJ_NAME}"
        )
INSTALL(FILES ${${PROJ_NAME}_GEN_HEADERS}
        DESTINATION "${${PROJ_MAIN_NAME}_PATH_INSTALL}/include/${PROJ_NAME}"
        )