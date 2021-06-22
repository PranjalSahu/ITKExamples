#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkMassProperties.h>
#include <vtkSmoothPolyDataFilter.h>


int main(int argc, char* argv[])
{
  // Parse command line arguments
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " Filename(.vtp) e.g. Torso.vtp"
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];

  vtkNew<vtkMassProperties> mass_properties;
  
  // Read all the data from the vtp file
  vtkNew<vtkXMLPolyDataReader> reader;
  reader->SetFileName(filename.c_str());
  reader->Update();
  
  // Smooth the volume with the vtkSmoothPolyDataFilter
  vtkNew<vtkSmoothPolyDataFilter> smooth_filter;
  smooth_filter->SetNumberOfIterations(5);
  smooth_filter->SetInputDataObject (0, reader->GetOutput());
  smooth_filter->Update();

  //mass_properties->SetInputData(reader->GetOutput());
  mass_properties->SetInputData(smooth_filter->GetOutputDataObject(0));
  std::cout << "Volume of the given vtp file is " << ": ";
  std::cout << mass_properties->GetVolume() << std::endl;
  

  return EXIT_SUCCESS;
}
