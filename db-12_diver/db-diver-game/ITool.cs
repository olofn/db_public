using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using DB.DoF.Entities;
using DB.Gui;

namespace DB.DoF
{
    public interface ITool
    {
        Texture2D Icon {get;}

        void Update(Diver diver, Room room, State s);

        void OnUse(Diver diver, Room room);

        void Draw(Graphics graphics, Diver diver);


    }
}
