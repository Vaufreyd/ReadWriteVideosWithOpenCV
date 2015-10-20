# Known issues

Our code was tested with ffmpeg version 2.4.7. With some older (on fedora 20 for instance), `ffprobe` may complain about unkown or bad parameter for `-hide_banner` option.
You can solve it by:
+ installing a more recent version of [ffmpeg](https://www.ffmpeg.org/)
+ compiling defining the 'USE_OLD_FFMPEG'
+ add this code to your `VideoIO` objects:

	// Create a MyVideoIO instance of VideoIO class  
	VideoIO MyVideoIO;
	
	// Remove call to the -hide_banner option  
	MyVideoIO.ShowInfos |= SHOW_BANNER;

