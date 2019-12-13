-- a = "MoveOverTime"
-- b = "Attacker Serial"
-- c = "Attacker -80 117 -50   53 117 -190  10"
-- d = CreateCommand(a,b,c)
-- AddCommandToGroup(d, 0)

-- a = "FollowCurveOverTime"
-- b = "Attacker Serial"
-- c = "Attacker -80 117 -50   -200 117 -200   53 117 -190  10"
-- d = CreateCommand(a,b,c)
-- AddCommandToGroup(d, 0)

-- a = "RotateOverTime"
-- b = "Attacker Serial"
-- c = "Attacker 0 180 0   0 90 0  10"
-- d = CreateCommand(a,b,c)
-- AddCommandToGroup(d, 0)

-- a = "SerialGroup"
-- b = "Attacker Serial"
-- c = ""
-- AttackerSerial = CreateCommand(a,b,c)
-- AddCommandToGroup(AttackerSerial, 0)

-- a = "FollowCurve" 
-- b = "curveTest" 
-- c = "Attacker   120.0 100.0 45.0   147.0 105.0 -150.0   46.5 115 -193   15.0 10.0 10.0"
-- d = CreateCommand(a,b,c)
-- AddCommandToGroup(d, AttackerSerial)


-- a = "Rotate"
-- b = "Rotate Attacker"
-- c = "Attacker 0.0 -90.0 0.0 4.0 0.0 0.0"
-- d = CreateCommand(a,b,c)
-- AddCommandToGroup(d, 0)

-- a = "ParallelGroup"
-- b = "Bombard"
-- c = ""
-- Bombard = CreateCommand(a,b,c)
-- AddCommandToGroup(Bombard, AttackerSerial)

-- a = "FollowCurve" 
-- b = "curveTest" 
-- c = "Ball1   46.3 115 -193   46.3 117 -195   46.3 115 -197   5.0 10.0 10.0"
-- d = CreateCommand(a,b,c)
-- AddCommandToGroup(d, Bombard)
-- a = "FollowCurve" 
-- b = "curveTest" 
-- c = "Ball2   46.4 115 -193   46.4 117 -195   46.4 115 -197   5.0 10.0 10.0"
-- d = CreateCommand(a,b,c)
-- AddCommandToGroup(d, Bombard)
-- a = "FollowCurve" 
-- b = "curveTest" 
-- c = "Ball3   46.5 115 -193   46.5 117 -195   46.5 115 -197   5.0 10.0 10.0"
-- d = CreateCommand(a,b,c)
-- AddCommandToGroup(d, Bombard)
-- a = "FollowCurve" 
-- b = "curveTest" 
-- c = "Ball4   46.6 115 -193   46.6 117 -195   46.6 115 -197   5.0 10.0 10.0"
-- d = CreateCommand(a,b,c)
-- AddCommandToGroup(d, Bombard)

-- a = "FollowObject"
-- b = "FOLLOW THAT SHIP"
-- c = "Ship Ship2 100.0 1000.0 40.0 30.0"
-- d = CreateCommand(a,b,c)
-- AddCommandToGroup(d, 0)

-- a = "SerialGroup"
-- b = "idk Serial something it is a name for debugging"
-- c = "This is needed but does nothing for groups because it is params for other commands"
-- d = CreateCommand(a,b,c)
-- AddCommandToGroup(d, 0)

-- a = "LocationTrigger"
-- b = "TRIGGERED"
-- c = "Ship 400.0 1000.0 -100.0 10.0"
-- e = CreateCommand(a,b,c)
-- AddCommandToGroup(e, d)

-- a = "Rotate"
-- b = "Rotate name thingy"
-- c = "Ship 100.0 0.0 -30.0 20.0 0.0 0.0"
-- e = CreateCommand(a,b,c)
-- AddCommandToGroup(e, d)