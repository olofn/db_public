using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Reflection;
using Microsoft.CSharp;
using System.CodeDom;
using System.CodeDom.Compiler;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using DB.DoF.Entities;

namespace DB.DoF
{

    public class Room
    {
        public enum Layer
        {
            Background,
            Player,
            Foreground
        }

        public const int WidthInTiles = 25;
        public const int HeightInTiles = 17;

        public Point Size { get { return TileMap.SizeInPixels; } }

        public bool LeaveRoomEnabled = true;
        public TileMap TileMap;
        IList<Entity> entities = new List<Entity>();
        Texture2D glowTexture;
        public Sea Sea;
        public int SeaX, SeaY;
        public Diver Diver;

        public Room(SpriteGrid tileSet, Sea sea)
        {
            TileMap = new TileMap(tileSet, WidthInTiles, HeightInTiles);
            glowTexture = DiverGame.DefaultContent.Load<Texture2D>("glow");
            this.Sea = sea;
        }

        public static Room FromFile(string filename, SpriteGrid tileSet, bool skipPersistent, Sea sea)
        {
            Room room = new Room(tileSet, sea);

            using (TextReader r = new StreamReader(filename))
            {
                room.TileMap.Load(r);

                IList<string> lines = new List<string>();
                
                foreach(string line in r.ReadToEnd().Split("\n".ToCharArray()))
                {
                    string linet = line.Trim(" \n\r\t".ToCharArray());
                    if (linet.Length > 0 && !linet.StartsWith("//"))
                    {
                        System.Console.WriteLine(linet);
                        lines.Add(linet);
                    }
                }

                room.LoadEntities(lines, skipPersistent);
            }

            return room;
        }

        public void LoadState(TextReader r)
        {
            int numLines = int.Parse(r.ReadLine());
            IList<string> lines = new List<string>();
            for (int i = 0; i < numLines; i++)
            {
                string linet = r.ReadLine().Trim(" \n\r\t".ToCharArray());
                if (linet.Length > 0 && !linet.StartsWith("//"))
                {
                    System.Console.WriteLine(linet);
                    lines.Add(linet);
                }
            }

            if (lines.Count > 0)
            {
                LoadEntities(lines, false);
            }
        }

        public void SaveState(TextWriter w)
        {
            IList<PersistentEntity> persistents = new List<PersistentEntity>();

            foreach (Entity e in entities)
            {
                if (e is PersistentEntity && e != Diver)
                {
                    persistents.Add((PersistentEntity)e);
                }
            }

            w.WriteLine(persistents.Count.ToString());

            foreach (PersistentEntity p in persistents)
            {
                w.WriteLine(p.GetConstructorString());
            }
        }

        void LoadEntities(IList<string> lines, bool skipPersistent)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("using System;");
            sb.AppendLine("using System.Collections.Generic;");
            sb.AppendLine("using DB.DoF.Entities;");
            sb.AppendLine("using DB.DoF.Tools;");
            sb.AppendLine("using Microsoft.Xna.Framework;");
            sb.AppendLine("using Microsoft.Xna.Framework.Graphics;");
            sb.AppendLine("namespace DB.DoF {");
            sb.AppendLine("public class CSCodeEvaler {");
            sb.AppendLine("public void InsertEntities(IList<Entity> entities) {");
            sb.AppendLine("Entity e;");
            foreach (string line in lines)
            {
                sb.AppendLine("e = new " + line + ";");
                if (skipPersistent)
                {
                    sb.AppendLine("if (!(e is PersistentEntity))");
                }
                sb.AppendLine("entities.Add(e);");
            }

            sb.AppendLine("}}}");

            CodeDomProvider cdp = new CSharpCodeProvider();
            CompilerParameters compilerParameters = new CompilerParameters();
            foreach (Assembly asm in AppDomain.CurrentDomain.GetAssemblies())
            {
                compilerParameters.ReferencedAssemblies.Add(asm.Location);
            }

            compilerParameters.GenerateInMemory = true;

            CompilerResults cr = cdp.CompileAssemblyFromSource(compilerParameters, sb.ToString());
            if (cr.Errors.Count > 0)
            {
                throw new Exception(cr.Errors[0].ErrorText + " : " + sb.ToString().Split("\n".ToCharArray())[cr.Errors[0].Line - 1]);
            }

