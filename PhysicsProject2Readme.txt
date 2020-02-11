Build
	Build Degenerate in x64 released or debug. Dependencies applied to build the rest

Controls
	[W] apply force to sphere forward relitive to camera
	[S] apply force to sphere backwards relitive to camera
	[A] apply force to sphere Left relitive to camera
	[D] apply force to sphere Right relitive to camera
	[Space] apply force to sphere Up on y axis
	[Tab] switch between spheres
	[L-Click] and drag to rotate around sphere
	[R-Click] and drag forward and back to zoom in and out
	
Implemeneted
	ReadMe - $(SolutionDir)PhysicsProject2Readme.txt
	Compiles
	Decoupled - Wrapper is a dll
	External File - $(SolutionDir)Degenerate/assets/config/Config.json
	Reasonable Rendering - rendered with grid to show curvature 
	Camera - targeted sphere, rotation, zoom $(SolutionDir)Degenerate/Camera/c3rdPersonCamera
	Better Camera - no bounce
	
	Intergration - RK4 cWorld calls Integrates RK4 $(SolutionDir)MyPhysics/physics/Integrator
	
	Planes - 1 floor rendered, 4 walls invisable so you can see the spheres. Defined in External File
	Spheres - 18 size form 0.5 to 4.0, mass and radius match size, random locations. Defined in External File
		Reading shapes in $(SolutionDir)Degenerate/LoadingStuff/Load

	Interation - looks good to me
	Controls - shown above	in $(SolutionDir)Degenerate/UserInput/NewUserInput