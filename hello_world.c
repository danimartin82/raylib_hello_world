#include "raylib.h"

int main(void)
{
    // Window parameters
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Hello World");

    // Camera parameters
    Camera3D camera = { 0 };
    camera.position = (Vector3){ -50.0f, 50.0f, -50.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.type = CAMERA_PERSPECTIVE;                   // Camera mode type

    // Car parameters
    int carWidth=20.0f;
    int carHeight=20.0f;
    int carLenght=40.0f;
    Vector3 carPosition = { 0.0f, carHeight/2, 0.0f };
    
    Color carColor= MAROON;
    
    // Mirrors parameters
    int mirrorsWidth=carWidth*1.1f;
    int mirrorsHeight=1.0f;
    int mirrorsLenght=1.0f;
    Vector3 mirrorsPosition = { carPosition.x+carLenght/4, carHeight/2, 0.0f };
    Color mirrorsColor= BLUE;
     
    // Lines parameters
    int line_Width=0.1f;
    int line_Height=0.0f;
    int line_Length=60.0f;
    float step=1.0f;
    
    Vector3 start_line1 ={ -carLenght/2, 0.0f, carWidth/2 };
    Vector3 end_line1 =  { -carLenght/2-line_Length, 0.0f, carWidth/2 };
    Vector3 start_line2 ={ -carLenght/2, 0.0f, -carWidth/2 };
    Vector3 end_line2 =  { -carLenght/2-line_Length, 0.0f, -carWidth/2 };

    // Camera parameters
    Vector3 camera_R_pos=   { mirrorsPosition.x,mirrorsPosition.y,mirrorsPosition.z+mirrorsWidth/2};
    Vector3 camera_R_target={ mirrorsPosition.x-10.0f,mirrorsPosition.y,mirrorsPosition.z+mirrorsWidth/2};
    Vector3 camera_L_pos=   { mirrorsPosition.x,mirrorsPosition.y,mirrorsPosition.z-mirrorsWidth/2};
    Vector3 camera_L_target={ mirrorsPosition.x-10.0f,mirrorsPosition.y,mirrorsPosition.z-mirrorsWidth/2};

    // Set a free camera mode
    SetCameraMode(camera, CAMERA_FREE); 
    SetTargetFPS(60);

    
    while (!WindowShouldClose())
    {
        UpdateCamera(&camera);
        if (IsKeyDown('M')){ 
            // Left mirror
            camera.target = camera_L_target;
            camera.position = camera_L_pos;
        } 
        if (IsKeyDown('N')){ 
            // Right mirror
            camera.target = camera_R_target;
            camera.position = camera_R_pos;
        } 
        
        end_line2.z+=step;
        end_line1.z+=step;
        if  ((end_line2.z>=50.0f)||(end_line2.z<=-50.0f))
        {
            step=(-1.0f)*step;
        }
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                // Draw car
                DrawCube(carPosition, carLenght, carHeight, carWidth,carColor);
                DrawCube(mirrorsPosition, mirrorsLenght, mirrorsHeight, mirrorsWidth, mirrorsColor);
                //DrawSphere(camera_R_target, 1.0f, BLUE);   
                //DrawSphere(camera_R_pos, 1.0f, BLUE);  
                //DrawSphere(camera_L_target, 1.0f, BLUE);  
                //DrawSphere(camera_L_pos, 1.0f, BLUE);  
                // Draw line 1
                DrawLine3D(start_line1,end_line1,RED);   
                // Draw line 2
                DrawLine3D(start_line2,end_line2,RED);   
                
                
                DrawGrid(100, 5.0f);

            EndMode3D();

            DrawRectangle( 10, 10, 320, 153, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 153, BLUE);

            DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
            DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
            DrawText("- M to set camera to left mirror", 40, 100, 10, DARKGRAY);
            DrawText("- N to set camera to right mirror", 40, 120, 10, DARKGRAY);
            DrawFPS(10, 170);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}