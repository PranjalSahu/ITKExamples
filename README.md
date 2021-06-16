# ITKExamples
# Command to run the first registration sample

cd InsightToolkit-5.2.0/
mkdir build
cd build
cmake ../
make ImageRegistration1


./ImageRegistration1 BrainProtonDensitySliceBorder20.png BrainProtonDensitySliceShifted13x17y.png ImageRegistration1Output.png ImageRegistration1DifferenceAfter.png ImageRegistration1DifferenceBefore.png
