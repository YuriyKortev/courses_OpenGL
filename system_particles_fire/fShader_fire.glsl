#version 330 core

in vec3 color;
in float phase;
in float vRot;

uniform sampler2D sprite;
uniform sampler2D colorMap;

const float mid=0.5;

void main()
{

    float vRotation=vRot;
    vec2 rotated = vec2(cos(vRotation) * (gl_PointCoord.x - mid) + sin(vRotation) * (gl_PointCoord.y - mid) + mid,
                            cos(vRotation) * (gl_PointCoord.y - mid) - sin(vRotation) * (gl_PointCoord.x - mid) + mid);

    vec4 c1 = texture2D ( sprite, rotated );
    vec4 c2 = texture2D ( colorMap, vec2 ( (phase), 1.0 ) );
    vec4 c=(1.0 - phase) * vec4 ( c1.rgb * c2.rgb, 0.0 );

    gl_FragColor=vec4(c1.rgb*c2.rgb,c1.a*(1-phase));

}
