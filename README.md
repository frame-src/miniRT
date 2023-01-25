<h1> Mini RT </h1>

This project is an introduction to the beautiful world of Raytracing.

So once you run "make" the 
```bash 
./miniRT ./source/<mapname>.rt
```
will be capable of render beautiful images like this:

![](.img/first_camera0.png)
<p align="center"> <sub> First Image we ever rendered</sub></p>

![](.img/first_camera1.png)
<p align="center"> <sub> The same but in the input2.rt the camera is farther</sub></p>

We had to handle multiple object, cylinders planes and spheres:

![](.img/multi_90.png)
<p align="center"> <sub> Multiple objs composition</sub></p>

...and diffent settings for the camera such as the FOV:

![](.img/multi_180.png)
<p align="center"> <sub> Same composition but maxFOV</sub></p>

Different atmosphere can be settled setting different Ambient Light:

![](.img/dark_light.png)
<p align="center"> <sub> Single sphere, dark atmo</sub></p>

...

![](.img/dark_light_a.png)
<p align="center"> <sub> Ambient Light ratio = 0.9</sub></p>

Or the brightness can be modified changing the ration of the Spot Light:

![](.img/dark_light_0.png)
<p align="center"> <sub> Light parameter ratio = 0.1</sub></p>

enjoy:

![](.img/dark_light_0.png)
<p align="center"> <sub> Enjoy, Marius Winter and Francesco Messina </sub></p>
