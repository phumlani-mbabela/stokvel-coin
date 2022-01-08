project(eosiostokveltoken)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( eosiostokveltoken eosiostokveltoken eosiostokveltoken.cpp )
target_include_directories( eosiostokveltoken PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( eosiostokveltoken ${CMAKE_SOURCE_DIR}/../ricardian )