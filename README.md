# Intro
A C++ OOP Draughts implementation without GUI and implementing some AIs.
User input won't be checked, so be careful when typing.

The design is bad on purpose as I wanted to face a "challenging" implementation.
Also, both references and pointers have been used.

Besides an Human player, the currently implemented AIs are:

1. Random AI
2. Alpha Beta Pruning

# Random AI
A random destiny will be choseon for a previously random chosen destiny, it does even win sometimes!

# Alpha-Beta Pruning AI
The heuristic takes into acount the following

1. The most important value is the number of pieces for each player, kings count as 3, men as 1.
2. As we want the AI to move forward, the next factor is the proximity of men to being promoted to kings.
3. Next is a balance between invincibles pieces (those who cannot be eaten but can move) 
and unusable pieces (those who cannot be moved), considering the first ones as slightly more important.
4. The last unit is a random number, as we want AI not to appear so deterministic.

**Fun fact:** If you witness a match where both players are of this kind of AI,
match will never end as both players will foresee the same!

# Requisites

1. Make utility.
2. C++ 2011 compatible compiler.

# Building

Just execute make on repository folder.

# Executing

Execute Draughts and set up match.

1. Select AI type
2. If Human was selected, program will ask for movements, following format "A1B2",
where first position is origin, and second position is destiny.
