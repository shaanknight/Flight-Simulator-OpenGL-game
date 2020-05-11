#include "ball.h"
#include "main.h"

Ball::Ball(float x,float y,float z)
{
	// local rotation matrix declaration
	this->local_rotation = glm::mat4(1.0f);
    this->speed = 0;

	this->position = glm::vec3(x,y,z);
    /*this->velocity = glm::vec3(0,0,0);
    this->acceleration = glm::vec3(0,0,0);*/

    int n;
    n = 100;
    GLfloat g_vertex_buffer_data[100000],g_vertex_buffer_data_fin[500];

    // cylinder construction

    float cy_x = 1.0f, cy_y = 1.0f, ang = 2*3.14159, x1 , y1;
    ang/=(float)(n);
    int ind = 0;

    for(int i=0;i<n;++i)
    {
        x1 = cy_x*cos(ang)-cy_y*sin(ang);
        y1 = cy_x*sin(ang)+cy_y*cos(ang);

        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = cy_y;
        g_vertex_buffer_data[ind++] = -2.0f;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = cy_y;
        g_vertex_buffer_data[ind++] = 2.0f;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = y1;
        g_vertex_buffer_data[ind++] = 2.0f;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = cy_y;
        g_vertex_buffer_data[ind++] = -2.0f;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = y1;
        g_vertex_buffer_data[ind++] = -2.0f;

        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = y1;
        g_vertex_buffer_data[ind++] = 2.0f;
        
        cy_x = x1;
        cy_y = y1;
    }

    // cone construction
    float cone_x = 0, cone_y = 0, cone_z = -4.0f;

    cy_x = 1.0f, cy_y = 1.0f, ang = 2*3.14159;
    ang/=(float)(n);

    for(int i=0;i<n;++i)
    {
        x1 = cy_x*cos(ang)-cy_y*sin(ang);
        y1 = cy_x*sin(ang)+cy_y*cos(ang);

        g_vertex_buffer_data[ind++] = cone_x;
        g_vertex_buffer_data[ind++] = cone_y;
        g_vertex_buffer_data[ind++] = cone_z;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = cy_y;
        g_vertex_buffer_data[ind++] = -2.0f;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = y1;
        g_vertex_buffer_data[ind++] = -2.0f;
        
        cy_x = x1;
        cy_y = y1;
    }

    // propeller construction

    float prop_x = 0, prop_y = 0, prop_z = 2.5f;

    this->propeller_angle = 0;

    int m = 4;

    cy_x = 2.0f, cy_y = 2.0f, ang = 2*3.14159;
    ang/=(float)(m);

    for(int i=0;i<m;++i)
    {
        x1 = cy_x*cos(ang/4)-cy_y*sin(ang/4);
        y1 = cy_x*sin(ang/4)+cy_y*cos(ang/4);

        g_vertex_buffer_data[ind++] = prop_x;
        g_vertex_buffer_data[ind++] = prop_y;
        g_vertex_buffer_data[ind++] = prop_z;
        
        g_vertex_buffer_data[ind++] = cy_x;
        g_vertex_buffer_data[ind++] = cy_y;
        g_vertex_buffer_data[ind++] = prop_z;
        
        g_vertex_buffer_data[ind++] = x1;
        g_vertex_buffer_data[ind++] = y1;
        g_vertex_buffer_data[ind++] = prop_z;

        x1 = cy_x*cos(ang)-cy_y*sin(ang);
        y1 = cy_x*sin(ang)+cy_y*cos(ang);
        
        cy_x = x1;
        cy_y = y1;
    }

    // fins construction

    int f_ind = 0;

    // front fin

    float zex = 1;

    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0-zex;

    g_vertex_buffer_data_fin[f_ind++] = 2.5f;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = -1-zex;

    g_vertex_buffer_data_fin[f_ind++] = -2.5f;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = -1-zex;

    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0-zex;

    g_vertex_buffer_data_fin[f_ind++] = 2.5f;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = -1-zex;

    g_vertex_buffer_data_fin[f_ind++] = 3.0f;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0-zex;

    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0-zex;

    g_vertex_buffer_data_fin[f_ind++] = -2.5f;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = -1-zex;

    g_vertex_buffer_data_fin[f_ind++] = -3.0f;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0-zex;

    // backfin

    float xex = 1.0f;
    zex = 1.0f;

    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0.0+zex;

    g_vertex_buffer_data_fin[f_ind++] = 2.5f+xex;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = -1+zex;

    g_vertex_buffer_data_fin[f_ind++] = -2.5f-xex;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = -1.0+zex;

    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0.0+zex;

    g_vertex_buffer_data_fin[f_ind++] = 2.5f+xex;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = -1.0+zex;

    g_vertex_buffer_data_fin[f_ind++] = 3.0f+xex;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0.0+zex;

    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0+zex;

    g_vertex_buffer_data_fin[f_ind++] = -2.5f-xex;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = -1+zex;

    g_vertex_buffer_data_fin[f_ind++] = -3.0f-xex;
    g_vertex_buffer_data_fin[f_ind++] = 0;
    g_vertex_buffer_data_fin[f_ind++] = 0+zex;

    this->object = create3DObject(GL_TRIANGLES,6*n,g_vertex_buffer_data,COLOR_GREY,GL_FILL);
    this->head = create3DObject(GL_TRIANGLES,3*n,g_vertex_buffer_data+18*n,COLOR_BLACK,GL_FILL);
    this->propeller = create3DObject(GL_TRIANGLES,3*m,g_vertex_buffer_data+27*n,COLOR_BLACK,GL_FILL);
    this->fin = create3DObject(GL_TRIANGLES,18,g_vertex_buffer_data_fin,COLOR_BLACK,GL_FILL);

}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*this->local_rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->head);
    draw3DObject(this->fin);

    glm::mat4 rotate = glm::rotate((float)(this->propeller_angle*M_PI/180.0f),glm::vec3(0,0,1));
    Matrices.model *= (rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID,1,GL_FALSE,&MVP[0][0]);
    draw3DObject(this->propeller);
}

void Ball::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::tick() { 
    // handling the rotation of propeller
    this->propeller_angle -= 20;
    this->position -= glm::vec3(this->local_rotation[2][0]*this->speed,
            this->local_rotation[2][1]*this->speed,this->local_rotation[2][2]*this->speed);
    if(this->speed > 0.1)
        this->speed -= 1;
    else
        this->speed = 0;
}