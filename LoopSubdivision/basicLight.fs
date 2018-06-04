uniform sampler2D u_Texture;
varying vec2 v_TexCoords;
varying vec4 v_Normal;
varying vec3 v_Position;

//const vec3 directionalLight = normalize(-vec3(1.0, -1.0, -0.5));

uniform vec4 u_PositionOrDirection;
// composantes ambiantes
const vec3 lightAmbiantColor = vec3(1.0, 0.0, 0.5);

// composantes diffuses
const vec3 lightDiffuseColor = vec3(0.5, 0.5, 0.5);
const vec3 lightSpecularColor = vec3(1, 1,1);

const vec3 u_materialAmbiantColor = vec3(0.5,0.5,0.5);
const vec3 u_materialDiffuseColor= vec3(0.5,0.5,0.5);
const vec3 u_materialSpecularColor= vec3(1,1,1);
const float u_Shininess = 10;


void main(void)
{
	

    vec2 uv = vec2(v_TexCoords.x, 1.0 - v_TexCoords.y);

	vec3 N = normalize(v_Normal.xyz);
	
	vec3 P = v_Position;
	
	vec3 L = vec3(-u_PositionOrDirection);
	
	if (u_PositionOrDirection.w > 0.0) {
		// Positionnel (point light ou spot light)
		L = normalize(u_PositionOrDirection.xyz - P);
	}
	
	vec3 R = normalize(-reflect(L,N));
	vec3 E = normalize(- P);
	vec3 H = normalize(L-P);
	
	float diffuseFactor = max(dot(N, L), 0.0);
	vec3 diffuseColor = lightDiffuseColor * vec3(u_materialDiffuseColor);
	vec4 diffuse = vec4(diffuseFactor * diffuseColor, 1.0);
	
	
	texturee=texture2D(u_Texture, uv);

		
	
	vec4 specular;
	vec3 ambiantColor = lightAmbiantColor * vec3(u_materialAmbiantColor);
		
	vec3 specularColor =  vec3(u_materialSpecularColor)*lightSpecularColor;
		
		
		
	specular = vec4(pow(max(dot(R,E),0.0),u_Shininess)*specularColor,1.0) ;
		

	gl_FragColor = vec4(ambiantColor, 1.0) * texturee+ diffuse * texturee + specular;
	gl_FragColor.a = 0.5;
	
}
