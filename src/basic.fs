varying vec3 v_Position;
varying vec2 v_TexCoords;
varying vec4 v_Normal;
varying vec4 v_Color;


uniform sampler2D u_Texture;

const vec3 directionalLight = normalize(-vec3(0.0, -1.0, 0.0));

// composantes ambiantes
const vec3 lightAmbiantColor = vec3(0.2, 0.2, 0.2);
const vec3 materialAmbiantColor = vec3(1.0, 1.0, 1.0);
const vec3 lightSpecularColor = vec3(1, 1,1);
// composantes diffuses
const vec3 lightDiffuseColor = vec3(0.5,0.5, 0.5);
const vec3 materialDiffuseColor = vec3(0.8, 0.8, 0.8);
const vec3 materialSpecularColor = vec3(1.0, 1.0, 1.0);
const float u_Shininess=10;

//uniform vec4 color;

void main(void)
{
	vec3 diffuseColor = lightDiffuseColor * materialDiffuseColor;
	//vec3 diffuseColor = materialDiffuseColor;
    vec2 uv = vec2(v_TexCoords.x, 1.0 - v_TexCoords.y);
	// on a en fait passer des normales comme couleur
	//vec4 color = vec4(v_Normal.rgb * 0.5 + 0.5, 1.0);
	

	// ||u||*||v||*cos0 -> cos0 = U.V / ||u||*||v||
	// attention! U.V peut être négatif

	// la dricetion de v_Normal a pu être deformee par l'interpolation
	// il faut donc re-normaliser afin que la longueur du verteur soit correcte
	vec3 normal = normalize(v_Normal.xyz);
	float diffuseFactor = max(dot(normal, directionalLight), 0.0);
	
	vec4 diffuse = vec4(diffuseFactor * diffuseColor, 1.0);
	
	

	vec3 P = v_Position;
	vec3 L = vec3(directionalLight);
	vec3 R = normalize(-reflect(L,normal));
	vec3 E = normalize(- P);
	
	vec3 specularColor =  vec3(materialSpecularColor)*lightSpecularColor;
	vec3 ambiantColor = lightAmbiantColor * vec3(materialAmbiantColor);
	vec4 specular = vec4(pow(max(dot(R,E),0.0),u_Shininess)*specularColor,1.0) ;
	//gl_FragColor = diffuseFactor;
	//gl_FragColor = diffuse*v_Color+ vec4(ambiantColor, 1.0) *v_Color;
	gl_FragColor = diffuse*v_Color+ vec4(ambiantColor, 1.0) *v_Color+specular;
}
