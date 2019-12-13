type = "MoveOverTime"
name = "Cam Move"
params = "Cam 105 125 57   -90 125 -35  5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, 0)

type = "RotateOverTime"
name = "Cam Rotate"
params = "Cam 12 -145 0   12 145 0  5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, 0)