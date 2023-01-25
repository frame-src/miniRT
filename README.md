<h1> Mini RT </h1>

![logo](.img/first_camera0.png)
<p align="center"> <sub> First Image we ever rendered</sub></p>

This project is an introduction to the beautiful world of Raytracing.

So once you run "make" the 
```bash 
./miniRT ./source/<mapname>.rt
```
will be capable of render beautiful images like this:



</br>
<p align="center">
  <kbd><img src="https://github.com/frame-src/miniRT/blob/main/img/first_camera1.png" height=400></kbd>
</p>
</br>

![example](.img/first_camera1.png)
<p align="center"> <sub> The same but in the input2.rt the camera is farther</sub></p>

We had to handle multiple object, cylinders planes and spheres:

![example1](.img/multi_90.png)
<p align="center"> <sub> Multiple objs composition</sub></p>

...and diffent settings for the camera such as the FOV:

![example2](.img/multi_180.png)
<p align="center"> <sub> Same composition but maxFOV</sub></p>

Different atmosphere can be settled setting different Ambient Light:

![example3](.img/dark_light.png)
<p align="center"> <sub> Single sphere, dark atmo</sub></p>

...

![example4](.img/dark_light_a.png)
<p align="center"> <sub> Ambient Light ratio = 0.9</sub></p>

Or the brightness can be modified changing the ration of the Spot Light:

![example5](.img/dark_light_0.png)
<p align="center"> <sub> Light parameter ratio = 0.1</sub></p>

enjoy:

![example6](.img/dark_light_0.png)
<p align="center"> <sub> Enjoy, Marius Winter and Francesco Messina </sub></p>
