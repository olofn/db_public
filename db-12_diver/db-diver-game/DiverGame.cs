using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;

using DB.Gui;
using DB.Gui.Boxes;
using DB.Audio;

namespace DB.DoF
{
    public class State
    {
        public Input Input;
        public GameTime Time;
    }

    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class DiverGame : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphicsDeviceManager;
        SpriteBatch spriteBatch;
        GuiManager guiManager = new GuiManager();
        SpriteFont font;
        AudioDevice audioDevice;
        AudioMixer audioMixer;
        AudioClip audioClip;
        Graphics graphics;
        public static ContentManager DefaultContent;
        RenderTarget2D renderTarget;
        State state;
        public static Texture2D White;
        public static Random Random = new Random();
        Sea sea;
        Effect waterEffect;

        public DiverGame()
        {
            DefaultContent = Content;
            graphicsDeviceManager = new GraphicsDeviceManager(this);

            Content.RootDirectory = "Content";
            IsMouseVisible = true;

            audioDevice = new AudioDevice();
            audioMixer = new AudioMixer(audioDevice);
            state = new State();
            state.Input = new Input();
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            // TODO: Add your initialization logic here
            graphicsDeviceManager.PreferredBackBufferWidth = 800;
            graphicsDeviceManager.PreferredBackBufferHeight = 600;
            graphicsDeviceManager.SynchronizeWithVerticalRetrace = true;
            
            //graphicsDeviceManager.IsFullScreen = true;
            graphicsDeviceManager.SynchronizeWithVerticalRetrace = true;
            // graphicsDeviceManager.ToggleFullScreen();
            graphicsDeviceManager.ApplyChanges();

            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            graphics = new Graphics(GraphicsDevice);
            renderTarget = new RenderTarget2D(GraphicsDevice, 512, 512, 0, SurfaceFormat.Color, MultiSampleType.None, 1);
         
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);

            White = new Texture2D(GraphicsDevice, 4, 4, 1, TextureUsage.Tiled, SurfaceFormat.Color);
            White.SetData(new uint[] { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                                       0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                                       0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                                       0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff });
           

            font = Content.Load<SpriteFont>("Font");

            guiManager.Top = new Container();
            guiManager.Top.Size = new Point(GraphicsDevice.Viewport.Width, GraphicsDevice.Viewport.Height);
            guiManager.Top.Font = font;

            BorderBox areaDefault = new BorderBox(White, true, Color.Gray, Color.Black, 2);
            BorderBox areaPressed = new BorderBox(White, true, Color.Black, Color.White, 2);
            BorderBox areaHover = new BorderBox(White, true, Color.LightGray, Color.Black, 2);

            Button b = new Button("Click me!", areaDefault, areaPressed, areaHover);
            b.X = 10; 
            b.Y = 10;
            guiManager.Top.Add(b);
            b.AutoResize();

            audioClip = new AudioClip(Content.RootDirectory + "/" + "clip.wav");

            b.Clicked += new Button.ClickedHandler(PlaySound);

            waterEffect = DefaultContent.Load<Effect>("water");

            sea = new Sea("sea", 2, 2, 1, 0);

            // TODO: use this.Content to load your game content 

            Console.WriteLine(GraphicsDevice.GraphicsDeviceCapabilities.MaxPixelShaderProfile);
        }

        void PlaySound(Button sender, int x, int y, MouseButton button)
        {
            audioClip.Play();
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            Content.Unload();
            audioDevice.Dispose();
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            // Allows the game to exit
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed
                || Keyboard.GetState().IsKeyDown(Keys.Escape))
                this.Exit();

            state.Input.Update();
            state.Time = gameTime;

            sea.Update(state);

            guiManager.Update(gameTime);

            base.Update(gameTime);            
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {            
            graphicsDeviceManager.GraphicsDevice.SetRenderTarget(0, renderTarget);
            graphicsDeviceManager.GraphicsDevice.Clear(Color.Black);
           
            graphics.BeginClip();
           
            sea.Draw(graphics, gameTime);
           

            //guiManager.Draw(graphics, gameTime);
            
            GraphicsDevice.SetRenderTarget(0, null);
           
            graphics.Begin(SpriteBlendMode.None, SpriteSortMode.Immediate, SaveStateMode.None);
            graphics.GraphicsDevice.SamplerStates[0].MagFilter = TextureFilter.None;

            if (!sea.IsDiverOnBoat())
            {
                waterEffect.Begin();
                waterEffect.Parameters["time"].SetValue(gameTime.TotalGameTime.Ticks / 3000000.0f);
                waterEffect.CurrentTechnique.Passes[0].Begin();
            }
            graphics.Draw(renderTarget.GetTexture(),
                          new Rectangle(0, 0, 800, Room.HeightInTiles*16*2),
                          new Rectangle(0, 0, 400, Room.HeightInTiles * 16), 
                          Color.White);
            if (!sea.IsDiverOnBoat())
            {
                waterEffect.CurrentTechnique.Passes[0].End();
                waterEffect.End();
            }
            graphics.End();

            graphics.Begin(SpriteBlendMode.None, SpriteSortMode.Immediate, SaveStateMode.None);
            graphics.GraphicsDevice.SamplerStates[0].MagFilter = TextureFilter.None;
            graphics.Draw(renderTarget.GetTexture(),
                          new Rectangle(0, Room.HeightInTiles * 16 * 2, 800, 600 - Room.HeightInTiles * 16 * 2),
                          new Rectangle(0, Room.HeightInTiles * 16, 400, 300 - Room.HeightInTiles * 16),
                          Color.White);
            graphics.End();

            graphics.EndClip();

  
            base.Draw(gameTime);
        }


    }
}
