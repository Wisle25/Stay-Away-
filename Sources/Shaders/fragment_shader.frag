varying in vec4 vert_pos;

uniform sampler2D texture;
uniform bool hasTexture;
uniform vec2 light;

void main()
{
    // Ambient Lighting
    vec4 ambient = vec4(0.32, 0.22, 0.5, 1.0);

    // Convert light to camera coords
    light = (gl_ModelViewProjectionMatrix * vec4(light, 0, 1)).xy;

    // Calculate the vector from light to pixel
    vec2 lightToFrag = light - vert_pos.xy;
    lightToFrag.y = lightToFrag.y / 1.7;

    // Length of vector
    float vecLength = clamp(length(lightToFrag) * 4, 0, 1);

    // Lookup the pixel in texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // Multiply it by the color and lighting
    if (hasTexture)
        gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1 - vecLength, 1 - vecLength, 1 - vecLength, 1), 0, 1));
    else
        gl_FragColor = gl_Color;
}