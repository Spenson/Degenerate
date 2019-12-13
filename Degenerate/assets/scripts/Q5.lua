type = "SerialGroup"
name = "Cannon"
params = ""
Cannon = CreateCommand(type,name,params)
AddCommandToGroup(Cannon, 0)

type = "FollowCurveOverTime" 
name = "Fire 1" 
params = "Ball1   53 119.95 -180   53 127 -189   52.8 118 -197   2.5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)
type = "FollowCurveOverTime" 
name = "Fire 2" 
params = "Ball1   53.1 119.95 -180   53 127 -189   52.8 118 -197   2.5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)
type = "FollowCurveOverTime" 
name = "Fire 3" 
params = "Ball1   53.23 119.95 -180   53 127 -189   52.8 118 -197   2.5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)
type = "FollowCurveOverTime" 
name = "Fire 4" 
params = "Ball1   53.4 119.95 -180   53 127 -189   52.8 118 -197   2.5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)
type = "FollowCurveOverTime" 
name = "Fire 8" 
params = "Ball1   53.4 -119.95 -180   53 -129 -189   52.8 -121 -197   0"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)

type = "Wait"
name = ""
params = "10"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)

type = "FollowCurveOverTime" 
name = "Fire 5" 
params = "Ball1   53 119.95 -180   53 127.5 -189   52.8 120 -197   2.5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)
type = "FollowCurveOverTime" 
name = "Fire 6" 
params = "Ball1   53.1 119.95 -180   53 128 -189   52.8 120.5 -197   2.5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)
type = "FollowCurveOverTime" 
name = "Fire 7" 
params = "Ball1   53.23 119.95 -180   53 128.5 -189   52.8 121 -197   2.5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)
type = "FollowCurveOverTime" 
name = "Fire 8" 
params = "Ball1   53.4 119.95 -180   53 129 -189   52.8 121.5 -197   2.5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)
type = "FollowCurveOverTime" 
name = "Fire 8" 
params = "Ball1   53.4 -119.95 -180   53 -129 -189   52.8 -121 -197   0"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)
--<Position x="53" y="117" z="-197"/>


type = "SerialGroup"
name = "Defender"
params = ""
DefenderSerial = CreateCommand(type,name,params)
AddCommandToGroup(DefenderSerial, 0)

type = "Wait"
name = ""
params = "12.5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, DefenderSerial)


type = "MoveOverTime"
name = "Defender up!"
params = "Defender 53 117 -197   53 123 -197  30"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, DefenderSerial)