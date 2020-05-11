#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x_pos, float y_pos, float z_pos) {
    this->position = glm::vec3(x_pos, y_pos, z_pos);

    int n,ind = 0;
    n = 60;
    GLfloat g_vertex_buffer_data[10000];

    float x = 2.5f, y = 2.5f, ang = 2*3.14159, x1 , y1;
    ang/=(float)(n);
    for(int i=0;i<n;++i)
    {
        x1 = x*cos(ang)-y*sin(ang);
        y1 = x*sin(ang)+y*cos(ang);
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = 3.0f;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = x;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = y;
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = y1;
        x = x1;
        y = y1;
    }

    float colordata[10000];
    ind = 0;

    for(int i=0;i<n;++i)
    {
        colordata[ind++] = 0.89f;
        colordata[ind++] = 0.81f;
        colordata[ind++] = 0.34f;
        colordata[ind++] = 1.0f;
        colordata[ind++] = 0.15f;
        colordata[ind++] = 0.09f;
        colordata[ind++] = 1.0f;
        colordata[ind++] = 0.15f;
        colordata[ind++] = 0.09f;
    }

    this->object = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, colordata, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}