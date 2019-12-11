a = "FollowCurve" 
b = "curveTest" 
c = "Ship   100.0 1000.0 -30.0   200.0 1000.0 0.0   200.0 1000.0 -100.0   100.0 1000.0 -300.0   400.0 1000.0 -100.0   20.0 10.0 10.0"
d = CreateCommand(a,b,c)
AddCommandToGroup(d, 0)

a = "FollowObject"
b = "FOLLOW THAT SHIP"
c = "Ship Ship2 100.0 1000.0 40.0 30.0"
d = CreateCommand(a,b,c)
AddCommandToGroup(d, 0)

a = "SerialGroup"
b = "idk Serial something it is a name for debugging"
c = "This is needed but does nothing for groups because it is params for other commands"
d = CreateCommand(a,b,c)
AddCommandToGroup(d, 0)

a = "LocationTrigger"
b = "TRIGGERED"
c = "Ship 400.0 1000.0 -100.0 10.0"
e = CreateCommand(a,b,c)
AddCommandToGroup(e, d)

a = "Rotate"
b = "Rotate name thingy"
c = "Ship 100.0 0.0 -30.0 20.0 0.0 0.0"
e = CreateCommand(a,b,c)
AddCommandToGroup(e, d)