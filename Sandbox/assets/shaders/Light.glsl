#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_Position;

void main()
{
	v_TexCoord = a_TexCoord;
	v_Normal = a_Normal;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
    v_Position = vec3(u_Transform * vec4(a_Position, 1.0));
}

#type fragment
#version 330 core
			
layout(location = 0) out vec4 color;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 position; 
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_Position;

uniform vec4 u_Color;

uniform vec3 viewPos; 
uniform Material material;
uniform Light light;

void main()
{
	// ambient
    vec3 ambient = light.ambient * texture(material.diffuse, v_TexCoord).rgb;
  	
    // diffuse 
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(light.position - v_Position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, v_TexCoord).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - v_Position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, v_TexCoord).rgb;
        
    vec3 lightResult = (ambient + diffuse + specular) * vec3(u_Color);
	color = vec4(lightResult, 1.0);
}