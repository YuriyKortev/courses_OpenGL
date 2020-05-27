varying vec4 color;
in vec3 eyecoord;
in vec3 tnorm;
in vec2 v_texCoord;
in vec3 FragPos;

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
    vec3 ambient = l.la * material.ka;

    vec3 n = normalize( tnorm );
    vec3 lightDir = normalize(l.position - FragPos);
    float diff = max(dot(n, lightDir), 0.0);
    vec3 diffuse = l.ld * (diff * material.kd);

    vec3 viewDir = normalize(eyecoord - FragPos);
    vec3 reflectDir = reflect(-lightDir, n);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
    vec3 specular = l.ls * (spec * material.ks);

    vec4 color_t=texture2D(texture,v_texCoord);
    gl_FragColor=vec4(1.0f,0.99f,0.8f,1.0f)*color_t*vec4((ambient+diffuse+spec),1.0f);
}
