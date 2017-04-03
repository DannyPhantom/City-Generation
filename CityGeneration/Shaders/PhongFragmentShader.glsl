#version 410 core

in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
    vec4 C;
    vec2 uv;
} fs_in;

uniform vec4 specular_color = vec4(0.7);
uniform float specular_power = 1.0;
uniform float ambient = 0.4f;

const vec4 moonlightColor = vec4(34.f/255.f, 63.f/255.f, 89.f/255.f, 1);

// Texture Mapping
uniform sampler2D TextureUniform;
uniform bool TextureValid;

void main(void)
{
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    // Calculate R locally
    vec3 R = reflect(-L, N);

	vec4 color = fs_in.C;
	if (TextureValid) color = texture(TextureUniform, fs_in.uv);

   /* vec4 diffuse = max(dot(N, L), 0.3) * fs_in.C;
	if (TextureValid)
		diffuse *= texture(TextureUniform, fs_in.uv);

    vec4 specular = pow(max(dot(R, V), 0.0), specular_power) * specular_color;*/

	vec4 diffuseMoon = max(dot(N, L), 0.3) * moonlightColor;

    // Write final colour to the framebuffer
    //gl_FragColor = (1.0f + ambient) * diffuse + specular;
	gl_FragColor = color + ambient * diffuseMoon;
}
