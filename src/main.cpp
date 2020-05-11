#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"
#include "ring.h"
#include "parachute.h"
#include "island.h"
#include "volcano.h"
#include "compass.h"
#include "speedometer.h"
#include "altitude.h"
#include "height.h"
#include "bullet.h"
#include "enemy.h"
#include "bomb.h"
#include "power.h"

using namespace std;

#define ll long long
#define pb push_back

GLMatrices Matrices;
GLMatrices Matrices2;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball plane;
Sea sea;
vector<Ring> vec_ring;
vector<Parachute> vec_par;
vector<Island> vec_isl;
vector<Volcano> vec_voc;
Compass compass;
Speedometer speedometer;
Altitude altitude,fuel,health;
vector<Height> vec_height;
vector<Height> vec_fuel;
vector<Bullet> vec_bul;
vector<Bullet> enm_bul;
vector<Enemy> vec_enm;
vector<Bomb> vec_bom;
vector<Height> vec_health;
vector<Power> vec_pow;

float amt_fuel = 10;
ll steps = 0, cnt_bull = 0, cnt_bomb = 0, loop_signal = 0, barrel_signal = 0, amt_health = 1000;
ll cnt_enm_bul = 0;
double curx,cury,prevx,prevy,helix,heliy;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, loop_start_time = 0;
float camera_rotation_angle = 0;
int points = 0;

Timer t60(1.0 / 60);

glm::vec3 eye,target,up;
int camera_option = 0;

