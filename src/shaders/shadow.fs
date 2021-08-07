#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    sampler2D texture_diffuse;
    vec3  specular;
    float shininess;
}; 

uniform sampler2D shadowMap;
uniform sampler2D normalMap;
uniform bool useNormal = false;

uniform Material material;
uniform Light light;
uniform vec3 _color;
uniform bool useTexture;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 normal;

    if (useNormal) {
        // obtain normal from normal map in range [0,1]
        normal = texture(normalMap, fs_in.TexCoords).rgb;
        // transform normal vector to range [-1,1]
        normal = normalize(normal * 2.0 - 1.0);   
    } else {
        normal = normalize(fs_in.Normal);
    }

    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    // vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(light.position - fs_in.FragPos);
    float bias = max(0.01 * (1.0 - dot(normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{           
    vec3 color;

    if (useTexture) {
        color = texture(material.texture_diffuse, fs_in.TexCoords).rgb;
    } else {
        color = _color;
    }

    vec3 normal;

    if (useNormal) {
        // obtain normal from normal map in range [0,1]
        normal = texture(normalMap, fs_in.TexCoords).rgb;
        // transform normal vector to range [-1,1]
        normal = normalize(normal * 2.0 - 1.0);   
    } else {
        normal = normalize(fs_in.Normal);
    }

    // vec3 color = mix(texture(diffuseTexture, fs_in.TexCoords), vec4(color, 0.6), 0.4).rgb;
    // vec3 color = color;
    // vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    // vec3 normal = normalize(fs_in.Normal);
    // vec3 lightColor = vec3(0.3);
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse, fs_in.TexCoords));
    // vec3 ambient = light.ambient * material.ambient * color;
    // diffuse
    vec3 lightDir = normalize(light.position - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse, fs_in.TexCoords));  
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  

    // spec = pow(max(dot(normal, halfwayDir), 0.0), 64);
    spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
        // vec3 specular = light.specular * (spec * vec3(texture(material.specular, fs_in.TexCoords)));
    vec3 specular = light.specular * (spec * material.specular);
    // calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    FragColor = vec4(lighting, 1.0);
}