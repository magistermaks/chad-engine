#include "Helper.h"
#include "Screen.h"
#include "Renderer.h"
#include "Main.h"


//using namespace helper;
using namespace cv;

typedef std::chrono::high_resolution_clock Clock;

Vector3 cameraAngle = Vector3(0, 0, 0);
Vector3 cameraPosition = Vector3(0, 0, 0);
float depth[width][height];
Mat image;


int x = 0, y = 0;

void mouse_callback(int event, int xm, int ym, int flag, void* param)
{
    if (event == EVENT_MOUSEMOVE)
    {
        x = xm;
        y = ym;
    }
    else if (event == EVENT_MOUSEWHEEL)
    {
        if (getMouseWheelDelta(flag) > 0)
            dist -= 0.2f;
        else
            dist += 0.2f;
    }
}

int main()
{

    //std::cout << __cplusplus << std::endl;

    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    image = Mat::zeros(width, height, CV_8UC3);

    auto t1 = Clock::now();
    setMouseCallback("Display window", mouse_callback);

    Main rend;
    rend.Start();

    uchar fpsSpowalniacz = 0;
    string fps;

    while (true)
    {

        cameraAngle.y =  x / 50.0f;
        cameraAngle.x =  y / 50.0f;

        char key = (char)waitKey(1);

        switch (key)
        {
        case ('q'):
            cameraPosition.y += 1;
            break;
        case ('e'):
            cameraPosition.y -= 1;
            break;
        case ('w'):
            cameraPosition.z += 1;
            break;
        case ('s'):
            cameraPosition.z -= 1;
            break;
        case ('a'):
            cameraPosition.x += 1;
            break;
        case ('d'):
            cameraPosition.x -= 1;
            break;
        }
        rend.Update();



        if (fpsSpowalniacz >= 10)
        {
            auto t2 = Clock::now();
            fps = to_string(10000.0f / std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()) + " FPS x" + to_string(x) + " y " + to_string(y);
            
            t1 = Clock::now();
            
            
            fpsSpowalniacz = 0;
        }
        else
            fpsSpowalniacz++;
        Renderer::render();
        Screen::PrintFrame();
        //Screen::DebugDepth();
        putText(image, fps, Point(0, 12), FONT_HERSHEY_SIMPLEX, 0.5f, Scalar(255, 255, 255), 1);
    }
    return 0;
}