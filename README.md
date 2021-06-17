# ITKExamples
# Command to run the first registration sample

cd InsightToolkit-5.2.0/<br/>
mkdir build<br/>
cd build<br/>
cmake ../<br/>
make ImageRegistration1<br/>


./ImageRegistration1 BrainProtonDensitySliceBorder20.png BrainProtonDensitySliceShifted13x17y.png ImageRegistration1Output.png ImageRegistration1DifferenceAfter.png ImageRegistration1DifferenceBefore.png


# Command to run the First CMake Sample 

./FirstSample /home/pranjal/Downloads/lena512.bmp /home/pranjal/Downloads/lena512_output.png
