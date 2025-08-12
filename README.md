# KeyControls
## KeyOperations
W: Move to front on the Z axis  
S: Move to rear on the Z axis  
A: Move to left on the X axis  
D: Move to right on the X axis  
E: Move to top on the Y axis  
Q: Move to bottom on the Y axis  

H: Increase height (cylinder/cone only)  
G: Decrease height (cylinder/cone only)  

B: Increase diameter (sphere/cylinder only) / Increase angle (cone only)  
V: Decrease diameter (sphere/cylinder only) / Decrease angle (cone only)  

up: Rotate upward along the Y-axis (for lights: increase brightness)  
down: Rotate downward along the Y-axis (for lights: decrease brightness)  
right: Rotate to the right along the X-axis (for lights: decrease color) (for sphere texture: Rotate the texture)  
Left: Rotate left on the X axis (for lights: increase color) (for sphere texture: Rotate the texture)  

+: Select next light  
-: Select previous light  

space: Switch target mode (camera / light / object)  

R: Reset only selected target  

C: Reset all  

Z: Print the current scene in rt format  

Esc: Close screen and exit  

## MouseOperations
Mouse down: Select object (Acquire pixels, send rays from the camera to the pixels, and set the closest object)

<br><br>
# Additonal formats for bonus  

## Cone:
co 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 0.5 10,0,255  
∗ identifier: co  
∗ x, y, z coordinates of the center of the cone: 50.0,0.0,20.6  
∗ 3D normalized vector of axis of cone, in the range [-1,1] for each x, y, z axis: 0.0,0.0,1.0  
∗ the cone height: float 14.2  
∗ the opposite cone height: float 21.42  
∗ the cone angle: float 0.5 (rad) （Since it is a half apex angle, it becomes a 180° open cone at 1.57 rad.）  
∗ R, G, B colors in the range [0,255]: 10, 0, 255  



## Material format （put after object parameter）
Mirror,specn,speckv cb tx bump  

Mirror: float (0.0〜1.0)  
specn: float (1.0〜100.0+)  
speckv: float (0.0〜1.0)  

cb(checkerboard): t_bool (0 or 1)  

tx: string (To escape, write NULL) (ex. scene/tx/2k_earth.png)  
bump: string (To escape, write NULL) (ex. scene/tx/2k_earth_bump.png)  