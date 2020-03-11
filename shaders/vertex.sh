#version 330 core
layout (location = 0) in vec3 positions;
layout (location = 1) in vec3 colors;

uniform mat4 scale;
uniform mat4 rotate;
uniform mat4 translate;

out vec3 colorOut;


mat4 CreateProjectionMatrix( float screenWidht, float screenHeight,float zfar,float znear)
{
		const float FOV = 90.0f*3.141592653589793238462643383279202884 / 180.f;
		float AspectRatio = screenHeight / screenWidht;
		float Znear =znear;
		float Zfar = zfar;
		float q = 1.0f / tan(FOV / 2);
        mat4 array4x4;
		array4x4[0][0] = q * AspectRatio;
        array4x4[0][1] = 0;
        array4x4[0][2] = 0;
        array4x4[0][3] = 0;
        array4x4[1][0] = 0;
		array4x4[1][1] = q;
        array4x4[1][2] = 0;
        array4x4[1][3] = 0;
        array4x4[2][0] = 0;
        array4x4[2][1] = 0;
		array4x4[2][2] = (Znear + Zfar) / (Znear - Zfar);
		array4x4[2][3] = -1;
        array4x4[3][0] = 0;
        array4x4[3][1] = 0;
		array4x4[3][2] = 2 * (Znear*Zfar) / (Znear - Zfar);
        array4x4[3][3] = 0;
		
   return array4x4;
}
void main()
{
    mat4 projection = CreateProjectionMatrix(1024, 768,1000.f,0.1f);
    vec3 newposition;
    if( gl_InstanceID > 5)
    {
        newposition = positions+vec3(0.0f,gl_InstanceID,0.0f);
    }
    else
    {
        newposition = positions+vec3(gl_InstanceID,0.0f,0.0f);
    }
    gl_Position = projection *translate*rotate*scale*vec4(newposition,1.0f);
    colorOut = colors;
}