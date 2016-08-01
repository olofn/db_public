===============================================================================

                                GREEN GRAPPLER

                                                             BY: Team Darkbits
===============================================================================

   
   About:
      This our entry for SpeedHack 2011, http://www.speedhack.allegro.cc/
      
      Created in 72 hours by
      
        Olof Naessen:         Code, Graphics, Music
        Per Larsson:          Code, Graphics, Music
        Alexander Schrab:     Code
		Timur Kondrakov:      Graphics

   Controls:
      * Arrow keys to move
      * Left control to use grapple
      * Esc to exit levels
	  
	There are exprimental Xbox 360 controller support implemented.

   Implemented rules:
      * E for Everyone
        There is no graphics violence or blood, and all enimies are robots.
        
      * Random Playing
        Has been replaced with the Act of Chameleon which spinned Realistic physics.
	        
      * Laziness
        If the player dies the game will gradually become easier. This effects lots of areas in a subtle way. Examples are
		the speed of monsters, how fast coins disappears after you get hurt and the health of the last boss. 
        
      * Brainwashing Propaganda
        The game theme is very anti nuclear. Green energy is the way to go!
        
      * Color Symbolism
        Well, the game talks about green energy a lot. And we like to think that the green symbolises trees and what not.
		Also, the games uses a four colour palette which for us symbolises childhood with the Gameboy.
		
	  * Act of Chameleon
	    Used and spinned Realistic physics. The game must make use of realistic physics in some way or another. 
		Bonus points of creative use of physics, such as things outside the normal scope of game design (kinematics and mechanics).
		
	  * Realistic physics
	    The hero's grappling hook is simulated using hooks law. We have also implemented gravity as described by Newton. 
		The game also respects physical laws such as conservation of monentum... in some places...
		
   Code reuse:

      * Code from our own framework mainly developed during Tins and Speedhack competitions in the past. It includes
			Animation.*
			Resource.*
			Blending.*
			Input.*
			GameState.*
			Music.*
			Screen.*
			ScreenManager.*
			Game.*
			Timer.*
			Font.*
			Sound.*
			Util.*
	  * Vector math classes in math3d folder.

   Music:
      * Composed by us, mostly prior to the competition.

   Libraries Needed:
      * Dumb, http://dumb.sourceforge.net/
	  * tmx-parser, http://code.google.com/p/tmx-parser/

EOF