#version 330 core


out vec4 fFragColor;

in vec3 vNormal_vs;
in vec3 vFragPos_vs;
in vec2 vVertexTexcoords;
in vec3 vFragPos_os;
in vec3 vNormal_os;


struct Material
{
    float shininess;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight 
{
    float intensity;
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};   

uniform sampler2D texture_diffuse;
uniform Material material;
uniform PointLight pointLight;

vec3 ComputePointLight(vec3 planetColor, Material material, PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main()
{
    // Normal and View direction in VIEW SPACE
    vec3 Normal_vs = normalize(vNormal_vs);
    vec3 viewDir_vs = normalize(-vFragPos_vs);

    // Texture
    fFragColor = texture(texture_diffuse, vVertexTexcoords);
    fFragColor = vec4(ComputePointLight(fFragColor.rgb, material, pointLight, Normal_vs, vFragPos_vs, viewDir_vs), 1);
}

vec3 ComputePointLight(vec3 planetColor, Material material, PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float diffuseStrength = max(dot(normal, lightDir), 0.0);
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * planetColor * diffuseStrength;
    vec3 specular = light.specular * material.specular * specularStrength;

    return vec3(ambient + diffuse + specular) * light.intensity;
}



