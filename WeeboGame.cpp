#include"raylib.h"


struct AnimData
{
    Rectangle REC;
    Vector2 POS;
    int Frame;
    float UpdateTime;
    float RunningTime;
};

//checking if the player is on the ground  
bool isOnGround(AnimData data,int WindowHeight)
{
    return data.POS.y>=WindowHeight - data.REC.height;
}


//update Weebo character animation frame
AnimData UpdateWeeboAnimation(AnimData data,float DeltaTime)
{
       //update running time 
        data.RunningTime+=DeltaTime;

        if(data.RunningTime>=data.UpdateTime)
        {

            data.RunningTime=0.0;

            //update animation frame
            data.REC.x = data.Frame * data.REC.width;

            data.Frame++;

            if(data.Frame > 5)
            {

            data.Frame = 0 ;

            }

        }

        return data;
}

//update Killshot character animation frame
AnimData UpdateKillshotAnimation(AnimData data,float DeltaTime,int KillshotsaVel)
{
        
        data.POS.x += KillshotsaVel*DeltaTime;

        data.RunningTime+=DeltaTime;

        if(data.RunningTime >= data.UpdateTime)
        {

            data.RunningTime=0.0;

            data.REC.x = data.Frame * data.REC.width;

            data.Frame++;

            if(data.Frame > 4)
            {
                data.Frame = 0;
            }

        }

        return data;
}

//background animation looping
float BackGroundLooping(Texture2D data,float GX)
{
    if(GX<= - data.width*2)
     {
        GX = 0.0;
     }
        return GX;
}

//back ground update Drawing function
Texture2D BackGroundDrawing(Texture2D data ,float GX)
{
        Vector2 XPos ={GX, 0.0};
        
        DrawTextureEx(data, XPos,0.0 ,2.0,WHITE);
        
        Vector2 XPos2{GX +  data.width * 2, 0.0};

        DrawTextureEx(data, XPos2, 0.0, 2.0,WHITE);  

        GX=BackGroundLooping( data, GX);

        return data;
}


