Grayscale oil painting filter 
1. Description of grayscale oil painting filter
  In this project, I developed a grayscale oil painting filter which can change a picture from RGB space into a grayscale picture in the form of oil painting.

2. Technology used
Outline: In the project, I used color space conversion from BGR grayscale, medianBlur, modified Laplacian filter. Those functions are realized by myself instead of using opencv functions.
2.1 toGray function
  First, I use toGray() function to transform original image from RGB color space to grayscale space:
   Here I used  I=(11*B+59*G+30*R)/100, as you can see in the expression, I used integer instead of float in order to reduce computation and speed up the program.
     
2.2 medianBlur function
  In the program, medianBlur() function is self-realized median filter which uses a 7*7 window to filter the matrix:
   Firstly, we use a 7*7 matrix to filter the picture pixels, then we use a function called `medValue()` function to get the median value of the pixels within this window, and then use the median value to replace each pixel in the window. This `medValue()` function is realized by the bubble sorting function to find the median value the 7*7 matrix.
   Here we use median filter because normal picture in the Internet contains a lot of noise, a median filter can reduce the effect of salt and pepper noise very well.

2.3 modified Laplacian function
  `Laplacian()` function is a modified Laplacian filter which also uses convolution but with an different kernel matrix:
   Usually, in Laplacian filter of opencv, we use 3*3, 5*5 or 7*7 kernel matrix, for example, if we want to use a 5*5 kernel, it is listed as bellow:
0	 0	 1	 0 	 0
0	 1	 2	 1	 0
1	 2	-17  2	 1
0	 1	 2	 1 	 0
0	 0 	 1	 0	 0
Table 1 5*5 laplacian filter
   If we use the table 1 filter as the kernel, we will get the edge of the grayscale image of the original image, but here we use a different kernel which is shown bellow:

0	   0	-1	 0	 0
0	  -1	-2	-1	 0
-1	-2	17	-2	-1
0	  -1	-2	-1   0
0	   0	-1	 0	 0
Table 2modified laplacian filter
   We will get a grayscale oil painting image instead of the edge image of the original picture.

3. Summary
   My project is a grayscale oil painting filter which is realized by modified Laplacian filter. Instead of using laplacian filter as edge detector, here we use it as a different filter which transform the picture into a different style by converting the value of the kernel matri.

4. Future work  
   In this project, we can only get a grayscale oil painting picture, the function doesn¡¯t work well in producing an oil painting picture with RGB color space. Next, I will try find a corresponding filter which works as well with RGB pictures.

Reference
1.	Laplacian filter: http://www.uoguelph.ca/~hydrogeo/Whitebox/Help/FilterLaplacian.html
2.	Spatial Filters: http://homepages.inf.ed.ac.uk/rbf/HIPR2/log.htm

