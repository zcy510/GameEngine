#type vertex
#version 450 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactorx;
layout(location = 5) in float a_TilingFactory;
layout(location = 6) in int a_EntityID;

// uniform mat4 u_ViewProjection;
// uniform float u_Time;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
	float x_TilingFactor;
	float y_TilingFactor;
};

layout (location = 0) out VertexOutput Output;
layout (location = 4) out flat float v_TexIndex;
layout (location = 5) out flat int v_EntityID;

// out vec2 v_TexCoord;
// flat out float v_TexIndex;
// out float v_TilingFactor;
// out vec4 v_Color;
// flat out int v_EntityID;

void main()
{
	// v_Color = a_Color;
	// v_TexCoord = a_TexCoord;
	// v_TexIndex = a_TexIndex;
	// v_TilingFactor = a_TilingFactor;
	Output.Color = a_Color;
	Output.TexCoord = a_TexCoord;
	Output.x_TilingFactor = a_TilingFactorx;
	Output.y_TilingFactor = a_TilingFactory;
	v_TexIndex = a_TexIndex;
	vec3 pos = a_Position;
    // pos.y += sin(a_Position.x * 10.0 + u_Time) * 0.1; // 正弦函数用于波动效果
	v_EntityID = a_EntityID;
    gl_Position = u_ViewProjection * vec4(pos, 1.0);
	// gl_Position = u_ViewProjection * vec4(a_Position+0.5, 1.0);
}

#type fragment
#version 450 core
			
layout(location = 0) out vec4 color;
layout(location = 1) out int color2;

// in vec2 v_TexCoord;
// flat in float v_TexIndex;
// in float v_TilingFactor;
// in vec4 v_Color;
// flat in int v_EntityID;

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
	float x_TilingFactor;
	float y_TilingFactor;
};

layout (location = 0) in VertexOutput Input;
layout (location = 4) in flat float v_TexIndex;
layout (location = 5) in flat int v_EntityID;

// uniform sampler2D u_Textures[32];

layout (binding = 0) uniform sampler2D u_Textures[32];

void main()
{
	// TODO: u_TilingFactor
	color = texture(u_Textures[int(v_TexIndex)], vec2(Input.TexCoord.x * Input.x_TilingFactor, Input.TexCoord.y * Input.y_TilingFactor)) * Input.Color;
	color2 = v_EntityID;
}