SOME TECHNICAL CONSIDERATIONS:

[####] MEMORY AND EASE OF WRITING OVER COMPOSITION [####]
Looking at the "architecture" I made with my structs and helpers, it is clear just how valuable composition can be in such a context as this one.
For example I have a PhysicsObject - an object affected by physics and that has a collider (an OBB collider with a number of vertices).
This works great for my purposes but say however that I aim to have an object that is affected by physics and yet has no collider, floating text perhaps.
I have a struct for text - AnimatableText - and I could create another struct that holds an AnimatableText and a PhysicsObject and in doing so I could use the PhysicsObject for the position affected by gravity and the AnimatableText for the text-related things I want to do.
This is precisely what I have done.
However a PhysicsObject holds a lot of fields that are related to collision checking, one of them is a struct for the OBB collider.
The base use case for my floating texts does not necessitate a collider, this means that my architecture wastes precious memory for no good reason.
By the time I made this realization I was roughly near the end of the project, the part related to gameplay at least.
Changing it then would have had a big impact on what I had already done and I'd have had to spend an amount of time refactoring code that I could have spent on finishing this little playground project, so I decided to keep my architecture the way it was in favor of faster development time.
Mind you this is a project that I would never have to come back to - no after release maintenence needed whatsoever - so I could afford a codebase with these "imperfections" since I wouldn't have had to work on it anymore after it was done.

[####] MEMORY USAGE FOR DEBRIS [####]
In the source file "gameplay.c" we have a function "UpdateCrates()" that basically contains the game loop for a level.
It spawns the crates and inside a for cycle it updates their position and rotation through physics (coming from another file "physics.h") and also handles the collision between mouse and crates.
Clicking on a crate we split it in four different parts, these are called "debris" and are PhysicsObject for all intents and purposes and as such they occupy space in memory and they have to be calculated as well for physics.
What I did was allocate an array of lenght = level.phys_objs_to_throw + (level.phys_objs_to_throw * 8) so that we could have a satisfying amount of debris on screen and avoid having crates just disappear after a couple of cases destroyed.
For a project of this small size I'm not excessively worried about the usage of memory - high as it can be - however I'm not entirely happy with how I treated the calculation of physics for the debris in the for cycle, and this is because I could've been a lot smarter with it.
The for cycle starts from the index relating to the first physics object in that specific wave and then goes onwards until it reaches the end of the whole array of objects to account for debris since these will be placed in the array AFTER the physics objects relating normal crates in the level.
This forces us to loop over the whole array for the most part, only saving on a couple cycles regarding intact crates that belonged to previous waves.
How I could've approached this better would've been with dividing this big array into two, one for the crates and the other for the debris, and we could've done with less than halfe the iterations the for cycle does now.
I believe it's an objectively better solution than the one I use now however I didn't go for it because by the time I thought of this idea I had in front of me this structure already - albeit with some bugs that needed fixing at the time - so I decided to just finish what I had in front of me in order to make the game playable and stable and then move on to other projects.
If I had to come back to this game to update it or to mantain it then the first thing I would do would definetly implement this new solution in order to have better performances.
