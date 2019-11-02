# Degenerate
Degenerate Game Engine

Simulation time based off deltaTime between frames (max 0.1 perframe)

All waepons fire at 0.1 seconds! This makes frame really slow as shooters find targets

XXX
Bottom left corner 2 robots close together, one shoots bomb at other 0.1 seconds in. Bomb exploades ~3.6 seconds in (simulation time). Draws damages sphere for 0.1 seconds (Simulation time)
XXX

Q1: arena made with student number 0780372
Q2: robots placed with rand and set to ground level. Renderd by giving it a pointer to a game object in the g_vec_GameObjects
Q3: iWeapons class for clean access.  Renderd by giving it a pointer to a game object in the g_vec_GameObjects
Q4: Loops through calling robot update.
	Robot asks world for target and calls shoot on iWeapon
	no target found randomly relocates and tries again

		weapon shoots at position with radius and damage
		world deals damage to that area
			
		bomb creates projectile that is lobbed at target
		projectile reaches target it explodes
Q5: