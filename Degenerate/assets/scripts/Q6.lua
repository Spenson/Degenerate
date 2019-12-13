type = "SerialGroup"
name = "defender"
params = ""
DefenderSerial = CreateCommand(type,name,params)
AddCommandToGroup(DefenderSerial, 0)

type = "MoveOverTime"
name = ""
params = "Defender 53 123 -197   0 123 -197  10"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, DefenderSerial)
type = "RotateOverTime"
name = ""
params = "Defender 0 -90 0   0 -45 0  3"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, DefenderSerial)
type = "MoveOverTime"
name = ""
params = "Defender 0 123 -197   -70 100 -127  20"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, DefenderSerial)

type = "SerialGroup"
name = "Attacker"
params = ""
AttackerSerial = CreateCommand(type,name,params)
AddCommandToGroup(AttackerSerial, 0)

type = "ParallelGroup"
name = "Attacker"
params = ""
AttackerParallel = CreateCommand(type,name,params)
AddCommandToGroup(AttackerParallel, AttackerSerial)
type = "FollowCurveOverTime"
name = ""
params = "Attacker 53 120 -180   83 120 -180   83 120 -210   45 120 -210   35 120 -205  14"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, AttackerParallel)

type = "SerialGroup"
name = "Attacker"
params = ""
rotateSerial = CreateCommand(type,name,params)
AddCommandToGroup(rotateSerial, AttackerParallel)
type = "RotateOverTime"
name = ""
params = "Attacker 0 90 0   0 180 0  5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, rotateSerial)
type = "RotateOverTime"
name = ""
params = "Attacker 0 180 0   0 -90 0  5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, rotateSerial)
type = "RotateOverTime"
name = ""
params = "Attacker 0 -90 0   0 -45 0  2.5"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, rotateSerial)

 type = "MoveOverTime"
 name = ""
 params = "Attacker 35 120 -205   -40 100 -155  20"
 command = CreateCommand(type,name,params)
 AddCommandToGroup(command, AttackerSerial)

-- type = "FollowObject"
-- name = ""
-- params = "Attacker Defender 6 17 40 10"
-- command = CreateCommand(type,name,params)
-- AddCommandToGroup(command, AttackerSerial)

type = "SerialGroup"
name = "cam"
params = ""
CamSerial = CreateCommand(type,name,params)
AddCommandToGroup(CamSerial, 0)

type = "MoveOverTime"
name = ""
params = "Cam 30 125 -208   30 125 -228  4"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, CamSerial)

type = "RotateOverTime"
name = ""
params = "Cam 10 50 0   20 -45 0  20"
command = CreateCommand(type,name,params)
AddCommandToGroup(command, CamSerial)
-- type = "MoveOverTime"
-- name = ""
-- params = "Defender 0 123 -197   -120 123 -77  27"
-- command = CreateCommand(type,name,params)
-- AddCommandToGroup(command, DefenderSerial)