type = "SerialGroup"
name = "SerialGroup"
params = ""
Serialgroup = CreateCommand(type,name,params)
AddCommandToGroup(Serialgroup, 0)

type = "RotateOverTime"
name = "Rotate before move"
params = "Attacker 0 180 0   0 135 0  3"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Serialgroup)


type = "MoveOverTime"
name = "Attacker Towards Defender"
params = "Attacker -80 117 -50   20 117 -158  20"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, Serialgroup)

-- type = "RotateOverTime"
-- name = "Rotate before move"
-- params = "Attacker 0 135 0   0 180 0  3"
-- command = CreateCommand(type,name,params)
-- AddCommandToGroup(command, Serialgroup)

type = "ParallelGroup"
name = "Aligning"
params = ""
ParallelGroup = CreateCommand(type,name,params)
AddCommandToGroup(ParallelGroup, Serialgroup)


type = "FollowCurveOverTime"
name = "Aligning"
params = "Attacker 20 117 -158   35 118 -180   53 120 -180  10"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, ParallelGroup)

type = "RotateOverTime"
name = "Rotate before move"
params = "Attacker 0 135 0   0 90 0  7"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, ParallelGroup)




type = "SerialGroup"
name = "CameraSeq"
params = ""
CameraSerial = CreateCommand(type,name,params)
AddCommandToGroup(CameraSerial, 0)

type = "Wait"
name = ""
params = "10"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, CameraSerial)



type = "ParallelGroup"
name = "CameraMove"
params = ""
ParallelGroup = CreateCommand(type,name,params)
AddCommandToGroup(ParallelGroup, CameraSerial)

type = "MoveOverTime"
name = "Attacker Towards Defender"
params = "Cam -90 125 -35   30 125 -208  25"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, ParallelGroup)



type = "SerialGroup"
name = "rotategroup"
params = ""
rotateSerial = CreateCommand(type,name,params)
AddCommandToGroup(rotateSerial, ParallelGroup)
type = "Wait"
name = ""
params = "16"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, rotateSerial)
type = "RotateOverTime"
name = "Rotate Cam"
params = "Cam   12 145 0   10 50 0  9"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, rotateSerial)