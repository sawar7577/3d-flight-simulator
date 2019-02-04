#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragColor;
in vec3 fragPos;
in vec3 Normal;


// output data
out vec3 color;

void main()
{
    // Ambient light
    float strength = 0.5f;
    vec3 ambient = strength*vec3(1.0f,1.0f,1.0f);
    
    
    // Diffuse light
    vec3 posdirvec = normalize(fragPos - vec3(2500.0f, 2500.0f , 2500.0f));;
    vec3 diffuseColor = vec3(1.0f,1.0f,1.0f);
    float diffuse = clamp(dot(fragPos, Normal),0,1);
    vec3 diffuseFinal = 0.5f * diffuse * diffuseColor;


    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices of the triangle
    color = (fragColor * ((diffuseFinal + ambient)));
}
