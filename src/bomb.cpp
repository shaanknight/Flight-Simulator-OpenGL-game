#include "main.h"
#include "bomb.h"

Bomb::Bomb(float x, float y, float z) {

    this->position = glm::vec3(x, y, z);

    float cy_x = 0.3f,cy_y = 0.3f,x1,y1; 
    float ang = 2*3.14159;
    int n = 60,ind = 0;
    GLfloat g_vertex_buffer_data[10000];
    ang/=(float)(n);

    for(int i=0;i<n;++i)
    {
        x1 = cy_x*cos(ang)-cy_y*sin(ang);
        y1 = cy_x*sin(ang)+cy_y*cos(ang);

        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] =-0.9f;
        g_vertex_buffer_data[ind++] = cy_y;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = cy_y;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = y1;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] =-0.9f;
        g_vertex_buffer_data[ind++] = cy_y;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] =-0.9f;
        g_vertex_buffer_data[ind++] = y1;

        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = y1;
        
        cy_x = x1;
        cy_y = y1;
    }

    this->object = create3DObject(GL_TRIANGLES, 6*n, g_vertex_buffer_data,{43,53,12}, GL_FILL);

}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    //glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bomb::tick()
{
    this->position.y -= 0.3;
}

