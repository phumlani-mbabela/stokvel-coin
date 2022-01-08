project(bank)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( bank bank bank.cpp )
target_include_directories( bank PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( bank ${CMAKE_SOURCE_DIR}/../ricardian )