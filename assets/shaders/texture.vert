attribute vec2 aPosition;
attribute vec2 aTexCoord;

uniform mat4 uMvpMatrix;

varying vec2 vTexCoord;

void main()
{
    gl_Position = uMvpMatrix * vec4(aPosition, 0.0, 1.0);
    vTexCoord = aTexCoord;
}
