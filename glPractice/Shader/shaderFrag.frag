#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    sampler2D cusTex[2];
    float shiness;
};

struct Light {
    vec3 position;
    vec3 direction;

    float cutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main()
{
    vec3 lightDir = normalize(light.position - FragPos);

    float theta = dot(lightDir, normalize(-light.direction));
    if (theta > light.cutOff)
    {
        vec3 ambient = light.ambient * texture(material.cusTex[0], texCoord).rgb;

        // diffuse
        vec3 norm = normalize(Normal);
        // vec3 lightDir = normalize(-light.direction);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * texture(material.cusTex[0], texCoord).rgb;

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shiness);
        vec3 specular = light.specular * spec * texture(material.cusTex[1], texCoord).rgb;

        // attenuation
        float distance = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

        ambient *= 1;
        diffuse *= attenuation;
        specular *= attenuation;

        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    }
    else
    {
        FragColor = vec4(light.ambient * texture(material.cusTex[0], texCoord).rgb, 1.0);
    }
}