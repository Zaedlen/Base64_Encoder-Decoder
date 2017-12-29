# Base64_Encoder-Decoder

WIP of an linux-based encoder and decoder for Base64.

At this moment, there is only an alfa version of the decoder part's code

TO DO:
----------------------------------------------------------------------------------------------------------------------
  1. Clean up the code and organize it on a library
  
    1b. If the output file already exists, truncate it (reset)
    1c. If the Base64 code provided to the decoder its not correct, detect it and generate an exception
    
  2. Create the encoder part, based on the decoder one <b>Done</b>
  
  3. Add it to the library
  
  4. Add also some functions to clean the file management part
  
  5. Create the main file
  
  6. Create the makefile
  

Some ideas:
----------------------------------------------------------------------------------------------------------------------
  1. Make it easy to give an input file and chose to encode or decode it
  2. Make it easy to give an output file or create a default one if it is not given
  
  3. Try to achieve a terminal version, where you can chat with the program, encoding or decoding any lines you want
     until you chose to finish
