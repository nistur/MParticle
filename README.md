Maratis Particle System
=======================

Particle system for the Maratis3D engine. http://maratis3d.com

This is a plugin, so won't currently work with Maratis until the plugin feature is released. Sorry.

05.04.2012
----------
* Removed ParticleLib as it was causing too many problems
* Started implementation of custom particle system
* ParticleEmitter - behavior which "spawns" and renders the particles
* ParticleSystem - manages the particles after they've been emitted
* Particle - container for per-particle data
Notes:
* Currently these only display as single pixel points
* They currently are "forced" to go up at 1unit/second
* Dead particles still render
* No collision
* No gravity
* No...