double music_spawn_time = 0.0, bomb_spawn_time = 0.0;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    /* boilerplate references 

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    */

    if(camera_option == 0)
    {
        eye = glm::vec3(plane.position.x , plane.position.y + 10, plane.position.z + 20);
        target = glm::vec3(plane.position.x ,plane.position.y ,plane.position.z);
        up = glm::vec3(0, 1, 0);
    }
    else if(camera_option == 1)
    {
        ll pers = 20;
        eye = plane.position + glm::vec3(pers*plane.local_rotation[2][0],
            pers*plane.local_rotation[2][1],pers*plane.local_rotation[2][2]) +
            glm::vec3(pers*plane.local_rotation[1][0],
            pers*plane.local_rotation[1][1],pers*plane.local_rotation[1][2]);
        target = glm::vec3(plane.position.x,plane.position.y,plane.position.z);
        up = glm::vec3(0,1,0);
    }
    else if(camera_option == 2)
    {
        ll pers = 100, ahd = 5;
        eye = glm::vec3(plane.position.x,plane.position.y,plane.position.z)
            - glm::vec3(ahd*plane.local_rotation[2][0],
            ahd*plane.local_rotation[2][1],ahd*plane.local_rotation[2][2]);
        target = plane.position - glm::vec3(pers*plane.local_rotation[2][0],
            pers*plane.local_rotation[2][1],pers*plane.local_rotation[2][2]);
        up = glm::vec3(0,1,0);
    }
    else if(camera_option == 3)
    {
        ll pers = 20;
        eye = plane.position + glm::vec3(2*plane.local_rotation[2][0],
            2*plane.local_rotation[2][1],2*plane.local_rotation[2][2])
            + glm::vec3(pers*plane.local_rotation[1][0],
            pers*plane.local_rotation[1][1],pers*plane.local_rotation[1][2]);
        target = glm::vec3(plane.position.x,plane.position.y,plane.position.z);
        up = glm::vec3(0,1,0);
    }
    else if(camera_option == 4)
    {
        ll pers = 20;
        eye = plane.position + glm::vec3(pers*plane.local_rotation[2][0],
            pers*plane.local_rotation[2][1],pers*plane.local_rotation[2][2]) +
            glm::vec3(pers*plane.local_rotation[1][0],
            pers*plane.local_rotation[1][1],pers*plane.local_rotation[1][2]) +
            glm::vec3(pers*plane.local_rotation[0][0],
            pers*plane.local_rotation[0][1],pers*plane.local_rotation[0][2]);
        target = glm::vec3(plane.position.x,plane.position.y,plane.position.z);
        up = glm::vec3(0,1,0);
    }
    else if(camera_option == 5)
    {
        glfwGetCursorPos(window,&curx,&cury);
        helix += 0.15f*(curx-prevx);
        heliy += 0.15f*(cury-prevy);
        prevx = curx;
        prevy = cury;

        float ang = 3.14159;

        eye = glm::vec3(plane.position.x+10*cos(helix*ang/180.0f)*sin(heliy*ang/180.0f),
                        plane.position.y+10*cos(heliy*ang/180.0f),
                        plane.position.z+18*sin(helix*ang/180.0f)*sin(heliy*ang/180.0f));
        target = glm::vec3(plane.position.x,plane.position.y,plane.position.z);
        up = glm::vec3(0,1,0);
    }


    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); 
    Matrices2.view = glm::lookAt(glm::vec3(0,0,4), glm::vec3(0,0,3), glm::vec3(0,1,0) );// Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP2 = Matrices2.projection * Matrices2.view;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    plane.draw(VP);
    sea.draw(VP);
    for(auto v:vec_ring)
        v.draw(VP);
    for(auto v:vec_par)
        v.draw(VP);
    for(auto v:vec_isl)
        v.draw(VP);
    for(auto v:vec_voc)
        v.draw(VP);
    compass.draw(VP2);
    speedometer.draw(VP2);
    altitude.draw(VP2);
    fuel.draw(VP2);
    health.draw(VP2);
    for(ll i=0;i<(plane.position.y+10)/2;++i)
    {
        vec_height[i].draw(VP2);
        if(i == vec_height.size()-1)
            break;
    }
    for(ll i=0;i<amt_fuel;++i)
        vec_fuel[i].draw(VP2);
    for(ll i=0;i<(50+amt_health)/100;++i)
        vec_health[i].draw(VP2);
    for(auto v:vec_bul)
        v.draw(VP);
    for(auto v:vec_enm)
        v.draw(VP);
    for(auto v:vec_bom)
        v.draw(VP);
    for(auto v:enm_bul)
        v.draw(VP);
    for(auto v:vec_pow)
        v.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (left) {
        // Do something
    }

    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int fwd = glfwGetKey(window, GLFW_KEY_UP);
    int bkd = glfwGetKey(window, GLFW_KEY_DOWN);
    int x = glfwGetKey(window, GLFW_KEY_X);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int f1 = glfwGetKey(window, GLFW_KEY_F1);
    int f2 = glfwGetKey(window, GLFW_KEY_F2);
    int f3 = glfwGetKey(window, GLFW_KEY_F3);
    int f4 = glfwGetKey(window, GLFW_KEY_F4);
    int f5 = glfwGetKey(window, GLFW_KEY_F5);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int l = glfwGetKey(window, GLFW_KEY_L);
    int k = glfwGetKey(window, GLFW_KEY_K);

    // camera controls

    if(f1)
    {
        // Follow-cam view
        camera_option = 1;
    }
    if(f2)
    {
        // Plane view
        camera_option = 2;
    }
    if(f3)
    {
        // Top view
        camera_option = 3;
    }
    if(f4)
    {
        // Tower view
        camera_option = 4;
    }
    if(f5)
    {
        // Camera view
        camera_option = 5;
    }

    // movement about y axis

    if(a){
        plane.local_rotation = glm::rotate((float)(0.5f*M_PI/180.0f),
                    glm::vec3(plane.local_rotation[1][0],plane.local_rotation[1][1],
                    plane.local_rotation[1][2]))*plane.local_rotation;
    }

    if(d){
        plane.local_rotation = glm::rotate((float)(-0.5f*M_PI/180.0f),
                    glm::vec3(plane.local_rotation[1][0],plane.local_rotation[1][1],
                    plane.local_rotation[1][2]))*plane.local_rotation;
    }

    // movement about x axis

    if(w){
        plane.local_rotation = glm::rotate((float)(0.5f*M_PI/180.0f),
                    glm::vec3(plane.local_rotation[0][0],plane.local_rotation[0][1],
                    plane.local_rotation[0][2]))*plane.local_rotation;
    }

    if(s){
        plane.local_rotation = glm::rotate((float)(-0.5f*M_PI/180.0f),
                    glm::vec3(plane.local_rotation[0][0],plane.local_rotation[0][1],
                    plane.local_rotation[0][2]))*plane.local_rotation;
    }

    // movement in forward and backward direction

    if(fwd){
        amt_fuel -= 0.002;
        plane.position -= glm::vec3(plane.local_rotation[2][0]*0.5,
            plane.local_rotation[2][1]*0.5,plane.local_rotation[2][2]*0.5);
    }
    if(bkd){
        amt_fuel -= 0.002;
        plane.position += glm::vec3(plane.local_rotation[2][0]*0.5,
            plane.local_rotation[2][1]*0.5,plane.local_rotation[2][2]*0.5);
    }

    // movement about z direction

    if(x){
        plane.local_rotation = glm::rotate((float)(0.5f*M_PI/180.0f),
                    glm::vec3(plane.local_rotation[2][0],plane.local_rotation[2][1],
                    plane.local_rotation[2][2]))*plane.local_rotation;
    }
    if(c){
        plane.local_rotation = glm::rotate((float)(-0.5f*M_PI/180.0f),
                    glm::vec3(plane.local_rotation[2][0],plane.local_rotation[2][1],
                    plane.local_rotation[2][2]))*plane.local_rotation;
    }

    // acceleration of plane

    if(space)
    {
        amt_fuel -= 0.4f;
        plane.speed += 5;
    }

    // bullet firing

    if(f)
    {
        cnt_bull++;
        if(cnt_bull > 4)
        {
            vec_bul.pb(Bullet(plane.position.x - plane.local_rotation[2][0]*2,
                          plane.position.y - plane.local_rotation[2][1]*2,
                          plane.position.z - plane.local_rotation[2][2]*2,
                          COLOR_GOLD,glm::vec3(plane.local_rotation[2][0]*5,
                          plane.local_rotation[2][1]*5,
                          plane.local_rotation[2][2]*5)));
            cnt_bull = 0;
            if(time(NULL)-music_spawn_time>2.0)
            {
                music_spawn_time = time(NULL);
                system("aplay -q bullet_music.wav&");
            }
        }
    }

    // bullet firing

    if(b)
    {
        cnt_bomb++;
        if(cnt_bomb > 2)
        {
            vec_bom.pb(Bomb(plane.position.x,plane.position.y,plane.position.z));
            cnt_bomb = 0;
        }
    }

    // loop-a-loop

    if(l)
        loop_signal = 1;

    // barrel-roll

    if(k)
        barrel_signal = 1;

}

