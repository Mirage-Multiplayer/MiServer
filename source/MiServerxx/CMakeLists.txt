add_library(miserverxx STATIC
	"core/Core.cpp"
	"core/CoreInstance.cpp" 

	"netgame/NetGame.cpp"
	"netgame/Player.cpp"
	"netgame/Vehicle.cpp"

	"packet/AimSync.cpp" 
	"packet/BulletSync.cpp" 
	"packet/PassangerSync.cpp" 
	"packet/PlayerSync.cpp" 
	"packet/UnoccupiedSync.cpp" 
	"packet/VehicleSync.cpp" 
	"packet/PositionSync.cpp" 

	"RPC/RPCList.cpp" 
	"RPC/RPC.cpp" 
	
	"RPC/incoming/EnterVehicle.cpp"
	"RPC/incoming/ExitVehicle.cpp"
	"RPC/incoming/VehicleDamaged.cpp"
	"RPC/incoming/ScmEvent.cpp"
	"RPC/incoming/SendSpawn.cpp"
	"RPC/incoming/ChatMessage.cpp"
	"RPC/incoming/SendCommand.cpp"
	"RPC/incoming/InteriorChangeNotification.cpp"
	"RPC/incoming/DeathNotification.cpp"
	"RPC/incoming/DialogResponse.cpp"
	"RPC/incoming/RequestClass.cpp"
	"RPC/incoming/RequestSpawn.cpp"
	"RPC/incoming/UpdateScoresAndPings.cpp"
	"RPC/incoming/ClientJoin.cpp"
	"RPC/incoming/HandleUnsupported.cpp"
	
	"query/SAMPQuery.cpp"
	"util/euler.cpp" "netgame/Dialog.cpp"  "core/RPCHandler.cpp" "core/PacketHandler.cpp" "packet/Connection.cpp")

target_link_directories(miserverxx PUBLIC ${CMAKE_INSTALL_PREFIX})
target_link_libraries(miserverxx PRIVATE mirak glm::glm)

install(TARGETS miserverxx)