
set(SOURCE_FILES
  logger.cpp
    )

add_library(thelog STATIC ${SOURCE_FILES})
target_link_libraries(thelog ${LIBS})
install(TARGETS thelog DESTINATION lib)

