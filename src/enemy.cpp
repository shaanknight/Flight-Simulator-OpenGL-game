#include "main.h"
#include "enemy.h"

Enemy::Enemy(float x, float y, float z) {

    this->position = glm::vec3(x, y, z);
    
    GLfloat vertex_buffer_data1[] = {
        -0.5f,-0.5f,-0.5f, // triangle 1 : begin
        -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f, // triangle 1 : end
        0.5f, 0.5f,-0.5f, // triangle 2 : begin
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f, // triangle 2 : end
        0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f, 0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,
        0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        0.5f,-0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f, 0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f,-0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f,-0.5f, 0.5f,
    };

    this->ucube = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data1, COLOR_ORANGE, GL_FILL);

    int n,ind = 0;
    n = 60;
    GLfloat g_vertex_buffer_data[10000];

    x = 3.0f, y = 3.0f;
    float ang = 2*3.14159,x1 , y1;
    ang/=(float)(n);
    for(int i=0;i<n;++i)
    {
        x1 = x*cos(ang)-y*sin(ang);
        y1 = x*sin(ang)+y*cos(ang);
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] =-3.9f;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = x;
        g_vertex_buffer_data[ind++] =-3.9f;
        g_vertex_buffer_data[ind++] = y;
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] =-3.9f;
        g_vertex_buffer_data[ind++] = y1;
        x = x1;
        y = y1;
    }

    float colordata[10000];
    ind = 0;

    for(int i=0;i<n;++i)
    {
        colordata[ind++] = 0.0f;
        colordata[ind++] = 0.0f;
        colordata[ind++] = 0.0f;
        colordata[ind++] = 0.5f;
        colordata[ind++] = 0.5f;
        colordata[ind++] = 0.5f;
        colordata[ind++] = 0.0f;
        colordata[ind++] = 0.0f;
        colordata[ind++] = 0.0f;
    }

    this->carpet = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, colordata, GL_FILL);

    float cy_x = 1.0f, cy_y = 1.0f; 
    ang = 2*3.14159;
    ang/=(float)(n);

    for(int i=0;i<n;++i)
    {
        x1 = cy_x*cos(ang)-cy_y*sin(ang);
        y1 = cy_x*sin(ang)+cy_y*cos(ang);

        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] =-2.0f;
        g_vertex_buffer_data[ind++] = cy_y;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = cy_y;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = y1;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = -2.0f;
        g_vertex_buffer_data[ind++] = cy_y;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = -2.0f;
        g_vertex_buffer_data[ind++] = y1;

        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = 0.0f;
        g_vertex_buffer_data[ind++] = y1;
        
        cy_x = x1;
        cy_y = y1;
    }

    this->cylinder = create3DObject(GL_TRIANGLES, 6*n, g_vertex_buffer_data+9*n, COLOR_BLACK, GL_FILL);

    cy_x = 1.5f; cy_y = 1.5f; 
    ang = 2*3.14159;
    ang/=(float)(n);

    for(int i=0;i<n;++i)
    {
        x1 = cy_x*cos(ang)-cy_y*sin(ang);
        y1 = cy_x*sin(ang)+cy_y*cos(ang);

        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] =-3.9f;
        g_vertex_buffer_data[ind++] = cy_y;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] =-2.0f;
        g_vertex_buffer_data[ind++] = cy_y;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] =-2.0f;
        g_vertex_buffer_data[ind++] = y1;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] =-3.9f;
        g_vertex_buffer_data[ind++] = cy_y;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] =-3.9f;
        g_vertex_buffer_data[ind++] = y1;

        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] =-2.0f;
        g_vertex_buffer_data[ind++] = y1;
        
        cy_x = x1;
        cy_y = y1;
    }

    this->lcube = create3DObject(GL_TRIANGLES, 6*n, g_vertex_buffer_data+27*n, COLOR_BROWN, GL_FILL);

}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    //glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->carpet);
    draw3DObject(this->cylinder);
    draw3DObject(this->lcube);
    draw3DObject(this->ucube);
}

