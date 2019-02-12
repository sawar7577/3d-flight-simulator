#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragColor;
in vec3 fragPos;
in vec3 Normal;


// output data
uniform vec3 lightpos;
out vec4 color;

void main()
{
    // Ambient light
    float strength = 1.0f;
    vec3 ambient = strength*normalize(vec3(1.0f,1.0f,1.0f));
    
    
    // Diffuse light
    // lightpos = vec3(2500.0f,2500.0f,2500.0f);
    vec3 posdirvec = normalize(vec3(2500.0f,2500.0f,2500.0f) - fragPos);;
    vec3 diffuseColor = normalize(vec3(1.0f,1.0f,1.0f));
    float diffuse = clamp(dot(posdirvec, normalize(Normal)),0,1);
    vec3 diffuseFinal = (diffuse * diffuseColor);

    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices of the triangle
    color =  vec4(fragColor * (ambient + diffuseFinal),1);
    // color = (fragColor );

}
