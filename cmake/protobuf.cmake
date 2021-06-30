# import protobuf required by onnx proto
FetchContent_GetProperties(protobuf)
if(NOT protobuf_POPULATED)
    FetchContent_Populate(protobuf)
    add_subdirectory(${protobuf_SOURCE_DIR}/cmake ${protobuf_BINARY_DIR})
    set(PPLNN_PROTOBUF_COMPILE_OPTIONS "-Wno-sign-compare -Wno-unused-variable -Wno-unused-function -Wno-uninitialized")
    set_target_properties(libprotobuf PROPERTIES COMPILE_FLAGS ${PPLNN_PROTOBUF_COMPILE_OPTIONS})
    set_target_properties(libprotobuf-lite PROPERTIES COMPILE_FLAGS ${PPLNN_PROTOBUF_COMPILE_OPTIONS})
    set_target_properties(protoc PROPERTIES COMPILE_FLAGS ${PPLNN_PROTOBUF_COMPILE_OPTIONS})
    set_target_properties(libprotoc PROPERTIES COMPILE_FLAGS ${PPLNN_PROTOBUF_COMPILE_OPTIONS})
endif()
