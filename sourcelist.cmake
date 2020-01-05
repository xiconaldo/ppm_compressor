
target_sources(	compressor PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic_compressor.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/model.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/tree_map.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/file_buffer.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/memory_buffer.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/tree_list.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/tree.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/definitions.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/tree.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic_compressor.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/model.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/tree_map.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/buffer.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/file_buffer.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/memory_buffer.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/probability.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/tree_list.hpp
)
