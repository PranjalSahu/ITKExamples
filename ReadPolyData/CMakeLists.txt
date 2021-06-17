
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(ReadPolyData)

find_package(VTK COMPONENTS 
  vtkCommonColor
  vtkCommonCore
  vtkIOXML
  vtkInteractionStyle
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkRenderingOpenGL2
  QUIET
)

if (NOT VTK_FOUND)
  message("Skipping ReadPolyData: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(ReadPolyData MACOSX_BUNDLE ReadPolyData.cxx )
  target_link_libraries(ReadPolyData PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(ReadPolyData MACOSX_BUNDLE ReadPolyData.cxx )
  target_link_libraries(ReadPolyData PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS ReadPolyData
    MODULES ${VTK_LIBRARIES}
    )
endif ()
