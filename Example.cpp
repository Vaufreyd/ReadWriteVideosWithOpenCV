/**
 * @file Example.cpp
 * @ingroup ReadWriteOpenCVMovies
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */
#include "DataManagement/VideoIO.h"

/** @brief Example program for the VideoIO class. You need under all operating systems (Windows, Linux, Mac OSX) to install
 *         ffmpeg and ffprobe. They must be callable from the standard shell. In this example we
 *         use the big-buck-bunny_trailer.webm video file (see https://peach.blender.org/) as
 *         input. We produce an mp4 video reading and then writing OpenCV cv::Mat and rescaling it.
 *		   This program let you read almost every type of video, i.e. all video supported by ffmpeg.
 *		   The same for video writing. Anyway, this program is not design for performance and will not
 *		   support writing audio stream.
 *
 */
int main( int argc, char *argv[] )
{
	// Create an input and an output VideoIO object
	VideoIO VideoIn, VideoOut;

	// Set the VideoIn *only* in debug mode (trace will be show);
	VideoIn.DebugMode = true;

	// Open the video file
	if ( VideoIn.Open( "big-buck-bunny_trailer.webm" ) == false )
	{
		fprintf( stderr, "Could not open video file for reading\n" );
		return -1;
	}
	
	// We will create a mp4 video when we get the first frame
	bool FirstFrame = true;

	// A cv::Mat to fill with VideoFrame
	cv::Mat VideoImg;
	while( VideoIn.ReadFrame( VideoImg ) )
	{
		if ( FirstFrame == true )
		{
			// First frame, ok create the video Output
			FirstFrame = false;

			// Change size (width sets artificially to 1.5*original) of the output to test if auto rescaling is working
			// "-y" => force overwrite of output file
			// "-codec:v libx264 -profile:v high -preset slow -b:v 500k -maxrate 500k -bufsize 1000k -threads 0 -pix_fmt yuv420p" => mp4 codec parameters
			VideoOut.Create( "Result.mp4", (int)(VideoIn.Width*1.5), (int)(VideoIn.Height*1.5), VideoIn.Fps,
				"-y -codec:v libx264 -profile:v high -preset slow -b:v 500k -maxrate 500k -bufsize 1000k -threads 0 -pix_fmt yuv420p" );
		}

		// Write the current frame to the mp4 file
		if ( VideoOut.WriteFrame( VideoImg ) == false )
		{
			fprintf( stderr, "Could not write frame\n" );
			return -2;
		}

		// Show it, as fast as processing is done (not a fps rate)
		cv::imshow("check", VideoImg);
		cv::waitKey(1);
	}

	// VideoIO objects will be close automatically

	return 0;
}
