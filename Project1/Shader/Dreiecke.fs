#version 450 core  // 420, 330 core , compatibility

//source: https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/6.multiple_lights/6.multiple_lights.fs

#define MaxLights 2

in vec2 vs_tex_coord;
in vec3 Normal;
in vec3 FragPos;
in vec4 outColor;
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform sampler2D tex;
uniform vec3 viewPos;
uniform Material material;
uniform Light light[MaxLights];
uniform int flagTexture;

layout(location=0) out vec4 fColor;

vec3 CalcDirLight(Light l, vec3 norm, vec3 viewDir)
{
	vec3 lightDir = normalize(l.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient = l.ambient * material.ambient;
	vec3 diffuse = l.diffuse * (diff * material.diffuse);
	vec3 specular = l.specular * (spec * material.specular);

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(Light l, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	float cutOff = 0.95;
	float outerCutOff = 0.8;
	float constant = 1.0f;
	float linear = 0.09;
	float quadratic = 0.032;

    vec3 lightDir = normalize(l.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(l.position - fragPos);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-l.position));
    float epsilon = cutOff - outerCutOff;
    float intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
	vec3 ambient = l.ambient * material.ambient;
	vec3 diffuse = l.diffuse * (diff * material.diffuse);
	vec3 specular = l.specular * (spec * material.specular);

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void main()
{
	vec4 objectColor = texture(tex,vs_tex_coord);
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	// Two light sources: Direct and Spotlight.

	vec3 result = CalcDirLight(light[0], norm, viewDir);;
	result += CalcSpotLight(light[1], norm,  FragPos, viewDir);	

	if (flagTexture == 1)
	{
		// Cube without texture
		fColor = vec4(result,1.0) * outColor;
	} 
	else
	{
		// Boden and Tetra with texture
		fColor = vec4(result,1.0) * objectColor;
	}
}
