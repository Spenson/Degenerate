type = "MoveOverTime"
name = ""
params = "Defender -70 100 -127  -180 100 -17   20"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, 0)

type = "SerialGroup"
name = "Cannon"
params = ""
Cannon = CreateCommand(type,name,params)
AddCommandToGroup(Cannon, 0)
type = "FollowCurveOverTime" 
name = "Fire" 
params = "Ball1    -75 101 -122 -65 105 -140   -40 100 -155   2.5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)
type = "FollowCurveOverTime" 
name = "Fire 8" 
params = "Ball1   -40 0 -155   53 0 -189   -75 0 -122  0"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Cannon)


type = "SerialGroup"
name = "def"
params = ""
def = CreateCommand(type,name,params)
AddCommandToGroup(command, 0)

type = "FollowObject"
name = ""
params = "Attacker Defender 5 2.5 40 10"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, def)

type = "MoveOverTime"
name = ""
params = "Cam 30 125 -228  -70 123 -127   20"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, 0)