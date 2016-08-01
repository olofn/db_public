using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Input;

namespace DB.DoF
{
    public class Input
    {
        KeyboardState lastKeyboardState;
        KeyboardState keyboardState;
        Dictionary<Action, Keys> keyBindings = new Dictionary<Action,Keys>();

        public enum Action
        {
            Jump,
            Item1,
            Item2,
            Left,
            Right,
            Up,
            Down,
            Map,
            Select
        }

        public Input()
        {
            keyBindings.Add(Action.Jump, Keys.C);
            keyBindings.Add(Action.Item1, Keys.Z);
            keyBindings.Add(Action.Item2, Keys.X);
            keyBindings.Add(Action.Left, Keys.Left);
            keyBindings.Add(Action.Right, Keys.Right);
            keyBindings.Add(Action.Up, Keys.Up);
            keyBindings.Add(Action.Down, Keys.Down);
            keyBindings.Add(Action.Map, Keys.Tab);
            keyBindings.Add(Action.Select, Keys.Space);
        }

        public void Update()
        {
            lastKeyboardState = keyboardState;
            keyboardState = Keyboard.GetState();
        }

        public bool WasPressed(Action action)
        {
            return lastKeyboardState.IsKeyUp(keyBindings[action])
                && keyboardState.IsKeyDown(keyBindings[action]);
        }

        public bool IsHeld(Action action)
        {
            return keyboardState.IsKeyDown(keyBindings[action]);
        }

        public bool WasReleased(Action action)
        {
            return lastKeyboardState.IsKeyDown(keyBindings[action])
                 && keyboardState.IsKeyUp(keyBindings[action]);
        }
    }
}
