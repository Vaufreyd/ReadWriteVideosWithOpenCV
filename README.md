# Read Write Videos With OpenCV

This aim of this project is to provide a convenient way to read and write almost any kind of video
with [OpenCV](http://opencv.org/). The idea is to use [ffmpeg](https://www.ffmpeg.org/) as a pipe tool to read and write videos (sound is not supported)
to/from [OpenCV](http://opencv.org/) cv::Mat objects under Windows/Linux/Mac OSX. Efficiency is not the goal here, we want to share
our Swiss knife to facilitate video manipulation as you may have encounter problems to do so.

### Benefits

Using this code you will be able, even under Windows (the poor sibling of [OpenCV](http://opencv.org/) on this task),
to read and to generate various types of videos :
+ We encoutered problems when reading some videos with OpenCV alone, this code solve them. For instance, you may have troubles to create videos from small images (like 100x100).
+ While OpenCV let you define size and frame rate of the video, here, you can precisely define all kind of parameters for reading or writing videos: codecs, quality, bandwith, size, pixel format, etc.
+ You can do the same with your webcam as input (see Webcam.md)

## RGBD Sync SDK

This project and the DataManagement repository are subparts of the [RGBD Sync SDK](https://github.com/Vaufreyd/RGBDSyncSDK). 
This SDK is design for file access to data (robot information, depth, infrared, video, bodies and faces from a Kinect2, ...) and easy way to read them synchronously
from separate sources almost like in ROS bag. 

The [RGBD Sync SDK](https://github.com/Vaufreyd/RGBDSyncSDK) has been use to record the [MobileRGBD corpus](http://MobileRGBD.inrialpes.fr/). It is available for people who want
to work on this corpus, and anyone who need to use it within the term of the LICENSE.

## Building the example

### Requirements

First, as we used submodules in our project, in order to clone this repo, you must ask git to work recursively:

    $> git clone --recursive https://github.com/Vaufreyd/ReadWriteMoviesWithOpenCV.git
    
Using file reading and synchronization does not involve using specific things except a C++ compiler (g++, Visual Studio, etc.).
Some steps are mandatory to use the VideoIO class:
* First, you **DO NOT** need to recompile OpenCV to support specific codecs. You just need to install it. This source code
was tested with OpenCV 2.4.10 (Linux/Windows/Mac OSX) and 3.0.0 (on Windows only for this last version.)
* You must install [ffmpeg](https://www.ffmpeg.org/) version 2.4.7 (or later) to your computer in a way you can call `ffprobe` and `ffmpeg`.
For older version, please read KnownIssues.md.
In a command shell (even in the standard cmd.exe shell on Windows), you can test `ffprobe` and `ffmpeg` to see if it is working.

    $> ffprobe --version  
    $> ffmpeg --version

On Linux and Mac OSX, if this test is working, you can go ahead. On Windows, you must install Visual Studio 2013 (Express, for the free
version) or later.

### Example.cpp
    
The example file Example.cpp contains a code using VideoIO objects to read from a webm file and to produce a mp4 file
with specific option for the codecs.

#### Linux/Mac OSX compilation

On these environments, you need to call `make` to compile the Test program:

    $> make

In order to build the documentation, you can invoke:

    $> make doc

#### Windows compilation

On Windows, you just have to lunch the ReadWriteMoviesWithOpenCV.sln solution with Visual Studio (Express). You must ensure
that OpenCV 3.0.0 is installed in an "opencv" folder at the same level as the ReadWriteMoviesWithOpenCV folder. **If you use
another version or another folder location/name**, you will need to change:
+ the include folder to add the header folder from your OpenCV version.
+ the extra library folder in the linker general option. We used the static library in x64 mode.
+ the name of the libraries to link with. These names are specific to each OpenCV version (3.0.0 in our case).

You just have to use Visual Studio as usual. For the documentation, you need Doxygen 1.8.10 at least. Then, just run `doxygen Doxyfile`
in the ReadWriteMoviesWithOpenCV.

#### Test

The test program processes the "big-buck-bunny_trailer.webm" video file (see [Big Buck Bunny licensing below](#BigBunnyLicensing)) from
the ReadWriteMoviesWithOpenCV folder. On Windows, you can use the Visual Studio environment or launch the Test program in the cmd.exe shell.
In other environments, you can test the program in a graphical environment:

    $> ./Test

The program opens the "big-buck-bunny_trailer.webm" video, write a new mp4 video changing size to a larger version (1.5 times the original size). The video is
shown at processing frame rate (**not video frame rate**) in an OpenCV window. Enjoy it!

## Get involved!

You can help us finding bugs, proposing new functionalities and more directly on this website! Click on the "New issue" button in the menu to do that.
You can browse the git repository here on GitHub, submit patches and push requests!

## Licensing

### <a name="BigBunnyLicensing"></a>Big Buck Bunny video

The movie Big Buck Bunny has been licensed under [Creative Commons Attribution 3.0 License](http://creativecommons.org/licenses/by/3.0/) (see [https://peach.blender.org/](https://peach.blender.org/)).
(c) copyright Blender Foundation | www.bigbuckbunny.org.
The file "big-buck-bunny_trailer.webm" was taken from [Wikimedia](https://commons.wikimedia.org/wiki/File:Big_Buck_Bunny_Trailer_1080p.ogg), in the transcoded section and then
was renamed accordingly.

### RGBD Sync SDK and submodules

RGBD Sync SDK and submodules are free software; you can redistribute and/or modify them under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.
[Consult the license on the FSF website](http://www.gnu.org/licenses/lgpl-3.0.txt).

If you are a researcher and this software helps you, please cite our publication on MobileRGBD:  
+ *MobileRGBD, An Open Benchmark Corpus for mobile RGB-D Related Algorithms*, Dominique Vaufreydaz, Amaury N&egrave;gre,
13th International Conference on Control, Automation, Robotics and Vision, Dec 2014, Singapore, 2014. [(go to author version)](https://hal.inria.fr/hal-01095667)

Copyright (c) 2015, University of Grenoble Alpes and Inria, All rights reserved.
Dominique Vaufreydaz <Dominique.Vaufreydaz@inria.fr> 
