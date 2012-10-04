Maratis Particle System
=======================

Particle system for the Maratis3D engine. http://maratis3d.com

This plugin should compile against the stock Maratis SDK, but also Maratis/MIngEd. For the latter, you can use the following to install MParticle. At this stage, there is no easy way to load a plugin in the standard Maratis SDK (it can be loaded manually) Also, any lua interface may be incompatible

Linux:
`MPlugin install MParticle.so`
`MPlugin install-sys MParticleEditor.so`

Windows:
`MPlugin install MParticle.dll`
`MPlugin install-sys MParticleEditor.dll`

OS X:
`MPlugin install MParticle.dylib`
`MPlugin install-sys MParticleEditor.dylib`

Updates
-------

Update 02.10.2012 - 
* Updated MIngEd support
* Split into editor plugin and runtime plugin

Update 14.07.2012 - Added support for MIngEd system

Update 05.04.2012 - 
* Removed ParticleLib as it was causing too many problems
* Started implementation of custom particle system
* ParticleEmitter - behavior which "spawns" and renders the particles
* ParticleSystem - manages the particles after they've been emitted
* Particle - container for per-particle data

Notes
-----

* Currently these only render as point sprites
* Dead particles still render
* No collision
* No gravity (this is currently hard coded)
* No...

TODO
----

* Kill dead particles.
* Support standard billboard quads.
* Draw particles via shader.
* Package some default particle textures. Maybe atlas them?
* Create ParticleDef system and create sample particle systems.
* lua API for MParticle
* lua editor for MIngEd