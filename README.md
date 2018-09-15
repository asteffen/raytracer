Libraries used: Eigen, png++<br/>
Usage: ./raytracer [scene#]<br/>
where scene# is the number of the scene (01, 02, or 03).<br/>
The scenes are hardcoded in input-01.h, input-02.h, input-03.h.<br/>
The image is written to the file output.png.<br/>

![img01](https://github.com/asteffen/raytracer/blob/master/imgs/image-01.png)<br/>
A room with two reflective surfaces <br/>
Command: ./raytracer 8<br/>
Runtime: 13.840000 seconds<br/>
Features demonstrated: phong shading, shadows, reflections, point lights, write to png<br/>

![img02](https://github.com/asteffen/raytracer/blob/master/imgs/image-02.png)<br/>
A shuttle and a tiny planet <br/>
Command: ./raytracer 5<br/>
Runtime: 163.510000 seconds<br/>
Features demonstrated: read .obj file, phong shading, shadows, directional lights, write to png<br/>

![img03](https://github.com/asteffen/raytracer/blob/master/imgs/image-03.png)<br/>
Reflective ellipsoids <br/>
Command: ./raytracer 9<br/>
Runtime: 46.130000 seconds<br/>
Features demonstrated: render arbitrarily oriented ellipsoids, phong shading, shadows, reflections, point lights, write to png<br/>
