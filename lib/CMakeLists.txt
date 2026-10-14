set(ASSIGNMENT_4_PLUGINS HelloWorld OpcodeCounter ArithmeticSimplifier CFGPrinter FunctionCallCounter InstructionReplacer ConstantPropagation DeadCodeElimination)

set(HelloWorld_SOURCES HelloWorld.cpp)
set(OpcodeCounter_SOURCES OpcodeCounter.cpp)
set(ArithmeticSimplifier_SOURCES ArithmeticSimplifier.cpp)
set(CFGPrinter_SOURCES CFGPrinter.cpp)
set(FunctionCallCounter_SOURCES FunctionCallCounter.cpp)
set(InstructionReplacer_SOURCES InstructionReplacer.cpp)
set(ConstantPropagation_SOURCES ConstantPropagation.cpp)
set(DeadCodeElimination_SOURCES DeadCodeElimination.cpp)

foreach(plugin ${ASSIGNMENT_4_PLUGINS})
  # Create a library corresponding to 'plugin'
  add_library(${plugin} SHARED ${${plugin}_SOURCES})
  llvm_map_components_to_libnames(llvm_libs Support Core Analysis Passes)
  target_link_libraries(${plugin} PRIVATE ${llvm_libs})

  # Configure include directories for 'plugin'
  target_include_directories(${plugin}
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")

endforeach()
