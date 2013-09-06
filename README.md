CG-2DPaint
==========

<div>
<p align="CENTER"><strong>2D Paint Program</strong></p>
</div>

<p>

</p><h2><a name="SECTION00001000000000000000">
Assignment Specifications</a>
</h2>

<p>
In this assignment you have to write a 2D Paint program. The program
reads an input file in which geometric objects and associated attributes
are described, and draws it on the screen.  The objects are layered
based on the order of their specification (the latest being drawn on
top). Modified attributes affect only objects which are specified after
their modification. The program should satisfy the following:

</p><p>

</p><ol>
<li><em>Supported objects:</em> Objects that may be drawn by the program include:
  
<ul>
<li>Rectangle - specified by two 2D points describing its lower
    left and upper right corners.
</li>
<li>Circle - specified by a 2D point describing its center and a radius.
</li>
<li>Polyline - specified by a list of up to ten 2D points
</li>
<li>Polygon - specified by a list of up to ten 2D points. The
    last point is assumed to be connected to the first one.
  
</li>
</ul>

<p>
</p></li>
<li><em>Supported attributes:</em> Attributes of objects include the following:
  
<ul>
<li>Color - the color of the object to be drawn specified as three RGB
          components (each in the range [0..1]).
</li>
<li>Fill mode - a flag indicating whether the object should be
    drawn filled or not (1 indicates that the object should be filled).
</li>
<li>Translation - specified by a 2D vector with respect to the origin.
</li>
<li>Rotation - specified by an angle in degrees. Rotation is
    assumed to be about the origin.
</li>
<li>Scale - specified by two scale factors in the X and Y
    directions. Scaling is assumed to be about the origin.
  
</li>
</ul>

<p>
</p></li>
<li><em>Input file format:</em> The input file describing the objects
is a text file in which each line describes the addition of an object or
the modification of the current attributes. Empty lines, and lines
beginning with a # should be ignored. All the numbers in the file are
considered to be real numbers.  The following are possible lines in the
input file:

<p>
</p><pre>  # Add a rectangle:
  ar &lt;ll-corner-x&gt; &lt;ll-corner-y&gt; &lt;ur-corner-x&gt; &lt;ur-corner-y&gt;

  # Add a circle:
  ac &lt;center-x&gt; &lt;center-y&gt; &lt;radius&gt;

  # Add a polyline:
  al &lt;num-vertices&gt; &lt;v1-x&gt; &lt;v1-y&gt; &lt;v2-x&gt; &lt;v2-y&gt; ...

  # Add a polygon:
  ap &lt;num-vertices&gt; &lt;v1-x&gt; &lt;v1-y&gt; &lt;v2-x&gt; &lt;v2-y&gt; ...

  # Set color:
  sc &lt;R&gt; &lt;G&gt; &lt;B&gt;

  # Set fill mode:
  sf &lt;0.0|1.0&gt;

  # Set translation:
  st &lt;trans-x&gt; &lt;trans-y&gt;

  # Set rotation:
  sr &lt;deg-angle&gt;

  # Set scale:
  ss &lt;scale-x&gt; &lt;scale-y&gt;
</pre>

<p>
</p></li>
<li><em>Applying the attributes:</em>
Whenever an object is drawn it should be drawn with the currently set
attributes.  Changed attributes remain in effect until modified
again. Transformations are considered in this program as attributes and
should always be applied in a fixed order regardless of the order of
their specification. Transformations should be applied in the following
order: first the object should be scaled, then rotated, and finally
translated. The initial attributes are:

<ul>
<li>Color: 1.0 1.0 1.0 (white)
</li>
<li>Fill mode: 1.0 (filled)
</li>
<li>Translation: 0.0 0.0 (none)
</li>
<li>Rotation: 0.0 (none)
</li>
<li>Scale: 1.0 1.0 (none)
</li>
</ul>

