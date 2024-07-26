add_library(miserver STATIC
	"Server.cpp"
)

target_link_directories(miserver PUBLIC ${CMAKE_INSTALL_PREFIX})
target_link_libraries(miserver PRIVATE mirak)

install(TARGETS miserver)