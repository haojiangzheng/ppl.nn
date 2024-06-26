install(TARGETS pplnn_basic_static DESTINATION lib)

set(__PPLNN_CMAKE_CONFIG_FILE__ ${CMAKE_CURRENT_BINARY_DIR}/generated/pplnn-config.cmake)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/pplnn-config.cmake.in
    ${__PPLNN_CMAKE_CONFIG_FILE__}
    @ONLY)
install(FILES ${__PPLNN_CMAKE_CONFIG_FILE__} DESTINATION lib/cmake/ppl)
unset(__PPLNN_CMAKE_CONFIG_FILE__)

install(DIRECTORY include/ppl/nn/common DESTINATION include/ppl/nn)
install(DIRECTORY include/ppl/nn/runtime DESTINATION include/ppl/nn)
install(DIRECTORY include/ppl/nn/utils DESTINATION include/ppl/nn)

install(FILES include/ppl/nn/engines/engine.h DESTINATION include/ppl/nn/engines)

if(PPLNN_ENABLE_PMX_MODEL)
    install(DIRECTORY include/ppl/nn/models/pmx DESTINATION include/ppl/nn/models)
endif()

install(TARGETS ${PPLNN_ONNX_GENERATED_LIBS} DESTINATION lib)
