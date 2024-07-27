add_library(miserver STATIC
	"server/Server.cpp"
	"player/PlayerPool.cpp"
	"player/Player.cpp"
	"packet/AimSync.cpp" 
	"packet/BulletSync.cpp" 
	"packet/PassangerSync.cpp" 
	"packet/PlayerSync.cpp" 
	"packet/UnoccupiedSync.cpp" 
	"packet/VehicleSync.cpp" 
	"RPC/RPCList.cpp" 
	"RPC/RPC.cpp" 
	"server/ServerInstance.cpp" 
	"vehicle/VehiclePool.cpp" 
	"packet/PositionSync.cpp")

target_link_directories(miserver PUBLIC ${CMAKE_INSTALL_PREFIX})
target_link_libraries(miserver PRIVATE mirak)

install(TARGETS miserver)