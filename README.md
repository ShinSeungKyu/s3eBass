s3eBass
=======

Marmalade extension for BASS audio engine.

Tested and worked on OSX, iOS, Android, only tested xm playback.

I've put the download bass files in bass folder, which itself is a marmalade extension, it can be used in Marmalade's X86 simulator under OSX, might be useful for quick test with BASS, or try to use codes depend on BASS.

To use the s3eBass extension, just change all BASS call from BASS_XXX to s3eBASS_XXX.

Warning
-------

I have no idea about BASS usage yet, this is just an early stage of something compiled, also I'm pretty new to Marmalade and even C++ too, so it might have problems in it.

Though I think it's a solid start point, and I plan to use BASS as the audio engine of our games, so it will get improved in the next couple of months, also if you're interested in the similar approach or have codes based on BASS, please help with tests or improvement, thanks.

Links
-----
Information about BASS audio engine: http://www.un4seen.com/bass.html

It's free for un-commercial usage, and the price of the shareware license (cover mobile platform too) is reasonable.

Note
----
The include TestBass project is not working from the repository, since it use other files that not being open-sourced, though the s3eBass related codes are just copied form BASS's sample, you should able to use the same code in your project easily.
