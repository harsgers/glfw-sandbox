#version 400
in vec3 vp;
uniform float offset;
out vec4 colorVert;
void main() {
    gl_Position = vec4((vp.x + offset), -vp.y, vp.z, 1.0);
    colorVert = gl_Position;
}
