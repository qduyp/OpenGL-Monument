#version 450 core  // 420, 330 core , compatibility
in vec2 vec2_Coord;
in vec3 vec3_Normal;
in vec3 Fragment_posistion;
uniform sampler2D tex;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
layout(location=0) out vec4 fColor;
vec3 spotLight(){    
    float innerCone = 0.75;
    float outerCone =0.7;
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;
	vec3 norm = normalize(vec3_Normal);
	vec3 lightDir = normalize(lightPos - Fragment_posistion);
	float diffuseStrength = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diffuseStrength * lightColor;
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - Fragment_posistion);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
	vec3 specular = specularStrength * spec * lightColor;
	float angle = dot(vec3(0.0,-1.0,0.0),-lightDir);
	float inten = clamp((angle - outerCone)/(innerCone - outerCone),0.0,1.0);
	return vec3(ambient + diffuse*inten + specular);
}
vec3 directLight(){
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;
	vec3 norm = normalize(vec3_Normal);
	vec3 lightDir = normalize(lightPos - Fragment_posistion);
	float diffuseStrength = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diffuseStrength * lightColor;
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - Fragment_posistion);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
	vec3 specular = specularStrength * spec * lightColor;
	return vec3(ambient + diffuse + specular);
}
vec3 pointLight(){
    vec3 lightVec = lightPos - Fragment_posistion;
    float dist = length(lightVec);
    float a = 0.5, b = 0.7;
    float inten = 1/(a*dist*dist + b*dist);
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;
	vec3 norm = normalize(vec3_Normal);
	vec3 lightDir = normalize(lightPos - Fragment_posistion);
	float diffuseStrength = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diffuseStrength * lightColor;
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - Fragment_posistion);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
	vec3 specular = specularStrength * spec * lightColor;
	return vec3(ambient + diffuse*inten + specular);
}
void main(){
	vec4 objectColor = texture(tex,vec2_Coord);
	vec4 result = vec4(directLight(),1.0) * objectColor;
	fColor = result; 
 }	