int main()
{

    // window dimension 
    const int WindowWidth=512;
    const int WindowHight=380;

    // initilaize the window
    InitWindow(WindowWidth,WindowHight,"WeeboVOX");
    
    // acceleration due to gravity (pexels/sec)/frame
    const int  Gravity{1000};

    // Weebo Variables
    Texture2D Weebo = LoadTexture("textures/Run.png");

    AnimData WEEBO;
    WEEBO.REC.width=Weebo.width/8;
    WEEBO.REC.height=Weebo.height;
    WEEBO.REC.x=0;
    WEEBO.REC.y=0;
    WEEBO.POS.x=WindowWidth/2 - WEEBO.REC.width/2;
    WEEBO.POS.y=WindowHight-WEEBO.REC.height;
    WEEBO.Frame=0;
    WEEBO.UpdateTime=1.0/12.0;
    WEEBO.RunningTime=0;

    // the number of killshots
    int KillshotsCount=20;
    // the space bitween every killshot
    int Space{};

    Texture2D killshot = LoadTexture("textures/Killshot.png");

    AnimData Killshots[KillshotsCount]={};

    //for creating too many killshots
    for (int i= 0; i < KillshotsCount; i++)
    {

        Killshots[i].REC.width = killshot.width / 5;
        Killshots[i].REC.height =  killshot.height;
        Killshots[i].REC.x = 0;
        Killshots[i].REC.y = 0;
        Killshots[i].POS.x = WindowWidth+Space; 
        Killshots[i].POS.y = WindowHight - Killshots[i].REC.height + 30;
        Killshots[i].Frame = 0;
        Killshots[i].RunningTime =0.0;
        Killshots[i].UpdateTime = 1.0/12.0;
        Space+=300;
        
    }
    //the finishing line for the wining
    float FinishLine{ Killshots[KillshotsCount-1].POS.x};
    
    Texture2D Background = LoadTexture("textures/1.png");

    Texture2D Background2 = LoadTexture("textures/2.png");

    Texture2D Background3 = LoadTexture("textures/3.png");
    
    Texture2D Background4 = LoadTexture("textures/4.png");

    Texture2D Background5 = LoadTexture("textures/5.png");

    Texture2D Background6 = LoadTexture("textures/6.png");

    Texture2D Background7 = LoadTexture("textures/8.png");

    Texture2D Background8 = LoadTexture("textures/9.png");

   


    // Killshots X Velocity pexl/sec
    int KillshotsaVel{-200};

    // check the Rectangle is in air ??
    bool IsInAir;


    // the jump velocity 
    int Velocity{0};

    
    // the jump value 
    const int Jumpvel{-600};
    //weeebo character and the kill shots collision
    bool Collision{};

    //the killshots GX
    float GX[8];

    // frames per sec
    SetTargetFPS(60);
 
    while (!WindowShouldClose())
    {
        
        BeginDrawing();

        ClearBackground(WHITE);
        
        float DeltaTime{GetFrameTime()};

 
        GX[0]=BackGroundLooping( Background, GX[0]-= 40 * DeltaTime);
        Background=BackGroundDrawing(Background,GX[0]);

        GX[1]=BackGroundLooping( Background2, GX[1]-= 20 * DeltaTime);
        Background2=BackGroundDrawing(Background2,GX[1]);
    
        GX[2]=BackGroundLooping( Background3, GX[2]-= 15 * DeltaTime);
        Background3=BackGroundDrawing(Background3,GX[2]);

        GX[3]=BackGroundLooping( Background4, GX[3]-= 40 * DeltaTime);
        Background4=BackGroundDrawing(Background4,GX[3]);

        GX[4]=BackGroundLooping( Background5, GX[4]-= 40 * DeltaTime);
        Background5=BackGroundDrawing(Background5,GX[4]);

        GX[5]=BackGroundLooping( Background6, GX[5]-= 80 * DeltaTime);
        Background6=BackGroundDrawing(Background6,GX[5]);

        GX[6]=BackGroundLooping( Background7, GX[6]-= 80 * DeltaTime);
        Background7=BackGroundDrawing(Background7,GX[6]);

        GX[7]=BackGroundLooping( Background8, GX[7]-= 80 * DeltaTime);
        Background8=BackGroundDrawing(Background8,GX[7]);


        FinishLine+=KillshotsaVel*DeltaTime;

        // is the Rectangle on the ground
        if(isOnGround( WEEBO, WindowHight))
        {
            Velocity=0;
            IsInAir=false;
        }

        else
        {
            Velocity+=Gravity*DeltaTime;
            IsInAir=true;
        }

       // Jump Check
       if(IsKeyPressed(KEY_SPACE)&& !IsInAir )
       {

        Velocity+=Jumpvel;
        
       }    
     

        // Update  Weebo position
        WEEBO.POS.y += Velocity * DeltaTime;

        WEEBO.RunningTime+=DeltaTime;

        if(!IsInAir)
        {

           WEEBO=UpdateWeeboAnimation( WEEBO,DeltaTime); 
        
        }

 
        
        
        for (AnimData killshot :Killshots)
        {
            float pad{90};
            Rectangle killshotRec{killshot.POS.x+pad,killshot.POS.y+pad,killshot.REC.width - 2*pad,killshot.REC.height - 2*pad};
            Rectangle WeeboREC{WEEBO.POS.x,WEEBO.POS.y,WEEBO.REC.width,WEEBO.REC.height};

            if (CheckCollisionRecs(killshotRec,WeeboREC))
            {
                Collision = true;
            }

        }   
        
           
        if(Collision)
        {

         DrawText("   Game Over !",WindowWidth/4,WindowHight/2,30.0,GREEN);

        }
        
        else if (WEEBO.POS.x+-400>=FinishLine)
        {
            DrawText("     You Win",WindowWidth/4,WindowHight/2,30.0,GREEN);
        }


        else
        {

        for (int i = 0; i < KillshotsCount; i++)
        {
          

        // Update Killshots Position
        Killshots[i] = UpdateKillshotAnimation( Killshots[i], DeltaTime,KillshotsaVel );
               
        // Draw Killshots
        DrawTextureRec(killshot,Killshots[i].REC,Killshots[i].POS,GREEN);

        
        // Draw Weebo Character 
        DrawTextureRec(Weebo,WEEBO.REC,WEEBO.POS,Color(WHITE));

        }

        }
        
             
        EndDrawing();

    }


    UnloadTexture(Weebo);

    UnloadTexture(killshot); 

    UnloadTexture(Background);
    UnloadTexture(Background2);
    UnloadTexture(Background3);
    UnloadTexture(Background4);
    UnloadTexture(Background5);
    UnloadTexture(Background6);
    UnloadTexture(Background7);
    
    CloseWindow();

}