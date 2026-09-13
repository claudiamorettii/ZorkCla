# ELOS - my version of Zork
ELOS is a console-based text adventure inspired by as Zork.
<br>The player explores an abandoned house and the surrounding forest, collects and combines items, solves riddles, fights enemies and searches for a mysterious crystal.

The game was developed in C++ using Visual Studio 2022 Community.

## Author
Claudia Moretti

## Repository
https://github.com/claudiamorettii/ZorkCla

## Requirements

### To Play

* Windows 10 or later is recommended.
* The game may also run on Windows 7, but ANSI colours might not be displayed correctly.

### To Build

* Visual Studio 2022 Community
* A compiler supporting modern C++


## Complete Walkthrough
0. Type "help" to show all available commands.
1. From the dark forest, go east to the forest clearing.
2. Take the sword.
3. You can collect and eat the Berries, but each one has a 50% chance of either restoring health or causing damage.
4. Return west and go south to the abandoned garden.
5. Talk to the Troll.
6. Answer "echo" to receive the basement key peacefully.
7. Alternatively, defeat the Troll and loot the key from its body.
8. Enter the old house.
9. Search the Kitchen and take the Flashlight and the Apple. Unlike the Berries, the Apple is always safe to eat.
10. Search the living room and take the old map.
11. Examine the map to discover the marked location.
12. Use the basement key to enter the basement.
13. Find and take the batteries.
14. Place the batteries inside the flashlight.
15. Equip the flashlight.
16. Return to the forest clearing and dig at the location marked on the map.
17. Enter the revealed passage and go down.
18. Talk to the Cave Guardian.
19. Answer "keyboard" to weaken it before combat.
20. Equip the sword and defeat the Cave Guardian.
21. Continue south into the crystal cave.
22. Take the crystal to complete the game.

## Project Structure
- GameObject — base class for objects in the game
- Game — manages the world, commands and game progression
- Room — represents locations and their exits
- Player — manages health, inventory and equipped items
- Item — represents weapons, food, keys and tools
- Enemy — manages enemy health, combat, dialogue and loot
- textUtil — provides shared text normalization and name matching

## Development Notes

I developed the game gradually, starting with the creation of rooms and movement between them. I then introduced items, inventory management, equipment, combat and dialogue. The main challenges involved moving items correctly between different locations, recognizing multi-word commands and managing enemy states based on the player’s previous actions.

I particularly enjoyed creating the enemy riddles, especially the Troll encounter (more in line with my D&D-inspired style, where not every encounter has to end in combat), as well as the hidden passage revealed by the map. I also focused on making the game visually pleasant despite being entirely text-based, using colours, separators and an ASCII map to make rooms, objects, dialogue and important events clearer and more engaging.

## License
MIT License

Copyright (c) 2026 Claudia Moretti

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


