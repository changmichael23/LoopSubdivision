
attribute vec4 a_Position;
attribute vec4 a_Normal;
attribute vec2 a_TexCoords;
attribute vec4 a_Color;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_CameraMatrix;

uniform float u_Time;

varying vec4 v_Normal;
varying vec2 v_TexCoords;
varying vec3 v_Position;
varying vec4 v_Color;

void main(void)
{
	v_TexCoords = a_TexCoords;
	// si u_WorldMatrix n'est pas une matrice orthogonale
	//v_normal = transpose(inverse(u_WorldMatrix)) * vec4(a_Normal.xyz, 0.0);
	// si on est sur que la matrice u_WorldMatrix est orthogonale
	// on peut simplifier avec inverse(inverse())
	v_Normal = u_WorldMatrix * vec4(a_Normal.xyz, 0.0);  // OU v_Normal = mat3(u_WorldMatrix) * a_Normal.xyz;
	v_Position = vec3(u_WorldMatrix * a_Position);
	gl_Position = u_ProjectionMatrix * u_WorldMatrix * u_CameraMatrix *  a_Position;
	v_Color = a_Color;
}
