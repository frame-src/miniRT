<h1> Mini RT </h1>
</br>
<p align="center">
   <img src="https://github.com/frame-src/miniRT/blob/main/img/first_camera0.png" height=400>
</p>
<p align="center">
   <sub>First Image we ever rendered</sub>
</p>
</br>

This project is an introduction to the beautiful world of Raytracing.

So once you run "make" the 
```bash 
./miniRT ./source/<mapname>.rt
```
will be capable of render beautiful images like this:



</br>
<p align="center">
   <img src="https://github.com/frame-src/miniRT/blob/main/img/first_camera1.png" height=600>
</p>
<p align="center"><sub> 
   The same but in the input2.rt the camera z component is farther </sub>
</p>

We had to handle multiple object, cylinders planes and spheres:

</br>
<p align="center">
   <img src="https://github.com/frame-src/miniRT/blob/main/img/multi_90.png" height=600>
</p>
<p align="center"> <sub> 
   Multiple objs composition</sub>
</p>
</br>

...and diffent settings for the camera such as the FOV:
</br>
<p align="center">
   <img src="https://github.com/frame-src/miniRT/blob/main/img/multi_180.png" height=600>
</p>
<p align="center"><sub> Same composition but maxFOV</sub></p>
</br>

Different atmosphere can be settled setting different Ambient Light:

</br>
<p align="center">
   <img src="https://github.com/frame-src/miniRT/blob/main/img/dark_light.png" height=600>
   </p>
<p align="center"><sub>Single sphere, dark atmo</sub></p>
</br>

...
</br>
<p align="center">
   <img src="https://github.com/frame-src/miniRT/blob/main/img/dark_light_a.png" height=600>
   </p>
<p align="center"><sub> Ambient Light ratio = 0.9</sub></p>
</br>

Or the brightness can be modified changing the ration of the Spot Light:

</br>
<p align="center">
   <img src="https://github.com/frame-src/miniRT/blob/main/img/dark_light_0.png" height=600>
</p>
<p align="center"><sub> Light parameter ratio = 0.1</sub></p>
</br>

enjoy:

</br>
<p align="center">
   <img src="https://github.com/frame-src/miniRT/blob/main/img/room.png" height=600>
</p>
<p align="center"><sub> Enjoy</sub></p>
</br>
