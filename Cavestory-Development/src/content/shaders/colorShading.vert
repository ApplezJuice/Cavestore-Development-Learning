#version 460
//The vertex shader operates on each vertex

//input data from VBO. Each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragPosition;
out vec4 fragColor;
out vec2 fragUV;

void main() {
    //Set the x,y position on the screen
    gl_Position.xy = vertexPosition;

    //the z position is zero since we are 2d
    gl_Position.z = 0.0;

    //indicate that the coordinates are nomalized
    gl_Position.w = 1.0;

	fragPosition = vertexPosition;

    fragColor = vertexColor;

	// opengl needs to flip the coordinates
	fragUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}