#include "main.h"
#include "ring.h"

Ring::Ring(float x,float y,float z)
{
	this->position = glm::vec3(x,y,z);

    int n;
    n = 100;
    GLfloat g_vertex_buffer_data[10000];

    this->propeller_angle = 0;

    // cylinder construction

    float cy_x = 3.5f, cy_y = 3.5f, ang = 2*3.14159, x1 , y1;
    ang/=(float)(n);
    int ind = 0;

    for(int i=0;i<n;++i)
    {
        x1 = cy_x*cos(ang)-cy_y*sin(ang);
        y1 = cy_x*sin(ang)+cy_y*cos(ang);

        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = cy_y;
        g_vertex_buffer_data[ind++] = -0.2f;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = cy_y;
        g_vertex_buffer_data[ind++] = 0.2f;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = y1;
        g_vertex_buffer_data[ind++] = 0.2f;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = cy_y;
        g_vertex_buffer_data[ind++] = -0.2f;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = y1;
        g_vertex_buffer_data[ind++] = -0.2f;

        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = y1;
        g_vertex_buffer_data[ind++] = 0.2f;
        
        cy_x = x1;
        cy_y = y1;
    }

    float yex = 1.7f;

    GLfloat g_vertex_buffer_arr[] = {
        0.0f, 3.1f+yex, 0.0f,
       -1.0f, 5.1f+yex, 0.0f,
        1.0f, 5.1f+yex, 0.0f,

        0.0f, 4.1f+yex, 0.0f,
       -1.0f, 7.1f+yex, 0.0f,
        1.0f, 7.1f+yex, 0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES,6*n,g_vertex_buffer_data,COLOR_DARKRED,GL_FILL);
    this->arrow = create3DObject(GL_TRIANGLES,6,g_vertex_buffer_arr,COLOR_GOLD,GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->arrow);

    glm::mat4 rotate = glm::rotate((float)(this->propeller_angle*M_PI/180.0f),glm::vec3(0,0,1));
    Matrices.model *= (rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID,1,GL_FALSE,&MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Ring::tick() { 
    // handling the rotation of propeller
    this->propeller_angle -= 10;
}
