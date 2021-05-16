/*
This Program was Developed by Nkemdilim Okechukwu Umezude, 
with assistance from Hoang Phan and Taoufik Touti.

The entirety of the project process and technique was conceived by 
Nkemdilim Okechukwu Umezude
*/

----------------------------------------------------------------------------------------------
This Program takes as input text files that contain all the information of the discretized 
elements that come together to make up the bulk sheet metal.
----------------------------------------------------------------------------------------------


The text files can be generated easily, by making a copy of a '.obj' file, 
and simply changing its file extension from '.obj', to '.txt'.

Once that is done, the text file just needs to be entered as input to the program.
To enter the text file as input;
1) Right-Click on the '.txt' file and get its absolute path from the properties tab.

2) When prompted, input the text file, along with its extension (i.e, '.txt').

3) Initialize the Poisson's ratio, Young's Modulus, thickness variables, constrained node
number and individual constrained nodes, number of nodes with applied load and loads applied
on each individual node, in either the x or y direction.

4) The program would calculate and display the local stiffness matrices for all the elements/faces,
the global stiffness matrix (ID form), the global stiffness matrix with applied boundary conditions
(ID form), the strain displacements.

5) The strain displacements are added by ID to the original coordinates.

6) The new coordinates are exported into a new '.txt' file, which you can convert to a '.obj' file.

7) This new '.obj' file, can be viewed on Meshworks. 