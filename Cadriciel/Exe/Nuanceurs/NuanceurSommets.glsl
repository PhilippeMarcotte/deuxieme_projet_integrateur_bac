#version 430

uniform mat4 matrModel;
uniform mat4 matrVisu;
uniform mat4 matrProj;

layout(location=0) in vec4 Vertex;
layout(location=3) in vec4 Color;

out vec4 couleur;

void main( void )
{
   // transformation standard du sommet
   gl_Position = matrProj * matrVisu * matrModel * Vertex;

   // couleur du sommet
   couleur = Color;
}