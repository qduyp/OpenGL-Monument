#version 450 core  // 420, 330 core , compatibility

in vec2 vs_tex_coord;
in vec3 Normal;
in vec3 FragPos;
in vec3 outColor;
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform sampler2D tex;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
//uniform vec4 objectColor;
uniform Material material;

layout(location=0) out vec4 fColor;

vec3 pointLight()
{
	vec3 lightVec = lightPos - FragPos;

	//Intensiti of light with distance, constants a and b
	float dist = length(lightVec);
	float a = 0.5, b = 0.7;
	float inten = 1/(a*dist*dist + b*dist);

	//Ambient-Light
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;

	//Diffuse-Light
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuseStrength = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diffuseStrength * lightColor;

	//Specular-Light
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
	vec3 specular = specularStrength * spec * lightColor;

	return vec3(ambient + diffuse*inten + specular);
}

vec3 directLight()
{
	//Ambient-Light
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;

	//Diffuse-Light
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuseStrength = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diffuseStrength * lightColor;

	//Specular-Light
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
	vec3 specular = specularStrength * spec * lightColor;

	return vec3(ambient + diffuse + specular);
}

vec3 spotLight()
{
	float innerCone = 0.75;
	float outerCone =0.7;

	//Ambient-Light
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;

	//Diffuse-Light
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuseStrength = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diffuseStrength * lightColor;

	//Specular-Light
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
	vec3 specular = specularStrength * spec * lightColor;

	float angle = dot(vec3(0.0,-1.0,0.0),-lightDir);
	float inten = clamp((angle - outerCone)/(innerCone - outerCone),0.0,1.0);

	return vec3(ambient + diffuse*inten + specular);
}

void main()
{
	vec4 objectColor = texture(tex,vs_tex_coord);

	//Result
	vec4 result = vec4(directLight(),1.0) * vec4(outColor, 1.0) * objectColor; 
	fColor = result;
}
