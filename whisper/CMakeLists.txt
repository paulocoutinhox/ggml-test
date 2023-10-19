set(
    WHISPER_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/ggml.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ggml-alloc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ggml-metal.m
    ${CMAKE_CURRENT_SOURCE_DIR}/whisper.cpp
)

add_compile_definitions(GGML_USE_ACCELERATE)
add_compile_definitions(GGML_USE_METAL)

add_library(whisper STATIC ${WHISPER_SRC})

set_target_properties(
    whisper
    PROPERTIES
    XCODE_ATTRIBUTE_OTHER_CFLAGS "-framework Foundation -framework Metal -framework MetalKit -fno-objc-arc"
    RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/ggml-metal.metal"
)
