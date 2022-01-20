#version 450 core  // 420, 330 core , compatibility

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
uniform Light light;
uniform int flagTexture;

layout(location=0) out vec4 fColor;

void main()
{
	vec4 objectColor = texture(tex,vs_tex_coord);

	vec3 ambient = light.ambient * material.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	if (flagTexture == 1)
	{
		fColor = vec4(result,1.0) * outColor;
	} 
	else
	{
		fColor = vec4(result,1.0) * objectColor;
	}
}
