#version 450 core  // 420, 330 core , compatibility
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 vTexture;
layout(location = 3) in vec3 vNormal; 
uniform mat4 ModelViewProjection;
uniform mat4 Model;
out vec2 vs_tex_coord;
out vec3 Fragment_position;
out vec3 vec3_Normal;
void main(){ 
	Fragment_position     = vec3(Model * vPosition);
	vec3_Normal	    = inverse(transpose(mat3(Model))) * vNormal;	
 	gl_Position = ModelViewProjection*vPosition;
	vs_tex_coord = vTexture;
  }
