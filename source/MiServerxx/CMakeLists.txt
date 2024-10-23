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
	
	"event/EventPool.cpp"
	
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

	"RPC/outgoing/InitGame.cpp"
	"RPC/outgoing/WorldVehicleAdd.cpp"
	"RPC/outgoing/WorldVehicleRemove.cpp"
	"RPC/outgoing/PlayerEnterVehicle.cpp"
	"RPC/outgoing/PlayerExitVehicle.cpp"
	"RPC/outgoing/SetPlayerSkin.cpp"
	"RPC/outgoing/SetPlayerHealth.cpp"
	"RPC/outgoing/SetPlayerArmour.cpp"
	"RPC/outgoing/SetPlayerPos.cpp"
	"RPC/outgoing/SetPlayerFacingAngle.cpp"
	"RPC/outgoing/SetPlayerColor.cpp"
	"RPC/outgoing/SendClientMessage.cpp" 
	"RPC/outgoing/SetCheckpoint.cpp" 
	"RPC/outgoing/DisableCheckpoint.cpp"
	
	"query/SAMPQuery.cpp"
	"util/euler.cpp")

target_link_directories(miserverxx PUBLIC ${CMAKE_INSTALL_PREFIX})
target_link_libraries(miserverxx PRIVATE mirak glm::glm)

install(TARGETS miserverxx)