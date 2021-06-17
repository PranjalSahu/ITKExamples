/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

//  Software Guide : BeginCommandLineArgs
//    INPUTS:  {BrainProtonDensitySliceBorder20.png}
//    INPUTS:  {BrainProtonDensitySliceShifted13x17y.png}
//    OUTPUTS: {ImageRegistration1Output.png}
//    OUTPUTS: {ImageRegistration1DifferenceAfter.png}
//    OUTPUTS: {ImageRegistration1DifferenceBefore.png}
//  Software Guide : EndCommandLineArgs



#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCastImageFilter.h"
#include <itkAdditiveGaussianNoiseImageFilter.h>


int
main(int argc, char * argv[])
{
  if (argc < 3)
  {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " fixedImageFile  movingImageFile ";
    return EXIT_FAILURE;
  }
  
  // Read the Input Image from the given file path
  constexpr unsigned int Dimension = 2;
  using PixelType = float;
  using FixedImageType = itk::Image<PixelType, Dimension>;
  
  using FixedImageReaderType = itk::ImageFileReader<FixedImageType>;
  FixedImageReaderType::Pointer fixedImageReader =
    FixedImageReaderType::New();

  fixedImageReader->SetFileName(argv[1]);
  fixedImageReader->Update();
  
  FixedImageType::Pointer image = fixedImageReader->GetOutput();
  
  // Define the Additive Noise Image filter and set the parameters
  using OutputPixelType = unsigned char;
  using OutputImageType = itk::Image<OutputPixelType, Dimension>;

  using GaussianFilterType = itk::AdditiveGaussianNoiseImageFilter<FixedImageType, FixedImageType>;
  GaussianFilterType::Pointer GaussianFilter = GaussianFilterType::New();
  
  GaussianFilter->SetInput(image);
  GaussianFilter->SetMean(0);
  GaussianFilter->SetStandardDeviation(15);
  GaussianFilter->Update();
  
  FixedImageType::Pointer filtered_image = GaussianFilter->GetOutput();
  
  // Cast the filtered image to right output type for saving
  using CastFilterType =
     itk::CastImageFilter<FixedImageType, OutputImageType>;

  using WriterType = itk::ImageFileWriter<OutputImageType>;
  
  
  WriterType::Pointer     writer = WriterType::New();
  CastFilterType::Pointer caster = CastFilterType::New();
  
  caster->SetInput(filtered_image);
  
  // Write the image to output path
  writer->SetFileName(argv[2]);
  writer->SetInput(caster->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}
