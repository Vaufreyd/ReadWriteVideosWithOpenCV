# How to use the code with a webcam?

## On Windows

First of all, you need to list all video devices hiding the ffmpeg banner, using the `dshow` plugin on the `dummy` input:

	C:\Users\vaufreyd\>ffmpeg -hide_banner -f dshow -list_devices true -i dummy
	[dshow @ 029e2ae0] DirectShow video devices
	[dshow @ 029e2ae0]  "HD Webcam [Fixed]"
	[dshow @ 029e2ae0] DirectShow audio devices
	[dshow @ 029e2ae0] Could not enumerate audio devices.       
	dummy: Immediate exit requested
	
In our example, `ffmpeg` found only one camera called "HD Webcam [Fixed]". Now, ask for the device capabilities:

	C:\Users\vaufreyd\>ffmpeg -hide_banner -f dshow -list_options true -i video="HD Webcam [Fixed]"
	[dshow @ 02942b40] DirectShow video device options
	[dshow @ 02942b40]  Pin "Capturer"
	[dshow @ 02942b40]   pixel_format=yuyv422  min s=640x480 fps=5 max s=640x480 fps=30
	[dshow @ 02942b40]   pixel_format=yuyv422  min s=640x400 fps=5 max s=640x400 fps=30
	[dshow @ 02942b40]   pixel_format=yuyv422  min s=352x288 fps=5 max s=352x288 fps=30
	[dshow @ 02942b40]   pixel_format=yuyv422  min s=320x240 fps=5 max s=320x240 fps=30
	[dshow @ 02942b40]   pixel_format=yuyv422  min s=176x144 fps=5 max s=176x144 fps=30
	[dshow @ 02942b40]   pixel_format=yuyv422  min s=1280x720 fps=5 max s=1280x720 fps=10
	[dshow @ 02942b40]   vcodec=mjpeg  min s=640x480 fps=5 max s=640x480 fps=30
	[dshow @ 02942b40]   vcodec=mjpeg  min s=640x400 fps=5 max s=640x400 fps=30
	[dshow @ 02942b40]   vcodec=mjpeg  min s=352x288 fps=5 max s=352x288 fps=30
	[dshow @ 02942b40]   vcodec=mjpeg  min s=320x240 fps=5 max s=320x240 fps=30
	[dshow @ 02942b40]   vcodec=mjpeg  min s=176x144 fps=5 max s=176x144 fps=30
	[dshow @ 02942b40]   vcodec=mjpeg  min s=1280x720 fps=5 max s=1280x720 fps=30
	[dshow @ 02942b40]   pixel_format=bgr24  min s=640x480 fps=5 max s=640x480 fps=30
	[dshow @ 02942b40]   pixel_format=bgr24  min s=640x400 fps=5 max s=640x400 fps=30
	[dshow @ 02942b40]   pixel_format=bgr24  min s=352x288 fps=5 max s=352x288 fps=30
	[dshow @ 02942b40]   pixel_format=bgr24  min s=320x240 fps=5 max s=320x240 fps=30
	[dshow @ 02942b40]   pixel_format=bgr24  min s=176x144 fps=5 max s=176x144 fps=30
	[dshow @ 02942b40]   pixel_format=bgr24  min s=1280x720 fps=5 max s=1280x720 fps=10
	video=HD Webcam [Fixed]: Immediate exit requested
                         
We have now the list of capabilities four our webcam. Let's choose the biggest one at 30 fps in yuyv422 pixel format.
The source code to read from this Webcam is then:

	// Create VideoIn;
	VideoIO VideoIn;
                             
        // Open the webcam, first put the name of the camera with the "video=" prefix, width, height, framerate and them provide a string with camera parameters
	if ( VideoIn.Open( "video=\"HD Webcam [Fixed]\"", 640, 480, 30.0, "-f dshow -pixel_format yuyv422 -video_size 640x480 -framerate 30" )
	{
		fprintf( stderr, "Could not open webcam for reading\n" );
		return -1;
	}
                             
## On Linux

We will use the `video4linux2` as a driver. First, ask for list of devices:
	
	$ v4l2-ctl --list-devices
	USB2.0 PC CAMERA (usb-0000:00:1e.1-2):
        	/dev/video0
        	
In this example, there was 1 camera on device `/dev/video0`. Ask for camera capabilities:

	$ ffmpeg -hide_banner -f v4l2 -list_formats all -i /dev/video0
	[video4linux2,v4l2 @ 02942b40] Raw       :   yuyv422 :     YUV 4:2:2 (YUYV) : 640x480 320x240 640x360
	[video4linux2,v4l2 @ 02942b40] Compressed:     mjpeg :                MJPEG : 640x480 320x240 640x360
	
Ok, let's ask for a 640x480 video in yuyv422 format at 30 fps. In our code, it shows:

	// Create VideoIn;
	VideoIO VideoIn;
        
	// Open /dev/video0 with yuyv422 pixel_format, 640x480 as geometry and 30 fps.
	if ( VideoIn.Open( "/dev/video0", 640, 480, 30.0, "-f v4l2 -pixel_format yuyv422 -video_size 640x480 -framerate 30" )
	{
		fprintf( stderr, "Could not open webcam for reading\n" );
		return -1;
	}
	
## On Mac OSX

**At the writing time, we did not test webcam under Mac OSX**. Looking on the web, it is the same way to go. First ask for devices:

	$ ffmpeg -hide_banner -f avfoundation -list_devices true -i ""
	
It should retrieve the list of devices. Then, you may ask for device information about `DEVICE_NAME` using:

	$ ffmpeg -hide_banner -f avfoundation -list_formats all -i "DEVICE_NAME"
	
Last, you should adapt the opening call with retrieved parameters (let's say 30 fps, 640x380 and mjpeg format):

	// Create VideoIn;
	VideoIO VideoIn;
        
	// Open /dev/video0 with yuyv422 pixel_format, 640x480 as geometry and 30 fps.
	if ( VideoIn.Open( "DEVICE_NAME", 640, 480, 30.0, "-f avfoundation -pixel_format mjpeg -video_size 640x480 -framerate 30" )
	{
		fprintf( stderr, "Could not open webcam for reading\n" );
		return -1;
	}
