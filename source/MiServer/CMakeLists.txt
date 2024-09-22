add_library(miserver STATIC
	"server.cpp"
	"netgame.cpp"
	"event.cpp"
)

target_link_directories(miserver PUBLIC ${CMAKE_INSTALL_PREFIX})
target_link_libraries(miserver PRIVATE mirak miserverxx glm::glm)

install(TARGETS miserver)