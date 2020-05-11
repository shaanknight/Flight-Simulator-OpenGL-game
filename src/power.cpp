#include "power.h"
#include "main.h"

using namespace std;

Power::Power(float x,float y,float z)
{
	this->position = glm::vec3(x,y,z);

    int n;
    n = 60;
    GLfloat g_vertex_buffer_data[10000];

    float cy_x = 1.6f, cy_y = 1.6f, ang = 2*3.14159, x1 , y1;
    ang/=(float)(n);
    int ind = 0;
    int l_ind = 0;

    float cone_x = 0, cone_y = 0.0f, cone_z = 0.0f;

    cy_x = 1.6f, cy_y = 1.6f, ang = 2*3.14159;
    ang/=(float)(n);

    float zexx = 0.05f;

    for(int i=0;i<n;++i)
    {
        x1 = cy_x*cos(ang)-cy_y*sin(ang);
        y1 = cy_x*sin(ang)+cy_y*cos(ang);

        g_vertex_buffer_data[ind++] = cone_x;
        g_vertex_buffer_data[ind++] = cone_y;
        g_vertex_buffer_data[ind++] = cone_z-zexx;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = cy_y;
        g_vertex_buffer_data[ind++] = 0.0f-zexx;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = y1;
        g_vertex_buffer_data[ind++] = 0.0f-zexx;
        
        cy_x = x1;
        cy_y = y1;
    }

    this->inner_ring = create3DObject(GL_TRIANGLES,3*n,g_vertex_buffer_data,COLOR_BACKGROUND,GL_FILL);

    cy_x = 1.7f, cy_y = 1.7f, ang = 2*3.14159;
    ang/=(float)(n);

    zexx = 0.1f;

    for(int i=0;i<n;++i)
    {
        x1 = cy_x*cos(ang)-cy_y*sin(ang);
        y1 = cy_x*sin(ang)+cy_y*cos(ang);

        g_vertex_buffer_data[ind++] = cone_x;
        g_vertex_buffer_data[ind++] = cone_y;
        g_vertex_buffer_data[ind++] = cone_z-zexx;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = cy_y;
        g_vertex_buffer_data[ind++] = 0.0f-zexx;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = y1;
        g_vertex_buffer_data[ind++] = 0.0f-zexx;
        
        cy_x = x1;
        cy_y = y1;
    }

    this->outer_ring = create3DObject(GL_TRIANGLES,3*n,g_vertex_buffer_data+9*n,COLOR_DARKRED,GL_FILL);

    float dx = 0.6, dy = 2.3;
    GLfloat crossdata[] = {
        -dx, dy, 0.0f,
         dx, dy, 0.0f,
        -dx,-dy, 0.0f,

         dx, dy, 0.0f,
        -dx,-dy, 0.0f,
         dx,-dy, 0.0f,

        -dy, dx, 0.0f,
         dy, dx, 0.0f,
        -dy,-dx, 0.0f,

         dy, dx, 0.0f,
        -dy,-dx, 0.0f,
         dy,-dx, 0.0f,
    };

    this->cross = create3DObject(GL_TRIANGLES,12,crossdata,COLOR_DARKRED,GL_FILL);
}

void Power::draw(glm::mat4 VP) {
    //std::cout << this->position[1] << endl;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    //glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    draw3DObject(this->outer_ring);
    draw3DObject(this->inner_ring);
    draw3DObject(this->cross);
    //std::cout << this->position[1] << endl;
}

void Power::tick() {
    this->position.y -= 0.03;
}