#include "gui/extendedallegroinput.hpp"

namespace gcn
{
    void ExtendedAllegroInput::pollMouseInput()
    {
        if (mouse_needs_poll())
        {
            poll_mouse();
        }
        int mouseX = mouse_x / 2;
        int mouseY = mouse_y / 2;
        int mouseZ = mouse_z;
        int mouseB1 = mouse_b & 1;
        int mouseB2 = mouse_b & 2;
        int mouseB3 = mouse_b & 4;

        // Check mouse movement
        if (mouseX != mLastMouseX || mouseY != mLastMouseY)
        {
            mMouseQueue.push(MouseInput(MouseInput::EMPTY,
                                        MouseInput::MOVED,
                                        mouseX,
                                        mouseY,
                                        0));
            mLastMouseX = mouseX;
            mLastMouseY = mouseY;
        }

        // Check mouse Wheel
        while (mLastMouseZ < mouseZ)
        {
            mMouseQueue.push(MouseInput(MouseInput::EMPTY,
                                        MouseInput::WHEEL_MOVED_UP,
                                        mouseX,
                                        mouseY,
                                        0));
            mLastMouseZ++;
        }

        while (mLastMouseZ > mouseZ)
        {
            mMouseQueue.push(MouseInput(MouseInput::EMPTY,
                                        MouseInput::WHEEL_MOVED_DOWN,
                                        mouseX,
                                        mouseY,
                                        0));
            mLastMouseZ--;
        }

        // Check mouse buttons
        if (!mMouseButton1 && mouseB1)
        {
            mMouseQueue.push(MouseInput(MouseInput::LEFT,
                                        MouseInput::PRESSED,
                                        mouseX,
                                        mouseY,
                                        0));
        }

        if (mMouseButton1 && !mouseB1)
        {
            mMouseQueue.push(MouseInput(MouseInput::LEFT,
                                        MouseInput::RELEASED,
                                        mouseX,
                                        mouseY,
                                        0));
        }


        if (!mMouseButton2 && mouseB2)
        {
            mMouseQueue.push(MouseInput(MouseInput::RIGHT,
                                        MouseInput::PRESSED,
                                        mouseX,
                                        mouseY,
                                        0));
        }

        if (mMouseButton2 && !mouseB2)
        {
            mMouseQueue.push(MouseInput(MouseInput::RIGHT,
                                        MouseInput::RELEASED,
                                        mouseX,
                                        mouseY,
                                        0));
        }


        if (!mMouseButton3 && mouseB3)
        {
            mMouseQueue.push(MouseInput(MouseInput::MIDDLE,
                                        MouseInput::PRESSED,
                                        mouseX,
                                        mouseY,
                                        0));
        }

        if (mMouseButton3 && !mouseB3)
        {
            mMouseQueue.push(MouseInput(MouseInput::MIDDLE,
                                        MouseInput::RELEASED,
                                        mouseX,
                                        mouseY,
                                        0));
        }

        mMouseButton1 = mouseB1;
        mMouseButton2 = mouseB2;
        mMouseButton3 = mouseB3;
    }
}
