===============================================================================

                                SECRET of FANTASY
                                       ~                                         
                               The Calcium Crystals

                                                             BY: Team Darkbits
===============================================================================

   
   About:
      This our entry for SpeedHack 2009, http://www.speedhack.allegro.cc/
      
      Created in 72 hours by
      
        Olof Naessen:  Code, Graphics, Music
        Per Larsson:   Code, Graphics, Music
        Ted Steen:     Code
        Emil Jönsson:  Graphics, Levels
        Tomas Almgren: Graphics

   Controls:
      * Arrow keys to move
      * Left control to attack
      * Left alt for actions
      * Space to use items
      * I to open your inventory (can be used to pause the game!)
      * ESC quits the game immediately (be careful!)

   Implemented rules:
      * Fantastically Mundane
        The game is all about buying Milk at the grocery, but someone intervenes...
        The implementation of this rule is to be honest quite lame, but what the
        hell, we wanted to do an RPG.
        
      * Dynamic Environment
        Blocks are explodable opening paths. Dirt can be digged up.  
	        
      * Zoom, Zoom!
        There is a zoom effect when changing rooms.
        
      * Unlockable Content
        When the game is complete heroic mode is unlocked.
        
      * Post-Mortem
        At the end the player is given statistics about the course of the game.

   Code reuse:

      * resourcehandler

        timer
        music
        os

        from Ballz, http://code.google.com/p/db-tins07/

      * bomb
        blending
        explodable
        from Doomsday Treasure Hunter, http://amarillion.bafsoft.net/tins08/
        
      * animation
        splashscreen
        parts of dialog
        stringutil
        entity 
        util
        fileutil
        from Dr Madness,  http://code.google.com/p/db-speedhack07/

   Music:
      * Composed by us, mostly prior to the competition.

   Libraries Needed:
      * Guichan 0.8.1, http://code.google.com/p/guichan
      * Dumb, http://dumb.sourceforge.net/

EOF