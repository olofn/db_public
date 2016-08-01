using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using DB.Gui;
using DB.DoF.Tools;

namespace DB.DoF.Entities
{
    public class Inventory : PersistentEntity
    {
        List<ITool> tools = new List<ITool>();

        SpriteFont font;

        Texture2D toolSelectorTexture;
        Texture2D backgroundTexture;

        int inventorySelected = 0;

        bool isGUIActive = false;
        bool diverInInventory = false;

        public Inventory(int x, int y)
        {
            this.X = x;
            this.Y = y;
            this.Width = 20;
            this.Height = 20;
            font = DiverGame.DefaultContent.Load<SpriteFont>("Font");
            toolSelectorTexture = DiverGame.DefaultContent.Load<Texture2D>("tool_selector");
            backgroundTexture = DiverGame.DefaultContent.Load<Texture2D>("inventory");
            /*
            tools.Add(new HarpoonTool());
            tools.Add(new HarpoonTool());
            tools.Add(new HarpoonTool());
            tools.Add(new HarpoonTool());
            tools.Add(new BombTool());
            tools.Add(new HarpoonTool());
            tools.Add(new BombTool());
            tools.Add(new HarpoonTool());
            tools.Add(new BombTool());
            tools.Add(new HarpoonTool());
            tools.Add(new BombTool());
            tools.Add(new HarpoonTool());
            tools.Add(new BombTool());
            tools.Add(new HarpoonTool());
            tools.Add(new BombTool());
            tools.Add(new BombTool());
            tools.Add(new HarpoonTool());
            tools.Add(new BombTool());
            tools.Add(new HarpoonTool());
            tools.Add(new BombTool());
            */
        }

        public Inventory(int x, int y, ITool[] tools)
        :this(x, y)
        {
            foreach (ITool tool in tools)
            {
                this.tools.Add(tool);
            }
        }

        public void AddTool(ITool tool)
        {
            tools.Add(tool);
        }

        public void RemoveTool(ITool tool)
        {
            tools.Remove(tool);
        }

        public override void Draw(DB.Gui.Graphics g, Microsoft.Xna.Framework.GameTime gameTime, Room.Layer layer)
        {
            int x = 0, y = 0;
            g.Begin();
            g.Draw(DiverGame.White, this.Dimension, Color.White);

            if (diverInInventory)
            {
                if (!isGUIActive)
                {
                    g.DrawStringShadowed(font,
                     "Press Space to open inventory",
                     new Rectangle(0, 100, 400, 20),
                     TextAlignment.Center,
                     Color.White);
                }

            }

            if (isGUIActive)
            {
                Color c = new Color(255, 255, 255, 230);
                x = 400/2 - backgroundTexture.Width / 2;
                y = 300/2 - backgroundTexture.Height / 2;

                g.Draw(backgroundTexture, new Point(x, y), c);
                y += 15;
                g.DrawStringShadowed(font,
                                     "Inventory",
                                     new Rectangle(x, y, backgroundTexture.Width, 20),
                                     TextAlignment.Center,
                                     Color.White);

                int spaceBetween = 30;
                x += 30; y += 20;

                int xOffs = 0;
                foreach (ITool tool in tools)
                {
                    g.Draw(tool.Icon, new Point(x + (xOffs%7)*spaceBetween + 4, y + (xOffs/7)*spaceBetween + 4), Color.White);
                    xOffs += 1;
                }


                g.Draw(toolSelectorTexture, new Point(spaceBetween*(inventorySelected%7) + x, y + (inventorySelected/7)*spaceBetween), Color.White);

            }

            g.End();

        }

        public override void Update(State s, Room room)
        {

            diverInInventory = false;
            foreach (Entity entity in room.GetCollidingEntities<Diver>(this))
            {
                if (room.Diver == entity)
                {
                    diverInInventory = true;
                    break;
                }
            }

            if (isGUIActive)
            {
                if (s.Input.WasPressed(Input.Action.Select))
                {
                    isGUIActive = false;
                    room.Diver.Freeze = false;
                }
                if (tools.Count != 0)
                {
                    if (s.Input.WasPressed(Input.Action.Right))
                    {
                        inventorySelected = (inventorySelected + 1) % tools.Count;
                    }
                    if (s.Input.WasPressed(Input.Action.Left))
                    {
                        inventorySelected = inventorySelected == 0 ? tools.Count - 1 : inventorySelected - 1;
                    }

                    ITool selectedTool = tools.Count != 0 ? tools[inventorySelected] : null;

                    if (s.Input.WasPressed(Input.Action.Item1))
                    {
                        if (selectedTool == room.Diver.Tool2) room.Diver.Tool2 = room.Diver.Tool1;
                        room.Diver.Tool1 = selectedTool;
                    }

                    if (s.Input.WasPressed(Input.Action.Item2))
                    {
                        if (selectedTool == room.Diver.Tool1) room.Diver.Tool1 = room.Diver.Tool2;
                        room.Diver.Tool2 = selectedTool;
                    }
                }
                //System.Console.WriteLine("GUI!! " + s.Time.TotalRealTime.Milliseconds);
            }
            else
            {
                if (s.Input.WasPressed(Input.Action.Select) && diverInInventory)
                {
                    isGUIActive = true;
                    room.Diver.Freeze = true;
                }
            }
        }

        public override void OnMessageReceived(string channel, string message, object obj)
        {
            if (channel == "inventory" && message == "add")
            {
                AddTool((ITool)obj);
            }
        }


        protected override string[] GetConstructorArguments()
        {
            string[] toolConstructorStrings = new string[tools.Count];

            int i = 0;
            foreach (ITool tool in tools)
            {                
                toolConstructorStrings[i] = "new " + tool.GetType().Name + "()";
                i++;
            }

            string[] arguments = new string[] {
            "" + X,
            "" + Y,
            "new ITool[] {" + CommaSeparate(toolConstructorStrings) + "}"
            }; 
            return arguments;
        }
    }
}