<p>
</p></li>
<li><em>Modifying the coordinate system:</em> By default the displayed
part of the coordinate system is a range of <img width="97" height="36" align="MIDDLE" border="0" src="./CS-411 - Assignment 1 (5%)_files/img1.png" alt="$[-10.0, 10.0]$"> in both the
<img width="14" height="18" align="BOTTOM" border="0" src="./CS-411 - Assignment 1 (5%)_files/img2.png" alt="$x$"> and <img width="14" height="31" align="MIDDLE" border="0" src="./CS-411 - Assignment 1 (5%)_files/img3.png" alt="$y$"> directions. By pressing 'i' on the keyboard a ``zoom-in''
effect should be obtained by modifying the displayed range of the
coordinate system to be half of its previous value in both the <img width="14" height="18" align="BOTTOM" border="0" src="./CS-411 - Assignment 1 (5%)_files/img2.png" alt="$x$"> and
<img width="14" height="31" align="MIDDLE" border="0" src="./CS-411 - Assignment 1 (5%)_files/img3.png" alt="$y$"> directions. By pressing 'o' on the keyboard a ``zoom-out'' effect
should be obtained by modifying the displayed range of the coordinate
system to be double of its previous value in both the <img width="14" height="18" align="BOTTOM" border="0" src="./CS-411 - Assignment 1 (5%)_files/img2.png" alt="$x$"> and <img width="14" height="31" align="MIDDLE" border="0" src="./CS-411 - Assignment 1 (5%)_files/img3.png" alt="$y$">
directions.

<p>
</p></li>
<li><em>Automatic generation of files (extra credit):</em> Write a separate 
program that automatically generates an input file based on one or more parameters.

<p>
</p></li>
</ol>

<p>

</p><h2><a name="SECTION00002000000000000000">
Specific implementation notes</a>
</h2>

<p>
The following are required implementation notes:

</p><p>

</p><ul>
<li>All the drawing should occur in the ``display handler''. 

<p>
</p></li>
<li>A circle should be drawn as a GL_POLYGON object. 

<p>
</p></li>
<li>Sample input files are available on the course's website.

<p>
</p></li>
<li>A sample program demonstrating how to read the input file will be
provided.

<p>
</p></li>
<li>Some Windows systems have a bug that causes objects to be garbled
when zooming in too much and then disappear when zooming out.

<p>
</p></li>
</ul>

<p>

</p><h2><a name="SECTION00003000000000000000">
Electronic Submission Instructions</a>
</h2>

<p>
Please follow the following submission procedure:

</p><p>

</p><ol>
<li>Use OpenGL, C/C++, and GLUT. Do not use any Microsoft specific
classes (MFC). 

<p>
</p></li>
<li>Direct all questions/comments regarding the assignment to:
<!-- MATH
 $cs.iit.edu$
 -->
<img width="131" height="15" align="BOTTOM" border="0" src="./CS-411 - Assignment 1 (5%)_files/img4.png" alt="$cs.iit.edu$">

<p>
</p></li>
<li>On or before the due date upload a ZIP file with the necessary 
components into blackboard. Please do not email the assignment. The ZIP file 
should contain the following:

<p>

</p><ul>
<li>Report: prepared as a PDF file. The report should contain a
  summary of program design issues, description of specific problems you
  faced and the way in which you solved them, and sample input/output
  results (text/graphic). The report needs to be sufficiently detailed.
  
</li>
<li>Source code: all the source code files and the project file (or
  a make file) that are necessary in order to compile your program.
</li>
<li>Executable: the executable file of your program. Please do not
  submit intermediate object files and/or workspace files.
</li>
</ul>
<em>Note: we must be able to view your report, compile your code, and
execute your program in order to grade it</em>

<p>
</p></li>
<li>The organization of the submitted material should be as follows:

<ul>
<li>Create a directory called: <code>first_last_ass#</code> where
  ``first''/``last'' is your name and ``#'' is the assignment number.
</li>
<li>Inside this directory create four sub-directories called:
    <code>code</code>, <code>report</code>, <code>exe</code>, <code>data</code>. Place in these
    directories the files you need to submit.
</li>
<li>Please do not use space inside file/directory names.
</li>
</ul>

<p>
</p></li>
<li>Do not submit a paper copy of your report.  You will be contacted
by email if some material is missing or if you will need to meet with
the TA.

<p>
</p></li>
<li>If you are late in the submission upload it as soon as you have it.
``late days'' will be determined by your sybmission date.
</li>
</ol>

<p>
<br></p>
