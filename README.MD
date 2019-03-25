About
This repository contains a simple method to convert your video files to the 1-bit Bitmap format needed by arduino. You will find an example code to create your own video player.
This tutorial assumes you have previous experience with Arduino and command line and have everything already setup.

 
Main library
This entire project would not have been possible without the amazing U8G2 library from Oli Kraus. https://github.com/olikraus/u8g2/
You will also need the Esp8266 or Esp32 hardware setup 

Required Hardware:

• A Wemos d1-Mini was used for this tutorial but any controller based on the Esp8266 chip will work, the example will also run on an Esp32..

• An Oled display (Model: SSD1306 i2C)

• A Pushbutton 

• A few jumper male/female cables


Required Softwares:
	•	Arduino

	•	Terminal or editor of your choice

	•	Atom (please download and install the sequential Number package: https://atom.io/packages/sequential-number)

	•	imagemagick (https://www.imagemagick.org/ 

	•	Ffmpeg

	•	XNconvert if you want to preview your XBM files (https://www.xnview.com/en/xnconvert/)

	•	Image editor of your choice (Adobe Photoshop, Gimp)

	•	Video editor of your choice (After effects, iMovie)


Please install ImageMagick and FFMPEG.

https://www.imagemagick.org/ 
- easy install if you have Brew (https://brew.sh/) installed - -$ brew install imagemagick

https://ffmpeg.org/
- easy install if you have Brew (https://brew.sh/) installed - -$ brew install ffmpeg

Once you have both platforms installed and running, you can now proceed with this tutorial.

Open the Folder “video_animator” inside of “HAVAS_ANIMATOR”. Inside of it, you will find 3 empty folders and 2 video files.
Open your Terminal of choice and navigate to the “video_animator” folder

Rename your video to “myMovie.mp4”,
(I recommend a video no longer than 20 sec for better results, but this is up to you and your hardware)


Single Step Export: 
Quicker process, but less control on the final output
$ ffmpeg -i myMovie.mp4 -r 15 -vf scale=128:64 ffmpeg_xbm/myMovie$filename%01d.xbm



3 steps Export: 
This give you a more control on your final output for true two color threshold bitmap

Step one: Convert to Jpeg with a frame rate of 15fps
:
$ ffmpeg -i myMovie.mp4 -r 15 -vf scale=128:64 jpg_output/myMovie_$filename%01d.jpg

Step two: Convert to 1-bit array Bitmap:

$ convert jpg_output/myMovie*.jpg -depth 1 -threshold 50% BMP3:bmp_output/myMovie_.bmp

Step Three: Convert to XBM:

$ convert bmp_output/myMovie_-*.bmp -depth 1 -threshold 50% BMP3: xbm_output/myMovie_.xbm

Take note of the number of files contained in the folder.

Run the final command to append all the .xbm files into one single .h file, do not forget to add the number you wrote down in the [#here]

If you followed the 1 step process use the method below:

$ cat ffmpeg_xbm/myMovie{1..[#here]}.xbm > myMovie.h
- Reverse frame order
$ cat ffmpeg_xbm/myMovie{[#here]..1}.xbm > myMovie.h


$ cat ffmpeg_xbm/myMovie{1..98}.xbm > myMovie.h

For the 3 steps process:
 
$ cat xbm_output/myMovie{1..[#here]}.xbm > myMovie.h
- Reverse frame order
$ cat xbm_output/myMovie{[#here]..1}.xbm > myMovie.h


$ cat xbm_output/myMovie{1..96}.xbm > myMovie.h


You should now see a movie.h file in your main directory.

 
Open it with Atom (don’t forget to install the sequential Number package: https://atom.io/packages/sequential-number)


Step 1: clear all the #define parameters.

Copy the top two #define
#define image_width 128
#define image_height 64

Press cmd + F

paste it into the find area, select “Find All”
Make sure the “replace in current buffer” is empty

Press “Replace All”

This will delete all these parameters


Step 2: Rename image_bits to myMoviebits

Press cmd + F 
Search for “image_bits” follow the previous process to find all copies of it, 
And replace all by “myMoviebits_-“ 
[name_rename.gif]
Once all have been changed, 

Repeat the first step and search for “-”, find,
[sequential_number_a.gif]
Once you have them all selected, open the Packages Tab and scroll down to “Sequential Number”, press it.
Write “0” in the input field, this will replace all “-” with numbers starting from 0.

Paste this code snippet at the bottom of your page:

 const uint8_t * myMovie[] = {


 };


Step 3: prepare XBM array
Create a new document and paste “myMoviebits_-, “  in it.
Repeat this process until you have the number of files needed in the myMovie.h file.

By pressing “cmd + F” you will be able to see how many duplicates you have,
Once you have the correct number,
search for “-”, find, press “Select All”
 

Once you have them all selected, 
open the Packages Tab and scroll down to “Sequential Number”, press it.
Write “0” in the input field, this will replace all “-” with numbers starting from 0.


You are almost done, 

copy every values from your current document and paste them into the “const uint8_t …{here}; block”.
Your final code will look like this 
 

 const uint8_t * myMovie[] = {

   myMoviebits_0,myMoviebits_1,myMoviebits_2,myMoviebits_3,myMoviebits_4,myMoviebits_5,myMoviebits_6,myMoviebits_7,myMoviebits_8,myMoviebits_9,
   myMoviebits_10,myMoviebits_11,myMoviebits_12,myMoviebits_13,myMoviebits_14,myMoviebits_15,myMoviebits_16,myMoviebits_17,myMoviebits_18,myMoviebits_19,
   myMoviebits_20,………………. 

 };

Step 3: Replace Static unsigned char

Repeat the previous step but instead search for “static unsigned char ”, find all and replace all with “static const unsigned char PROGMEM ”

Step 4: Define the movie parameters


You can now paste this to the top of the page, don’t forget to add the number of frames you have
#define myMoviebits_frames [your frame number]
#define myMoviebits_begin 0
#define myMoviebits_end  [your frame number]

Make sure to have the right number or your ESP8266 will reboot itself


You are now done. 

Copy the file myMovie.h file and paste it into the havas_animator folder.

And open the file havas_animator.ino.
The tab myMovie.h should be now located in the upper side of your Arduino sketch window,

Compile your code.

 if it doesn’t compile, check if you have the correct number of XBM at the bottom of the “myMovie.h” file,
Also if you do not have enough space, you may run into some issues.

If it compiles, you are done, 

You can now enjoy your first animations, 
It is now your turn to make things, just do not forget to tag your project “#havasgermany, @havasgermany” if you post it on Instagram or any other social.
