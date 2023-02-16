set(GLAD_DIR "../external/glad/")

add_executable(${PROJECT_NAME}
    pomo.cpp
    timing.cpp
    ${GLAD_DIR}/src/glad.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${GLAD_DIR}/include/
)