void tick_elements() {
    plane.tick();
    for(auto v:vec_ring)
        v.tick();
    for(ll i=0;i<2000;++i)
        vec_par[i].tick();
    compass.setdirection(plane.local_rotation[2][2],plane.local_rotation[2][0]);
    speedometer.setdirection(plane.speed);
    for(ll i=0;i<vec_bul.size();++i)
        vec_bul[i].tick();
    for(ll i=0;i<vec_bom.size();++i)
        vec_bom[i].tick();
    for(ll i=0;i<enm_bul.size();++i)
        enm_bul[i].tick();
    for(ll i=0;i<vec_pow.size();++i)
        vec_pow[i].tick();
    //camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane      = Ball(0.0f, 0.0f, -2.0f);
    sea        = Sea(0.0f, 0.0f, 0.0f);

    for(ll i=1;i<=40;++i)
        vec_ring.pb(Ring(rand()%100-rand()%100,2.0f,rand()%(5)-80*i));

    for(ll i=1;i<=2000;++i)
        vec_par.pb(Parachute(rand()%100-rand()%100,10.0f+i,rand()%5-40*i));

    for(ll i=1;i<=20;++i)
        vec_pow.pb(Power(rand()%100-rand()%100,10.0f+i,rand()%(50)-200*i));

    for(ll i=1;i<=20;++i)
        vec_isl.pb(Island(rand()%100-rand()%100,-3.0f,rand()%(5)-200*i));

    for(ll i=1;i<=20;++i)
        vec_voc.pb(Volcano(rand()%100-rand()%100,-3.0f,100+rand()%(5)-200*i));

    for(ll i=1;i<=20;++i)
        vec_enm.pb(Enemy(vec_ring[2*i-1].position.x,vec_ring[2*i-1].position.y,
                    vec_ring[2*i-1].position.z-10));

    for(ll i=1;i<=10;++i)
    {
        vec_height.pb(Height(-3,-3.9+(i-1)*0.2,4,COLOR_RED));
        vec_fuel.pb(Height(-2.3,-3.9+(i-1)*0.2,4,COLOR_LITEYELLOW));
        vec_health.pb(Height(-1.6,-3.9+(i-1)*0.2,4,COLOR_GREEN));
    }

    compass = Compass(-3,3,4);
    speedometer = Speedometer(3,-3,4);
    altitude = Altitude(-3,-3,4);
    fuel = Altitude(-2.3,-3,4);
    health = Altitude(-1.6,-3,4);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices2.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

float distance(glm::vec3 pos1,glm::vec3 pos2)
{
    return (pos1.x-pos2.x)*(pos1.x-pos2.x) + 
           (pos1.y-pos2.y)*(pos1.y-pos2.y) +
           (pos1.z-pos2.z)*(pos1.z-pos2.z);
}

float distance2D(glm::vec3 pos1,glm::vec3 pos2)
{
    return (pos1.x-pos2.x)*(pos1.x-pos2.x) +
           (pos1.z-pos2.z)*(pos1.z-pos2.z);
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    ll bc = 0;

    window = initGLFW(width, height);

    initGL (window, width, height);
    double strt_time = time(NULL);
    pid_t pl;
    system("aplay -q ChillingMusic.wav&");

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if(time(NULL)-strt_time > 28.0)
        {
            strt_time = time(NULL);
            system("aplay -q ChillingMusic.wav&");
        }

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // handling loop a loop movements

            if(loop_signal)
            {
                loop_signal++;
                amt_fuel -= 0.002;
                plane.position -= glm::vec3(plane.local_rotation[2][0]*0.5,
                    plane.local_rotation[2][1]*0.5,plane.local_rotation[2][2]*0.5);
                plane.local_rotation = glm::rotate((float)(0.5f*M_PI/180.0f),
                    glm::vec3(plane.local_rotation[0][0],plane.local_rotation[0][1],
                    plane.local_rotation[0][2]))*plane.local_rotation;
                if(loop_signal>720)
                    loop_signal = 0;
            }

            // handling barrel roll movements

            if(barrel_signal)
            {
                barrel_signal++;
                plane.local_rotation = glm::rotate((float)(0.5f*M_PI/180.0f),
                    glm::vec3(plane.local_rotation[2][0],plane.local_rotation[2][1],
                    plane.local_rotation[2][2]))*plane.local_rotation;
                if(barrel_signal>720)
                    barrel_signal = 0;
            }

            if(amt_fuel <= 0 || amt_health <= 0 || plane.position.y <= -4)
                quit(window);

            tick_elements();
            tick_input(window);

            // enemy firing at plane

            for(ll i=0;i<vec_enm.size();++i)
            {
                Enemy v = vec_enm[i];
                cnt_enm_bul++;
                if(cnt_enm_bul >= 20 && v.position.z<plane.position.z
                    && abs(v.position.z-plane.position.z)<=200)
                {
                    enm_bul.pb(Bullet(v.position.x,v.position.y-4,v.position.z,
                               {43,53,12},glm::vec3(0.04*(v.position.x-plane.position.x),
                                          0.04*(v.position.y-4-plane.position.y),
                                          0.04*(v.position.z-plane.position.z))));
                    //cout << i << endl;
                    //cout << v.position.x << " " << v.position.z << endl;
                    cnt_enm_bul = 0;
                    break;
                }
                else if(v.position.z<plane.position.z)
                    break;
            }

            // collision of plane with parachute

            for(ll i=0;i<vec_par.size();++i)
            {
                if(distance(vec_par[i].position,plane.position)<4.5*4.5)
                {
                    amt_health -= 50;
                    cout << "Health decreases to : " << amt_health << endl;
                    vec_par[i].position.y -= 100;
                }
            }

            // collision of bullet with parachute

            for(ll i=0;i<vec_par.size();++i)
            {
                for(ll j=0;j<vec_bul.size();++j)
                {
                    if(distance(vec_par[i].position,vec_bul[j].position)<9.0)
                    {
                        vec_par[i].position.y -= 100;
                        vec_bul[j].position.y -= 100;
                        points += 20;
                        cout << "\n You get 20 points for that. \n";
                    }
                }
            }

            // collision of bullet with checkpoint enemy

            for(ll i=0;i<vec_enm.size();++i)
            {
                for(ll j=0;j<vec_bul.size();++j)
                {
                    if(distance(vec_enm[i].position,vec_bul[j].position)<9.0)
                    {
                        vec_enm[i].position.y -= 100;
                        vec_enm[i].position.z += 1000;
                        vec_bul[j].position.y -= 100;
                        points += 30;
                        cout << "\n You get 30 points for that. \n";
                    }
                }
            }

            // collision of enemy_bullet with plane

            for(ll i=0;i<enm_bul.size();++i)
            {
                if(distance(enm_bul[i].position,plane.position)<9.0)
                {
                    enm_bul[i].position.y -= 100;
                    amt_health -= 10;
                    cout << "\n That must have hurt \n";
                }
            }

            // collision of volcano with plane

            for(ll i=0;i<vec_voc.size();++i)
            {
                if(distance(vec_voc[i].position,plane.position)<65)
                {
                    vec_voc[i].position.y -= 100;
                    amt_health -= 20;
                    cout << "\n That burns . Don't go in close proximity to the volcano \n";
                }
            }

            // collision of bomb with island

            for(ll i=0;i<vec_bom.size();++i)
            {
                for(ll j=0;j<vec_isl.size();++j)
                {
                    if(abs(vec_bom[i].position.y - vec_isl[j].position.y) < 0.5f
                        && distance2D(vec_isl[j].position,vec_bom[i].position)<200.0f)
                    {
                        if(time(NULL)-bomb_spawn_time>2.0)
                        {
                            bomb_spawn_time = time(NULL);
                            system("aplay -q bomb.wav&");
                        }
                        vec_isl[j].position.y -= 100;
                        vec_bom[i].position.y -= 100;
                    }
                }
            }

            // collision of bomb with enemy

            for(ll i=0;i<vec_bom.size();++i)
            {
                for(ll j=0;j<vec_enm.size();++j)
                {
                    if(abs(vec_bom[i].position.y - vec_enm[j].position.y) < 0.5f
                        && distance2D(vec_enm[j].position,vec_bom[i].position)<200.0f)
                    {
                        if(time(NULL)-bomb_spawn_time>2.0)
                        {
                            bomb_spawn_time = time(NULL);
                            system("aplay -q bomb.wav&");
                        }
                        vec_enm[j].position.y -= 100;
                        vec_enm[j].position.z += 1000;
                        vec_bom[i].position.y -= 100;
                    }
                }
            }

            // collision of plane with ring

            for(ll i=0;i<vec_ring.size();++i)
            {
                glm::vec3 pr = vec_ring[i].position;
                glm::vec3 pp = plane.position;
                if(abs(plane.position.z-vec_ring[i].position.z)<=2 &&
                    5-sqrt((pr.x-pp.x)*(pr.x-pp.x)+(pr.y-pp.y)*(pr.y-pp.y))<=2)
                {
                    vec_ring[i].position.z += 1000;
                    amt_health -= 20;
                    cout << "\n You destroyed the ring :( \n " << i 
                     << "  Now u lose ur health value by 20 \n ";
                     break;
                }
            }

            // collision of plane with health cards/power ups

            /*for(ll i=0;i<vec_pow.size();++i)
            {
                glm::vec3 pr = vec_pow[i].position;
                glm::vec3 pp = plane.position;
                cout << i << endl;
                if(abs(plane.position.z-vec_pow[i].position.z)<=0.2f &&
                    sqrt((pr.x-pp.x)*(pr.x-pp.x)+(pr.y-pp.y)*(pr.y-pp.y))<=2.5f)
                {
                    vec_pow[i].position.z += 10;
                    amt_health += 200;
                    cout << "\n You get a boost of 200 health \n ";
                    break;
                }
                cout << i << endl;
            }*/

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices2.projection = glm::ortho(left, right, bottom, top);
    Matrices.projection = glm::perspective(1.0f, 1.0f, 1.0f, 500.0f);
}
