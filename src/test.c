#include <OpenCL/opencl.h>
#include <stdio.h>
int main()
{
   // 1. Get a platform.
   cl_platform_id platform;
   clGetPlatformIDs( 1, &platform, NULL );
   // 2. Find a gpu device.
   cl_device_id device;
   clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

   // 3. Create a context and command queue on that device.
   cl_context context = clCreateContext( NULL, 1, &device, NULL, NULL, NULL);
   cl_command_queue queue = clCreateCommandQueue( context, device, 0, NULL );


   // 4. Perform runtime source compilation, and obtain kernel entry point.
     std::ifstream file("kernel.txt");
     std::string source;
     while(!file.eof()){
       char line[256];
       file.getline(line,255);
       source += line;
     }
     const char* str = source.c_str();
     cl_program program = clCreateProgramWithSource( context, 1, &str, NULL, NULL );
     cl_int result = clBuildProgram( program, 1, &device, NULL, NULL, NULL );
     if ( result ){
       std::cout << "Error during compilation! (" << result << ")" << std::endl;
     }

cl_kernel kernel = clCreateKernel( program, "main", NULL );

   printf("%d", (int)platform);

   return 0;
}
