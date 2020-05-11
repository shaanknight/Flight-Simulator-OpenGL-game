#include "main.h"
#include "speedometer.h"

Speedometer::Speedometer(float x, float y, float z) {
    
    this->position = glm::vec3(x, y, z);

    GLfloat vertex_buffer_comp[] = {
        -0.15f, 0.0f, 0.0f,
         0.15f, 0.0f, 0.0f,
         0.0f, 0.8f, 0.0f,

        -0.15f, 0.0f, 0.0f,
         0.15f, 0.0f, 0.0f,
         0.0f, -0.8f, 0.0f,
    };

    float vertex_buffer_color[] = {
        
        0.0, 0.0, 0.0,
        0.36, 0.20, 0.09,
        0.36, 0.20, 0.09,

        0.0, 0.0, 0.0,
        0.36, 0.20, 0.09,
        0.0, 0.0, 0.0,

    };

    this->propeller_angle = 0;

    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_comp, vertex_buffer_color, GL_FILL);

    int n;
    n = 100;
    GLfloat g_vertex_buffer_data[100000];

    float cy_x = 0.9f, cy_y = 0.0f, ang = 2*3.14159, x1 , y1;
    ang/=(float)(n);
    int ind = 0;

    for(int i=0;i<n;++i)
    {
        x1 = cy_x*cos(ang)-cy_y*sin(ang);
        y1 = cy_x*sin(ang)+cy_y*cos(ang);

        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] =-0.2f;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = cy_y;
        g_vertex_buffer_data[ind++] =-0.2f;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = y1;
        g_vertex_buffer_data[ind++] =-0.2f;
        
        cy_x = x1;
        cy_y = y1;
    }

    cy_x = 0.8f, cy_y = 0, ang = 2*3.14159;
    ang/=(float)(n);

    for(int i=0;i<n;++i)
    {
        x1 = cy_x*cos(ang)-cy_y*sin(ang);
        y1 = cy_x*sin(ang)+cy_y*cos(ang);

        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] =-0.2f;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = cy_y;
        g_vertex_buffer_data[ind++] =-0.2f;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = y1;
        g_vertex_buffer_data[ind++] =-0.2f;
        
        cy_x = x1;
        cy_y = y1;
    }

    this->outerring = create3DObject(GL_TRIANGLES,(3*n)/2,g_vertex_buffer_data,COLOR_BROWN,GL_FILL);
    this->innerring = create3DObject(GL_TRIANGLES,(3*n)/2,g_vertex_buffer_data+9*n,COLOR_BACKGROUND,GL_FILL);
}

void Speedometer::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    //glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we want to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->outerring);
    draw3DObject(this->innerring);

    glm::mat4 rotate = glm::rotate((float)(-this->propeller_angle*M_PI/180.0f),glm::vec3(0,0,1));
    Matrices.model *= (rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID,1,GL_FALSE,&MVP[0][0]);
    draw3DObject(this->object);
}

void Speedometer::setdirection(float xc)
{
    float ang = xc*3;
    if(ang > 90)
        ang = 90;
    this->propeller_angle = ang;
}