            Assembly a = cr.CompiledAssembly;
            object o = a.CreateInstance("DB.DoF.CSCodeEvaler");

            Type t = o.GetType();
            MethodInfo mi = t.GetMethod("InsertEntities");

            mi.Invoke(o, new object[] { entities });
            
        }

        public void Draw(Gui.Graphics g, GameTime gt)
        {
            foreach (Layer layer in Enum.GetValues(typeof(Layer)))
            {
                if (layer == Layer.Player)
                {
                    TileMap.DrawLadders(g);
                }

                foreach (Entity entity in entities)
                {
                    if (entity != Diver)
                        entity.Draw(g, gt, layer);
                }

                if (layer == Layer.Player)
                {
                    Diver.Draw(g, gt, layer);
                    TileMap.Draw(g);
                }
            }


            /*
            g.Begin(SpriteBlendMode.AlphaBlend, SpriteSortMode.Immediate, SaveStateMode.SaveState);
            g.GraphicsDevice.RenderState.SourceBlend = Blend.DestinationColor;
            g.GraphicsDevice.RenderState.DestinationBlend = Blend.Zero;
            g.Draw(glowTexture, new Rectangle(-300, -300, 400 + 600, 300 + 600), new Color(255,255,255,128));
            g.End();*/
        }

        public void Update(State s, bool isActive)
        {
            LeaveRoomEnabled = true;

            List<Entity> entitiesCopy = new List<Entity>(entities);
            foreach (Entity entity in entitiesCopy)
            {

                if (entity.IsUpdateNeeded(this) || isActive)
                {
                    entity.Update(s, this);

                    if (LeaveRoomEnabled &&
                        (IsEntityLeftOfRoom(entity)
                        || IsEntityRightOfRoom(entity)
                        || IsEntityAboveRoom(entity)
                        || IsEntityBelowRoom(entity)))
                    {
                        Sea.OnLeftRoom(entity, this);
                    }
                }
            }
        }

        public IList<Entity> GetCollidingEntities(Entity entity)
        {
            return GetCollidingEntities<Entity>(entity);
        }

        public IList<T> GetCollidingEntities<T>(Entity entity) where T : Entity
        {
            IList<T> result = new List<T>();

            foreach (Entity e in entities)
            {
                if (typeof(T).IsAssignableFrom(e.GetType()) && e.Dimension.Intersects(entity.Dimension) && e != entity)
                {
                    result.Add((T)e);
                }
            }

            return result;
        }

        public IList<Entity> GetCollidingSolidEntities(Rectangle rect)
        {
            IList<Entity> result = new List<Entity>();

            foreach (Entity e in entities)
            {
                if (e.IsSolid && e.Dimension.Intersects(rect))
                {
                    result.Add(e);
                }
            }

            return result;
        }

        public bool IsEntityLeftOfRoom(Entity entity)
        {
            return entity.X + entity.Width < 0;
        }

        public bool IsEntityRightOfRoom(Entity entity)
        {
            return entity.X > Size.X;
        }

        public bool IsEntityAboveRoom(Entity entity)
        {
            return entity.Y + entity.Height < 0;
        }

        public bool IsEntityBelowRoom(Entity entity)
        {
            return entity.Y > Size.Y;
        }

        public void RemoveEntity(Entity entity)
        {
            entities.Remove(entity);
        }

        public void AddEntity(Entity entity)
        {
            entities.Add(entity);
        }

        public void Broadcast(String channel, String message, object obj)
        {
            foreach (Entity entity in entities)
            {
                entity.OnMessageReceived(channel, message, obj);
            }
        }

        public void SurfaceDiver()
        {
            Sea.EnterBoat();
        }

        public void OnDiverLeftRoom()
        {
            List<Entity> entitiesCopy = new List<Entity>(entities);
            foreach (Entity entity in entitiesCopy)
            {
                if (entity.CleanUpOnRoomLeft)
                {
                    entities.Remove(entity);
                }
            }
        }

        public void OnDiverChange(Diver diver)
        {
            Diver = diver;
            Sea.onDiverChange(diver);
        }
    }
}
