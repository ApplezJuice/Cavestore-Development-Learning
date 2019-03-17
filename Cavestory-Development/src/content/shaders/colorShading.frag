#version 460

in vec2 fragPosition;
in vec4 fragColor;
in vec2 fragUV;

//outputs a vector3 RGB (r,g,b,a)
out vec4 color;

// uniform variables are globla variables for the whole mesh and not the vertex
//uniform float time;
// 1d / 2d texture uses a sampler
uniform sampler2D mySampler;

void main(){
// vec with rgb?

	// y axis is V and x axis is U that range from 0->1
	// so if we are making a person, we want to load in the full texture
	// the texture is on a quad, which is 6 vertices for 2 triangles
	// bottom left is 0v0u, bottom right is 0v1u, top left is 1vu0, top right is 1v,1u

	// lookup the texture, mySampler and lookup the texture vertexes in UV
	vec4 textureColor = texture(mySampler, fragUV);

	color = textureColor * fragColor;

	//color = vec4(tan(fragPosition.y/fragPosition.x*time),tan(fragPosition.y/fragPosition.x*time),tan(fragPosition.y/fragPosition.x*time), fragColor.a + time) * ;
	//color = vec4(cos(fragPosition.y/fragPosition.y*time),
	//						tan(fragPosition.x/fragPosition.y *time),
	//						sin(fragPosition.y/fragPosition.x*time), fragColor.a + time) * textureColor;
	//color = vec4(fragColor.r * (cos(fragPosition.x * 4.0 / time) / (cos(fragPosition.y)) + 1) * 0.5,
	//			 fragColor.g * (sin(fragPosition.y * 4.0 / time) + 1) * 0.5,
	//			 fragColor.b * (sin(fragPosition.x * 2.0 / time) + 1) * 0.5, fragColor.a);
    //color = vec4(1.0 * (cos(time)+1.0) * 0.5, 
	//						1.0 * (cos(time)+2.0) * 0.5, 
	//						1.0 * (sin(time)+1.0) * 0.5, 0.0) * textureColor;
}