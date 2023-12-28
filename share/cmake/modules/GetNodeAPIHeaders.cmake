# Include Node-API headers
execute_process(
  COMMAND node -p "require('node-api-headers').include_dir"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE NODE_API_HEADERS_DIR
)
string(REGEX REPLACE "[\r\n\"]" "" NODE_API_HEADERS_DIR ${NODE_API_HEADERS_DIR})

set(NODE_API_HEADERS_DIR "${NODE_API_HEADERS_DIR}"
  CACHE
  PATH
  "Node API Headers directory."
  FORCE
)

message(STATUS "NODE_API_HEADERS_DIR = ${NODE_API_HEADERS_DIR}")

include_directories(${NODE_API_HEADERS_DIR})
