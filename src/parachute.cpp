#include "parachute.h"
#include "main.h"

using namespace std;

Parachute::Parachute(float x,float y,float z)
{
	this->position = glm::vec3(x,y,z);

    int n;
    n = 6;
    GLfloat g_vertex_buffer_data[1000],g_vertex_buffer_data_line[1000];

    float cy_x = 1.0f, cy_y = 1.0f, ang = 2*3.14159, x1 , y1;
    ang/=(float)(n);
    int ind = 0;
    int l_ind = 0;

    float cone_x = 0, cone_y = 2.0f, cone_z = 0.0f;

    cy_x = 1.0f, cy_y = 1.0f, ang = 2*3.14159;
    ang/=(float)(n);

    for(int i=0;i<n;++i)
    {
        x1 = cy_x*cos(ang)-cy_y*sin(ang);
        y1 = cy_x*sin(ang)+cy_y*cos(ang);

        g_vertex_buffer_data_line[l_ind++] = x1;
        g_vertex_buffer_data_line[l_ind++] = 0.0f;
        g_vertex_buffer_data_line[l_ind++] = y1;

        g_vertex_buffer_data_line[l_ind++] = 0.0f;
        g_vertex_buffer_data_line[l_ind++] = -2.5f;
        g_vertex_buffer_data_line[l_ind++] = 0.0f;

        g_vertex_buffer_data[ind++] = cone_x;
        g_vertex_buffer_data[ind++] = cone_y;
        g_vertex_buffer_data[ind++] = cone_z;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = cy_y;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = y1;
        
        cy_x = x1;
        cy_y = y1;
    }

    int yex = 2;
    GLfloat g_vertex_buffer_cube[] = {
        -0.5f,-0.5f-yex,-0.5f, // triangle 1 : begin
        -0.5f,-0.5f-yex, 0.5f,
        -0.5f, 0.5f-yex, 0.5f, // triangle 1 : end
        0.5f, 0.5f-yex,-0.5f, // triangle 2 : begin
        -0.5f,-0.5f-yex,-0.5f,
        -0.5f, 0.5f-yex,-0.5f, // triangle 2 : end
        0.5f,-0.5f-yex, 0.5f,
        -0.5f,-0.5f-yex,-0.5f,
        0.5f,-0.5f-yex,-0.5f,
        0.5f, 0.5f-yex,-0.5f,
        0.5f,-0.5f-yex,-0.5f,
        -0.5f,-0.5f-yex,-0.5f,
        -0.5f,-0.5f-yex,-0.5f,
        -0.5f, 0.5f-yex, 0.5f,
        -0.5f, 0.5f-yex,-0.5f,
        0.5f,-0.5f-yex, 0.5f,
        -0.5f,-0.5f-yex, 0.5f,
        -0.5f,-0.5f-yex,-0.5f,
        -0.5f, 0.5f-yex, 0.5f,
        -0.5f,-0.5f-yex, 0.5f,
        0.5f,-0.5f-yex, 0.5f,
        0.5f, 0.5f-yex, 0.5f,
        0.5f,-0.5f-yex,-0.5f,
        0.5f, 0.5f-yex,-0.5f,
        0.5f,-0.5f-yex,-0.5f,
        0.5f, 0.5f-yex, 0.5f,
        0.5f,-0.5f-yex, 0.5f,
        0.5f, 0.5f-yex, 0.5f,
        0.5f, 0.5f-yex,-0.5f,
        -0.5f, 0.5f-yex,-0.5f,
        0.5f, 0.5f-yex, 0.5f,
        -0.5f, 0.5f-yex,-0.5f,
        -0.5f, 0.5f-yex, 0.5f,
        0.5f, 0.5f-yex, 0.5f,
        -0.5f, 0.5f-yex, 0.5f,
        0.5f,-0.5f-yex, 0.5f
    };

    this->object[0] = create3DObject(GL_TRIANGLES,3,g_vertex_buffer_data,COLOR_DARKRED,GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES,3,g_vertex_buffer_data+9,COLOR_YELLOW,GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES,3,g_vertex_buffer_data+18,COLOR_GREEN,GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES,3,g_vertex_buffer_data+27,COLOR_ORANGE,GL_FILL);
    this->object[4] = create3DObject(GL_TRIANGLES,3,g_vertex_buffer_data+36,COLOR_BLUE,GL_FILL);
    this->object[5] = create3DObject(GL_TRIANGLES,3,g_vertex_buffer_data+45,COLOR_RED,GL_FILL);

    this->cube = create3DObject(GL_TRIANGLES,36,g_vertex_buffer_cube,COLOR_BROWN,GL_FILL);
    this->lines = create3DObject(GL_LINES,2*6,g_vertex_buffer_data_line,COLOR_RED,GL_FILL);

}

void Parachute::draw(glm::mat4 VP) {
    //std::cout << this->position[1] << endl;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    //glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<=5;++i)
        draw3DObject(this->object[i]);
    draw3DObject(this->lines);
    draw3DObject(this->cube);
    //std::cout << this->position[1] << endl;
}

void Parachute::tick() {
    this->position.y -= 0.03;
}