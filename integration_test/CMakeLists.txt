# 1. Main SDK Test
add_executable(test_sdk_with_server test_sdk_with_server.cpp)
target_link_libraries(test_sdk_with_server PUBLIC client_sdk gateway)

# 2. Server Test
add_executable(test_server test_server.cpp)
target_link_libraries(test_server PUBLIC client_sdk gateway) # Adjust libs as needed

# 3. Client Test
add_executable(test_client test_client.cpp)
target_link_libraries(test_client PUBLIC client_sdk gateway) # Adjust libs as needed
