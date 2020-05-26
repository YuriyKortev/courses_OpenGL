varying vec4 color;
in vec3 eyecoord;
in vec3 tnorm;
in vec2 v_texCoord;

struct LightInfo{
    vec4 position;
    vec3 la; //amb color
    vec3 ld;
    vec3 ls;
};

uniform LightInfo l;

struct MaterialInfo{
    vec3 ka; //amb str
    vec3 kd;
    vec3 ks;
    float Shininess;
};

uniform MaterialInfo material;
uniform sampler2D texture;

void main()
{    
    vec3 n = normalize( tnorm );
    vec3 s = normalize( vec3(l.position) - eyecoord );
    vec3 v = normalize(vec3(-eyecoord));
    vec3 r = reflect( -s, n );


    vec3 ambient=l.la*material.ka;

    float sDotN=max(dot(s,tnorm),0.0f);

    vec3 diffuse=l.ld*material.kd*sDotN;

    vec3 spec=l.ls*material.ks*pow(max( dot(r,v), 0.0 ), material.Shininess);

    vec4 color_t=texture2D(texture,v_texCoord);
    gl_FragColor=color_t*vec4((ambient+diffuse+spec),1.0f);
}
