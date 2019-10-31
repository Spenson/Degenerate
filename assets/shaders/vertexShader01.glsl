#version 420

//uniform mat4 MVP;
uniform mat4 matModel;		// Model or World 
uniform mat4 matModelInverseTranspose;		// For normal calculation
uniform mat4 matView; 		// View or camera
uniform mat4 matProj;		// Projection transform

in vec4 vColour;				// Was vec3
in vec4 vPosition;				// Was vec3
in vec4 vNormal;				// Vertex normal
in vec4 vUVx2;					// 2 x Texture coords

//out vec3 color;
//out vec4 vertWorld;			// Location of the vertex in the world
out vec4 fColour;	
out vec4 fVertWorldLocation;
out vec4 fNormal;
out vec4 fUVx2;

void main()
{
    vec4 vertPosition = vPosition;
	
    mat4 matMVP = matProj * matView * matModel;
	
	gl_Position = matMVP * vec4(vertPosition.xyz, 1.0);
	
	// Vertex location in "world space"
	// Vec4 = mat4x4 * vec4
	fVertWorldLocation = matModel * vec4(vertPosition.xyz, 1.0);		
	
	//mat4 matModelInverseTranspose = inverse(transpose(matModel));
	
	vec3 theNormal = normalize(vNormal.xyz);
 	fNormal = matModelInverseTranspose * vec4(theNormal, 1.0f);
	
//	fColour = vec4(1.0f,1.0f,1.0f,1.0f) * -1.0f/((fVertWorldLocation.y-100)/10)
//			+ vec4(1.0f,0.0f,0.0f,1.0f) * -1.0f/((fVertWorldLocation.y-50)/5)
//			+ vec4(0.0f,1.0f,0.0f,1.0f) * -1.0f/((fVertWorldLocation.y-10)/2)
//			+ vec4(0.0f,0.0f,1.0f,1.0f) * -1.0/(fVertWorldLocation.y)
//			;

	fColour = vec4(0.0f,0.0f,1.0f,1.0f) * min(1.0f,(1.0/(abs(0-fVertWorldLocation.y)/1)))
			+ vec4(0.5f,0.5f,0.3f,1.0f) * min(1.0f,(1.0/(abs(20-fVertWorldLocation.y)/12)))
			+ vec4(0.1f,0.1f,0.1f,1.0f) * min(1.0f,(1.0/(abs(60-fVertWorldLocation.y)/30)))
			+ vec4(1.0f,1.0f,1.0f,1.0f) * min(1.0f,(1.0/(abs(150-fVertWorldLocation.y)/22)));
			

	// Pass the colour and UV unchanged.
    //fColour = vColour;	
	fUVx2 = vUVx2;
}
